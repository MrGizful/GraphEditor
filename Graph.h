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

private:
    QList<NodeInfo> _nodeList;

public:
    Graph();

    void addNode(QPoint pos, NodeState state = stand);
    void removeNode(int nodeNum);

    void addEdge(int nodeOut, int nodeIn, float weight);
    void removeEdge(int nodeOut, int nodeIn);
    QList<AdjacencyListElement> getEdges(int nodeNum);
    bool hasEdge(int nodeOut, int nodeIn);

    float getWeight(int nodeOut, int nodeIn);

    void setPos(QPoint pos, int nodeNum);
    QPoint getPos(int nodeNum);

    void setState(NodeState state, int nodeNum);
    NodeState getState(int nodeNum);

    int nodeCount();
    int edgeCount(int nodeNum);
};
