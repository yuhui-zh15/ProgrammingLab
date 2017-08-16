#include "mythread.h"
#include "datanode.h"
#include <iostream>

extern QMutex mu[4];
extern dataNode* first[4];

MyThread::MyThread(int no_, QObject *parent) : QThread(parent)
{
    no = no_;
    //std::cout << no << std::endl;
}

void MyThread::run()
{
    for (;;)
    {
        mu[no].lock();
        if (first[no] == NULL)
        {
            mu[no].unlock();
            sleep(1);
            continue;
        }
        if (first[no]->key == -1)
        {
            mu[no].unlock();
            break;
        }
        b.push_back(first[no]->val);
        tmp.push_back(0);
        first[no] = first[no]->next;
        mu[no].unlock();
    }
    MergeSort(0, b.size()-1);
}

void MyThread::MergeSort(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    MergeSort(l, mid);
    MergeSort(mid + 1, r);
    int start1 = l, start2 = mid + 1;
    int now = l;
    while (start1 <= mid && start2 <= r)
        if (b[start1] < b[start2])
        {
            tmp[now++] = b[start1];
            start1++;
        }
        else
        {
            tmp[now++] = b[start2];
            start2++;
        }
    for (int i = start1; i <= mid; i++) tmp[now++] = b[i];
    for (int i = start2; i <= r; i++) tmp[now++] = b[i];
    for (int i = l; i <= r; i++) b[i] = tmp[i];
}

