#include <iostream>
#include <string.h>
using namespace std;


struct Instruction
{
    string code;
    string op1;
    string op2;
};
using namespace std;
int main()
{
    string instruction = "Move R1, R2";
    Instruction instr;
    int i = 0;
    char *cstr = new char[instruction.length() + 1];
    strcpy(cstr, instruction.c_str());
    char *tok = strtok(cstr, " ,");
    instr.code = tok;
    while (tok != NULL)
    {
        tok = strtok(cstr, " ,");
        if (i == 0)
        {

            tok = strtok(NULL, " ,");
            instr.op1 = tok;
        }
        else if (i == 1)
        {
            tok = strtok(NULL, " ,");
            instr.op2 = tok;
        }
        i++;
    }
    cout<<instr.code<<endl<<instr.op1<<endl<<instr.op2<<endl;
    return 0;
}
