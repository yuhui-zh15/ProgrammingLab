#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QPaintEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void acceptConnection();
    void receiveMessage();
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    QTcpServer* listenSocket;
    QTcpSocket* readWriteSocket;
    int type;
    int a, b, c, d, e, f;
};

#endif // MAINWINDOW_H
