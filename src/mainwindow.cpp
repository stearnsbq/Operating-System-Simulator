#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <string>
#include "mainwindow.h"
#include "main.hpp"
#include <stdio.h>
#include <thread>
#include <QPushButton>
#include <string.h>
#include <string>
#include <stdlib.h>
#include "fileoptionsdialog.h"
#include <fstream>
#include <QGraphicsRectItem>
#include <sstream>
#include <iostream>
#include <locale>
#include <QApplication>
#include <QPainter>
#include <QObject>
#include "PCB.hpp"
#include <QScrollBar>
#include <QGraphicsScene>
#include <QMap>
#include "loadfiledialog.h"
#include <QMessageBox>


using namespace std;

 QTextEdit *ptr;
 Scheduler *test = new Scheduler(MULTILEVEL_FEEDBACK_QUEUE);
 thread consoleThread;

 void MainWindow::createProcess(string instructions, int number, bool toRandom)
 {
     Process p = Process();
     istringstream f(instructions);
     for (string line; getline(f, line);)
     {
         if (line.find("Name:") != string::npos)
         {
             string name = line.substr(line.find(":") + 2);

             p.setName(name);
         }
         else if (line.find("Total runtime:") != string::npos)
         {
             string runtime = line.substr(line.find(":") + 2);

             if(!toRandom){
                 p.setCycles(stoi(runtime));
             }
         }
         else if (line.find("Memory:") != string::npos)
         {
             string memory = line.substr(line.find(":") + 2);
             p.setMemoryReq(stoi(memory));
         }
         else
         {
             if (line.length() > 0)
             {
                 if (line == "EXE")
                 {
                     break;
                 }
                 p.addInstruction(line, toRandom);
             }
         }
     }
     for (int i = 0; i < number; i++)
     {
         test->addNewProcess(p);
     }
      cout << "Program: " << p.getName() << " Loaded!"<< " Processes created: " << number  << endl;
 }

 void MainWindow::loadFileThread()
 {
     string buf;
     string programFileBuf;
     printf("Please enter a Program file name\n");
     getline(cin, buf);
     ifstream programFile("C:\\Users\\quinn\\Desktop\\dev\\BYRON_STEARNS_CMSC312_2019\\src\\" + buf);
     if (!programFile)
     {
         printf("file error\n");
         return;
     }
     bool isValid = false;
     for (string line; getline(programFile, line);)
     {
         programFileBuf += line + "\n";
         if (line == "EXE")
         {
             isValid = true;
         }
     }

     if (isValid)
     {
         printf("Please enter the number of processes you would like to create from this program: ");
         getline(cin, buf);
         int numProc = stoi(buf);
         printf("Would you like to randomize runtime?: ");
         getline(cin, buf);

         if(buf == "yes" || buf == "y"){
            createProcess(programFileBuf, numProc, true);
         }else{
            createProcess(programFileBuf, numProc, false);
         }

     }
     else
     {
         return;
     }

     programFile.close();
 }


 char *MainWindow::parseCommand(char *cmd)
 {
     char *out = (char *)malloc(sizeof(char) * 256);
     memset(out, 0, 256);
     if (!strcmp("load\n", cmd))
     {
       std::thread thread(&MainWindow::loadFileThread,this);
       thread.join();
         return out;
     }
     else if (!strcmp("clear\n", cmd))
     {
         system("cls");
         return out;
     }
     else if (!strcmp("start\n", cmd))
     {

         test->start(this, 1, "ms");
         return out;
     }
     strcpy(out, "Command Not Found \"Help\" to see all commands\n\0");
     return out;
 }

 void MainWindow::cli(){
     char buf[256];
      while (1)
      {
          printf("OS Simulator: ");
          fgets(buf, 256, stdin);
          printf("%s", this->parseCommand(buf));
      }
 }







void MainWindow::updateText(std::string in){
    QString str = QString::fromUtf8(in.c_str());
    ptr->append(str);
    ptr->verticalScrollBar()->setValue(ptr->verticalScrollBar()->maximum());
}





void MainWindow::changeStatus(){
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::red);
    ui->isRunning->setText("Not Running...");
    ui->isRunning->setPalette(pal);
    this->isRunning = false;


}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    qRegisterMetaType<std::string>("std::string");
    ui->setupUi(this);
    consoleThread = std::thread(&MainWindow::cli,this);
    consoleThread.detach();
    connect(this, &MainWindow::print, this, &MainWindow::updateText);
    connect(this, &MainWindow::done, this, &MainWindow::changeStatus);
    ptr = ui->simulatorOut;
    ptr->setReadOnly(true);
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::red);
    ui->isRunning->setPalette(pal);
    this->isRunning = false;


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::save(){

}


void MainWindow::on_loadFile_clicked()
{
    this->loadfile = new loadFileDialog();
    this->loadfile->setFixedSize(this->loadfile->size());
    connect(this->loadfile, &loadFileDialog::createProcesses, this, &MainWindow::createProcess);
      ui->simulatorOut->clear();
    loadfile->show();

}

void MainWindow::on_startSim_clicked()
{
    if(!this->isRunning){
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::green);
    ui->isRunning->setText("Running!");
    ui->isRunning->setPalette(pal);
    std::thread run = std::thread(&Scheduler::start, test, this, ui->time->value(),ui->timeUnit->currentText());
    run.detach();
    this->isRunning = true;
    }else{
     QMessageBox::warning(this, "Already Running!!", "The simulator is already running!");
    }

}
