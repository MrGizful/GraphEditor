#pragma once
#include <QPoint>
#include <QList>

class Graph
{
public:
    enum NodeState
    {
        stand = 0,
        selected
    };

private:
    struct AdjacencyListElement
    {
        int nodeNum;
        float weight;
    };

    struct NodeInfo
    {
        NodeState state;
        QPoint position;
        QList<AdjacencyListElement> adjacencyList;
    };

    QList<NodeInfo> _nodeList;

public:
    Graph();

    void addNode(QPoint pos, NodeState state = stand);
    void removeNode(int nodeNum);
    void addEdge(int nodeOut, int nodeIn, float weight);
    void setPos(QPoint pos, int nodeNum);
    QPoint getPos(int nodeNum);
    void setState(NodeState state, int nodeNum);
    NodeState getState(int nodeNum);
    int nodeCount();
};
