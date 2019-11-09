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

void split(std::string const &str, const char delim, std::vector<std::string> &out){
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos){
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
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
        deleteCurrentLine();
    } else if (this->nextCommand == "stf") {
        searchesForward(line);
    } else if (this->nextCommand == "/") {
        repeatSearch();
    } else if (this->nextCommand == "stb") {
        searchesBackward(line);
    } else if (this->nextCommand == "replace") {
        replaceOldStringWithNew(line);
    } else if (this->nextCommand == "Q") {
        this->exit = true;
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
    cout << this->output[currentLineNumber - 1] << endl;
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

void Document::searchesBackward(const string line){
    string searchedText = line.substr(1, line.size());

    for(int i = 0; i < this->currentLine; i++){
        if(this->output[i].find(searchedText) + 1){
            cout << this->output[i] << endl;
            this->currentLine = i + 1;
            break;
        }
    }
}

void Document::searchesForward(const string line){
    string searchedText = line.substr(1, line.size());
    auto size = this->output.size();

    this->setLastFind(searchedText);

    for(int i = this->currentLine; i < size - 1; i++){
        if(this->output[i].find(searchedText) + 1){
            cout << this->output[i] << endl;
            this->currentLine = i + 1;
            break;
        }
    }
}

void Document::repeatSearch(){
    auto size = this->output.size();

    for(int i = this->currentLine; i < size - 1; i++){
        if(this->output[i].find(this->lastFind) + 1){
            cout << this->output[i] << endl;
            this->currentLine = i + 1;
            break;
        }
    }
}

void Document::deleteCurrentLine(){ //d
    int size = this->output.size();
    int lastLine = this->currentLine - 1;

    this->output.erase(this->output.begin() + this->currentLine - 1);

    if (size == lastLine) { //if last line was removed  
        this->currentLine--;
    }
}

void Document::replaceOldStringWithNew(const string line){
    vector<string> words;
    split(line, '/', words);

    string oldLine = this->output[this->currentLine - 1];

    int wordPlace = oldLine.find(words[1]);
    oldLine.replace(wordPlace, words[1].size(), words[2]);

    this->output[this->currentLine - 1] = oldLine;
}

void Document::changeTheCurrentLineToText(string line){ //c
    this->output[this->currentLine - 1] = line;
}

void Document::setLastFind(const string text){
    this->lastFind = text;
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
    }
    else if (line == "a") {
        this->nextCommand = line;
    }
    else if (line == "i") {
        this->nextCommand = line;
    }
    else if (line == "c") {
        this->nextCommand = line;
    }
    else if (line == "d") {
        this->nextCommand = line;
    }
    else if (line[0] == '/') {
        if(line.size() == 1){
            this->nextCommand = line;
        } else {
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
    else if (line[0] == 's' && line[1] == '/') {
        vector<string> result;
        split(line, '/', result);
        if(result.size() == 3){
            this->nextCommand = "replace";
        }
    } else if (line == "Q") {
        this->nextCommand = "Q";
    }
}
