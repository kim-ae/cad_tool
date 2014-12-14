#include <cstdlib>
#include <list>
#include "aagReader.h"

using namespace std;
typedef enum{
    STATISTICS,
    SHOW,
    EXIT,
    INVALID
}options;

options stringToEnum(string option){
    if(option == "statistics") return STATISTICS;
    if(option == "show") return SHOW;
    if(option == "exit") return EXIT;
    return INVALID;
}

int main(int argc, char** argv)
{

    if(argc == 0){
        cout<< "forneća o nome do arquivo."<<endl;
        exit(-1);
    }
    AAGReader reader(argv[1]);
    Aig* aig = reader.readFile();
    cout << aig->getName()<<endl;
    bool continue_ = true;
    string choice;
    while(continue_){
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
            case EXIT:{
                continue_ = false;
                break;
            }
            case INVALID:
            default:
                cout << "Essa escolha não existe" << endl;
        }
        cin.sync();
    }

    return 0;
}
