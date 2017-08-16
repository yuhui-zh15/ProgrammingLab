#ifndef MYTHREAD2_H
#define MYTHREAD2_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QDebug>

class MyThread2: public QThread
{
public:
    MyThread2(QVector<int>&arr1, QVector<int>&arr2, int no_, QThread *parent = 0): QThread(parent), m_arr1(arr1), m_arr2(arr2) { no = no_; }
    void run() {
        int s1 = 0, s2 = 0;
        int now = 0;
        while (s1 < m_arr1.length() && s2 < m_arr2.length()) {
            if (m_arr1[s1] < m_arr2[s2]) { tmp.append(m_arr1[s1]); s1++; }
            else { tmp.append(m_arr2[s2]); s2++; }
        }
        for (int i = s1; i < m_arr1.length(); i++) tmp.append(m_arr1[i]);
        for (int i = s2; i < m_arr2.length(); i++) tmp.append(m_arr2[i]);
    }
    int no;
    QVector<int>& m_arr1, m_arr2;
    QVector<int> tmp;
};

#endif // MYTHREAD2_H
