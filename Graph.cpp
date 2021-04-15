#include "Graph.h"

Graph::Graph()
{
}

void Graph::addNode(QPoint pos)
{
    NodeInfo newNode;
    newNode.position = pos;
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

void Graph::setPos(QPoint pos, int nodeNum)
{
    QList<NodeInfo>::iterator iter = _nodeList.begin();
    for(int i = 0; i < nodeNum; i++)
        iter++;
    (*iter).position = pos;
}

QPoint Graph::getPos(int nodeNum)
{
    return _nodeList.at(nodeNum).position;
}

int Graph::nodeCount()
{
    return _nodeList.count();
}
