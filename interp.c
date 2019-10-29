#include<stdio.h>
#include<string.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
void main(){
  int registers[NumRegisters];//registers
  int memmory[NumMemoryLocations];//memory NumMemoryLocations
  char instruction[MaxInstructionLength];//inputted instruction
  char toQuit[] = {'Q','U','I','T','\0'};
  int zf = 0;//zero flag
  int sg = 0;//sign flag
  int of = 0;//overflow flag
  scanf("%s",instruction);
  printf("This is what you input = %d\n", strcmp(instruction,toQuit));
}
