#include "EditZone.h"

EditZone::EditZone(QWidget *parent)
    : QWidget(parent), _scale(1), _radius(20), _selectedNode(-1), _isDragged(false)
{
    _mousePos.setX(0);
    _mousePos.setY(0);
}

EditZone::Action EditZone::getAction(QMouseEvent *event)
{
    _mousePos = event->pos();

    if(_isDragged)
        return dragNode;

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
        _addEdgeDialog = new AddEdgeDialog();
        if(_addEdgeDialog->exec() == QDialog::Accepted)
            _graph.addEdge(_selectedNode, getNodeIndex(), _addEdgeDialog->getWeight());
        if(_addEdgeDialog->isEdgeDeleted())
            _graph.removeEdge(_selectedNode, getNodeIndex());
        delete _addEdgeDialog;

        _graph.setState(Graph::stand, _selectedNode);
        _selectedNode = -1;
        break;
    }
    case deselectNode:
    {
        _graph.setState(Graph::stand, _selectedNode);
        _selectedNode = -1;
        break;
    }
    case dragNode:
    {
        break;
    }
    }

    update();
}

void EditZone::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && isNodePos())
    {
        int distance = (event->pos() - _mousePos).manhattanLength();
        if(distance > QApplication::startDragDistance())
        {
            _isDragged = true;
            _selectedNode = getNodeIndex();
            _graph.setState(Graph::selected, _selectedNode);
            update();

            setAcceptDrops(true);
            QMimeData* mimeData = new QMimeData;

            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->exec(Qt::MoveAction);
        }
    }
}

void EditZone::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void EditZone::dragMoveEvent(QDragMoveEvent *event)
{
    QPoint pos = event->position().toPoint();
    if(isCorrectDropPos(pos))
        _graph.setPos(pos, _selectedNode);
    update();
}

void EditZone::dropEvent(QDropEvent *event)
{
    _isDragged = false;
    _mousePos = event->position().toPoint();

    if(isCorrectPos())
        _graph.setPos(_mousePos, _selectedNode);

    _graph.setState(Graph::stand, _selectedNode);
    _selectedNode = -1;
    setAcceptDrops(false);

    update();
}

void EditZone::paintEvent(QPaintEvent*)
{
    for(int nodeOut = 0; nodeOut < _graph.nodeCount(); nodeOut++)
    {
        QList<Graph::AdjacencyListElement> edges = _graph.getEdges(nodeOut);
        for(int index = 0; index < edges.count(); index++)
        {
            int nodeIn = edges.at(index).nodeNum;
            drawEdge(nodeIn, nodeOut);
        }
        for(int index = 0; index < edges.count(); index++)
        {
            int nodeIn = edges.at(index).nodeNum;
            drawWeight(nodeIn, nodeOut);
        }
    }

    for(int index = 0; index < _graph.nodeCount(); index++)
        drawNode(index);
}

void EditZone::drawEdge(int nodeIn, int nodeOut)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    QPoint outPoint = _graph.getPos(nodeOut);
    QPoint inPoint = _graph.getPos(nodeIn);

    if(_graph.hasEdge(nodeIn, nodeOut))
        transformEdgePoints(inPoint, outPoint);

    painter.drawLine(outPoint, inPoint);
    drawArrow(inPoint, outPoint, _graph.getPos(nodeIn), painter);
}

void EditZone::drawArrow(QPoint inPoint, QPoint outPoint, QPoint centerPoint, QPainter& painter)
{
    QPoint arrowPoint = getArrowPoint(inPoint, outPoint, centerPoint);
    QPolygon arrow;
    arrow.append(QPoint(0, -1 * _radius/3));
    arrow.append(QPoint(-1 * _radius, 0));
    arrow.append(QPoint(0,  _radius/3));

    painter.save();
    painter.translate(arrowPoint);
    float angle = atan2f(outPoint.y() - inPoint.y(), outPoint.x() - inPoint.x());
    painter.rotate(180/3.14 * angle);
    painter.drawConvexPolygon(arrow);
    painter.restore();
}

void EditZone::drawWeight(int nodeIn, int nodeOut)
{
    QPoint outPoint = _graph.getPos(nodeOut);
    QPoint inPoint = _graph.getPos(nodeIn);

    if(_graph.hasEdge(nodeIn, nodeOut))
        transformEdgePoints(inPoint, outPoint);

    QString weight = QString::number(_graph.getWeight(nodeOut, nodeIn));
    int length = weight.length();

    QPoint textPoint = inPoint - outPoint;
    textPoint /= 2;

    if(nodeOut > nodeIn)
        textPoint += outPoint - QPoint(_radius * length / 4, _radius / 1.2);
    else
        textPoint += outPoint - QPoint(_radius * length / 4, -1 * _radius / 4);

    QPainter painter(this);
    painter.setPen(QWidget::palette().color(QWidget::backgroundRole()));
    painter.setBrush(QBrush(QWidget::palette().color(QWidget::backgroundRole())));

    QRect fontZone(textPoint, QSize(_radius * length / 2, _radius / 1.2));
    painter.drawRect(fontZone);

    QColor color;
    color.setRgb(142, 69, 133);
    painter.setPen(color);

    painter.setFont(QFont("Times", _radius / 1.2, QFont::Bold));
    painter.drawText(fontZone, Qt::AlignCenter | Qt::TextDontClip, weight);
}

void EditZone::drawNode(int nodeNum)
{
    QPoint nodePos = _graph.getPos(nodeNum);

    QPen pen;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    switch (_graph.getState(nodeNum))
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
    painter.drawText(fontZone, Qt::AlignCenter | Qt::TextDontClip, QString::number(nodeNum + 1));
}

void EditZone::transformEdgePoints(QPoint &inPoint, QPoint &outPoint)
{
    int nodeOut = getNodeIndex(&outPoint);
    int nodeIn = getNodeIndex(&inPoint);

    if(nodeOut > nodeIn)
    {
        if(abs(outPoint.x() - inPoint.x()) < abs(outPoint.y() - inPoint.y()))
        {
            outPoint.setX(outPoint.x() - _radius/3);
            inPoint.setX(inPoint.x() - _radius/3);
        }
        else
        {
            outPoint.setY(outPoint.y() - _radius/3);
            inPoint.setY(inPoint.y() - _radius/3);
        }
    }
    else
    {
        if(abs(outPoint.x() - inPoint.x()) < abs(outPoint.y() - inPoint.y()))
        {
            outPoint.setX(outPoint.x() + _radius/3);
            inPoint.setX(inPoint.x() + _radius/3);
        }
        else
        {
            outPoint.setY(outPoint.y() + _radius/3);
            inPoint.setY(inPoint.y() + _radius/3);
        }
    }
}

//Line - y = kx + b
QPoint EditZone::getArrowPoint(QPoint inPoint, QPoint outPoint, QPoint centerPoint)
{
    inPoint -= centerPoint;
    outPoint -= centerPoint;
    float k = ((float)inPoint.y() - outPoint.y())/(inPoint.x() - outPoint.x());
    float b = (float)inPoint.y() - k * inPoint.x();

    float x0 = (-1 * k * b) / (k * k + 1);
    float y0 = b / (k * k + 1);
    float d = sqrtf(4 * _radius * _radius - b * b / (k * k + 1));
    float mult = sqrtf(d * d / (k * k + 1));

    float ax = x0 - mult;
    float ay = y0 - k * mult;
    float bx = x0 + mult;
    float by = y0 + k * mult;

    if((outPoint - QPoint(ax, ay)).manhattanLength() < (outPoint - QPoint(bx, by)).manhattanLength())
        return QPoint(ax, ay) + centerPoint;
    return QPoint(bx, by) + centerPoint;
}

bool EditZone::isCorrectPos()
{
    for(int index = 0; index < _graph.nodeCount(); index++)
    {
        QPoint nodePos = _graph.getPos(index);

        if((_mousePos.x() < (nodePos.x() - 5.5 * _radius)) || (_mousePos.x() > (nodePos.x() + 5.5 * _radius)))
            continue;
        if((_mousePos.y() < (nodePos.y() - 5.5 * _radius)) || (_mousePos.y() > (nodePos.y() + 5.5 * _radius)))
            continue;
        return false;
    }
    return true;
}

bool EditZone::isCorrectDropPos(QPoint position)
{
    for(int i = 0; i < _graph.nodeCount(); i++)
    {
        QPoint nodePos = _graph.getPos(i);

        if(i == _selectedNode)
            continue;
        if((position.x() < (nodePos.x() - 5.5 * _radius)) || (position.x() > (nodePos.x() + 5.5 * _radius)))
            continue;
        if((position.y() < (nodePos.y() - 5.5 * _radius)) || (position.y() > (nodePos.y() + 5.5 * _radius)))
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

int EditZone::getNodeIndex(QPoint* position)
{
    for(int index = 0; index < _graph.nodeCount(); index++)
    {
        QPoint nodePos = _graph.getPos(index);
        if(position == nullptr)
            position = &_mousePos;

        if((position->x() >= nodePos.x() - _radius) && (position->x() <= nodePos.x() + _radius) &&
           (position->y() >= nodePos.y() - _radius) && (position->y() <= nodePos.y() + _radius))
        {
            return index;
        }
    }
    return -1;
}
