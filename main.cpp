#include <QApplication>
#include <QScrollArea>
#include "GraphEditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphEditor wgt;
    wgt.show();

    return a.exec();
}
