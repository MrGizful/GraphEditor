#pragma once
#include <QtWidgets>

class EditZone : public QWidget
{
    Q_OBJECT

private:
    QPoint _mousePos;
    float _scale;
    int _radius;

    QList<QPoint> _nodeList;

    bool isCorrectPos();

public:
    EditZone(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};
