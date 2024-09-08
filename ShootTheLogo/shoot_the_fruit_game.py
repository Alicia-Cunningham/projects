#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Sep  5 23:42:06 2024

@author: aliciacunningham
"""

# shoot_the_fruit_game.py
import pgzrun #add pgzrun to code
import pygame #add pygame to code
import pgzero #add pgsero to code
from pgzero.builtins import Actor #allow us to make actors
from random import randint #add function randint to code
# Game settings
WIDTH = 800 #set game window width to 800 pixels
HEIGHT = 600#set game window width to 500 pixels
COMPANY_SIZE = 50 #set size of images to 50 pixels
score = 0 #set initial score to zero


apple = Actor("apple") #add apple logo to variable
nokia = Actor("nokia") #add nokia logo to variable
samsung = Actor("samsung") #add samsung logo to variable
google = Actor("google")#add google logo to variable
blackberry = Actor("blackberry")#add blackberry logo to variable



# List to hold  positions


def draw(): #define draw function
    screen.clear() #clear screen
    apple.draw() #draw apple logo
    nokia.draw() #draw nokia logo
    samsung.draw() #draw samsung logo
    google.draw() #draw google logo
    blackberry.draw() #draw blackberry logo
    screen.draw.text(f'Score: {score}', (10, 10), fontsize=30, color='white')# Display the score on the screen
    
    
def place_apple(): #define function to randomly place apple logo
    apple.x = randint(COMPANY_SIZE, WIDTH - COMPANY_SIZE)       #places apple logo at random point on x axis
    apple.y = randint(COMPANY_SIZE, HEIGHT - COMPANY_SIZE)     #places apple logo at random point on y axis

def place_nokia(): #define function to randomly place nokia logo
    nokia.x = randint(COMPANY_SIZE, WIDTH - COMPANY_SIZE)      #places nokia logo at random point on x axis
    nokia.y = randint(COMPANY_SIZE, HEIGHT - COMPANY_SIZE)      #places nokia logo at random point on y axis

def place_samsung(): #define function to randomly place samsung logo
    samsung.x = randint(COMPANY_SIZE, WIDTH - COMPANY_SIZE)        #places samsung logo at random point on x axis
    samsung.y = randint(COMPANY_SIZE, HEIGHT - COMPANY_SIZE)      #places samsung logo at random point on y axis
    
def place_google(): #define function to randomly place google logo
    google.x = randint(COMPANY_SIZE, WIDTH - COMPANY_SIZE)       #places google logo at random point on x axis
    google.y = randint(COMPANY_SIZE, HEIGHT - COMPANY_SIZE)      #places google logo at random point on y axis

def place_blackberry(): #define function to randomly place blackberry logo
    blackberry.x = randint(COMPANY_SIZE, WIDTH - COMPANY_SIZE)      #places blackberry logo at random point on x axis
    blackberry.y = randint(COMPANY_SIZE, HEIGHT - COMPANY_SIZE)      #places blackberry logo at random point on y axis


def on_mouse_down(pos): #define function to determine what happens when mouse is clicked
    global score #include global varible score
    if apple.collidepoint(pos): #detect if click collides with apple logo
        score += 1 #add to score
        print(f"Score: {score}") #print new score in terminal
        place_apple() #change apple position
        place_nokia() #change nokia position
        place_samsung() #change samsung position
        place_google() #change google position
        place_blackberry()#change blackberry position
    elif nokia.collidepoint(pos): #detect if click collides with nokia logo
        place_nokia() #change nokia position
        place_samsung() #change samsung position
        place_google() #change google position
        place_blackberry()
        place_apple() #change apple position
    elif samsung.collidepoint(pos): #detect if click collides with samsung logo
        score += 1 #add to score
        print(f"Score: {score}") #print new score in terminal
        place_samsung() #change samsung position
        place_google() #change google position
        place_blackberry() #change blackberry position
        place_apple() #change apple position
        place_nokia() #change nokia position
    elif google.collidepoint(pos): #detect if click collides with google logo
        score += 1 #add to score
        print(f"Score: {score}") #print new score in terminal
        place_google() #change google position
        place_blackberry() #change blackberry position
        place_apple() #change apple position
        place_nokia() #change nokia position
        place_samsung() #change samsung position
    elif blackberry.collidepoint(pos): #detect if click collides with blackberry logo
        place_blackberry() #change blackberry position
        place_apple() #change apple position
        place_nokia() #change nokia position
        place_samsung() #change samsung position
        place_google() #change google position
    else: #if click doesn't collide with anything
        print("Miss!") #tell the user they missed all logos
        

# Initialize the fruit's position
place_apple() #generate apple inital position
place_nokia() #generate nokia inital position
place_samsung() #generate samsung inital position
place_google() #generate google inital position
place_blackberry() #generate blackberry inital position

pgzrun.go() #run game