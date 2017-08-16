#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QPaintEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void acceptConnection();
    void receiveMessage();
    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;
    QTcpServer* listenSocket;
    QTcpSocket* readWriteSocket;
    int type;
    int a, b, c, d, e, f;
};

#endif // WIDGET_H
