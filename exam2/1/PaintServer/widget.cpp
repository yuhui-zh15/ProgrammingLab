#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QByteArray>
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QPolygon>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    readWriteSocket = new QTcpSocket;
    listenSocket = new QTcpServer;
    connect(listenSocket, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    listenSocket->listen(QHostAddress::LocalHost, 3024);
}

void Widget::acceptConnection() {
    readWriteSocket = listenSocket->nextPendingConnection();
    connect(readWriteSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
}

void Widget::receiveMessage() {
    QByteArray arr;
    arr = readWriteSocket->readAll();
    QDataStream ds(arr);
    ds >> type >> a >> b >> c >> d >> e >> f;
    qDebug() << type << ' ' << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << endl;
    repaint();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::NoBrush);
    for (int i = 0; i < height(); i+=50) {
        p.drawLine(0, i, width(), i);
    }
    for (int i = 0; i < width(); i+=50) {

        p.drawLine(i, 0, i ,height());
    }
    p.setBrush(Qt::yellow);
    if(type == 1) p.drawEllipse(QPoint(a, b), c, c);
    else if (type == 2) p.drawRect(a, b, c, d);
    else if (type == 3) { QPolygon tri; tri << QPoint(a, b) << QPoint(c, d) << QPoint(e, f); p.drawPolygon(tri);}


}
