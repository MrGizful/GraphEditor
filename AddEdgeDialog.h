#pragma once
#include <QDialog>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AddEdgeDialog : public QDialog
{
    Q_OBJECT
private:
    QDoubleSpinBox* _weight;
    bool _delete;

public:
    AddEdgeDialog(float weight = 0, QWidget* parent = nullptr);

    float getWeight();
    bool isEdgeDeleted();

public slots:
    void deleteEdge();
};
