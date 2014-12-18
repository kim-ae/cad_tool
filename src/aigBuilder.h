#ifndef AIGBUILDER_H
#define AIGBUILDER_H
#include "aig.h"
#include <list>

class AigBuilder{
    public:
        static AigNode* buildAplusBC(Aig* aig, list<AigNode*> inputs);
        static AigNode* buildXor(Aig* aig, list<AigNode*> inputs);
        static AigNode* buildOr(Aig* aig, list<AigNode*> inputs);
};

#endif