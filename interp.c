#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
#define numFlags 3
void print(int a[],int b[], int c[]);
int split(char a[],char b[100][100]);//where a is the original string and b is the tokenized string
void read(int a[], int pos, int num);
void write(int a[], int pos);
void add(int a[], int b[], int num1, int c[], int num2);
void subtract(int a[], int b[], int num1, int c[], int num2);

int main(){
  int flags[numFlags] = {0, 0, 0};//to store all the flags
  int registers[NumRegisters] = {128,128,128,128};//registers
  int memory[NumMemoryLocations] = {128,128,128,128,128,128,128,128};//memory NumMemoryLocations
  char instruction[100];//inputted raw instruction
  char instructionAfterParsing[100][100];//instruction stored after parsing
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
  while (1){//infinite loop until user quits
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
        read(memory,(instructionAfterParsing[2][1]-'0'),atoi(instructionAfterParsing[1]));//goes array,position,num
      }
      else if ( instructionAfterParsing[2][0] == 'r'){
        read(registers,(instructionAfterParsing[2][1]-'0'),atoi(instructionAfterParsing[1]));//goes array,position,num
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0],toRead) == 0) && size != 3){//if there is an illegal number of arguments
        printf("???\n");
    }
    //write command
    else if ((strcasecmp(instructionAfterParsing[0],toWrite)) == 0 && size == 2){//if the input command is to write
      if (instructionAfterParsing[1][0] == 'm'){
        write(memory,(instructionAfterParsing[1][1] - '0'));
      }
      else if (instructionAfterParsing[1][0] == 'r'){
        write(registers, (instructionAfterParsing[1][1] - '0'));
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0],toWrite)) == 0 && size != 2){//illegal number of arguments
      printf("???\n");
    }
    //add command
    else if ((strcasecmp(instructionAfterParsing[0], toAdd) == 0) && size == 3){
      if ( instructionAfterParsing[1][0] == 'm' && instructionAfterParsing[2][0] == 'r'){
        add(registers, memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( instructionAfterParsing[1][0] == 'r' && instructionAfterParsing[2][0] == 'm'){
        add(registers,registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( instructionAfterParsing[1][0] == 'r' && instructionAfterParsing[2][0] == 'r'){
        add(registers,registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if ( instructionAfterParsing[1][0] == 'm' && instructionAfterParsing[2][0] == 'm'){
        printf("???\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toAdd) == 0) && size != 3){//if the number of arguments are off
       printf("???\n");
    }
    //subtract command
    else if ((strcasecmp(instructionAfterParsing[0], toSubtract) == 0) && size == 3){
      if ( instructionAfterParsing[1][0] == 'm' && instructionAfterParsing[2][0] == 'r'){
        subtract(registers, memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( instructionAfterParsing[1][0] == 'r' && instructionAfterParsing[2][0] == 'm'){
        subtract(registers,registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( instructionAfterParsing[1][0] == 'r' && instructionAfterParsing[2][0] == 'r'){
        subtract(registers,registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if ( instructionAfterParsing[1][0] == 'm' && instructionAfterParsing[2][0] == 'm'){
        printf("???\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toSubtract) == 0) && size != 3){//if the number of arguments are off
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
/*this function tokenizes a string */
int split(char a[], char b[100][100]){
  int k = 0;
  char* token = strtok(a," ,\n");
  while (token){
    strcpy(b[k],token);
    token = strtok(NULL," ,\n");
    k++;
  }
  return k;
}
/*this function is used to implement the read command */
void read(int a[],int pos,int num){
  a[pos] = num;
}
/*this function is used to implement the write command*/
void write(int a[], int pos){
  if ( a[pos] > 127 || a[pos] < -128){
    printf("?\n");
  }
  else{
  printf("%d\n",a[pos]);
  }
}
/*this function is used to implement the add command*/
void add(int a[], int b[], int num1, int c[], int num2){
  if ( b[num1] + c[num2] > 127 || b[num1] + c[num2] < -128){
    a[0] = 128;
  }
  else{
  a[0] = b[num1] + c[num2];
  }
}
/*this function is used to implement the subtract command*/
void subtract(int a[], int b[], int num1, int c[], int num2){
 if ( c[num2] - b[num1] < -128){
   a[0] = 128;
 }
 else{
   a[0] = c[num2] - b[num1];
 }
}
