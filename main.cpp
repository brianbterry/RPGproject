//This menu-driven program will manage RPG Character data with a binary file
// Brian Terry
// 12/5/2019

//Includes
#include <iostream>
#include <string>
#include <vector>
#include "RPGproject.h"
#include "MessageManager.h"
#include "Character.h"

using namespace std;

//Prototypes
void loadMessages(MessageManager *mm);
void loadCharacters(MessageManager *mm, vector<Character> &v, string &filename);
void saveCharacters(MessageManager *mm, vector<Character> v, string &filename);
void listAll(MessageManager *mm, vector<Character> v);
void listOne(MessageManager *mm, vector<Character> v);
void addCharacter(MessageManager *mm, vector<Character> &v);
void modifyCharacter(MessageManager *mm, vector<Character> &v);
void deleteCharacter(MessageManager *mm, vector<Character> &v);
bool isValidId(vector<Character>, int id);

//Main Program
int main() {
    bool flag = true;
    string filename = "";
    string choice;
    vector<Character> v;

    //load messages
    MessageManager *mm = new MessageManager();
    loadMessages(mm);

    //hello
    cout << mm->getMessage(HELLO);
    system("pause");

    //program loop
    while (flag) {
        system("cls");
        cout << mm->getMessage(MENU_MAIN);
        cout << mm->getMessage(PROMPT_CHOICE);
        getline(cin, choice);
        cout << endl;

        switch (stoi(choice)) {
            case 1: 
                loadCharacters(mm, v, filename);
                break;
            case 2:
                saveCharacters(mm, v, filename);
                break;
            case 3:
                system("cls");
                listAll(mm, v);
                system("pause");
                break;
            case 4:
                listOne(mm, v);
                system("pause");
                break;
            case 5:
                addCharacter(mm, v);
                system("pause");
                break;
            case 6:
                modifyCharacter(mm, v);
                break;
            case 7:
                deleteCharacter(mm, v);
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

    //GOODBYE
    cout << mm->getMessage(GOODBYE);

    //release memory
    v.clear();
    delete mm;
    mm = nullptr;

    return 0;

}

void loadMessages(MessageManager *mm) {
    string str = "";

    mm->addMessage(HELLO, "Hello! This menu-driven program will manage RPG Characters with a data file.\n\n");
    mm->addMessage(LINE1, "============================================");

    str += mm->getMessage(LINE1);
    str += "\n              Main Menu\n";
    str += mm->getMessage(LINE1);
    str += "\n1) Load Characters from file\n";
    str += "2) Save Characters to file\n";
    str += "3) List all Characters\n";
    str += "4) Display Character data\n";
    str += "5) Add new Character\n";
    str += "6) Modify existing Character\n";
    str += "7) Delete existing Character\n";
    str += "0) Exit program\n\n";
    mm->addMessage(MENU_MAIN, str);

    str.clear();
    str += mm->getMessage(LINE1);
    str += "\n              MODIFY CHARACTER MENU\n";
    str += mm->getMessage(LINE1);
    str += "\n1) Modify name\n";
    str += "2) Modify race type\n";
    str += "3) Modify class type\n";
    str += "4) Reroll stats\n";
    str += "5) Modify level\n";
    str += "6) Modify hit points\n";
    str += "7) Modify armour class\n";
    str += "8) Update inventory\n";
    str += "0) Return to main menu\n\n";
    mm->addMessage(MENU_CHAR_MOD, str);

    mm->addMessage(PROMPT_FILENAME, "Enter name of data file ");
    mm->addMessage(PROMPT_CHOICE, "Please select an option from the menu: ");
    mm->addMessage(PROMPT_CHAR_DISP, "Please eneter ID of Character to display: ");
    mm->addMessage(PROMPT_CHAR_MOD, "Please eneter ID of Character to modify: ");
    mm->addMessage(PROMPT_CHAR_DEL, "Please eneter ID of Character to delete: ");
    mm->addMessage(SUCCESS_CHAR_ADD, "\nCharacter added...\n\n");
    mm->addMessage(SUCCESS_CHAR_DEL, "\nCharacter deleted...\n\n");
    mm->addMessage(SUCCESS_LOAD, "Characters loaded from file...\n\n");
    mm->addMessage(SUCCESS_SAVE, "Characters saved to file...\n\n");

    str.clear();
    str += mm-> getMessage(LINE1);
    str += "\n              LIST OF CHARACTERS\n";
    STR += mm->getMessage(LINE1);
    mm->addMessage(HEADER_BRIEF, str);

    str.clear();
    str += mm->getMessage(LINE1);
    str += "\n      DETAILED CHARACTER INFORMATION\n";
    str += mm->getMessage(LINE1);
    mm->addMessage(HEADER_FULL, str);

    mm->addMessage(ERR_FILE_NONE, "No file name set...\n");
    mm->addMessage(ERR_FILE_READ, "Error opening file. Creating new data file.\n");
    mm->addMessage(ERR_INVALID_CHOICE, "Sorry, that is not a valid selection! Please try again.\n\n");
    mm->addMessage(ERRID_NOT_FOUND, "Sorry, that ID was not found!\n");
    mm->addMessage(GOODBYE, "Program exiting. Goodbye!\n");        
}

void loadCharacters(MessageManager *mm, vector<Character> &v, string &filename) {
    v.clear();
    do {
        string str;
        if (filename.length() == 0) {
            cout << mm->getMessage(ERR_FILE_NONE); 
        }
        cout << mm->getMessage(PROMPT_FILENAME) << "[" << filename << "]: ";
        getline(cin, str);
        if (str.length() != 0) {
            filename = str; 
            }
    } 
    while (filename.length() == 0);

    DataManager *dm = new DataManager(filename, DataManager::READ);
    int count = dm->readInt();
    for (int i = 0; i < count; i++) {
        Character c;177  c.loadCharacter(dm);
        v.push_back(c);
    }

    delete dm;
    dm = nullptr;

    cout << mm->getMessage(SUCCESS_LOAD);

    system("pause");
}

