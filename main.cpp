#include <QApplication>
#include <QScrollArea>
#include "EditZone.h"
#include "Graph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    EditZone wgt;
//    wgt.show();

    Graph test;
    test.addNode(QPoint(1, 1));
    test.addNode(QPoint(2, 2));
    test.addNode(QPoint(3, 3));
    test.addNode(QPoint(4, 4));

    test.addEdge(0, 1, 1);
    test.addEdge(0, 2, 4);
    test.addEdge(0, 3, 5);
    test.addEdge(1, 0, 2);
    test.addEdge(1, 2, 7);
    test.addEdge(1, 3, 6);
    test.addEdge(2, 3, 9);
    test.addEdge(3, 1, 3);
    test.addEdge(3, 2, 8);

    test.removeNode(1);

    return a.exec();
}
