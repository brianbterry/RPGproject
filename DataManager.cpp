//Implementation of DataManager Class
// Brian Terry
// 17 November 2019

//Includes
#include "DataManager.h"

//Implementation
DataManager::DataManager(string filename, DataManager::Mode mode) {
    switch (mode) {
        case READ:
            data.open(filename, ios::in|ios::binary);
            if (!data) {
                data.close();
                data.open(filename, ios_base::out | ios_base::binary);
                writeInt(0);
                data.close();
                data.open(filename, ios_base::in | ios_base::binary);
            } else {
                data.seekg(0L, ios::end);
                data.clear();
                data.seekg(0L, ios::beg);
            }
            break;
        case WRITE:
            data.open(filename, iso::out|ios::binary);
            break;
        default: break;
    }
}

DataManager::~DataManager() {
    data.close();
}

void DataManager::writeString(std::string str) {
    writeInt(str.length());
    char ch;

    for (int i = 0; i < str.length(); i++) {
        ch = str[i];
        data.write(&ch, sizeof(ch));
    }
}

void DataManager::writeInt(int n) {
    data.write(reinterpret_cast<char*>(&n), sizeof(n));
}

void DataManager::writeLong(long n) {
    data.write(reinterpret_cast<char*>(&n), sizeof(n));
}

string DataManager::readString() {
    int length = readInt();
    string str = "";
    char ch;

    for (int i = 0; i < length; i++) {
        data.read(&ch, sizeof(ch));
        str += ch;
    }

    return str;
}

int DataManager::readInt() {
    int n;

    data.read(reinterpret_cast<char*>(&n), sizeof(n));
    
    return n;
}

long DataManager::readLong() {
    long n;

    data.read(reinterpret_cast<char*>(&n), sizeof(n));

    return n;
}

