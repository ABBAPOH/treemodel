#include <QtCore/QCoreApplication>

#include "treemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TreeModel t;

    return a.exec();
}
