#include "EditZone.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EditZone w;
    w.resize(350, 300);
    w.show();

    return a.exec();
}
