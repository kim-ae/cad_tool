#ifndef AIG_H
#define AIG_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <list>

using namespace std;

typedef enum {
    AND_NODE,
    INPUT_NODE,
    OUTPUT_NODE
} AigNodeType;

static const char* AigNodeTypeString[] = {"AND", "INPUT", "OUTPUT"};

class AigNode {
    private:
        int ID;
    public:
        virtual AigNodeType getType() = 0;
        virtual void connectTo(AigNode*, int, bool) = 0;
        virtual AigNode* getFanIn(int) = 0;
        virtual bool getInvertedFanIn(int) = 0;
        virtual vector<AigNode*> getFanOut() = 0;
        virtual vector<bool> getInvertedFanOut() = 0;
        virtual void setFanIn(int, AigNode*, bool) = 0;
        void setId(int id);
        int getId();
};

class AndNode:public AigNode {
    private:
        AigNode* in0;
        AigNode* in1;
        bool in0Inverted;
        bool in1Inverted;
        vector<AigNode*> fanOut;
        bool naturalInverted;
        vector<bool> invertedFanout;


    public:
        AndNode();
        AigNodeType getType();
        void connectTo(AigNode*, int, bool);
        AigNode* getFanIn(int);
        bool getInvertedFanIn(int);
        vector<AigNode*> getFanOut();
        vector<bool> getInvertedFanOut();
        bool isNaturalInverted();
        void setNaturalInverted(bool);
        void setFanIn(int, AigNode*, bool);

};

class InputNode:public AigNode {
    private:
        string name;
        vector<AigNode*> fanOut;
        vector<bool> invertedFanout;

    public:
        InputNode();
        void setName(string);
        string getName();
        AigNodeType getType();
        int getFanOutSize();
        void connectTo(AigNode*, int, bool);
        AigNode* getFanIn(int);
        bool getInvertedFanIn(int);
        vector<AigNode*> getFanOut();
        vector<bool> getInvertedFanOut();
        void setFanIn(int, AigNode*, bool);
};

class OutputNode:public AigNode {
    private:
        AigNode* in0;
        bool in0Inverted;
        string name;

    public:
        OutputNode();
        void setName(string);
        string getName();
        AigNodeType getType();
        void connectTo(AigNode*, int, bool);
        AigNode* getFanIn(int);
        bool getInvertedFanIn(int);
        vector<AigNode*> getFanOut();
        vector<bool> getInvertedFanOut();
        void setFanIn(int, AigNode*, bool);
};



class Aig {
    private:
        string name;
        int idCounter;
        list<AigNode*> nodes;
        list<AigNode*> inputs;
        list<AigNode*> outputs;
        list<int> maxDepth(AigNode* node, list<int> depth);
        void printCriticalPath(list<int>);

    public:
        Aig();
        string getName();
        list<AigNode*> getInputs();
        list<AigNode*> getOutputs();
        list<AigNode*> getNodes();
        void insertNode(AigNode*);
        void insertInputNode(AigNode*);
        void insertOutputNode(AigNode*);
        void setName(string);
        void showAIG();
        void AIGStatistics();
        void createInputs(int quantity);
        AigNode* createOutputs(AigNode*, bool);
        int getIdCounter();
        AigNode* createAnd(AigNode* input1, AigNode* Input2, bool invertion0, bool invertion1);

};


#endif