#include "GraphEditor.h"

GraphEditor::GraphEditor(QWidget *parent) : QWidget(parent)
{
    _directed = new QCheckBox("Directed");
    _weighted = new QCheckBox("Weighted");

    QGroupBox* propertiesFrame = new QGroupBox("Properties");
    QVBoxLayout* propLayout = new QVBoxLayout;
    propLayout->addWidget(_directed);
    propLayout->addWidget(_weighted);
    propertiesFrame->setLayout(propLayout);

    QGroupBox* operationFrame = new QGroupBox("Operation");

    QStringList operationList;
    operationList << "Depth-First search" << "Breath-First search" << "Dijkstra's algorithm" << "Bellman-Ford algorithm"
                  << "A* algorithm";
    _operation = new QComboBox();
    _operation->addItems(operationList);
    QPushButton* okBtn = new QPushButton("Calculate");
    QVBoxLayout* operLayout = new QVBoxLayout();
    operLayout->addWidget(_operation);
    operLayout->addWidget(okBtn);
    operationFrame->setLayout(operLayout);

    QVBoxLayout* manipLayout = new QVBoxLayout();
    manipLayout->addWidget(propertiesFrame);
    manipLayout->addWidget(operationFrame);

    _editZone = new EditZone();
    QScrollArea* editArea = new QScrollArea();
    editArea->setWidget(_editZone);
    editArea->setWidgetResizable(true);

    QHBoxLayout* finalLayout = new QHBoxLayout();
    finalLayout->addLayout(manipLayout, 1);
    finalLayout->addWidget(editArea, 4);
    setLayout(finalLayout);

    resize(500, 250);
}
