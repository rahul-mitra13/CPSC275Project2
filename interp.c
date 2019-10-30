#include<stdio.h>
#include<string.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
#define numFlags 3
void print(int a[],int b[], int c[]);
// void read(int instruction[], int memory[], int registers[])
int main(){
  //asci value of question mark is 63
  int registers[NumRegisters] = {63,63,63,63};//registers
  int memory[NumMemoryLocations] = {63,63,63,63,63,63,63,63};//memory NumMemoryLocations
  int flags[numFlags] = {0, 0, 0};//to store all the flags
  char instruction[MaxInstructionLength];//inputted raw instruction
  char *ptr;//this will act as a test pointer when looking for instructions
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
  while (strcasecmp(instruction, toQuit) != 0){//keep going until the user enters quit
    if (strcasecmp(instruction, toPrint) == 0){//if the input command is to print
      print(registers, memory, flags);
    }
    //the above two are the only single worded instructions
    if ( strcasecmp(instruction, toRead) == 0){
      //read(instruction,memory,registers);
      printf("You entered a read instruction\n");
    }
    scanf("%s",instruction);
  }
  return 0;
}
/*function that is called when input is prints*/
void print(int a[], int b[], int c[]){
  int i;
  for ( i = 0; i < NumRegisters; i++){
       printf("%c\t",a[i]);
  }
  for ( i = 0; i < NumMemoryLocations; i++){
    printf("%c\t",b[i]);
  }
  for ( i = 0; i < numFlags; i++){
    printf("%d\t",c[i]);
  }
  printf("\n");
  printf("--\t--\t--\t--\t--\t--\t--\t--\t--\t--\t--\t--\t--\t--\t--\n");
  for ( i = 0; i < NumRegisters; i++){
       printf("R%d\t",i);
  }
  for ( i = 0; i < NumMemoryLocations; i++){
    printf("M%d\t",i);
  }
  printf("ZF\t");
  printf("SF\t");
  printf("OF\t");
  printf("\n");
}
