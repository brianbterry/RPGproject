// Implementation of Character Class
//Brian Terry
//28 November 2019

//Includes
#include<iomanip>
#include <string>
#include <cstdlib>
#include<ctime>
#include "Character.h"

using namespace std;

int Character::NUM_STATS = 6;

Character::Character() {
    mm = new MessageManager();
    loadMessages();
    id = -1;
    name = "NO NAME";
    raceType = "NO RACE";
    classType = "NO CLASS";
    level = 0;
    armourClass = 0;
    hitPoints = 0;
    stats = new int[NUM_STATS];
    rollStats();
    inventory.clear();
}

Character::Character(const Character &obj){
    mm = new MessageManager();
    for (int i = 0; i < obj.mm->getMessage(); i++) {
        string msg = obj.mm->getMessage(i);
        mm->addMessage(i,msg);
    }
    id = obj.id;
    name =obj.name;
    raceType = obj.classType;
    level = obj.level;
    armourClass = obj.armourClass;
    hitPoints = obj.hitPoints;
    stats = new int[NUM_STATS];
    for (int i = 0; i < NUM_STATS; i++){
        stats[i] = obj.inventory;
    }
    inventory.clear();
    for (Item item : obj.inventory) { 
        Item temp;
        inventory.push_back(temp);
    }
}

Character::~Character() {
    inventory.clear();
    delete mm;
    mm = nullptr;
    delete [] stats;
    stats = nullptr;
}

void Character::loadMessages() {
    mm->addMessage(LINE1, "==================================");
    mm->addMessage(LINE2, "----------------------------------");

    string str = "";
    str += mm->getMessage(LINE1);
    str += "\n                   UPDATE INVENTORY MENU\n";
    str += mm->getMessage(LINE1);
    str += "\n1)Add new item\n";
    str += "2) Modifiy existing item \n";
    str += "3) Delete exisiting item\n";
    str += "0) Return to modify Character menu\n\n";
    mm->addMessage(MENU_INV_MOD, str);

    str.clear();
    str += mm->getMessage(LINE1);
    str += "\n                   UPDATE ITEM MENU\n";
    str += mm->getMessage(LINE1);
    str += "\n1) Modify name\n";
    str += "2) Modify quantity\n";
    str += "0) Return to modify Character menu\n\n";
    mm->addMessage(MENU_ITEM_MOD, str);

    mm->addMessage(PROMPT_CHOICE, "Please select an otption from the menu: ");
    mm->addMessage(PROMPT_ITEM_MOD, "Please enter ID of Item to modify: ");
    mm->addMessage(PROMPT_ITEM_DEL, "Please enter ID of Item to delete: ");

    str.clear();
    str += mm->getMessage(LINE1);
    str += "\n                   DETAILED CHARACTER INFORMATION\n";
    str += mm->getMessage(LINE1);
    mm->addMessage(HEADER_FULL, str);

    str.clear();
    str += mm->getMessage(LINE2);
    str += "\n  HP  AC  STR  DEX  CON  INT  WIS  CHA\n";
    str += mm->getMessage(LINE2);
    mm->addMessage(HEADER_STATS, str);

    str.clear();
    str += mm->getMessage(LINE2);
    str += "\n                   INVENTORY\n";
    str += mm->getMessage(LINE2);
    mm->addMessage(HEADER_INV, str);

    mm->addMessage(ERR_INVALID_CHOICE, "Sorry, that is not a valid selection! Please try again.\n\n");
    mm->addMessage(ERR_INVALID_CHOICE, "Sorry, that ID was not found!\n\n");
}

string Character::summary() {
    string s ="[" + to_string(id) + "] ";
    if (id < 10) {
        s += " "; 
    }
    s += name + ", Level ";
    s += to_string(level) + " ";
    s += raceType + " ";
    s += classType + "\n";
    return s;
}

void Character::rollStats() {
    static unsigned seed = 0;
    if (!seed) { seed = time(0; srand(seed); }

    int sides = 6;
    int d1, d2, d3, d4, min;

    for (int i = 0; i < NUM_STATS; i++) {
        //roll4 random dice
        d1 =(rand() % sides) + 1;
        d2 =(rand() % sides) + 1;
        d3 =(rand() % sides) + 1;
        d4 =(rand() % sides) + 1;

        //find min
        min = d1;
        min = d2 < min ? d2 : min;
        min = d3 < min ? d3 : min;
        min = d4 < min ? d4 : min;

        //toss out smallest and set stat
        stats[i] = d1 + d2 + d3 + d4 - min;
    }
}

void Character::updateInventory() {
    string str;
    int index;
    bool flag = true;
    
    while (flag) {
        system("cls");
        cout << *this << endl << endl;
        cout << mm->getMessage(MENU_INV_MOD);
        cout << mm->getMessage(PROMPT_CHOICE);
        getline(cin, str);
        cout << endl;

        switch (stoi(str)) {
            case 1:
                addItem();
                break
            case 2:
                modifyItem();
                break;
            case 3:
                deleteItem();
                break;
            case 0:
                flag = false;
                break;
            default:
                cout << mm->getMessage(ERR_INVALID_CHOICE);
                system("pause");
                break;
        }
    }
}

void Character::addItem() {
    Item item;
    cin >> item;
    item.setId(inventory.size() + 1);
    inventory.push_back(item);
}

void Character::modifyItem() {
    string str;
    int index;

    cout << mm->getMessage(PROMPT_ITEM_MOD);
    getline(cin, str);

    if (isValidId(stoi(str))) {
        bool flag = true;
        index = stoi(str) - 1;

        while (flag) {
            system("cls");
            cout << inventory[index] << endl << endl;
            cout << mm->getMessage(MENU_ITEM_MOD);
            cout << mm->getMessage(PROMPT_CHOICE);
            getline(cin, str);
            cout << endl;

            switch (stoi(str)) {
            case 1:
                cout << "New name: ";
                getline(cin, str);
                inventory[index].setName(str);
                break;
            case 2:
                cout << "New quantity: ";
                getline(cin, str);
                inventory[index].setQuantity(stoi(str));
                break;
            case 0:
                flag = false;
                break;
            default:
                cout << mm->getMessage(ERR_INVALID_CHOICE);
                system("pause");
                break;
            }
        }
    }
    else {
        cout << mm->getMessage(ERR_ID_NOT_FOUND) << endl;
        system("pause");
    }
}

void Character::deleteItem() {
    string str;
    int index, newId = 1;

    cout << mm->getMessage(PROMPT_ITEM_DEL);
    getlint(cin, str);

    if(isValidId(stoi(str))) {
        index = stoi(str) - 1;
        inventory.erase(inventory.begin() + index);
        for (int i = 0; i < inventory.size(); i++) {
            inventory[i].setId(newId);
            newId++;
        }
    }
    else {
        cout << mm->getMessage(ERR_ID_NOT_FOUND) << endl;
    }
}

void Character::saveCharacter(DataManager* dm) {
    dm->writeInt(id);
    dm->writeString(name);
    dm->writeString(raceType);
    dm->writeString(classType);
    dm->writeInt(level);
    dm->writeInt(armourClass);
    dm->writeInt(hitPoints);
    for (int i = 0; i < NUM_STATS; i++) {
        inventory[i].saveItem(dm);
    }
}

void Character::loadCharacter(DataManager* dm) {
    id = dm->readInt();
    name = dm->readString();
    raceType = dm->readString();
    classType = dm->readString();
    level = dm->readInt();
    armourClass = dm->readInt();
    hitPoints = dm->readInt();
    for (int = 0; i < NUM_STATS; i++) {
        stats[i] = dm.readInt();
    }
    inventory.clear();
    int numItems = dm->readInt();
    for (int i = 0; i <numItems; i++) {
        Item temp;
        temp.loadItem(dm);
        inventory.push_back(temp);
    }
}

const Character Character::operator =(const Character &rhs)
{
    if (this != &rhs){
        mm = new MessageManager();
        for (int i = 0; i < rhs.mm->count(); i++) {
            string msg = rhs.mm->getMessage(i);
            mm->addMessage(i, msg);
        }  
        id = rhs.id;
        name = rhs.name;
        raceType = rhs.raceType;
        classType = rhs.classType;
        level = rhs.level;
        armorClass = rhs.armorClass;
        hitPoints = rhs.hitPoints;
        stats = new int[NUM_STATS];
        for (int i = 0; i < NUM_STATS; i++) {
             stats[i] = rhs.stats[i];
        }
        inventory.clear();
        for (Item item : rhs.inventory) {
            Item temp = item;
            inventory.push_back(temp);
        }
    }   
    return *this;
}

ostream& operator <<(ostream &strm, const Character &obj) {
    strm << "[" << obj.id << "}   ";
    if (obj.id < 10) {
        strm << " ";
    }
    strm << obj.name;
    strm << ", Level " << obj.classType << endl;
    strm << obj.mm->getMessage(Character::HEADER_STATS) << endl;
    strm << setw(4) << obj.hitPoints << setw(5) << obj.armourClass;
    for (int i = 0; i < obj.inventory.size(); i++) {
        strm << obj.inventory[i] << endl;
    }
    return strm;
}

istream& operator >>(istream &strm, Character &obj) {
    string str;

    cout << "Character name: ";
    getline(strm, str);
    obj.name = str;
    cout << "Character race: ";
    getline(strm, str);
    obj.raceType = str;
    cout << "Character class: ";
    getline(strm, str);
    obj.classType = str;
    cout << "Character level: ";
    getline(strm, str);
    obj.level = stoi(str);
    cout << "Character armour class (AC): ";
    getline(strm, str);
    obj.armourClass = stoi(str);
    cout << "Character health (HP): ";
    getline(strm, str);
    obj.hitPoints = stoi(str);
    return strm;
}

