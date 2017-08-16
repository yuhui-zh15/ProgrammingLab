#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int no_, QObject *parent = 0);
    void run();
    QVector<int> b, tmp;

signals:

public slots:

private:
    int no;
    void MergeSort(int l, int r);
};

#endif // MYTHREAD_H
