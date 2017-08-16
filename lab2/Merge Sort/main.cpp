#include <QCoreApplication>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include "mythread.h"
#include <QMutex>
#include "datanode.h"
#include <string>
#include <iostream>
#include <QDebug>
#include <QVector>

const int N = 4;
MyThread* thread[4];
QMutex mu[4];
dataNode* first[4];

QVector<int> c;

using namespace std;

void Add(int key, int val)
{
    int mod = key % N;
    mu[mod].lock();
    dataNode *tmp = new dataNode;
    tmp->key = key;
    tmp->val = val;
    tmp->next = first[mod];
    first[mod] = tmp;
    mu[mod].unlock();
}

void Read()
{
    for (int i = 0; i < N; i++)
    {
        thread[i] = new MyThread(i);
        thread[i]->start();
    }
    ifstream fin("test2.txt");
    ofstream fout("result.txt");
    string s;
    while (fin >> s)
    {
        int key = 0, val = 0;
        int *now = &key;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ',')
            {
                now = &val;
                continue;
            }
            *now = *now * 10 + (s[i] - '0');
        }
        Add(key, val);
    }

    for (int i = 0; i < N; i++)
    {
        mu[i].lock();
        if (first[i] == NULL)
        {
            dataNode *tmp = new dataNode;
            tmp->key = -1;
            tmp->val = 0;
            tmp->next = first[i];
            first[i] = tmp;
        }
        else
        {
            dataNode* tf = first[i];
            while (tf->next) tf = tf->next;
            dataNode *tmp = new dataNode;
            tmp->key = -1;
            tmp->val = 0;
            tmp->next = NULL;
            tf->next = tmp;
        }
        mu[i].unlock();
    }

    for (int i = 0; i < N; i++) thread[i]->wait();
    int w[N];
    for (int i = 0; i < N; i++) w[i] = 0;
    for (;;)
    {
        int wj = -1;
        int now = 2000000000;
        for (int i = 0; i < N; i++)
        {
            if (w[i] == thread[i]->b.size()) continue;
            if (thread[i]->b[w[i]] < now)
            {
                now = thread[i]->b[w[i]];
                wj = i;
            }
        }
        if (wj == -1) break;
        w[wj]++;
        c.push_back(now);
    }
    for (int i = 0; i < c.size(); i++) fout << c[i] << ' ';
    fout << endl;
    fin.close();
    fout.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Read();
    cout << "aaa" << endl;
    return a.exec();
}
