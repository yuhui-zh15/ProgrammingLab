#include "dialog.h"
#include "ui_dialog.h"
#include <QDataStream>
#include <QByteArray>
#include <QFile>
#include <QTextStream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->listenSocket = new QTcpServer;
    connect(this->listenSocket, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    this->listenSocket->listen(QHostAddress::Any, 8888);
    //qDebug() << readWriteSocket->state();
}

void Dialog::acceptConnection() {

    readWriteSocket = listenSocket->nextPendingConnection();
    connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(recvMessage()));
}

void Dialog::recvMessage() {
    qDebug() << readWriteSocket->state();
    QByteArray arr;
    arr = this->readWriteSocket->readAll();
    QStringList args = QString(arr).split(' ');
    QString filename = args.at(1);
    qDebug() << QString(arr);
    qDebug() << filename;
    QString newFileName = filename.remove('/');
    QFile file(newFileName);
    qDebug() << newFileName;
    file.open(QIODevice::ReadWrite);
    QByteArray content = file.readAll();
    QByteArray ret;
    ret.clear();
//    ret.append("POST " + filename + " HTTP/1.1\nHost: localhost\nContent-Type: application/x-www-form-urlencoded\nContent-Length: 11\n\nSymbol=MSFT");

    ret.append("HTTP/1.1 200 OK\nContent-Type: text/xml; charset=utf-8\nContent-Length: " +QVariant(content.size()).toString() +"\n\n" + QString(content));

    qDebug() << QString(ret);
    readWriteSocket->write(ret);

}

Dialog::~Dialog()
{
    delete ui;
}
