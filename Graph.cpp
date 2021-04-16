#include "Graph.h"

Graph::Graph()
{

}

void Graph::addNode(QPoint pos, NodeState state)
{
    NodeInfo newNode;
    newNode.position = pos;
    newNode.state = state;
    _nodeList.append(newNode);
}

void Graph::removeNode(int nodeNum)
{
    QList<NodeInfo>::iterator currentNode = _nodeList.begin();

    for(int i = 0; i < _nodeList.count(); i++, currentNode++)
    {
        if(i == nodeNum)
            continue;

        int deleteIndex = -1;
        QList<AdjacencyListElement>::iterator edge = currentNode->adjacencyList.begin();

        for(int j = 0; j < currentNode->adjacencyList.size(); j++)
        {
            if(edge->nodeNum == nodeNum)
                deleteIndex = j;
            if(edge->nodeNum > nodeNum)
                edge->nodeNum--;
            edge++;
        }

        if(deleteIndex != -1)
            currentNode->adjacencyList.removeAt(deleteIndex);
    }

    _nodeList.removeAt(nodeNum);
}

void Graph::addEdge(int nodeOut, int nodeIn, float weight)
{
    QList<NodeInfo>::iterator node = _nodeList.begin();
    for(int i = 0; i < nodeOut; i++)
        node++;

    QList<AdjacencyListElement>::iterator edge = node->adjacencyList.begin();
    for(int i = 0; i < node->adjacencyList.size(); i++)
        if(edge->nodeNum == nodeIn)
        {
            edge->weight = weight;
            return;
        }
    AdjacencyListElement newEdge;
    newEdge.nodeNum = nodeIn;
    newEdge.weight = weight;
    node->adjacencyList.append(newEdge);
}

QList<Graph::AdjacencyListElement> Graph::getEdges(int nodeNum)
{
    return _nodeList.at(nodeNum).adjacencyList;
}

bool Graph::hasEdge(int nodeOut, int nodeIn)
{
    QList<AdjacencyListElement> edgesList = _nodeList.at(nodeOut).adjacencyList;
    for(int i = 0; i < edgesList.count(); i++)
        if(edgesList.at(i).nodeNum == nodeIn)
            return true;
    return false;
}

void Graph::setPos(QPoint pos, int nodeNum)
{
    QList<NodeInfo>::iterator iter = _nodeList.begin();
    for(int i = 0; i < nodeNum; i++)
        iter++;
    iter->position = pos;
}

QPoint Graph::getPos(int nodeNum)
{
    return _nodeList.at(nodeNum).position;
}

int Graph::nodeCount()
{
    return _nodeList.count();
}

int Graph::edgeCount(int nodeNum)
{
    return _nodeList.at(nodeNum).adjacencyList.size();
}

void Graph::setState(NodeState state, int nodeNum)
{
    QList<NodeInfo>::iterator iter = _nodeList.begin();
    for(int i = 0; i < nodeNum; i++)
        iter++;
    iter->state = state;
}

Graph::NodeState Graph::getState(int nodeNum)
{
    return _nodeList.at(nodeNum).state;
}
