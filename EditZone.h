#pragma once
#include <QtWidgets>
#include "Graph.h"

class EditZone : public QWidget
{
    Q_OBJECT

private:
    QPoint _mousePos;
    float _scale;
    int _radius;

    Graph _graph;

    bool isCorrectPos();

public:
    EditZone(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};
