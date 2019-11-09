#include <vector>
#include <string>
using  namespace std;

class Document {

    private:
    vector<string> output{};
    string nextCommand = "";
    string lastFind = "";
    bool exit = false;
    int currentLine = 0;

    void setNextCommand(string);
    void setCurrentLine(int);
    void setLastFind(const string);

    void executeCommand(string);
    
    string getCommand();
    vector<string> getOutput();

    //comands
    void appendNewTextAfterTheCurrentLine(const string);
    void insertNewTextBeforeCurrentLine(const string);
    void changeTheCurrentLineToText(const string);
    void searchesBackward(const string);
    void searchesForward(const string);
    void replaceOldStringWithNew(const string);
    void deleteCurrentLine();
    void repeatSearch();

    public:
    Document(){}
    ~Document(){};
    void executeNextLine(string);
    bool getExit();
};