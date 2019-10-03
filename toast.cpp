#include "toast.h"
#include "ui_toast.h"
#include <QtWinExtras/QtWin>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <Qsize>
#define taskbar 40

Toast::Toast(QWidget *parent) : QWidget(parent) , ui(new Ui::Form)
{
    ui->setupUi(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize reso = screen->size();
    this->move(QPoint(reso.rwidth()-this->width(), reso.rheight()-this->height() - taskbar));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background: transparent;");
    QtWin::enableBlurBehindWindow(this);
    QString css("Toast > QWidget { border: 1px solid %1; border-radius: 0px; background: transparent; background-color: rgb(65, 71, 89, 160)}");
    ui->toastBox->setStyleSheet(css.arg(QColor(91, 99, 124).name()));//25, 38, 58
}

//LIked this shit 86, 131, 201 for both border and fill at opacity 160
