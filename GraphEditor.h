#pragma once
#include <QWidget>
#include "EditZone.h"

class GraphEditor : public QWidget
{
    Q_OBJECT

    QCheckBox* _directed;
    QCheckBox* _weighted;
    QComboBox* _operation;
    EditZone* _editZone;

public:
    GraphEditor(QWidget *parent = nullptr);

};
