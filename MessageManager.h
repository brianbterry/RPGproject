//Specification file for MessageManager class
//  Richard Herschede
//  17 November 2019
#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

//INCLUDES
#include <string> 
#include <vector>
using namespace std;

//SPECIFICATION
class MessageManager {
    public:
        MessageManager();
        ~MessageManager();

        void addMessage(int key, string val);
        string getMessage(int key);
        int count() const { return messages.size(); }
        
    private:
        struct KVP  {
            int key;
            string value;
        };

        vector<KVP> messages;     
};
        
endif // MESSAGEMANAGER_H