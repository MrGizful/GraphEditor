#include "EditZone.h"

EditZone::EditZone(QWidget *parent)
    : QWidget(parent), _scale(1), _radius(20), _selectedNode(-1)
{
    _mousePos.setX(0);
    _mousePos.setY(0);
}

EditZone::Action EditZone::getAction(QMouseEvent *event)
{
    _mousePos = event->pos();

    if(event->button() == Qt::LeftButton)
    {
        if(_selectedNode == -1)
        {
            if(isNodePos())
                return selectFirstNode;
            if(isCorrectPos())
                return createNewNode;
            return nothing;
        }
        else
        {
            if(isNodePos())
            {
                if(getNodeIndex() == _selectedNode)
                    return deselectNode;
                return selectSecondNode;
            }
            return nothing;
        }
    }
    if(event->button() == Qt::RightButton)
    {
        if(_selectedNode == -1)
        {
            if(isNodePos())
                return deleteNode;
            return nothing;
        }
        else
        {
            return deselectNode;
        }
    }
    return nothing;
}

void EditZone::mousePressEvent(QMouseEvent *event)
{
    switch (getAction(event))
    {
    case nothing:
        break;
    case createNewNode:
    {
        _graph.addNode(_mousePos);
        break;
    }
    case deleteNode:
    {
        _graph.removeNode(getNodeIndex());
        break;
    }
    case selectFirstNode:
    {
        _selectedNode = getNodeIndex();
        _graph.setState(Graph::selected, _selectedNode);
        break;
    }
    case selectSecondNode:
    {
        //ToDo
        break;
    }
    case deselectNode:
    {
        _graph.setState(Graph::stand, _selectedNode);
        _selectedNode = -1;
        break;
    }
    }

    update();
}

void EditZone::paintEvent(QPaintEvent*)
{
    for(int index = 0; index < _graph.nodeCount(); index++)
    {
        QPoint nodePos = _graph.getPos(index);

        QPen pen;
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        switch (_graph.getState(index))
        {
        case Graph::stand:
        {
            pen.setColor(Qt::gray);
            brush.setColor(Qt::gray);
            break;
        }
        case Graph::selected:
        {
            QColor color;
            color.setRgb(48, 182, 235);
            pen.setColor(color);
            brush.setColor(color);
            break;
        }
        }

        QPainter painter(this);
        painter.setPen(pen);
        painter.setBrush(brush);
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

bool EditZone::isNodePos()
{
    for(int index = 0; index < _graph.nodeCount(); index++)
    {
        QPoint nodePos = _graph.getPos(index);

        if((_mousePos.x() >= nodePos.x() - _radius) && (_mousePos.x() <= nodePos.x() + _radius) &&
           (_mousePos.y() >= nodePos.y() - _radius) && (_mousePos.y() <= nodePos.y() + _radius))
        {
            return true;
        }
    }
    return false;
}

int EditZone::getNodeIndex()
{
    for(int index = 0; index < _graph.nodeCount(); index++)
    {
        QPoint nodePos = _graph.getPos(index);

        if((_mousePos.x() >= nodePos.x() - _radius) && (_mousePos.x() <= nodePos.x() + _radius) &&
           (_mousePos.y() >= nodePos.y() - _radius) && (_mousePos.y() <= nodePos.y() + _radius))
        {
            return index;
        }
    }
    return -1;
}
