#pragma once
#include <QtWidgets>
#include "Graph.h"

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

    Action getAction(QMouseEvent* event);
    bool isCorrectPos();
    bool isNodePos();
    int getNodeIndex();

public:
    EditZone(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};
