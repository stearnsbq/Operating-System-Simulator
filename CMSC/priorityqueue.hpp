#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE
#include "../process management/PCB.hpp"
#include <vector>
class PriorityQueue
{
private:
    std::vector<Process *> heap;
    int size;
    void heapify(int index);
    int left(int i);
    int right(int i);
    int parent(int i);
    void swap(Process *x, Process *y);

public:
    PriorityQueue();
    ~PriorityQueue();
    void addProcess(Process *data);
    Process *removeProcess();
    void printPQueue();
    int getSize();
};

#endif