#include <QApplication>
#include <QScrollArea>
#include "EditZone.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EditZone wgt;
    wgt.show();

    return a.exec();
}
