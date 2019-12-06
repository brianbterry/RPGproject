//Specification for DataManager Class
// Brian Terry
// 12/5/2019

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

//Includes
#include <fstream>
#include <string>

using namespace std;

//Specification
class DataManager {
    public:
        enum Mode { READ, WRITE };

        DataManager ( string filename, DataManager::Mode mode);
        ~DataManager();

        void writeString(string str);
        void writeInt(int n);
        void writeLong(long n);
        string readString();
        int readInt();
        long readLong();

    private:
        fstream data;
};

#endif