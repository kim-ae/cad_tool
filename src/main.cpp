#include <cstdlib>
#include <list>
#include "aagReader.h"

using namespace std;

typedef enum{
    READ_FILE,
    CREATE_XOR,
    STATISTICS,
    SHOW,
    EXIT,
    BACK,
    INVALID
}options;

options stringToEnum(string option){
    if(option == "statistics") return STATISTICS;
    if(option == "read file") return READ_FILE;
    if(option == "create xor") return CREATE_XOR;
    if(option == "show") return SHOW;
    if(option == "exit") return EXIT;
    if(option == "back") return BACK;
    return INVALID;
}

void showMenu1();
void showMenu2();

int main()
{
    Aig* aig = NULL;
    bool outerContinue = true;
    bool fileContinue = true;
    bool continueAction = true;
    string choice;
    while(outerContinue){
        while(fileContinue){
            showMenu1();
            cout<<"Choose one (i.e. read file): ";
            getline(cin, choice);
            switch(stringToEnum(choice)){
                case CREATE_XOR:{
                    string aigName;
                    aig = new Aig();
                    cout << "Aig name: ";
                    cin >> aigName;
                    aig->setName(aigName);
                    aig->createInputs(2);
                    list<AigNode*> inputs = aig->getInputs();
                    list<AigNode*>::iterator inputIter = inputs.begin();
                    AigNode* a = *inputIter;
                    inputIter++;
                    AigNode* b = *inputIter;
                    AigNode* finalNode = aig->createXor(a,b);
                    aig->createOutputs(finalNode, false);
                    cout << "Xor2 created." << endl;
                    fileContinue = false;
                    continueAction = true;
                    break;
                }
                case READ_FILE:{
                    string fileName;
                    cout << "Relative path: ";
                    cin >> fileName;
                    AAGReader reader(fileName);
                    aig = reader.readFile();
                    fileContinue = false;
                    continueAction = true;
                    cout << "File " << fileName << " read." << endl;
                    break;
                }
                case EXIT:{
                    continueAction = false;
                    fileContinue = false;
                    outerContinue = false;
                }
                case INVALID:
                default:
                    cout << "Essa escolha não existe" << endl;
            }
            cin.sync();
        }
        cout << "Aig " << aig->getName() << " created." << endl;
        cin.ignore(256, '\n');
        while(continueAction){
            showMenu2();
            cout<<"Choose one: ";
            getline(cin, choice);
            switch(stringToEnum(choice)){
                case STATISTICS:{
                    aig->AIGStatistics();
                    break;
                }
                case SHOW:{
                    aig->showAIG();
                    break;
                }
                case BACK:{
                    continueAction = false;
                    fileContinue = true;
                    break;
                }
                case EXIT:{
                    outerContinue = false;
                    continueAction = false;
                    break;
                }
                case INVALID:
                default:
                    cout << "Essa escolha não existe" << endl;
            }
            cin.sync();
        }
    }
    return 0;
}

void showMenu1(){
    cout << "#############################################################" << endl;
    cout << "### \033[33mread file\033[0m: Read the aig from a file given by the user ###" << endl;
    cout << "### \033[33mcreate xor\033[0m: Create a xor                              ###" << endl;
    cout << "### \033[31mexit\033[0m: Exit the system                                 ###" << endl;
    cout << "#############################################################" << endl;
}

void showMenu2(){
    cout << "#############################################################" << endl;
    cout << "### \033[33mstatistics\033[0m: Display the critical path for each        ###" << endl;
    cout << "###             input-output pair and the critical path to###" << endl;
    cout << "###             the aig                                   ###" << endl;
    cout << "### \033[33mshow\033[0m: Show each node with the respectives inputs and  ###" << endl;
    cout << "###       outputs                                         ###" << endl;
    cout << "### \033[32mback\033[0m: Go back to the aig read part                    ###" << endl;
    cout << "### \033[31mexit\033[0m: Exit the system                                 ###" << endl;
    cout << "#############################################################" << endl;
}