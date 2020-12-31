#include "gw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GW w;
    w.show();
    return a.exec();
}
