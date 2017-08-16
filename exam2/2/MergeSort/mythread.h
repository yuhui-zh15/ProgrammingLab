#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QDebug>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(int no_, QThread *parent = 0): QThread(parent) { no = no_; }
    QVector<int> tmp;
    QVector<int> arr;

    void run() override {
        mergeSort(0, arr.size() - 1);
    }

    void mergeSort(int l, int r) {
        if (l == r) return;
        int mid = (l + r) >> 1;
        mergeSort(l, mid);
        mergeSort(mid + 1, r);
        int s1 = l, s2 = mid + 1;
        int now = l;
        while (s1 <= mid && s2 <= r) {
            if (arr[s1] < arr[s2]) tmp[now++] = arr[s1++];
            else tmp[now++] = arr[s2++];
        }
        for (int i = s1; i <= mid; i++) tmp[now++] = arr[i];
        for (int i = s2; i <= r; i++) tmp[now++] = arr[i];
        for (int i = l; i <= r; i++) arr[i] = tmp[i];
    }

    int no;

public slots:
};

#endif // MYTHREAD_H
