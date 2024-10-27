#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

void getConsoleSize(int *width, int *height);
void printWithAnimation(const char *text); // animation text chatgpt
void setColor(int textColor, int bgColor);
void level_up(int *exp, int *level); // level func
void gotoxy(int x, int y);
void delay(int second); // delay func
void skeletonStatus();
void ratStatus();
void main_game();
void settins();
void credits();

// Define a structure for a class
struct PlayerClass {
    char name[20];   // Class name
    int health;      // Health points
    int attackPower; // Attack power
    int defense;     // Defense power
};

// Function to select a class
struct PlayerClass selectClass() {
    int choice;
    struct PlayerClass pc;

    // Display class options
    printf("\n");
    printf("\t\t\t\t\t\t-=CHOOSE YOUR CLASS =-\n\n");
    printf("\t\t[1] Warrior\t\t\t");
    printf("[2] Mage\t\t\t");
    printf("[3] Archer\n");
    delay(2);
    const char *classSelect = "\t\t  - Attack: 20\t\t\t  - Attack: 25\t\t\t  - Attack: 15\n\t\t  - Health: 150\t\t\t  - Health: 100\t\t\t  - Health: 120\n\t\t  - Defense: 15\t\t\t  - Defense: 5\t\t\t  - Defense: 10\n\n";
    // printWithAnimation(classSelect);
    printf("\t\t\t\t\t\t    [1-3]: ");
    scanf(" %d", &choice);

    // Assign class stats based on choice
    switch (choice) {
        case 1:
            strcpy(pc.name, "Warrior");
            pc.health = 150;
            pc.attackPower = 20;
            pc.defense = 15;
            system("cls");
            break;
        case 2:
            strcpy(pc.name, "Mage");
            pc.health = 100;
            pc.attackPower = 25;
            pc.defense = 5;
            system("cls");
            break;
        case 3:
            strcpy(pc.name, "Archer");
            pc.health = 120;
            pc.attackPower = 15;
            pc.defense = 10;
            system("cls");
            break;
        default:
            strcpy(pc.name, "Warrior");
            pc.health = 150;
            pc.attackPower = 20;
            pc.defense = 15;
            system("cls");
            break;
    }

    return pc;
}

int main() {
    char ch;
    int x, y = 10, consoleWidth, consoleHeight;
    int select = 1;
    int bgcolor = 6; // Green background color

    // Get the console size and calculate the center x coordinate
    getConsoleSize(&consoleWidth, &consoleHeight);
    x = (consoleWidth / 2) - 5;  // Adjust -5 to align the menu text correctly

    do {
        // display the menu
        system("cls");

        // Display menu items with highlighting based on selection
        printf("\n\n\n\n\n\n\t\t\t\t\t\t\t-= Game =-");
        gotoxy(x, y);
        setColor(select == 1 ? 15 : 7, select == 1 ? bgcolor : 0);
        printf("  Start     ");

        gotoxy(x, y + 1);
        setColor(select == 2 ? 15 : 7, select == 2 ? bgcolor : 0);
        printf("  Settings  ");

        gotoxy(x, y + 2);
        setColor(select == 3 ? 15 : 7, select == 3 ? bgcolor : 0);
        printf("  Credits   ");

        gotoxy(x, y + 3);
        setColor(select == 4 ? 15 : 7, select == 4 ? bgcolor : 0);
        printf("  Exit      ");

        // Reset color after menu
        setColor(7, 0);

        // Get user input for navigation
        ch = getch();
        if (ch == -32) {
            ch = getch();
            switch (ch) {
                case 72: // arrow up
                    select--;
                    break;
                case 80: // arrow down
                    select++;
                    break;
            }
        }

        // Wrap around menu selection
        if (select > 4) select = 1;
        if (select < 1) select = 4;
        if (ch == 13) { // if press Enter
            switch (select) {
                case 1:
                    // start game
                    system("cls");
                    main_game();
                    break;
                case 2:
                    // settings
                    system("cls");
                    settins();
                    break;
                case 3:
                    // credits
                    system("cls");
                    credits();
                    break;
                case 4:
                    exit(0);
                    break;
            }
        }
    } while (ch != 27);  // 27 is the ASCII code for the ESC key

    return 0;
}

void main_game() { // menu 1
    // Player selects a class
    struct PlayerClass pc = selectClass();

    // player information
    int health = pc.health;
    int damage = pc.attackPower;
    int defense = pc.defense;
    int money = 0, level = 0, exp = 0;

    // player answer
    char answer = 'd';

    // skeleton information
    int skeleton_level = 1;
    int skeleton_health = 5;
    int skeleton_defense = 2;
    int skeleton_damage = 1;

    // rat information
    int rat_level = 1;
    int rat_health = 3;
    int rat_defense = 1;
    int rat_damage = 1;

    const char *message1 = "Villager: Hello Adventurer I'm a normal villager in here\n";
    const char *message2 = "Villager: So... I need you to help me something, did you see?\n";
    const char *message3 = "Villager: Yeah! Those skeleton it's bother me so much when i'm doing something\n";
    const char *message4 = "Villager: You need to kill those skeleton for me please thank you!\n\n";
    delay(2);

    printWithAnimation(message1);
    delay(1);
    printWithAnimation(message2);
    delay(1);
    printWithAnimation(message3);
    delay(1);
    printWithAnimation(message4);
    delay(1);


    skeletonStatus(); // skeleton pic
    scanf(" %c", &answer);
    printf("\n");

    if (answer == 'f') { // flee option
        answer = 'd';
        const char *answer_flee = "Log: You ran away from Skeleton! And you found a Village And have something moved!\n";
        const char *message1 = "Villager: Hello Adventurer I'm a normal villager in here\n";
        const char *message2 = "Villager: So... I need you to help me something, did you see?\n";
        const char *message3 = "Villager: Yeah! Those skeleton it's bother me so much when i'm doing something\n";
        const char *message4 = "Villager: You need to kill those skeleton for me please thank you!\n\n";
        delay(2);

        printf("=========================================\n");
        printWithAnimation(answer_flee);
        printWithAnimation(message1);
        delay(1);
        printWithAnimation(message2);
        delay(1);
        printWithAnimation(message3);
        delay(1);
        printWithAnimation(message4);
        delay(1);
        printf("=========================================\n");

        ratStatus(); // rat pic
        scanf(" %c", &answer);
        printf("\n");
        system("cls");
        if (answer == 'b') { // rat attack
        answer = 'd';
        while (1) {
            if (health <= 0) {
                printf("=================================\n");
                printf("\tGame over!\n");
                printf("=================================\n");
                break;
            }

            rat_health = (rat_health - (damage - rat_defense));
            health = (health - (rat_damage - defense));

            delay(1);
            printf("====================================\n");
            printf("[Attack](a) | [Inv](i) | [Flee](f): \n");
            scanf(" %c", &answer);
            if (answer == 'a') {
                answer = 'd';
                printf("[%d]Rat, Health: %d, Damage: %d\n", rat_level, rat_health, rat_damage);
                printf("[%d]Player, Health: %d, Damage: %d\n", level, health, damage);
                if (skeleton_health <= 0) {
                    delay(1);
                    exp += 5;
                    printf("=================================\n");
                    printf("Log: Rat dead, Gain %d Exp!\n\n", exp);
                    level_up(&exp, &level);  // Fix: Pass exp and level by reference
                }
            }
            else if (answer == 'i') {
                answer = 'd';

            }
        }
    }
    }

    else if (answer == 'b') { // skeleton attack
        answer = 'd';
        while (1) {
            if (health <= 0) {
                printf("=================================\n");
                printf("\tGame over!\n");
                printf("=================================\n");
                break;
            }

            skeleton_health = (skeleton_health - (damage - skeleton_defense));
            health = (health - (skeleton_damage - defense));

            delay(1);
            printf("====================================\n");
            printf("[Attack](a) | [Inv](i) | [Flee](f): \n");
            scanf(" %c", &answer);
            if (answer == 'a') {
                answer = 'd';
                printf("[%d]Skeleton, Health: %d, Damage: %d\n", skeleton_level, skeleton_health, skeleton_damage);
                printf("[%d]Player, Health: %d, Damage: %d\n", level, health, damage);
                if (skeleton_health <= 0) {
                    delay(1);
                    exp += 5;
                    printf("=================================\n");
                    printf("Log: Skeleton dead, Gain %d Exp!\n\n", exp);
                    level_up(&exp, &level);  // Fix: Pass exp and level by reference
                    break;
                }
            }
            else if (answer == 'i') {
                answer = 'd';
            }
        }
    }
}

void settins() { // menu 2
    printf("Coming soon...");
    getch();
}

void credits() { // menu 3
    printf("Director: zProKZy\n");
    delay(1);
    printf("Written: zProKZy\n");
    delay(1);
    printf("Producer: zProKZy\n");
    delay(1);
    printf("Executive Producer: zProKZy\n\n");
    delay(1);
    printf("Press any key to back");
    getch();
}

void skeletonStatus() {
    int skeleton_level = 1;
    int skeleton_health = 5;
    int skeleton_defense = 1;
    int skeleton_damage = 1;

    printf("    [%d]Skeleton\n", skeleton_level);
    printf("         .-.\n");
    printf("        (o.o)\n");
    printf("         |=|\n");
    printf("        __|__\n");
    printf("      //.=|=.\\\\\n");
    printf("     // .=|=. \\\\\n");
    printf("     \\\\ .=|=. //\n");
    printf("Health: %d   Damage: %d\n", skeleton_health, skeleton_damage);
    printf("-------------------------------------\n");
    printf("[Battle](b) | [Flee](f): ");
}

void ratStatus() {
    int rat_level = 1;
    int rat_health = 3;
    int rat_defense = 1;
    int rat_damage = 1;

    printf("    [%d]Rat\n", rat_level);
    printf("      ()_()\n");
    printf("     ( o.o )\n");
    printf("      > ^ <\n");
    printf("     /     \\\n");
    printf("    /| | | |\\\n");
    printf("   (_|_|_|_|_)\n");
    printf("Health: %d   Damage: %d\n", rat_health, rat_damage);
    printf("-------------------------------------\n");
    printf("[Battle](b): | [Flee](f): ");
}

void level_up(int *exp, int *level) {
    int exp_needed[] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400};

    for (int i = *level; i < 20; i++) {
        if (*exp >= exp_needed[i]) {
            *exp -= exp_needed[i];
            *level += 1;
            printf("Log: Congratulations, now you are Level %d! Need %d exp to next level\n", *level, exp_needed[i + 1]);
        } else {
            break;
        }
    }
}

// delay
void delay(int second) {
    int milli_seconds = 1000 * second;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

// Text animation
void printWithAnimation(const char *text) {
    while (*text) {
        printf("%c", *text++);
        fflush(stdout); // force flush to display each character immediately
        usleep(50000);  // delay of 50 milliseconds between each character
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to set text color and background color
void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Function to get the console width and height
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
