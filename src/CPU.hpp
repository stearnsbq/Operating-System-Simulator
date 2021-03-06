#ifndef CPU_H
#define CPU_H
#include "mainmemory.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "kernel.h"
#include <QString>
#include "mutex.h"
#include "core.h"
#include <mutex>


class mainmemory;
class Core;
class ShortTermScheduler;
class CPU
{
private:
CPU();
~CPU(){
    delete core1;
    delete core2;
    delete memory;
    delete mutexLock;
}
unsigned int logicalAddr;
unsigned int nextOpenFrame;
mainmemory *memory;
int clockTime;
QString unit;
int timeQuantum;
std::thread clock_thread;
void run(int time, QString unit, ALGORITHM algoToUse);
Process runningProcess;
void migrateProcess(Process p, Core * coreToMigrateTo);
void loadBalancer(int time, QString unit);
void sleep(int time, QString unit);
Core * core1;
Core * core2;

public:

static CPU& getInstance(){     // make this singleton because I only ever need one instance of CPU

    static CPU instance;

    return instance;

}

void setPagesDirty(std::vector<page> pages);
mutex * mutexLock;
CPU(CPU const&) = delete;     // prevents possible insts
void operator=(CPU const&) = delete;
void start(int time, QString unit, ALGORITHM algo);
mainmemory * getMemory();
long long availableMemory();
Process& getRunningProcess();
void setRunningProcess(Process p);
unsigned int getNextLogicalAddr();
int getNextOpenFrame();
std::vector<page> alloc(unsigned int size);
void free(std::vector<page> pages);
std::mutex memoryMutex;
std::mutex critSection;
};

#endif
