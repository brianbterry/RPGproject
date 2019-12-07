//Implementation of MessageManager Class
// Brian Terry
// 12/5/2019

//Includes
#include "MessageManager.h"

using namespace std;

//Implementation
MessageManager::MessageManager() {
    messages.clear();
}

MessageManager::~MessageManager() {
    messages.clear();
}

void MessageManager::addMessage(int key, std::string val) {
    KVP message;
    message.key = key;
    message.value = val;
    messages.push_back(message);
}

string MessageManager::getMessage(int key) {
    int index = -1;

    for (int i = 0; i < messages.size(); i++) {
        if (messages[i].key == key) {
            index = i;
        }
    }
    return (index >= 0 ? messages[index].value : "\nKEY NOT FOUND\n\n");
}