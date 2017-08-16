#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void acceptConnection();
    void recvMessage();

private:
    Ui::Dialog *ui;
    QTcpServer* listenSocket;
    QTcpSocket* readWriteSocket;
};

#endif // DIALOG_H
