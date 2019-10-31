#include<stdio.h>
#include<string.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
#define numFlags 3
void print(int a[],int b[], int c[]);
int split(char a[],char b[3][8]);//where a is the original string and b is the tokenized string
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
  scanf(" %[^\n]s",instruction);
  size = split(instruction, instructionAfterParsing);
  printf("This is the size %d\n",size);
      for (i = 0; i < size; i++){
        printf("%s\n",instructionAfterParsing[i]);
      }
  scanf("%d",&tester);
  scanf(" %[^\n]s",instruction);
  size = split(instruction, instructionAfterParsing);
  printf("This is the size %d\n",size);
    for (i = 0; i < size; i++){
        printf("%s\n",instructionAfterParsing[i]);
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
    printf("%c\t",b[i]);
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
int split(char a[], char b[3][8]){
  int k = 0;
  char* token = strtok(a," ,\n");
  while (token){
    strcpy(b[k++],token);
    token = strtok(NULL," ,\n");
  }
  return k;
}
