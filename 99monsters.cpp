#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

// Define constants for player stats
const int MAX_LEVEL = 9;
const int INITIAL_HEALTH = 100;
const int INITIAL_DAMAGE = 10;

// Define item IDs
const int ITEM_MAGIC_SWORD = 1;
const int ITEM_HEALTH_POTION = 2;
const int ITEM_MAGIC_SCROLL = 3;

// Define item classes
class Item {
public:
    string name;
    int goldValue;

    Item(string name, int goldValue) : name(name), goldValue(goldValue) {}
};

class MagicSword : public Item {
public:
    MagicSword() : Item("Magic Sword", 50) {}
};

class HealthPotion : public Item {
public:
    HealthPotion() : Item("Health Potion", 25) {}
};

class MagicScroll : public Item {
public:
    MagicScroll() : Item("Magic Scroll", 20) {}
};

// Define player class IDs
const int CLASS_WARRIOR = 1;
const int CLASS_PRIESTESS = 2;
const int CLASS_MAGE = 3;

// Define monster class
class Monster {
public:
    int health;
    int damage;

    Monster() {
        // Generate random values for health and damage
        health = rand() % 99 + 1;
        damage = rand() % 10 + 1;
    }
};

// Define player class
class Player {
public:
    string name;
    int race;
    int playerClass;
    int level;
    int health;
    int damage;
    vector<int> inventory;

    Player() : race(0), playerClass(0) {
        level = 1;
        health = INITIAL_HEALTH;
        damage = INITIAL_DAMAGE;
    }


    void levelUp() {
        if (level < MAX_LEVEL) {
            level++;
            health += 10; // Increase health by 10 on level up
        }
    }
};


void playerAttack(Player& player, Monster& monster) {
    // Display attack options based on player's class
    cout << "Choose your attack move:" << endl;
    cout << "1. Normal Attack" << endl;

    // Add special abilities based on player's class
    switch (player.playerClass) {
    case CLASS_WARRIOR:
        cout << "2. Power Strike" << endl;
        cout << "3. Shield Block" << endl;
        break;
    case CLASS_PRIESTESS:
        cout << "2. Heal" << endl;
        cout << "3. Divine Smite" << endl;
        break;
    case CLASS_MAGE:
        cout << "2. Fireball" << endl;
        cout << "3. Frost Nova" << endl;
        break;
    default:
        break;
    }

    int choice;
    cin >> choice;

    int damageDealt = 0;

    // Calculate damage based on player's choice and class
    switch (choice) {
    case 1:
        // Normal attack
        damageDealt = player.damage;
        break;
    case 2:
        // Special abilities based on player's class
        switch (player.playerClass) {
        case CLASS_WARRIOR:
            damageDealt = player.damage * 2; // Double damage for Power Strike
            break;
        case CLASS_PRIESTESS:
            // Heal 50% of max health
            player.health += INITIAL_HEALTH / 2;
            if (player.health > INITIAL_HEALTH) {
                player.health = INITIAL_HEALTH; // Cap at max health
            }
            cout << "You healed yourself!" << endl;
            break;
        case CLASS_MAGE:
            damageDealt = 30 + rand() % 21; // Random damage between 30 and 50 for Fireball
            break;
        default:
            break;
        }
        break;
    case 3:
        // Additional abilities for each class
        switch (player.playerClass) {
        case CLASS_WARRIOR:
            // Shield Block - reduce incoming damage
            damageDealt = player.damage;
            cout << "You blocked some of the monster's attack!" << endl;
            break;
        case CLASS_PRIESTESS:
            // Divine Smite - deal bonus damage
            damageDealt = player.damage + 20; // Bonus damage
            break;
        case CLASS_MAGE:
            // Frost Nova - freeze the monster, preventing its next attack
            cout << "You froze the monster in place!" << endl;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    cout << "Your health: " << player.health << endl;
    cout << "Monster's health: " << monster.health << endl;

    if (damageDealt > 0) {
        monster.health -= damageDealt;
        cout << "You dealt " << damageDealt << " damage to the monster!" << endl;

        if (monster.health <= 0) {
            cout << "You defeated the monster!" << endl;
            // Handle victory (e.g., gain experience, loot)
        }
    }
}



void monsterAttack(Player& player, Monster& monster) {
    // Calculate damage dealt by the monster
    int damageDealt = monster.damage;

    cout << "The monster dealt " << damageDealt << " damage to you." << endl;
    player.health -= damageDealt;

    if (player.health <= 0) {
        cout << "You were defeated by the monster..." << endl;
        // Handle defeat (e.g., game over)
    }
}

// Vendor class
class Vendor {
public:
    enum Item {
        MAGIC_SWORD,
        HEALTH_POTION,
        MAGIC_SCROLL
    };

    static void sellItem(Player& player, Item item) {
        switch (item) {
        case MAGIC_SWORD:
            cout << "You purchased a Magic Sword!" << endl;
            player.inventory.push_back(ITEM_MAGIC_SWORD);
            break;
        case HEALTH_POTION:
            cout << "You purchased a Health Potion!" << endl;
            player.inventory.push_back(ITEM_HEALTH_POTION);
            break;
        case MAGIC_SCROLL:
            cout << "You purchased a Magic Scroll!" << endl;
            player.inventory.push_back(ITEM_MAGIC_SCROLL);
            break;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    // Seed for random number generation

    // Game setup
    cout << "Welcome to 99 Monsters!" << endl;
    cout << "Press enter to start the game." << endl;
    cin.get();

    // Player creation
    Player player;
    cout << "Enter your name: ";
    getline(cin, player.name);

    do {
        cout << "Choose your race (1: Elf, 2: Human, 3: Dwarf): ";
        cin >> player.race;
    } while (player.race < 1 || player.race > 3); // Validate race

    do {
        cout << "Choose your class (1: Warrior, 2: Priestess, 3: Mage): ";
        cin >> player.playerClass;
    } while (player.playerClass < 1 || player.playerClass > 3); // Validate class

    // Game loop
    while (true) {
        // Display game menu
        cout << "1. Adventure" << endl;
        cout << "2. Visit campsite" << endl;
        cout << "3. Search for traveling vendor" << endl;
        cout << "4. Check inventory" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            // Adventure - combat with monsters
            // Create a monster
            Monster monster;
            cout << "You encountered a monster with " << monster.health << " health and " << monster.damage << " damage." << endl;

            // Combat loop
            while (player.health > 0 && monster.health > 0) {
                // Player's turn
                cout << "It's your turn to attack!" << endl;
                playerAttack(player, monster);

                // Check if monster is defeated
                if (monster.health <= 0) {
                    cout << "The monster has been banished to the Shadow Realm!" << endl;
                    // Handle victory (e.g., gain experience, loot)
                    break;
                }

                // Monster's turn
                cout << "The monster is attacking!" << endl;
                monsterAttack(player, monster);

                // Check if player is defeated
                if (player.health <= 0) {
                    cout << "You were defeated by the monster..." << endl;
                    // Handle defeat (e.g., game over)
                    break; // Exit the combat loop
                }
            }
            break;
        }
        case 2:
            // Visit campsite - rest and recover health
            player.health = INITIAL_HEALTH; // Restore player's health
            cout << "You rest and regain your strength. You are now ready to adventure one again!" << endl;
            break;
        case 3: {
            // Search for traveling vendor
            // Simulate a 50% chance to find the vendor
            if (rand() % 2 == 0) {
                cout << "You found the traveling vendor!" << endl;
                // Display vendor's items
                cout << "Vendor's items for sale:" << endl;
                cout << "1. Magic Sword" << endl;
                cout << "2. Health Potion" << endl;
                cout << "3. Magic Scroll" << endl;

                cout << "Enter the item number you want to buy (or 0 to exit): ";
                int itemChoice;
                cin >> itemChoice;

                if (itemChoice != 0) {
                    // Handle item purchase
                    Vendor::sellItem(player, static_cast<Vendor::Item>(itemChoice - 1));
                    cout << "You purchased an item from the vendor." << endl;
                }
            }
            else {
                cout << "You didn't find the traveling vendor..." << endl;
            }
            break;
        }
        case 4: {
            // Check inventory
            cout << "Inventory:" << endl;
            if (player.inventory.empty()) {
                cout << "Your inventory is empty." << endl;
            }
            else {
                for (int item : player.inventory) {
                    switch (item) {
                    case ITEM_MAGIC_SWORD:
                        cout << "Magic Sword" << endl;
                        break;
                    case ITEM_HEALTH_POTION:
                        cout << "Health Potion" << endl;
                        break;
                    case ITEM_MAGIC_SCROLL:
                        cout << "Magic Scroll" << endl;
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        // Check if player is defeated
        if (player.health <= 0) {
            cout << "Game Over. You were defeated by the monsters." << endl;
            break; // Exit the game loop
        }
    }

    return 0;
}
