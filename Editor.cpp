#include <string>
#include <vector>
#include <iostream>
#include "Editor.h"
using namespace std;

void Editor::loop(){
    
    string nextLine;

    while(getline(cin, nextLine)){
        cout << nextLine << endl;
        this->doc.executeNextLine(nextLine);
        if(this->doc.getExit()){
            break;
        }
    }

}