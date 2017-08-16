#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

extern int aa[10000100];

void MyThread::run()
{
    quick_sort_recursive(aa, l, r);
}

void MyThread::quick_sort_recursive(int arr[], int start, int end) {
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
    quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}

void MyThread::Set(int l_, int r_)
{
    l = l_;
    r = r_;
}
