#include "widget.h"
#include <QApplication>
#include <toast.h>

extern bool Error;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Widget w;
    w.setWindowTitle("Is Internet Up?");
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    w.show();
    return a.exec();
}
