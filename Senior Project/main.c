//
//  main.c
//  Senior Project Code
//
//  Created by Alicia Cunningham on 9/11/24.
//

/**
 * main.c
 */
#include <iostream>
#include "gsl_fft.h"
#include "gsl_fft_complex.h"
#include <cmath>
#include "gsl_wavelet.h"
#include "gsl_complex.h"
#include "gsl_wavelet2d.h"
#include "gsl_vector.h"
#include "gsl_vector_complex_double.h"
#include "gsl_vector_double.h"
#include "config.h"
#include "gsl_rng.h"
#include "gsl_randist.h"
#include "gsl_math.h"


void addGaussianWhiteNoise(double* data, size_t size, double mean, double stddev) {
    gsl_rng* rng = gsl_rng_alloc(gsl_rng_default);

    for (size_t i = 0; i < size; i++) {
        double noise = gsl_ran_gaussian(rng, stddev) + mean;
        data[i] += noise;
    }

    gsl_rng_free(rng);
}
double getSampleRate(int totalSamples, double signalDuration) {
    return totalSamples / signalDuration;
}
size_t nextpow2(size_t x) {
    size_t result = 1;
    while (result < x) {
        result <<= 1;
    }
    return result;
}

void denoise(const gsl_vector* x) {
    // Set the threshold, thresholding type, and whether to keep approximation coefficients
    double thr, sorh;
    int keepapp;
    gsl_wavelet_workspace* workspace = gsl_wavelet_workspace_alloc(x->size);
    gsl_wavelet* wavelet = gsl_wavelet_alloc(gsl_wavelet_bspline, 3);

    gsl_wavelet_transform_forward(wavelet, x->data, 1, x->size, workspace);
    gsl_wavelet_workspace_free(workspace);

    gsl_wavelet_transform_inverse(wavelet, x->data, 1, x->size, workspace);
    gsl_wavelet_free(wavelet);
}

gsl_vector* freqshape(const gsl_vector* x, double g, const double* transitionV, double fs) {
    gsl_complex_packed_array data[10000];
    // Extract transition points
    double first = transitionV[0];
    double second = transitionV[1];
    double third = transitionV[2];
    double fourth = transitionV[3];

    size_t x_length = x->size;
    size_t n = nextpow2(x_length);
    size_t N = 1 << n; // Equivalent to 2^n
    double T = 1.0 / fs;

    // FFT of input signal
    gsl_fft_complex_wavetable* wave = gsl_fft_complex_wavetable_alloc(N);
    gsl_fft_complex_workspace* workspace = gsl_fft_complex_workspace_alloc(N);
    gsl_vector* X_real = gsl_vector_alloc(N);
    gsl_vector* X_imag = gsl_vector_alloc(N);
    gsl_vector* gain = gsl_vector_alloc(N);

    // Calculate gain for the first stage of frequencies
    double firstC = 0.3 * (g - 1) / first;
    size_t k = 0;
    while (k / N <= first / fs) {
        double val = firstC * k / (N * T) + 1;
        gsl_vector_set(gain, k, val);
        gsl_vector_set(gain, N - k - 1, val);
        k++;
    }

    // Calculate gain for the second stage of frequencies
    double secondC = firstC * first + 1;
    double secondC2 = (second - first) / 5.0;
    while (k / N <= second / fs) {
        double val = 1 + (secondC - 1) * exp(-((k / (N * T)) - first) / secondC2);
        gsl_vector_set(gain, k, val);
        gsl_vector_set(gain, N - k - 1, val);
        k++;
    }

    // Calculate gain for the third stage of frequencies
    double thirdC = 1 + (secondC - 1) * exp(-second / secondC2);
    double thirdC2 = (third - second) / 5.0;
    while (k / N <= third / fs) {
        double val = g + (thirdC - g) * exp(-((k / (N * T) - second)) / thirdC2);
        gsl_vector_set(gain, k, val);
        gsl_vector_set(gain, N - k - 1, val);
        k++;
    }

    // Calculate gain for the fourth stage of frequencies
    while (k / N <= fourth / fs) {
        double val = g;
        gsl_vector_set(gain, k, val);
        gsl_vector_set(gain, N - k - 1, val);
        k++;
    }

    // Calculate gain for the fifth stage of frequencies
    double fifthC = g;
    double fifthC2 = (fs / 2 - fourth) / 5.0;
    while (k / N <= 0.5) {
        double val = 1 + (fifthC - 1) * exp(-((k / (N * T) - fourth) / fifthC2));
        gsl_vector_set(gain, k, val);
        gsl_vector_set(gain, N - k - 1, val);
        k++;
    }

    // FFT of input signal
    gsl_fft_complex_wavetable* wave2 = gsl_fft_complex_wavetable_alloc(N);
    gsl_fft_complex_workspace* workspace2 = gsl_fft_complex_workspace_alloc(N);
    gsl_vector* Y_real = gsl_vector_alloc(N);
    gsl_vector* Y_imag = gsl_vector_alloc(N);

    gsl_fft_complex_forward(X_real->data, 1, N, wave, workspace);
    gsl_fft_complex_forward(X_imag->data, 1, N, wave, workspace);
    // Apply gain filter
    gsl_vector_memcpy(Y_real, X_real);
    gsl_vector_memcpy(Y_imag, X_imag);
    for (size_t i = 0; i < N; ++i) {
        double val = gsl_vector_get(gain, i);
        gsl_vector_set(Y_real, i, gsl_vector_get(Y_real, i) * val);
        gsl_vector_set(Y_imag, i, gsl_vector_get(Y_imag, i) * val);
    }

    // Inverse FFT
    gsl_fft_complex_inverse(Y_real->data, 1, N, wave2, workspace2);
    gsl_fft_complex_inverse(Y_imag->data, 1, N, wave2, workspace2);

    // Cleanup
    gsl_fft_complex_wavetable_free(wave);
    gsl_fft_complex_workspace_free(workspace);
    gsl_fft_complex_wavetable_free(wave2);
    gsl_fft_complex_workspace_free(workspace2);
    gsl_vector_free(X_real);
    gsl_vector_free(X_imag);
    gsl_vector_free(gain);
    gsl_vector_free(Y_imag);

    // Return the real part of the inverse FFT
    return Y_real;
}


void powercompress(gsl_vector* x, double Psat, double Fs) {
    size_t input_size = x->size;
    double sig_out[input_size]; // Output signal

    size_t len = Fs * 0.1; // Window length
    size_t iter = input_size / len;
    double Plow = 0.0001;

    for (size_t rg = 0; rg <= iter; rg++) {
        size_t start = rg * len;
        size_t en = (start + len) < input_size ? (start + len) : input_size;

        // Extract signal segment
        gsl_vector_view subvector = gsl_vector_subvector(x, start, en - start);
        gsl_vector* signal = &subvector.vector;


        // Perform FFT
        size_t n = nextpow2(en - start);
        size_t N = 2 * n;
        double X_real[N];
        double X_imag[N];
        gsl_fft_complex_wavetable* wave = gsl_fft_complex_wavetable_alloc(N);
        gsl_fft_complex_workspace* workspace = gsl_fft_complex_workspace_alloc(N);
        for (size_t i = 0; i < en - start; ++i) {
            X_real[i] = gsl_vector_get(signal, i);
            X_imag[i] = 0.0;
        }
        gsl_fft_complex_forward(X_real, 1, N, wave, workspace);
        gsl_fft_complex_forward(X_imag, 1, N, wave, workspace);
        gsl_fft_complex_wavetable_free(wave);
        gsl_fft_complex_workspace_free(workspace);

        // Calculate power spectrum and apply compression and denoising
        for (size_t k = 0; k <= N / 2; ++k) {
            double X_pow = sqrt(X_real[k] * X_real[k] + X_imag[k] * X_imag[k]) / N;
            if (X_pow < Plow) {
                X_real[k] = 0.0;
                X_imag[k] = 0.0;
                X_real[N - k] = 0.0;
                X_imag[N - k] = 0.0;
            } else if (X_pow > Psat) {
                double ratio = Psat / X_pow;
                X_real[k] *= ratio;
                X_imag[k] *= ratio;
                X_real[N - k] *= ratio;
                X_imag[N - k] *= ratio;
            }
        }

        // Perform inverse FFT
        wave = gsl_fft_complex_wavetable_alloc(N);
        workspace = gsl_fft_complex_workspace_alloc(N);
        gsl_fft_complex_inverse(X_real, 1, N, wave, workspace);
        gsl_fft_complex_inverse(X_imag, 1, N, wave, workspace);
        gsl_fft_complex_wavetable_free(wave);
        gsl_fft_complex_workspace_free(workspace);

        // Copy the denoised segment to the output signal
        for (size_t i = 0; i < en - start; ++i) {
            sig_out[start + i] = X_real[i];
        }

        gsl_vector_free(signal);
    }

    // Multiply the output signal by a constant factor
    for (size_t i = 0; i < input_size; ++i) {
        gsl_vector_set(input, i, sig_out[i] * 5000); // Adjust the constant factor as needed
    }
}
void hearingaid(const gsl_vector* x){
    double fs = getSampleRate(x->size, 1.0);

    double transitionV[4] = {1000.0, 2000.0, 3000.0, 4000.0};



    addGaussianWhiteNoise(x->data, x->size, 1, 0.02);
    denoise(x);

    gsl_vector* y = freqshape(x, 0.5, transitionV, fs);
    powercompress(y, 0.1, fs);

}
gsl_vector* readFromGPIOPin(int pin, size_t vectorSize) {
    // The path to the GPIO directory
    const char* gpioDir = "/sys/class/gpio";

    // Export the GPIO pin
    FILE* exportFile = fopen("/sys/class/gpio/export", "w");
    if (exportFile == NULL) {
        perror("Error exporting GPIO pin");
        return NULL;
    }
    fprintf(exportFile, "%d", pin);
    fclose(exportFile);

    // Set the direction of the GPIO pin to input
    char directionFilePath[256];
    snprintf(directionFilePath, sizeof(directionFilePath), "%s/gpio%d/direction", gpioDir, pin);
    FILE* directionFile = fopen(directionFilePath, "w");
    if (directionFile == NULL) {
        perror("Error setting direction of GPIO pin");
        return NULL;
    }
    fprintf(directionFile, "in");
    fclose(directionFile);

    // Read the value of the GPIO pin bit by bit and store it in a GSL vector
    gsl_vector* valueVector = gsl_vector_alloc(vectorSize);
    for (size_t i = 0; i < vectorSize; ++i) {
        char valueFilePath[256];
        snprintf(valueFilePath, sizeof(valueFilePath), "%s/gpio%d/value", gpioDir, pin);
        FILE* valueFile = fopen(valueFilePath, "r");
        if (valueFile == NULL) {
            perror("Error reading value of GPIO pin");
            gsl_vector_free(valueVector);
            return NULL;
        }
        int bitValue;
        fscanf(valueFile, "%d", &bitValue);
        fclose(valueFile);
        gsl_vector_set(valueVector, i, bitValue);
    }

    // Unexport the GPIO pin
    FILE* unexportFile = fopen("/sys/class/gpio/unexport", "w");
    if (unexportFile == NULL) {
        perror("Error unexporting GPIO pin");
        gsl_vector_free(valueVector);
        return NULL;
    }
    fprintf(unexportFile, "%d", pin);
    fclose(unexportFile);

    return valueVector;
}
int exportDataUsingGPIO(int pin, int data) {
    // The path to the GPIO directory
    const char* gpioDir = "/sys/class/gpio";

    // Export the GPIO pin
    FILE* exportFile = fopen("/sys/class/gpio/export", "w");
    if (exportFile == NULL) {
        perror("Error exporting GPIO pin");
        return -1;
    }
    fprintf(exportFile, "%d", pin);
    fclose(exportFile);

    // Set the direction of the GPIO pin to output
    char directionFilePath[256];
    snprintf(directionFilePath, sizeof(directionFilePath), "%s/gpio%d/direction", gpioDir, pin);
    FILE* directionFile = fopen(directionFilePath, "w");
    if (directionFile == NULL) {
        perror("Error setting direction of GPIO pin");
        return -1;
    }
    fprintf(directionFile, "out");
    fclose(directionFile);

    // Write data to the GPIO pin
    char valueFilePath[256];
    snprintf(valueFilePath, sizeof(valueFilePath), "%s/gpio%d/value", gpioDir, pin);
    FILE* valueFile = fopen(valueFilePath, "w");
    if (valueFile == NULL) {
        perror("Error writing data to GPIO pin");
        return -1;
    }
    fprintf(valueFile, "%d", data);
    fclose(valueFile);

    return 0;
}
int gslVectorToBinary(const gsl_vector* vector) {
    int binaryData = 0;
    size_t vectorSize = vector->size;

    // Convert the vector data to a binary representation
    for (size_t i = 0; i < vectorSize; ++i) {
        double value = gsl_vector_get(vector, i);
        binaryData |= (value > 0.5 ? 1 : 0) << i;
    }

    return binaryData;
}
int main() {
    gsl_vector* x = gsl_vector_alloc(16);
    while (true) {
        gsl_vector* pinValue = readFromGPIOPin(45, 16);
        gsl_vector_set(x, 0, pinValue);
           // Call the hearingaid function to process the input signal
           hearingaid(x);
           int bin = gslVectorToBinary(x);
           exportDataUsingGPIO(59, bin);

           gsl_vector_free(x);
       }


    return 0;
}
