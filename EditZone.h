#pragma once
#include <QtWidgets>
#include "Graph.h"
#include "AddEdgeDialog.h"

class EditZone : public QWidget
{
    Q_OBJECT
public:
    enum Action
    {
        nothing,
        createNewNode,
        deleteNode,
        selectFirstNode,
        selectSecondNode,
        deselectNode
    };

private:
    QPoint _mousePos;
    float _scale;
    int _radius;
    int _selectedNode;

    Graph _graph;
    AddEdgeDialog* _addEdgeDialog;

    Action getAction(QMouseEvent* event);
    QPoint getArrowPoint(QPoint inPoint, QPoint outPoint, QPoint centerPoint);
    void transformEdgePoints(QPoint& inPoint, QPoint& outPoint);
    bool isCorrectPos();
    bool isNodePos();
    int getNodeIndex(QPoint* position = nullptr);

    void drawEdge(int nodeIn, int nodeOut);
    void drawArrow(QPoint inPoint, QPoint outPoint, QPoint centerPoint, QPainter& painter);
    void drawWeight(int nodeIn, int nodeOut);
    void drawNode(int nodeNum);

public:
    EditZone(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};
