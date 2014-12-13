#ifndef AAGREADER_H
#define AAGREADER_H
#include "aig.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

class AAGReader
{
    private:
        ifstream source;
        ofstream debug;
        string word;
        char buf[250];
        bool isInverted(int number);
        AigNode* findById(int id, AigNode** nodes, int aigSize);
        vector<AigNode*> findByType(AigNodeType type, AigNode** nodes, int aigSize);

    public:
        int invertion(int number);
        AAGReader(string sourcePath);
        Aig* readFile();
};

#endif // AAGREADER_H
