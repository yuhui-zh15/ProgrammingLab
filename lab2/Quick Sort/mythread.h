#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void Set(int l_, int r_);

signals:
    void useSort();

public slots:

protected:
    void run();

private:
    void quick_sort_recursive(int arr[], int start, int end);
    int l, r;
};

#endif // MYTHREAD_H
