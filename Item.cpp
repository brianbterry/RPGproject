//Implementation file for Item Class
// Brian Terry
// 12/5/2019

//Includes
#include <iomanip>
#include "Item.h"

using namespace std;

//Implementation
Item::Item() : Item("UNDEFINED") {}

Item::Item(string val, int qty) {
    name = val;
    quantity = qty;
}

Item::Item(const Item &obj) {
    id = obj.id;
    name = obj.name;
    quantity = obj.quantity;
}

Item::~Item() {}

void Item::saveItem(DataManager *dm) {
    dm->writeInt(id);
    dm->writeString(name);
    dm->writeInt(quantity);
}

void Item::loadItem(DataManager *dm) {
    id = dm->readInt();
    name = dm->readString();
    quantity = dm->readInt();
}

const Item Item::operator =(const Item &rhs) {
    if (this != &rhs) {
        id = rhs.id;
        name = rhs.id;
        quantity = rhs.quantity;
    }
    return *this;
}

Item Item::operator++() {
    ++quantity;
    return *this;
}

Item Item::operator ++(int) {
    Item temp(name, quantity);
    temp.id = id;
    quantity++;
    return temp;
}

Item Item::operator--() {
    if (quantity > 0) { --quantity; }
    return *this;
}

Item Item::operator--(int) {
    Item temp(name, quantity);
    temp.id = id;
    if (quatity > 0) { quatity--; }
    return temp;
}

ostream& operator <<(ostream& strm, const Item& obj) {
    strm << "[" << obj.id << "]  ";
    if (obj.id < 10 ) {
        strm << " ";
    }
    strm << obj.quantity <<"x " << obj.name;
    return strm;
}

istream& operator >>(istream& strm, Item& obj) {
    cout << "Name: ";
    getline(strm, obj.name);
    cout << "Quantity: ";
    strm >> obj.quantity;
    strm.ignore();
    return strm;
}