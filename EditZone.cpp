#include "EditZone.h"

EditZone::EditZone(QWidget *parent)
    : QWidget(parent), _scale(1), _radius(20)
{
    _mousePos.setX(0);
    _mousePos.setY(0);
}

void EditZone::mousePressEvent(QMouseEvent *event)
{
    _mousePos = event->pos();

    if(event->button() == Qt::LeftButton)
    {
        if(isCorrectPos())
            _graph.addNode(_mousePos);
    }
    update();
}

void EditZone::paintEvent(QPaintEvent*)
{
    for(int index = 0; index < _graph.nodeCount(); index++)
    {
        QPoint nodePos = _graph.getPos(index);

        QPainter painter(this);
        painter.setPen(Qt::gray);
        painter.setBrush(QBrush(Qt::gray));
        painter.drawEllipse(nodePos.x() - _radius, nodePos.y() - _radius, 2 * _radius, 2 * _radius);

        painter.setFont(QFont("Times", _radius, QFont::Bold));
        painter.setPen(Qt::black);
        QRect fontZone(nodePos.x() - _radius, nodePos.y() - _radius/2, 2 * _radius, _radius);
        painter.drawText(fontZone, Qt::AlignCenter | Qt::TextDontClip, QString::number(index + 1));
    }
}

bool EditZone::isCorrectPos()
{
    for(int index = 0; index < _graph.nodeCount(); index++)
    {
        QPoint nodePos = _graph.getPos(index);

        if((_mousePos.x() < (nodePos.x() - 3 * _radius)) || (_mousePos.x() > (nodePos.x() + 3 * _radius)))
            continue;
        if((_mousePos.y() < (nodePos.y() - 3 * _radius)) || (_mousePos.y() > (nodePos.y() + 3 * _radius)))
            continue;
        return false;
    }
    return true;
}
