#include "AddEdgeDialog.h"

AddEdgeDialog::AddEdgeDialog(QWidget* parent) : QDialog(parent), _delete(false)
{
    _weight = new QDoubleSpinBox;
    _weight->setRange(-10000, 10000);
    QLabel* label = new QLabel("Edge weight:");
    QPushButton* okBtn = new QPushButton("Ok");
    QPushButton* deleteBtn = new QPushButton("Delete");
    QPushButton* cancelBtn = new QPushButton("Cancel");

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(okBtn);
    vLayout->addWidget(deleteBtn);
    vLayout->addWidget(cancelBtn);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(label);
    hLayout->addWidget(_weight);
    hLayout->addLayout(vLayout);
    setLayout(hLayout);

    connect(okBtn, SIGNAL(clicked()), SLOT(accept()));
    connect(deleteBtn, SIGNAL(clicked()), SLOT(deleteEdge()));
    connect(cancelBtn, SIGNAL(clicked()), SLOT(reject()));
}

void AddEdgeDialog::deleteEdge()
{
    _delete = true;
    reject();
}

float AddEdgeDialog::getWeight()
{
    return _weight->value();
}

bool AddEdgeDialog::isEdgeDeleted()
{
    return _delete;
}
