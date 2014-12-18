#include "aigBuilder.h"

AigNode* AigBuilder::buildAplusBC(Aig* aig, list<AigNode*> inputs){
    list<AigNode*>::iterator inputIter = inputs.begin();
    AigNode* a = *inputIter;
    inputIter++;
    AigNode* b = *inputIter;
    inputIter++;
    AigNode* c = *inputIter;
    AigNode* node1 = aig->createAnd(b,c,false,false);
    list<AigNode*> orInputList;
    orInputList.push_back(a);
    orInputList.push_back(node1);
    AigNode* orNode = buildOr(aig, orInputList);
    return orNode;
}

AigNode* AigBuilder::buildXor(Aig* aig, list<AigNode*> inputs){
    list<AigNode*>::iterator inputIter = inputs.begin();
    AigNode* a = *inputIter;
    inputIter++;
    AigNode* b = *inputIter;
    AigNode* node1 = aig->createAnd(a, b, false, false);
    AigNode* orNode = buildOr(aig, inputs);
    AndNode* orNodeCast = (AndNode*) orNode;
    bool isOrInverted = orNodeCast->isNaturalInverted();
    AigNode* node3 = aig->createAnd(node1, orNode, true, isOrInverted);
    return node3;
}

AigNode* AigBuilder::buildOr(Aig* aig, list<AigNode*> inputs){
    list<AigNode*>::iterator inputIter = inputs.begin();
    AigNode* a = *inputIter;
    inputIter++;
    AigNode* b = *inputIter;
    AigNode* node1 = aig->createAnd(a,b,true,true);
    AndNode* node1Cast = (AndNode*) node1;
    node1Cast->setNaturalInverted(true);
    return node1;
}