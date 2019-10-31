#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
#define numFlags 3
void print(int a[],int b[], int c[]);
int split(char a[],char b[3][8]);//where a is the original string and b is the tokenized string
void read(int a[], int pos, int num);
int main(){
  int registers[NumRegisters] = {128,128,128,128};//registers
  int memory[NumMemoryLocations] = {128,128,128,128,128,128,128,128};//memory NumMemoryLocations
  int flags[numFlags] = {0, 0, 0};//to store all the flags
  char instruction[MaxInstructionLength];//inputted raw instruction
  char instructionAfterParsing[3][8];//instruction stored after parsing
  int size;
  int i;
  char toRead[] = "READ";
  char toWrite[] = "WRITE";
  char toPrint[] = "PRINTS";
  char toMove[] = "MOVE";
  char toAdd[] = "ADD";
  char toSubtract[] = "SUB";
  char toMultiply[] = "MUL";
  char toDivide[] = "DIV";
  char toMod[] = "MOD";
  char toCompare[] = "COMP";
  char toQuit[] = "QUIT";
  int zf = 0;//zero flag
  int sg = 0;//sign flag
  int of = 0;//overflow flag
  int tester;
  while (1){
    scanf(" %[^\n]s",instruction);
    size = split(instruction, instructionAfterParsing);
    //quit command
    if ((strcasecmp(instructionAfterParsing[0],toQuit) == 0) && size == 1){//if the command is to quit
      break;
    }
    else if ((strcasecmp(instructionAfterParsing[0],toQuit) == 0) && size != 1){//syntax error if there is any argument to quit
      printf("???\n");
    }
    //print command
    else if ((strcasecmp(instructionAfterParsing[0],toPrint) == 0) && size == 1){//if the command is to print
      print(registers,memory,flags);
    }
    else if ((strcasecmp(instructionAfterParsing[0],toPrint) == 0) && size != 1){//syntax error if there is any argument to print
      printf("???\n");
    }
    //read command
    else if ((strcasecmp(instructionAfterParsing[0],toRead) == 0) && size == 3){//if the command is to print
      if ( instructionAfterParsing[2][0] == 'm'){
        read(memory,(instructionAfterParsing[2][1]-'0'),atoi(instructionAfterParsing[1]));//goes array position num
      }
      else if ( instructionAfterParsing[2][0] == 'r'){
        read(registers,(instructionAfterParsing[2][1]-'0'),atoi(instructionAfterParsing[1]));//goes array position num
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0],toRead) == 0) && size != 3){//if there is an illegal number of arguments
        printf("???\n");
    }
   }
    return 0;
}

/*function that is called when input is prints*/
void print(int a[], int b[], int c[]){
  int i;
  for ( i = 0; i < NumRegisters; i++){
       if (a[i] > 127 || a[i] < -128){
       printf("?\t");
       }
       else{
       printf("%d\t",a[i]);
       }
  }
  for ( i = 0; i < NumMemoryLocations; i++){
    if ( b[i] > 127 || b[i] < -128){
      printf("?\t");
    }
    else{
    printf("%d\t",b[i]);
    }
  }
  for ( i = 0; i < numFlags; i++){
    if (c[i] != 0 && c[i] != 1){
      printf("0\t");
    }
    else{
    printf("%d\t",c[i]);
    }
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
/*this function tokenizes a string */
int split(char a[], char b[3][8]){
  int k = 0;
  char* token = strtok(a," ,\n");
  while (token){
    strcpy(b[k++],token);
    token = strtok(NULL," ,\n");
  }
  return k;
}
/*this function is used to implement the read command */
void read (int a[],int pos,int num){
  a[pos] = num;
}
