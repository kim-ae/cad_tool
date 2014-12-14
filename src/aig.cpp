//copyright Prof. Andre Reis - UFRGS


#include "aig.h"

//------------------AidNode------------------
void AigNode::setId(int id) {
    this->ID = id;
}

int AigNode::getId() {
    return this->ID;
}

//------------------AndNode------------------
AndNode::AndNode(){}

AigNodeType AndNode::getType(){
    return AND_NODE;
}

void AndNode::connectTo(AigNode * dest, int pin, int isInverted){
    this->fanOut.push_back(dest);
    this->invertedFanout.push_back(isInverted);

    dest->setFanIn(pin,this,isInverted);
}

AigNode* AndNode::getFanIn(int index){
    if(index == 0) return this->in0;
    else if(index == 1) return this->in1;
    else {
        cout << "Index out of bounds!";
        return NULL;
    }
}

bool AndNode::getInvertedFanIn(int index){
    if(index == 0) return this->in0Inverted;
    else if(index == 1) return this->in1Inverted;
    else {
        cout << "Index out of bounds!";
        return -1;
    }
}

vector<AigNode*> AndNode::getFanOut(){
    return this->fanOut;
}

vector<bool> AndNode::getInvertedFanOut(){
    return this->invertedFanout;
}

void AndNode::setFanIn(int index, AigNode * node, bool isInverted){
    if(index == 0){
        this->in0 = node;
        this->in0Inverted = isInverted;
    }
    else if(index == 1){
        this->in1 = node;
        this->in1Inverted = isInverted;
    }
    else {
        cout << "Index out of bounds!";
    }
}

//------------------InputNode------------------
InputNode::InputNode(){}

void InputNode::setName(string newName){
    this->name = newName;
}

string InputNode::getName(){
    return this->name;
}

AigNodeType InputNode::getType(){
    return INPUT_NODE;
}

void InputNode::connectTo(AigNode * dest, int pin, int isInverted){
    this->fanOut.push_back(dest);
    this->invertedFanout.push_back(isInverted);

    dest->setFanIn(pin,this,isInverted);
}

AigNode* InputNode::getFanIn(int){
    cout << "Wrong type of node! InputNode can not getFanIn";
    return NULL;
}

bool InputNode::getInvertedFanIn(int){
    cout << "Wrong type of node! InputNode can not setFanIn";
    return NULL;
}

vector<AigNode*> InputNode::getFanOut(){
    return this->fanOut;
}

vector<bool> InputNode::getInvertedFanOut(){
    return this->invertedFanout;
}

void InputNode::setFanIn(int, AigNode *, bool){
    cout << "Wrong type of node! InputNode can not setFanIn";
}

//------------------OutputNode------------------

OutputNode::OutputNode(){}

void OutputNode::setName(string newName){
    this->name = newName;
}

string OutputNode::getName(){
    return this->name;
}

AigNodeType OutputNode::getType(){
    return OUTPUT_NODE;
}

void OutputNode::connectTo(AigNode*, int, int){
    cout << "Wrong type of node! OutputNode can not connectTo";
}

AigNode* OutputNode::getFanIn(int index){
    if(index != 0){
        cout << "Index out of bounds!";
        return NULL;
    }
    else{
        return this->in0;
    }
}

bool OutputNode::getInvertedFanIn(int index){
    if(index != 0){
        cout << "Index out of bounds!";
        return NULL;
    }
    else{
        return this->in0Inverted;
    }
}

vector<AigNode*> OutputNode::getFanOut(){
    cout << "Wrong type of node! OutputNode has not FanOut";
    return vector<AigNode*>();
}

vector<bool> OutputNode::getInvertedFanOut(){
    cout << "Wrong type of node! OutputNode has not FanOut";
    return vector<bool>();
}

void OutputNode::setFanIn(int index, AigNode * node, bool isInverted){
    if(index != 0) cout << "Index out of bounds!";
    else{
        this->in0 = node;
        this->in0Inverted = isInverted;
    }
}

//------------------AIG------------------

Aig::Aig(){

}

string Aig::getName(){
    return this->name;
}

list<AigNode*> Aig::getInputs(){
    return this->inputs;
}

list<AigNode*> Aig::getOutputs(){
    return this->outputs;
}

list<AigNode*> Aig::getNodes(){
    return this->nodes;
}

void Aig::insertNode(AigNode* node) {
    nodes.push_back(node);
}

void Aig::insertInputNode(AigNode* inputNode) {
    inputs.push_back(inputNode);
}

void Aig::insertOutputNode(AigNode* outputNode) {
    outputs.push_back(outputNode);
}

void Aig::setName(string newName){
    this->name = newName;
}

void Aig::showAIG(){
    string indentation = "    ";
    for(AigNode* node : this->getNodes()){
        switch(node->getType()){
            case INPUT_NODE:{
                InputNode* input = (InputNode*) node;
                vector<AigNode*> fanOuts = input->getFanOut();
                vector<bool> invertedFanOuts = input->getInvertedFanOut();
                int i = 0;
                cout << "\033[31mInput Node " << input->getName() << "(" << input->getId() <<") \033[0m\n";
                cout << " -> Conect to: \n";
                for(AigNode* fanOutNode : fanOuts){
                    cout << indentation << "Node " << fanOutNode->getId() << (invertedFanOuts[i] ? " is" : " inst") << " inverted of type " << AigNodeTypeString[fanOutNode->getType()] <<"\n";
                    i++;
                }
                break;
            }
            case AND_NODE:{
                AndNode* andNode = (AndNode*) node;
                cout << "\033[32mAnd Node " << andNode->getId() << "\033[0m\n";
                cout << "-> Inputs:\n";
                cout << indentation << andNode->getFanIn(0)->getId() << (andNode->getInvertedFanIn(0) ? " is" : " inst") << " inverted of type " << AigNodeTypeString[andNode->getFanIn(0)->getType()] <<"\n";
                cout << indentation << andNode->getFanIn(1)->getId() << (andNode->getInvertedFanIn(1) ? " is" : " inst") << " inverted of type " << AigNodeTypeString[andNode->getFanIn(1)->getType()] <<"\n";
                cout << "-> Connect to:\n";
                vector<AigNode*> fanOuts = andNode->getFanOut();
                vector<bool> invertedFanOuts = andNode->getInvertedFanOut();
                int i = 0;
                for(AigNode* fanOutNode : fanOuts){
                    cout << indentation << "Node " << fanOutNode->getId() << (invertedFanOuts[i] ? " is" : " inst") << " inverted of type " << AigNodeTypeString[fanOutNode->getType()] <<"\n";
                    i++;
                }
                break;
            }
            case OUTPUT_NODE:{
                OutputNode* output = (OutputNode*) node;
                cout << "\033[33mOutput Node " << output->getName()<<" ("<<output->getId() << ")\033[0m\n";
                cout << "-> Inputs:\n";
                cout << indentation << output->getFanIn(0)->getId() << (output->getInvertedFanIn(0) ? " is" : " inst") << " inverted of type " << AigNodeTypeString[output->getFanIn(0)->getType()] <<"\n";
            }
        }
    }
}