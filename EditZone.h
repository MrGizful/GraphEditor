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
        deselectNode,
        dragNode
    };

private:
    QPoint _mousePos;
    float _scale;
    int _radius;
    int _selectedNode;
    bool _isDragged;

    Graph _graph;
    AddEdgeDialog* _addEdgeDialog;

    Action getAction(QMouseEvent* event);
    QPoint getArrowPoint(QPoint inPoint, QPoint outPoint, QPoint centerPoint);
    void transformEdgePoints(QPoint& inPoint, QPoint& outPoint);
    bool isCorrectPos();
    bool isCorrectDropPos(QPoint position);
    bool isNodePos();
    int getNodeIndex(QPoint* position = nullptr);

    QSize getNewWidgetSize();

    void drawEdge(int nodeIn, int nodeOut);
    void drawArrow(QPoint inPoint, QPoint outPoint, QPoint centerPoint, QPainter& painter);
    void drawWeight(int nodeIn, int nodeOut);
    void drawNode(int nodeNum);

public:
    EditZone(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dropEvent(QDropEvent* event);
};
