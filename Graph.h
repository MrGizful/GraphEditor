#pragma once
#include <QPoint>
#include <QList>

class Graph
{
private:
    struct AdjacencyListElement
    {
        int nodeNum;
        float weight;
    };

    struct NodeInfo
    {
        QPoint position;
        QList<AdjacencyListElement> adjencyList;
    };

    QList<NodeInfo> _nodeList;

public:
    Graph();

    void addNode(QPoint pos);
    void setPos(QPoint pos, int nodeNum);
    QPoint getPos(int nodeNum);
    int nodeCount();
};
