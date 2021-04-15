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
