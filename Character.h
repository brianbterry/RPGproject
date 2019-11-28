//Specification for Character Class
//Brian Terry
// 28 November 2019

#ifndef CHARACTER_H
#define CHARACTER_H


//Includes
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "DataManage.h"
#include "MessageManager.h"

using namespace std;

//Forward Declaration
class Character;

//Stream Prototypes
ostream &operator <<(ostream &strm, const Character &obj);
istream &operator >>(istream &strm, Character &obj);

//Specification
class Character {
    public:
        Character();
        Character(string val);
        ~Character();
        Character(const Character &obj);

        void setId(int val) { id = val; }
        void setName(string val) { name = val; }
        void setRaceType(string val) { raceType = val; }
        void setClassType(string val) { classType = val; }
        void setLevel(int val) { level = val; }
        void setArmourClass(int val) { armourClass = val; }
        void setHitPoints(int val) { hitPoints = val; }
        void setStat(int val) { stat = val; }

        int getId() const { return id; }
        string getName() const { return name; }
        string getRaceType() const { return raceType; }
        string getClassType() const { return classType; }
        int getLevel() const { return level; }
        int getArmourClass() const { return armourClass; }
        int getHitPoints() const { return hitPoints; }
        int getStat(StatType stat) const { return stats[stat];}

        string summary();
        void rollStats();
        void updateInventory();

        void saveCharacter(DataManager *dm);
        void loadCharacter(DataManager *dm);

        const Character operator = (const Character &rhs*);

        friend ostream &operator <<(ostream &strm, const Character &obj);
        friend istream &operator >>(istream &strm, Character &obj);

    private:
        enum {
            MENU_ITEM_MOD,
            MENU_INV_MOD,
            PROMPT_CHOICE,
            PROMPT_ITEM_MOD,
            PROMPT_ITEM_DEL,
            SUCCESS_ITEM_ADD,
            SUCCESS_ITEM_DEL,
            HEADER_FULL,
            HEADER_STATS,
            HEADER_INV,
            LINE1,
            LINE2,
            ERR_INVALID_CHOICE,
            ERR_ID_NOT_FOUND,
            ERR_NO_INV
        };

        static int NUM_STATS;

        MessageManager *mm;
        int id;
        string name;
        string raceType;
        string classType;
        int level;
        int armourClass;
        int hitPoints;
        int *stats;
        vector<Item> inventory;

        void loadMessenges();
        void addItem();
        void modifyItem();
        void deleteItem();
        bool isValidId(int val) { return (val > 0 && val <= inventory.size()); }
};

#endif // CHARACTER_H