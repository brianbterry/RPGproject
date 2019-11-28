//INCLUDES
#include <iostream>
#include "MessageSet.h"
using namespace std;

//GLOBAL CONSTANTS
string MESSAGE_FILE = "RPGPrrojectMessages.txt";

//PROTOTYPES
void displayMessage(MessageSet ms, string key);

//MAIN
int main() {
    MessageSet ms(MESSAGE_FILE);

    displayMessage(ms, "HELLO");
    displayMessage(ms, "GOODBYE");

    return 0;    
}

//DEFINITIONS
void displayMessage(MessageSet ms, string key)
