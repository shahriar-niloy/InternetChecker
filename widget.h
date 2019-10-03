#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QTimer>
#include <QPoint>
#include <QSound>
#include <QMouseEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QFile>
#include <QDateTime>
#include <QMediaPlayer>
#include "toast.h"

namespace Ui {
class Widget;
class Form;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event) override;
    ~Widget();

public slots:
    void check();
    void slot();
    void netError();
    void activateWan();
    void activateLan();
    void createIconContextMenu();
    void debug();
    void log();
    void clearLog();
    void close();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void closeToastNotification();
    void toggleSilent();

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_close_clicked();
    void on_minimize_clicked();
    void on_toTray_clicked();


private:
    bool Error;
    QPoint mpos;
    QMenu *conMenu;
    QMenu *menu;
    QMenu *iconContextMenu;
    QAction *a0;
    QAction *a1;
    QAction *a2;
    QAction *a3;
    QTimer *timer = NULL;
    QNetworkReply *rep = NULL;
    bool mode;
    QSystemTrayIcon *trayIcon;
    QUrl *url;
    QFile logFile;
    QDateTime time;
    Ui::Widget *ui;
    Toast *toastBox;
    QMediaPlayer beep;
};

#endif // WIDGET_H
