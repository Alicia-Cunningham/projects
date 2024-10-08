//
//  main.c
//  Unbreakable
//
//  Created by Alicia Cunningham on 8/27/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int genrandom(int, int);
int fork1(int);
int fork2(int);
int checkStat(int, int);

struct Stats
{
    char name[20];
    int strength;
    int intelligence;
    int luck;
};

void pressAnyKeyToContinue()
{
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

int main()
{
    struct Stats Player;
    printf(" _    _ _   _ ____  _____  ______          _  __          ____  _      ______ \n");
    printf("| |  | | \\ | |  _ \\|  __ \\|  ____|   /\\   | |/ /    /\\   |  _ \\| |    |  ____|\n");
    printf("| |  | |  \\| | |_) | |__) | |__     /  \\  | ' /    /  \\  | |_) | |    | |__   \n");
    printf("| |  | | . ` |  _ <|  _  /|  __|   / /\\ \\ |  <    / /\\ \\ |  _ <| |    |  __|  \n");
    printf("| |__| | |\\  | |_) | | \\ \\| |____ / ____ \\| . \\  / ____ \\| |_) | |____| |____ \n");
    printf(" \\____/|_| \\_|____/|_|  \\_\\______/_/    \\_\\_|\\_\\/_/    \\_\\____/|______|______|\n");
    printf("-----------------------------------------------------------------------------------------\n");

    printf("Welcome to Unbreakable! A Text-Based Adventure\n\n");
    printf("Please enter in a name for your character: ");
    fgets(Player.name, 20, stdin);
    for (int i = 0; Player.name[i] != '\0'; ++i)
    {
        if (Player.name[i] == '\n')
            Player.name[i] = '\0';  // Replace newline with null terminator
    }
    printf("\nYou have 20 points you may spend on your strength, intelligence, and luck stats. You may allocate them however you like.");
    printf("How many points do you want to allocate to strength?\n");
    scanf("%d", &Player.strength);
    int skill_points = 20;
    while (Player.strength > 20 || Player.strength < 0)
    {
        if (Player.strength > 20)
        {
            printf("Error! You may not allocate more than 20 points into a stat. Please enter a different number: ");
            scanf("%d", &Player.strength);
        }
        else if (Player.strength < 0)
        {
            printf("Error! You may not have a negative stat! Please enter a different number: ");
            scanf("%d", &Player.strength);
        }
    }
    skill_points -= Player.strength;

    printf("\nYou now have %d points left.\n", skill_points);
    printf("Please enter how many points you'd like to spend into intelligence: ");
    scanf("%d", &Player.intelligence);
    while (Player.intelligence > skill_points || Player.intelligence < 0)
    {
        if (Player.intelligence > skill_points)
        {
            printf("Error! You do not have enough points to do that! Please enter a different number: ");
            scanf("%d", &Player.intelligence);
        }
        else if (Player.intelligence < 0)
        {
            printf("Error! You may not have a negative stat! Please enter a different number: ");
            scanf("%d", &Player.intelligence);
        }
    }

    skill_points -= Player.intelligence;

    printf("\nYour remaining %d points have been put into your luck stat.\n", skill_points);

    Player.luck = skill_points;
    printf("-----------------------------------------------------------------------------------------\n");

    printf("Disaster has struck the fair city of Astergarn! The Princess Fairain has been kidnapped by the diabolical demon king.\n\n");

    int dec_fork1;
    printf("You come across a three-way fork in the road. You have the option to:\n");
    printf("1. Circle around the left of the castle.\n");
    printf("2. Go straight across the bridge, directly in the front door.\n");
    printf("3. Circle around the right of the castle.\n");
    printf("\nWhat do you do? (Enter the number of your action)\n");

    scanf("%d", &dec_fork1);
    while (fork1(dec_fork1) == -1)
    {
        printf("Error! Invalid direction entered. Please enter a different direction: ");
        scanf("%d", &dec_fork1);
    }

    switch (fork1(dec_fork1)) {
    case 0:
        printf("You tripped on a branch, fell into the moat and drowned. Tough luck.");
        printf("\nGAME OVER\n");
        pressAnyKeyToContinue();
        return(EXIT_SUCCESS);
    case 1:
        printf("\nYou go straight towards the front door... To your surprise it opens for you.\nYou enter the castle cautiously.\n");
        break;
    case 2:
        printf("You decide to circle around to the right of the castle.\n");
        printf("Suddenly you hear the distinct twang of bows being fired.\n");
        printf("Soon enough, arrows shower down on your position and you are killed.\n");
        printf("GAME OVER\n");
        pressAnyKeyToContinue();
        return(EXIT_SUCCESS);
    }

    printf("\nAfter entering the castle, you find your path blocked by a heavy boulder.\n");
    printf("\"Luckily I am the legendary hero. I should be able to move this easily!\" You think to yourself.\n");
    printf("\nSuddenly you hear a cacophony of footsteps coming from behind you.\n");
    printf("It's a horde of goblins heading your way! There's much too many of them for you to handle on your own!\n");
    pressAnyKeyToContinue();
    printf("-----------------------------------------------------------------------------------------\n");
    if (checkStat(Player.strength, 7) == 1)
    {
        printf("\nYou get to work immediately and push the boulder with all your might.\n");
        printf("Thankfully, with your tremendous strength, you are able to move it out of the way in time and just barely escape the goblins.\n");
    }
    else if (checkStat(Player.strength, 7) == 0)
    {
        printf("\nYou begin to push the boulder with all your might. However, it just won't budge!\n");
        printf("You've severely underestimated the weight of this boulder...\n");
        printf("\nThe goblins are getting ever closer to your position. You've gotta think FAST to get out of this situation!\n");
        pressAnyKeyToContinue();
        if (checkStat(Player.intelligence, 5) == 1)
        {
            printf("\nWith your quick wit, you remember that you brought along a set of noise makers.\n");
            printf("You quickly take them out and throw them off into another hallway, luring the goblin horde towards it.\n");
            printf("\nThis gives you just enough time to escape through a tiny crack to the side of the boulder. That was close!\n");
        }
        else if (checkStat(Player.intelligence, 5) == 0)
        {
            printf("\nYou've run out of options and panic begins to set in.\n");
            printf("The goblin army is now upon you and they make quick work of you through sheer numbers.\n");
            printf("GAME OVER\n");
            return(EXIT_SUCCESS);
        }
    }

    printf("\n\nAfter catching your breath. You steel youself and venture forward, your mind set on saving the princess.\n");
    printf("You find yourself in a large open room, a massive hole spans the length of it.\n");
    printf("\nThere are two bridges that stretch across the hole. One on the left and one on the right.\n");
    printf("1. The left bridge appears to be in disrepair and sways around in a concerning manner.\n");
    printf("2. The right bridge appears to be well-worn, but well-maintained. You'd feel more confident crossing this one.\n");
    printf("\nWhich bridge do you cross?\n");

    int dec_fork2;
    scanf("%d", &dec_fork2);
    while (fork2(dec_fork2) == -1)
    {
        printf("Error! Invalid direction entered. Please enter a different direction: ");
        scanf("%d", &dec_fork2);
    }
    printf("-----------------------------------------------------------------------------------------\n");
    switch (fork2(dec_fork2)) {
    case 0:
        printf("Against your best judgement, you decide to cross the more damaged bridge.\n");
        printf("The bridge makes creaking noises and the railing falls apart when you touch it.\n");
        printf("\nYou think to yourself, \"Why did I decide to go over this bridge!?!\"\n");
        printf("You almost make it across when suddenly the bridge begins to buckle under your weight. It's falling apart!\n");
        printf("You begin to panic as the ropes begin to snap and you begin to plummet down to the depths below.\n");
        printf("\nYou are not sure how you survived the fall, but your journey is over.\n");
        printf("GAME OVER\n");
        pressAnyKeyToContinue();
        return(EXIT_SUCCESS);
    case 1:
        printf("You make your way across the more stable bridge.\n");
        printf("Surprisingly, there are no traps or anything. You make it across safely!\n");
        break;
    }

    printf("\nOnce you cross the bridge, you make your way to the doors of the next room.\n");
    printf("Before you lies a long hallway that ends with a grand double door that almost certainly leads to the demon king's throne room.\n");
    printf("However, you hear voices coming from behind the door. One sounds like a gruff man and the other sounds like a small girl.\n");
    printf("You think to yourself, \"That must be the princess! I need to rescue her right away!\"\n");
    printf("You charge ahead and kick the door open, but... you are not prepared for what happens next.\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\nSuddenly you feel a sharp pain in your abdomen. Looking down you see the tip of a large blade piercing through you.\n");
    printf("You notice your blood begin to drip from your body. A figure then kicks you off the blade onto the ground.\n");
    printf("As your vision fades, the last thing you see is a tall figure approaching you. That must be the demon king!\n");
    printf("GAME OVER\n\n");
    pressAnyKeyToContinue();
    return(EXIT_SUCCESS);
}

int genrandom(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int fork1(int decision)
{
    int lower = 1;
    int upper = 4;
    if (decision > 3 || decision < 1)
    {
        return -1;
    }
    else if (decision == 1)
    {
        int chance = genrandom(lower, upper);
        if (chance <= 2)
        {
            return 0;
        }
        else if (chance > 2)
        {
            return 2;
        }
    }
    else if (decision == 2)
    {
        return 1;
    }
    else if (decision == 3)
    {
        int chance = genrandom(lower, upper);
        if (chance <= 2)
        {
            return 0;
        }
        else if (chance > 2)
        {
            return 2;
        }
    }
    return 1;
}

int fork2(int decision)
{
    int lower = 1;
    int upper = 4;
    if (decision > 2 || decision < 1)
    {
        return -1;
    }
    else if (decision == 1)
    {
        int chance = genrandom(lower, upper);
        if (chance <= 2)
        {
            return 0;
        }
        else if (chance > 2)
        {
            return 1;
        }
    }
    else if (decision == 2)
    {
        return 1;
    }
    return 1;
}

int checkStat(int stat, int level)
{
    if (stat >= level)
    {
        return 1;
    }
    else if (stat < level)
    {
        return 0;
    }
    return 0;
}

