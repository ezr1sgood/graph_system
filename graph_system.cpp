//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>
#define pi 3.14159265358979323846

using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 1000;
int Param::GRAPH_MAX_NUM_EDGES = 1000;

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    mFlgAutoNodeDeletion = false;
    createDefaultGraph();//
    
    //createNet_Circular(12,3);//
    //createNet_Square(11, 3);//
    //createNet_RadialCircular(24);//
    //createRandomGraph_DoubleCircles(24);
}

void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();
    Nodes.clear();
    Edges.clear();
    mNumofNodes = 0;
    mNumofEdges = 0;
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    reset( );
    //
    // Implement your own stuff
    //
    addNode(0.0, 0.0, 0.0, 1.0);
    addNode(0.0, 0.0, 5.0, 1.0);
    addNode(5.0, 0.0, 0.0, 1.0);

    addEdge(1, 2);
    addEdge(0, 2);
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );

    //
    // Implement your own stuff
    //
    for (int i = 0;i < n;i++) {

        float x1 = 10.0 * cos(2 * i * pi / n);
        float y1 = 0.0;
        float z1 = 10.0 * sin(2 * i * pi / n);
        float r1 = 1.0;
        float x2 = 20.0 * cos(2 * i * pi / n);
        float y2 = 0.0;
        float z2 = 20.0 * sin(2 * i * pi / n);
        float r2 = 1.0;

        addNode(x1, y1, z1, r1);
        addNode(x2, y2, z2, r2);
    }
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset( );

    for (int i = 0;i < n;i++) {

        for (int j = 1;j < 5;j++) {

            float x = 5.0 * j * cos(2 * i * pi / n);
            float y = 0.0;
            float z = 5.0 * j * sin(2 * i * pi / n);
            float r = 1.0;

            addNode(x, y, z, r);
        }
    }

    for (int i = 0;i < n;i++) {

        for (int j = 0;j < num_layers;j++) {

            addEdge(4 * i + j, 4 * i + j + 1);
        }
    }
    for (int i = 0;i < num_layers;i++) {

        for (int j = 0;j < n - 1;j++) {

            addEdge(4 * j + i, 4 * j + i + 4);
        }
        addEdge(4 * (n - 1) + i, 4 * 0 + i);
    }
}
void GRAPH_SYSTEM::createNet_Square( int n, int num_layers )
{
    reset( );

    //
    // Implement your own stuff
    //

    for (int i = 0;i < n;i++) {

        for (int j = 0;j < n;j++) {

            float x = i * 5;
            float y = 0.0;
            float z = j * 5;
            float r = 1.0;

            addNode(x, y, z, r);
        }
    }

    for (int i = 0;i < n;i++) {

        for (int j = 0;j < n;j++) {

            if (j != n - 1) {

                addEdge(n * i + j, n * i + j + 1);
            }
            if (i != n - 1) {

                addEdge(n * i + j, n * i + j + n);
            }
        }
    }

    int left = (n - num_layers) / 2;
    int right = left + num_layers - 1;
    for (int i = left;i <= right;i++) {

        for (int j = left;j <= right;j++) {

            deleteNode(n * i + j);
        }
    }
}

void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset( );

    //
    // Implement your own stuff
    //    

    addNode(0.0, 0.0, 0.0, 1.0);
    for (int i = 0;i < n;i++) {

        float x = 15.0 * cos(2 * i * pi / n);
        float y = 0.0;
        float z = 15.0 * sin(2 * i * pi / n);
        float r = 1.0;

        addNode(x, y, z, r);
    }

    for (int i = 1;i <= n;i++) {

        addEdge(0, i);
    }
}

// return node id
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    //
    // Implement your own stuff
    //  
    GRAPH_NODE node;

    node.p = vector3(x, y, z);
    node.id = mNumofNodes;
    node.r = r;
    node.dynamicID = mNumofNodes;

    Nodes.push_back(node);

 //   cout << Nodes.capacity() << endl;

    mNumofNodes++;

    return node.id;
}

// return edge id
int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    //
    // Implement your own stuff
    //  
    GRAPH_EDGE edge;

    edge.id = mNumofEdges;
    edge.nodeID[0] = nodeID_0;
    edge.nodeID[1] = nodeID_1;
    edge.dynamicID = mNumofEdges;

    Edges.push_back(edge);

    mNumofEdges++;

    return edge.id;
}

void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    // 
    cout << "Key usage:" << endl;
    cout << "1: create a default graph" << endl;
    cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontal y" << endl;
    cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
    cout << "4: create a graph with 10x10 ndoes. Creatta 10 randomly generated edges" << endl;
    cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << endl;
    cout << "Use the mouse to select nodes and add edges." << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << endl;
    cout << "A selected node is highlighted as red." << endl;
}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE* n = 0;
    //
    // Implement your own stuff
    // 
    for (int i = 0;i < mNumofNodes;i++) {

        if ((Nodes[i].p.x - x) * (Nodes[i].p.x - x) + (Nodes[i].p.z - z) * (Nodes[i].p.z - z) <= 1) {
            
            n = (GRAPH_NODE*)&Nodes[i];
            break;
        }
    }

    return n;
}

bool GRAPH_SYSTEM::edgebetweennodes(int node1, int node2) {

    for (int i = 0;i < Edges.size();i++) {
        
        if (Edges[i].nodeID[0] == node1 && Edges[i].nodeID[1] == node2) {

            return true;
        }
        if (Edges[i].nodeID[0] == node2 && Edges[i].nodeID[1] == node1) {

            return true;
        }
    }

    return false;
}
//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{
    //
    // Implement your own stuff
    // 
    GRAPH_NODE* node = mSelectedNode;
    
    for (int i = 0;i < mNumofNodes;i++) {

        if ((Nodes[i].p.x - x) * (Nodes[i].p.x - x) + (Nodes[i].p.z - z) * (Nodes[i].p.z - z) <= 1) {
            
            if (mSelectedNode == 0 && node != &Nodes[i]) {

                mSelectedNode = &Nodes[i];
            }
            else if (mSelectedNode != 0 && node != &Nodes[i] && !edgebetweennodes(node->id, Nodes[i].id)) {
                //check if there's an edge between nodes
                
                addEdge(node->id, Nodes[i].id);

                mSelectedNode = 0;
            }
            else {

                mSelectedNode = 0;
            }
            break;
        }
    }
    for (int i = 0;i < mNumofNodes;i++) {

        if (!((Nodes[i].p.x - x) * (Nodes[i].p.x - x) + (Nodes[i].p.z - z) * (Nodes[i].p.z - z) <= 1) && i == mNumofNodes - 1) {

            mSelectedNode = 0;
        }
        if ((Nodes[i].p.x - x) * (Nodes[i].p.x - x) + (Nodes[i].p.z - z) * (Nodes[i].p.z - z) <= 1) {

            break;
        }
    }
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    //
    // Implement your own stuff
    // 

    auto it = Nodes.begin();
    int tmp = 0;
    for (it = Nodes.begin();it != Nodes.end();it++) {

        if (it->id == nodeID) {

            theres_a_bug_but_i_dont_know_how_this_happened = true;
            break;
        }
    }
    Nodes.erase(it);
    vector<GRAPH_NODE>(Nodes).swap(Nodes);
    mNumofNodes--;
    //我不知道為甚麼會這樣 凸(OAO凸#)

    auto it_2 = Edges.begin();
    for (it_2 = Edges.begin();it_2 != Edges.end();it_2++) {

        if (it_2->nodeID[0] == nodeID || it_2->nodeID[1] == nodeID) {
            
            auto tmp = it_2;
            Edges.erase(tmp);
            it_2--;
            mNumofEdges--;
        }
    }
    vector<GRAPH_EDGE>(Edges).swap(Edges);
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    //
    // Implement your own stuff
    // 

    if (mSelectedNode) {

        deleteNode(mSelectedNode->id);
        mSelectedNode = 0;
    }

    return;
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    //
    // Implement your own stuff
    // 
    
    if (mSelectedNode) {

        return true;
    }

    return false;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
    r = mSelectedNode->r;
    p = mSelectedNode->p;
    //
    // Implement your own stuff
    // 
}



void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    
    switch( key ) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode( );
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        reset();
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        reset();
        createNet_Circular(12, 3);
        mSelectedNode = 0;

        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        reset();
        createNet_Square(11, 3); // you can modify this
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        reset();
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        reset();
        createRandomGraph_DoubleCircles(24);
        mSelectedNode = 0;

        break;

    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'g':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    
    if (n == 0) {

        mPassiveSelectedNode = 0;
        return;
    }
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    // 
    return mNumofNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    // 
    r = Nodes[nodeIndex].r;
    p = Nodes[nodeIndex].p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    // 
    return mNumofEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    vector3 p;
    //
    // Implement your own stuff
    //
    int tmp = 0;
    for (int i = 0;i < Nodes.size();i++) {

        if (Edges[edgeIndex].nodeID[nodeIndex] == Nodes[i].id) {

            p = Nodes[i].p;
            tmp = i;
        }
    }

    return p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update( )
{
    if (!mFlgAutoNodeDeletion) {
     
        return;
    }
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;

    Sleep(250);
    //
    //
    // Implement your own stuff
    // 
}
