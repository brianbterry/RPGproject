//messages for the project
//INCLUDES
#include <iostream>
#include "MessagesSet.h"
using namespace std;

enum 
{
    HELLO,
    GOODBYE,
};

void loadMessages(MessagesSet &ms) {
    ms.add(HELLO, "Hello!\n");
    ms.add(GOODBYE. "Goodbye!\n");
}

void displayMessage(MessagesSet ms, int key) {
    cout << ms.getMessage(key);
}