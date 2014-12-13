#include "aagReader.h"
#include <string.h>
#include <string>
#include <list>
/** \brief Class used to read a file
 *
 * \param sourcePath string
 *
 */
AAGReader::AAGReader(string sourcePath)
{
    this->source.open(sourcePath.c_str());
    if(!this->source.is_open()){
        cout << "Can't find the file " << sourcePath << '\n';
        cout << "Please check the path."<< '\n';
        exit(-1);
    }
    this->debug.open("debugFile.txt");
}

Aig* AAGReader::readFile()
{
    Aig *aig = new Aig();
    aig->setName("C17");
    //treating header
    source.getline(this->buf, 250, '\n');
    istringstream line;
    string s = this->buf;
    int nodesCounter = 0;
    line.str(s);
    line >> word;

    if(strcmp("aag",word.c_str())!=0)
    {
        cout << "the file is not an AAG file!";
        return NULL;
    }

    int nNodes, nInputs, nFFs, nOutputs, nAnds;
    line >> word;
    nNodes = atoi(word.c_str());
    line >> word;
    nInputs = atoi(word.c_str());
    line >> word;
    nFFs = atoi(word.c_str());
    line >> word;
    nOutputs = atoi(word.c_str());
    line >> word;
    nAnds = atoi(word.c_str());

    if (nNodes != nInputs + nFFs + nAnds) {
        cout << "Wrong file header";
        return NULL;
    }

    if (nFFs != 0) {
        cout << "FF not supported yet";
        return NULL;
    }

    debug << s << "\nThe file header is ok!\n\n";

    AigNode** nodes = new AigNode*[nNodes+1];
    OutputNode* outputs = new OutputNode[nOutputs];
    InputNode* inputs = new InputNode[nInputs];
    AndNode * ands = new AndNode[nAnds];
    stringstream convertoToString;
    //treating inputs
    for (int i = 0; i < nInputs; i++, nodesCounter++) {
        source.getline(this->buf, 250, '\n');
        inputs[i].setId(atoi(this->buf));
        string name ("i" + to_string(i));
        inputs[i].setName(name);
        nodes[nodesCounter] = &inputs[i];
        debug << "read the input" << i << " from the file " << inputs[i].getName() << "\n";
        debug << "   create in" << i << " and add it to an input list and the all nodes list\n";
    }

    //treating outputs
    debug << "\n";
    for (int i = 0; i < nOutputs; i++, nodesCounter++) {
        source.getline(this->buf, 250, '\n');
        outputs[i].setId(atoi(this->buf));
        string name("o" + to_string(i));
        outputs[i].setName(name);
        nodes[nodesCounter] = &outputs[i];
        debug << "read the output" << i << " from the file " <<outputs[i].getName() << "\n";
        debug << "   create out" << i << " and add it to an output list and the all nodes list\n";
    }

    //connecting ands
    debug << "\n";
    for (int i = 0; i < nAnds; i++, nodesCounter++) {
        source.getline(this->buf, 250, '\n');
        istringstream line;
        string s = this->buf;
        line.str(s);
        line >> word;
        int id = atoi(word.c_str());
        line >> word;
        int in0 = atoi(word.c_str());
        line >> word;
        int in1 = atoi(word.c_str());
        AigNode* node1 = findById(in0, nodes, nNodes+1);
        AigNode* node2 = findById(in1, nodes, nNodes+1);
        ands[i].setFanIn(0,node1 ,this->invertion(in0));
        ands[i].setFanIn(1,node2 ,this->invertion(in1));
        ands[i].setId(id);
        node1->connectTo(&ands[i], 0, this->invertion(in0));
        node2->connectTo(&ands[i], 1, this->invertion(in1));
        nodes[nodesCounter] = &ands[i];
        debug << "read the and" << i << " output and inputs\n";
        debug << "   connect the and" << i << " and set the inversion of this pins\n";
    }
    debug << "\n";
    string aigName;
    while(source)
    {
        source.getline(buf, 250, '\n');
        s=buf;
        istringstream line;
        line.seekg(0);
        line.str(s);
        line >> word;
        if(strcmp("c",word.substr(0).c_str())==0){
            debug << "the comments began. Ignore the file from here!\n";
            break;
        } else if(strcmp(word.substr(0).c_str(),"i")==0){

        } else if(strcmp(word.substr(0).c_str(),"o")==0){

        } else if(strcmp(word.substr(0).c_str(),"l")==0){

        }
    }

    debug << "\ncreate the AIG and add all nodes\n";
    debug << "return the AIG";

    for(int i =0; i<nNodes + nOutputs;i++) {
    	debug << "\n";
        aig->insertNode(nodes[i]);
        switch(nodes[i]->getType()){
            case INPUT_NODE: aig->insertInputNode(nodes[i]);
                break;
            case OUTPUT_NODE: aig->insertOutputNode(nodes[i]);
                break;
        }
    }
    return aig;
}

int AAGReader::invertion(int number){
    return number % 2 == 0 ? 0 : 1;
}

AigNode* AAGReader::findById(int id, AigNode** nodes , int aigSize){

    if(this->invertion(id)){
        id -= 1;
    }

    for(int i = 0; i < aigSize ; i++){
        if(nodes[i]->getId() == id){
            return nodes[i];
        }
    }
    debug << "Err finding id " << id << "\n";
    cout << "Err finding id " << id << "\n";
    exit(-1);
}
