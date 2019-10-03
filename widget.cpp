#include "widget.h"
#include "ui_widget.h"
#include "ui_toast.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Toast Notification
    toastBox = NULL;
    //File Related Work
    logFile.setFileName("log.txt");
    //Tray Icon Related Work Starts
    createIconContextMenu();
    trayIcon = new QSystemTrayIcon(QIcon(":/Icon/ITCheck.ico"));
    trayIcon->setVisible(true);
    trayIcon->show();
    trayIcon->setContextMenu(iconContextMenu);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    //Tray Icon Related Work Ends
    mode = 0;//Either WAN Or LAN
    Error = false;
    //Right Click Context Menu Work Starts
    conMenu = new QMenu(this);
    a0 = new QAction("Silent Mode", conMenu);
    a1 = new QAction("Clear Log", conMenu);
    a2 = new QAction("Minimize To Tray", conMenu);
    a3 = new QAction("Quit", conMenu);
    a0->setCheckable(true);
    a2->setCheckable(true);
    a2->setChecked(false);
    conMenu->addAction(a0);
    conMenu->addAction(a1);
    conMenu->addAction(a2);
    conMenu->addAction(a3);
    connect(a0, SIGNAL(triggered()), this, SLOT(toggleSilent()));
    connect(a1, SIGNAL(triggered()), this, SLOT(clearLog()));
    connect(a3, SIGNAL(triggered()), this, SLOT(close()));
    //Right Click Finish
    //Mode Menu Starts
    menu = new QMenu(ui->menuButton);
    menu->addAction("WAN");
    menu->addAction("LAN");
    //connect(a1, SIGNAL(triggered()), this, SLOT(clearLog()));
    connect(menu->actions().at(0), SIGNAL(triggered()), this, SLOT(activateWan()));
    connect(menu->actions().at(1), SIGNAL(triggered()), this, SLOT(activateLan()));
    ui->menuButton->setMenu(menu);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mpos = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;
        this->move(newpos);
    }
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    conMenu->exec(event->globalPos());
    event->accept();
}

void Widget::check()
{
    if(rep != NULL){
        rep->abort();
    }
    Error = false;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    if(mode == 0)
        url = new QUrl("http://www.google.com");
    else
        url = new QUrl("http://192.168.0.1");
    rep = manager->get(QNetworkRequest(*url));
    connect(rep, SIGNAL(finished()), this, SLOT(slot()));
    connect(rep, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(netError()));
    connect(rep, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(netError()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot()
{
    if(Error){
        qDebug() << "Not Working";
        ui->statusBar->setText("Status: Down...");
        if(toastBox != NULL){
            toastBox->close();
            delete toastBox;
            toastBox = NULL;
        }
    }
    else{
        //Play Alert Sound
        QUrl *url = new QUrl;
        url->setUrl("file:///"+ QCoreApplication::applicationDirPath() + "/alert.mp3");
        beep.setMedia(*url);
        beep.play();
        //Update Status Bar
        ui->statusBar->setText("Status: Alive!");
        qDebug() << "Working";
        if(toastBox == NULL){
            qDebug() << "entering null";
            if(this->isVisible() == false){
                qDebug() << "entering visibility";
                toastBox = new Toast;
                toastBox->show();
                if(mode)
                    toastBox->ui->qLabelMode->setText("Mode: LAN");
                else
                    toastBox->ui->qLabelMode->setText("Mode: WAN");
                connect(toastBox->ui->btnToastUpIcon, SIGNAL(clicked()), this, SLOT(closeToastNotification()));
            }
        }
        else{
            connect(toastBox->ui->btnToastUpIcon, SIGNAL(clicked()), this, SLOT(closeToastNotification()));
            connect(toastBox->ui->btnToastExit, &QToolButton::clicked, this, [=](){toastBox->close();});
        }
    }
    log();
}

void Widget::netError()
{
    if(rep->errorString() == "Host requires authentication")
        Error = false;
    else
        Error = true;
    qDebug() << "Error " << rep->errorString();
    rep->abort();
}

void Widget::activateWan()
{
    mode = 0;
    ui->menuButton->setText("WAN");
}

void Widget::activateLan()
{
    mode = 1;
    ui->menuButton->setText("LAN");
}
//Tray Icon Context Menu
void Widget::createIconContextMenu()
{
    iconContextMenu = new QMenu();
    iconContextMenu->addAction("Restore");
    iconContextMenu->addAction("Quit");
    //QList lists = iconContextMenu->actions();
    connect(iconContextMenu->actions().at(0), SIGNAL(triggered()), this, SLOT(show()));
    connect(iconContextMenu->actions().at(1), SIGNAL(triggered()), this, SLOT(close()));
}

void Widget::debug()
{
    qDebug()<<"Active";
}

void Widget::log()
{
    logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    if(logFile.isOpen()){
        QTextStream out(&logFile);
        out << "Mode: " << mode << " " << "Error State: " << Error << "    " << time.currentDateTime().time().hour() << ":" << time.currentDateTime().time().minute() << ":" << time.currentDateTime().time().second() << "    ";
        out << time.currentDateTime().date().day() << "/" << time.currentDateTime().date().month() << "/" << time.currentDateTime().date().year() << endl;
    }
    else{
        qDebug() << "Error Opening File";
    }
    logFile.close();
}

void Widget::clearLog()
{
    logFile.remove("log.txt");
    logFile.setFileName("log.txt");
}

void Widget::close()
{
    delete trayIcon;
    QWidget::close();
}

void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
       switch(reason){
       case QSystemTrayIcon::ActivationReason::Trigger:
            this->show();
            break;
       default:
            break;
       }
}

void Widget::closeToastNotification()
{
    qDebug() << "Closing Noti";
    toastBox->close();
    this->on_stopButton_clicked();
    delete toastBox;
    toastBox = NULL;
}

void Widget::toggleSilent()
{
    if(beep.volume())
        beep.setVolume(0);
    else
        beep.setVolume(100);
}

void Widget::on_startButton_clicked()
{
    if(timer != NULL){
        timer->stop();
        delete timer;
        timer = NULL;
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
    timer->start(3000);
}

void Widget::on_stopButton_clicked()
{
    if(timer != NULL){
        timer->stop();
        delete timer;
        timer = NULL;
        rep->abort();
        delete rep;
        rep = NULL;
    }
    if(toastBox != NULL){
        delete toastBox;
        toastBox = NULL;
    }
    ui->statusBar->setText("Status: Idle...");
}

void Widget::on_close_clicked()
{
    this->close();
    QApplication::quit();
}

void Widget::on_minimize_clicked()
{
    if(a2->isChecked() == true)
        this->hide();
    else
        this->showMinimized();
}

void Widget::on_toTray_clicked()
{
    this->hide();
}
