#include <string>
#include <vector>
#include <iostream>
#include "Document.h"
using namespace std;

//_____________________________Help functions_____________________________//

bool isNumber(const string s){ 
    if(s.size() == 0){
        return false;
    }
    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i]) == false) {
            return false;
        }  
    }
    return true; 
}

void printCurrentLine(const string lineToPrint){
    cout << lineToPrint << endl;
}

void printLineNumberAndTab(const int lineNumber, const string line){
    cout << lineNumber << "\t" << line << endl;
}

void printAllLines(const vector<string> text){
    for(string line : text){
        cout << line << endl;
    }
}

//_____________________________Class functions_____________________________//

void Document::executeNextLine(string line) {
    setNextCommand(line);
    executeCommand(line);
}

void Document::executeCommand(string line){

    if(this->nextCommand == "p"){
        printCurrentLine(this->output[this->currentLine - 1]);
    } else if (this->nextCommand == "n") {
        printLineNumberAndTab(this->currentLine, this->output.at(this->currentLine - 1));
    } else if (this->nextCommand == "%p") {
        printAllLines(this->output);
    } else if (isNumber(this->nextCommand)) {
        setCurrentLine(stoi(this->nextCommand));
    } else if (this->nextCommand == "a" && line !="a") {
        appendNewTextAfterTheCurrentLine(line);
    } else if (this->nextCommand == "i" && line != "i") {
        insertNewTextBeforeCurrentLine(line);
    } else if (this->nextCommand == "c" && line != "c") {
        changeTheCurrentLineToText(line);
    } else if (this->nextCommand == "d") {

    } else if (this->nextCommand == "stf") {
        searchesForward(line);
    } else if (this->nextCommand == "/") {

    } else if (this->nextCommand == "stb") {
        searchesBackward(line);
    } else if (this->nextCommand == "s/old/new") {

    } else if (this->nextCommand == "Q") {
        this->exit = true;
    }
}

void Document::setNextCommand(string line){
    if(line == "p") {
        this->nextCommand = line;
    }
    else if (line == "n") {
        this->nextCommand = line;
    }
    else if (line == "%p") {
        this->nextCommand = line;
    }
    else if (isNumber(line)) {
        this->nextCommand = line;
        // cout << "ENTER TO " << line << endl;
    }
    else if (line == "a") {
        this->nextCommand = line;
        // cout << "ENTER TO " << line << endl;
    }
    else if (line == "i") {
        this->nextCommand = line;
        // cout << "ENTER TO " << line << endl;
    }
    else if (line == "c") {
        this->nextCommand = line;
        // cout << "ENTER TO " << line << endl;
    }
    else if (line == "d") {
        this->nextCommand = line;
        // cout << "ENTER TO " << line << endl;
    }
    else if (line[0] == '/') {
        if(line.size() == 1){
            // cout << "ENTER TO " << line << endl;
            this->nextCommand = line;
        } else {
            // cout << "ENTER TO SEARCH TEXT FORWARD" << endl;
            this->nextCommand = "stf";
        }
    }
    else if (line[0] == '?') {
        if(line.size() != 1){
            this->nextCommand = "stb";
        }
    } else if (line == ".") {
        this->nextCommand = line;
    }
    else if (line == "s/old/new") {
        this->nextCommand = line;
        // cout << "ENTER TO " << line << endl;
    } else if (line == "Q") {
        this->nextCommand = line;
        // cout << "ENTER TO " << line << endl;
    }
}

vector<string> Document::getOutput(){
    return this->output;
}

bool Document::getExit() {
    return this->exit;
}

string Document::getCommand(){
    return this->nextCommand;
}

void Document::setCurrentLine(const int currentLineNumber){
    this->currentLine = currentLineNumber;
    cout << this->output[currentLineNumber] << endl;
}

void Document::appendNewTextAfterTheCurrentLine(const string line) { //a
    auto it = this->output.begin() + this->currentLine;
    this->output.insert(it, line);
    this->currentLine++;
}

void Document::insertNewTextBeforeCurrentLine(const string line){ //i
    if(this->currentLine != 0){
        auto it = this->output.begin() + this->currentLine - 1;
        this->output.insert(it, line);
    } else {
        this->output.insert(this->output.begin(), line);
    }
    this->currentLine++;
}

void Document::searchesBackward(string line){
    string searchedText = "";
    for(int i = 1; i < line.size(); i++){
        searchedText = searchedText + line[i];
    }
    auto size = this->output.size();

    for(int i = 0; i < size - 1; i++){
        if(this->output[i] == searchedText){

            this->currentLine = i + 1;
            cout << searchedText << endl;
        }
    }
}

void Document::searchesForward(string line){
    //
}

void Document::deleteCurrentLine(){ //d
    this->output.erase(this->output.begin() + this->currentLine);
    //current - or + ???
}

void Document::changeTheCurrentLineToText(string line){
    this->output[this->currentLine] = line;
    this->currentLine++;
}

