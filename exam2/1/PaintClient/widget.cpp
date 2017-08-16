#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QByteArray>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    readWriteSocket = new QTcpSocket;
    readWriteSocket->connectToHost(QHostAddress::LocalHost, 3024);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_1_clicked()
{
    QByteArray arr;
    QDataStream ds(&arr,  QIODevice::ReadWrite);
    ds << 1 << ui->lineEdit_1->text().toInt() << ui->lineEdit_2->text().toInt() << ui->lineEdit_3->text().toInt();
    readWriteSocket->write(arr);
}

