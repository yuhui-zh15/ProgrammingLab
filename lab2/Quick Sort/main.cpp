#include <QCoreApplication>
#include <QDebug>
#include "mythread.h"
//#include "mergesort.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <QObject>

int aa[10000100];
int n;

MyThread *t1, *t2;

void quick_sort_recursive(int arr[], int start, int end) {
    if (start >= end)
        return;//這是為了防止宣告堆疊陣列時當機
    int mid = arr[end];
    int left = start, right = end - 1;
    while (left < right) {
        while (arr[left] < mid && left < right)
            left++;
        while (arr[right] >= mid && left < right)
            right--;
        std::swap(arr[left], arr[right]);
    }
    if (arr[left] >= arr[end])
        std::swap(arr[left], arr[end]);
    else
        left++;





    t1->Set(start, left-1);
    t2->Set(left+1, end);

    t1->start();
    t2->start();

//    t1->wait();
//    t2->wait();






//    quick_sort_recursive(arr, start, left - 1);
//    quick_sort_recursive(arr, left + 1, end);



}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    t1 = new MyThread;
    t2 = new MyThread;

    qDebug()<<"main thread:"<<QThread::currentThreadId();
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");

    fin >> n;
    for (int i = 0; i < n; i++) fin >> aa[i];

    // set clock start
    clock_t start_time, end_time;

    start_time = clock();


    quick_sort_recursive(aa, 0, n-1);

    end_time = clock();

    // output runtime
    std::cout << "Runtime: ";
    std::cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

    for (int i = 0; i < n; i++) std::cout << aa[i] << ' ';
    fout << std::endl;

    fin.close();
    fout.close();

    std::cout << "haha";

    /*
    MyThread *mt = new MyThread;
    ms->moveToThread(mt);
    QObject::connect(mt, SIGNAL(useSort()), ms, SLOT(Sort()));
    mt->start();
    */
    return a.exec();
}
