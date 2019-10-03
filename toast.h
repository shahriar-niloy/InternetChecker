#ifndef TOAST_H
#define TOAST_H

#include <QWidget>

namespace Ui {
class Form;
}

class Toast : public QWidget
{
    Q_OBJECT
public:
    explicit Toast(QWidget *parent = 0);
    Ui::Form *ui;
signals:

public slots:
private slots:

private:

};

#endif // TOAST_H
