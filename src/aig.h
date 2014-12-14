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
#include "path.h"

using namespace std;
/// Ebnumerator used to represents each of possible nodes in AIG.
typedef enum {
    AND_NODE, ///< and node code "0"
    INPUT_NODE, ///< input node code "1"
    OUTPUT_NODE ///< output node code "2"
} AigNodeType;

static const char* AigNodeTypeString[] = {"AND", "INPUT", "OUTPUT"};

/**
 * \brief Aig general class.
 * AIG node, can represent any of the 3 node types.
 */
class AigNode {
    private:
        int ID; /**< Identification to the node, according to the input file.*/
    public:
        virtual AigNodeType getType() = 0;
        virtual void connectTo(AigNode*, int, int) = 0;
        virtual AigNode* getFanIn(int) = 0;
        virtual bool getInvertedFanIn(int) = 0;
        virtual vector<AigNode*> getFanOut() = 0;
        virtual vector<bool> getInvertedFanOut() = 0;
        virtual void setFanIn(int, AigNode*, bool) = 0;
        void setId(int id);
        int getId();
};

/**
* \brief And node class.
* And specific class.
*/
class AndNode:public AigNode {
    private:
        AigNode* in0;
        AigNode* in1;
        bool in0Inverted;
        bool in1Inverted;
        vector<AigNode*> fanOut;
        vector<bool> invertedFanout;
        //precisa de referência para as saídas do nodo (uma lista, talvez)?

    public:
        AndNode();
        AigNodeType getType();
        void connectTo(AigNode*, int, int);
        AigNode* getFanIn(int);
        bool getInvertedFanIn(int);
        vector<AigNode*> getFanOut();
        vector<bool> getInvertedFanOut();
        void setFanIn(int, AigNode*, bool);
        //void imprime(ostream& saida);
};


/** \brief Blablabla
 */
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
        /** \brief
         *
         * \param AigNode* adsdasd
         * \param int asdasdas
         * \param int asdasda
         * \return void asdasdasdad
         *
         */
        int getFanOutSize();
        void connectTo(AigNode*, int, int);
        AigNode* getFanIn(int);
        bool getInvertedFanIn(int);
        vector<AigNode*> getFanOut();
        vector<bool> getInvertedFanOut();
        void setFanIn(int, AigNode*, bool);
        //void imprime(ostream& saida);
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
        void connectTo(AigNode*, int, int);
        AigNode* getFanIn(int);
        bool getInvertedFanIn(int);
        vector<AigNode*> getFanOut();
        vector<bool> getInvertedFanOut();
        /**
        * set`s the connection from a node to this node.
        * \param
        */
        void setFanIn(int, AigNode*, bool);
        //void imprime(ostream& saida);
};



class Aig {
    private:
        string name;
        list<AigNode*> nodes; //deve conter todos os nodos (and, entradas e saídas)
        list<AigNode*> inputs; //deve conter todas as entradas
        list<AigNode*> outputs; //deve conter todas as saidas
        list<int> maxDepth(AigNode* node, list<int> depth);
        Path* maxDepth(AigNode* node, Path currentDepth);
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
};


#endif