#include<stdio.h>
#include<string.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
int main(){
  int registers[NumRegisters];//registers
  int memmory[NumMemoryLocations];//memory NumMemoryLocations
  char instruction[MaxInstructionLength];//inputted instruction
  char *toRead = "READ";
  char *toWrite = "WRITE";
  char *toPrint = "PRINTS";
  char *toMove = "MOVE";
  char *toAdd = "ADD";
  char *toSubtract = "SUB";
  char *toMultiply = "MUL";
  char *toDivide = "DIV";
  char *toMod = "MOD";
  char *toCompare = "COMP";
  char *toQuit = "QUIT";
  int zf = 0;//zero flag
  int sg = 0;//sign flag
  int of = 0;//overflow flag
  scanf("%s",instruction);
  while (strcmp(instruction, toQuit) != 0){
    printf("This is what you entered = %s\n", instruction);
    scanf("%s",instruction);
  }
  return 0;
}
