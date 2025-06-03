#include <QApplication>
#include <QPushButton>
#include "Mainwindows.h"

int main(int argc, char *argv[]) {


    QApplication a(argc, argv);
    MainWindows mainWindows;
    mainWindows.show();


    return QApplication::exec();
}
