#include <vector>
#include <string>
using  namespace std;

class Document {

    private:
    vector<string> output{};
    string nextCommand = "";
    bool exit = false;
    int currentLine = 0;

    public:
    Document(){}
    ~Document(){};

    void setNextCommand(string);
    void setCurrentLine(int);

    void executeNextLine(string);
    void executeCommand(string);
    
    string getCommand();
    vector<string> getOutput();
    bool getExit();

    //comands
    void appendNewTextAfterTheCurrentLine(const string);
    void insertNewTextBeforeCurrentLine(const string);
    void changeTheCurrentLineToText(const string);
    void searchesBackward(string);
    void searchesForward(string);
    void deleteCurrentLine();

};