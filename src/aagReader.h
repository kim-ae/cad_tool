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
        int nodesCounter;
        int nNodes;
        int nInputs;
        int nFFs;
        int nOutputs;
        int nAnds;
        ifstream source;
        ofstream debug;
        string aigName;
        string word;
        char buf[250];
        bool isInverted(int number);
        AigNode* findById(int id, AigNode** nodes, int aigSize);
        vector<AigNode*> findByType(AigNodeType type, AigNode** nodes, int aigSize);
        AigNode* findByName(string name, AigNode** nodes, int aigSize);
        void connectAnds(AigNode** nodes);
        bool invertion(int number);

    public:
        AAGReader(string sourcePath);
        Aig* readFile();
};

#endif // AAGREADER_H
