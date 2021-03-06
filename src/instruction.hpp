#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>

enum TYPE
{
    CRITICAL_CALC,
    CRITICAL_IO,
    CALCULATE,
    IO,
    OUT,
    YIELD,
    FORK,
    SEND,
    RECIEVE
};

class Instruction
{
private:
std::string instr;
std::string out;
int burst;
TYPE type;
bool critical;
std::string msg;

public:
void decBurst();
bool isCritical();
Instruction(std::string instr, int burst, TYPE type, bool critical);
Instruction(std::string instr, std::string out, TYPE type);
Instruction(std::string instr,  TYPE type);
Instruction();
~Instruction();
std::string getInstr();
int getBurst();
TYPE getType();
std::string getOut();
void setOut(std::string out);
void setInstr(std::string instr);
void setBurst(int burst);
void setTYPE(TYPE type);
std::string getMsg();
};

#endif
