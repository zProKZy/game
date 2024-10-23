#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void delay(int second);
void printWithAnimation(const char *text);
void skeletonStatus();
void ratStatus();
void level_up(int *exp, int *level);
#define MAX_ITEMS 10 // Maximum items in inventory

// Define an Item structure
struct Item {
    char nameItem[30];  // Name of the item
    int quantity;   // Quantity of the item
};

// Define the Inventory structure
struct Inventory {
    struct Item items[MAX_ITEMS]; // Array to store items
    int itemCount;                // Total number of different items
};

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
    const char *classSelect = "\t\t  - Attack: 20\t\t\t  - Attack: 25\t\t\t  - Attack: 15\n\t\t  - Health: 150\t\t\t  - Health: 100\t\t\t  - Health: 120\n\t\t  - Defense: 15\t\t\t  - Defense: 5\t\t\t  - Defense: 10\n\n";
    delay(1);
    printf("\t\t\t\tEnter your choice (1-3): ");
    scanf("%d", &choice);

    // Assign class stats based on choice
    switch (choice) {
        case 1:
            strcpy(pc.name, "Warrior");
            pc.health = 150;
            pc.attackPower = 20;
            pc.defense = 15;
            break;
        case 2:
            strcpy(pc.name, "Mage");
            pc.health = 100;
            pc.attackPower = 25;
            pc.defense = 5;
            break;
        case 3:
            strcpy(pc.name, "Archer");
            pc.health = 120;
            pc.attackPower = 15;
            pc.defense = 10;
            break;
        default:
            printf("Invalid choice, defaulting to Warrior.\n");
            strcpy(pc.name, "Warrior");
            pc.health = 150;
            pc.attackPower = 20;
            pc.defense = 15;
            break;
    }

    return pc;
}

// Inventory functions
void initInventory(struct Inventory *inventory) {
    inventory->itemCount = 0; // Initialize with no items
}

void addItem(struct Inventory *inventory, const char *nameItem, int quantity) {
    // Check if the item is already in the inventory
    for (int i = 0; i < inventory->itemCount; i++) {
        if (strcmp(inventory->items[i].nameItem, nameItem) == 0) {
            inventory->items[i].quantity += quantity; // Update quantity
            printf("%d %s added to inventory.\n", quantity, nameItem);
            return;
        }
    }
    // Add new item if space is available
    if (inventory->itemCount < MAX_ITEMS) {
        strcpy(inventory->items[inventory->itemCount].nameItem, nameItem);
        inventory->items[inventory->itemCount].quantity = quantity;
        inventory->itemCount++;
        printf("%d %s added to inventory.\n", quantity, nameItem);
    } else {
        printf("Inventory is full!\n");
    }
}

void removeItem(struct Inventory *inventory, const char *nameItem, int quantity) {
    for (int i = 0; i < inventory->itemCount; i++) {
        if (strcmp(inventory->items[i].nameItem, nameItem) == 0) {
            if (inventory->items[i].quantity >= quantity) {
                inventory->items[i].quantity -= quantity;
                printf("%d %s removed from inventory.\n", quantity, nameItem);
                if (inventory->items[i].quantity == 0) {
                    // Shift the remaining items to avoid empty spaces
                    for (int j = i; j < inventory->itemCount - 1; j++) {
                        inventory->items[j] = inventory->items[j + 1];
                    }
                    inventory->itemCount--;
                }
            } else {
                printf("Not enough %s to remove!\n", nameItem);
            }
            return;
        }
    }
    printf("%s not found in inventory.\n", nameItem);
}

void displayInventory(const struct Inventory *inventory) {
    printf("Inventory:\n");
    for (int i = 0; i < inventory->itemCount; i++) {
        printf("  - %s (x%d)\n", inventory->items[i].nameItem, inventory->items[i].quantity);
    }
    if (inventory->itemCount == 0) {
        printf("  [empty]\n");
    }
}

int main() {
    // color system
    system("COLOR 0a");

    // Player selects a class
    struct PlayerClass pc = selectClass();

    // color system
    system("COLOR 06");

    // player information
    int health = pc.health;
    int damage = pc.attackPower;
    int defense = pc.defense;
    int money = 0;
    int level = 0;
    int exp = 0;
    struct Inventory playerInventory;
    initInventory(&playerInventory);

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

    skeletonStatus(); // skeleton pic
    scanf(" %c", &answer);
    printf("\n");

    if (answer == 'f') {
        // Flee logic
        answer = 'd';
        const char *answer_s = "Log: You ran away from Skeleton! And you found a Village\n";
        printf("===============================\n");
        printWithAnimation(answer_s);
        printf("===============================\n");
        ratStatus(); // rat pic
        scanf(" %c", &answer);
        printf("\n");
    }
    else if (answer == 'b') {
        // Battle logic
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
            printf("=================================\n");
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
                displayInventory(&playerInventory);
            }
        }
    }

    return 0;
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
