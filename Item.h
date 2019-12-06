//Specification for Item Class
// Brian Terry
// 12/5/2019
#ifndef ITEM_H
#define ITEM_H

//Includes
#include <iostream>
#include <string>
#include "DataManager.h"

using namespace std;

//Forward Declaration

class Item;

//Stream Prototypes
ostream &operator << (ostream &strm, const Item &obj);
istream &operator >> (istream &strm, Item &obj);

//Specification
class Item {
    public:
        Item();
        Item(string val, int qty  = 1);
        Item(const Item &obj);
        ~Item();

        void setId(int val) { id = val; }
        void setName(string val) { name = val; }
        void setQuantity(int val) { quantity = val; }
        int getId() const { return id; }
        string getName() const { return name; }
        int getQuantity() const { return quantity; }

        void saveItem(DataManager *dm);
        void loadItem(DataManager *dm);

        const Item operator =(const Item &rhs);
        Item operator ++();
        Item operator ++(int);
        Item operator --();
        Item operator --(int);

        friend ostream &operator << (ostream &strm, const Item &obj);
        friend istream &operator >> (istream &strm, Item &obj);

    private:
        int id;
        string name;
        int quantity;
};

#endif