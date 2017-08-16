#include <QCoreApplication>
#include <QThread>
#include <QString>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include "mythread.h"
#include "mythread2.h"
#include <QMutex>
#include <QList>
#include "datanode.h"

MyThread *thread[4];
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //create threads
    for (int i = 0; i < 4; i++) {
        thread[i] = new MyThread(i);
    }
    //read data
    int cnt = 0;
    QFile file("data.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "file can't open" << endl;
        return -1;
    }
    QTextStream ts(&file);
    while (1) {
        QString line = ts.readLine();
        if (line.length() == 0) break;
        int num = line.toInt();
        thread[cnt%4]->arr.append(num);
        thread[cnt++%4]->tmp.append(0);
    }
    //thread run
    for (int i = 0; i < 4; i++) {
        thread[i]->start();
    }
    //wait
    for (int i = 0; i < 4; i++) {
        thread[i]->wait();
    }
    qDebug() << "4threads ok!";
    //4->2
    MyThread2 *th1 = new MyThread2(thread[0]->arr, thread[1]->arr, 1);
    MyThread2 *th2 = new MyThread2(thread[2]->arr, thread[3]->arr, 2);
    th1->start(); th2->start();
    th1->wait(); th2->wait();
    //2->1
    MyThread2 *th3 = new MyThread2(th1->tmp, th2->tmp, 3);
    th3->start();
    th3->wait();
    //output
    QFile file2("out.txt");
    QTextStream ts2(&file2);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        cout << "file2 can't open" << endl;
        return -1;
    }
    for (int i = 0; i < th3->tmp.length(); i++) {
        ts2 << th3->tmp[i] << endl;
    }
    qDebug() << "Finished!";
    return a.exec();
}
