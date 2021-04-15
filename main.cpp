#include "EditZone.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditZone w;
    w.show();
    return a.exec();
}
