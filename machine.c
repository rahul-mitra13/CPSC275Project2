#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
#define numFlags 3
void print(int a[],int b[], int c[]);
int split(char a[],char c[100][100]);//where a is the original string and c is the tokenized string without coomments
void read(int a[], int pos, int num);
void write(int a[], int pos);
void add(int flags[],int a[], int b[], int num1, int c[], int num2);
void subtract(int flags[],int a[], int b[], int num1, int c[], int num2);
void multiply(int flags[],int a[], int b[], int num1, int c[], int num2);
void divide(int flags[],int a[], int b[], int num1, int c[], int num2);
void mod(int flags[],int a[], int b[], int num1, int c[], int num2);
void move(int b[], int num1, int c[], int num2);
void comp(int flags[], int registers[], int pos1, int pos2);

int main(){
  int flags[numFlags] = {0, 0, 0};//to store all the flags
  int registers[NumRegisters] = {128,128,128,128};//registers
  int memory[NumMemoryLocations] = {128,128,128,128,128,128,128,128};//memory NumMemoryLocations
  char instruction[100];
  char instructionAfterParsing[100][100];//instruction stored after parsing and removing comments
  char wholeProgram[100][100];
  int size;
  int i;
  int k;
  int numlines;
  char toRead[] = "READ";
  char toWrite[] = "WRITE";
  char toPrint[] = "PRINTS";
  char toMove[] = "MOVE";
  char toAdd[] = "ADD";
  char toSubtract[] = "SUB";
  char toMultiply[] = "MULT";
  char toDivide[] = "DIV";
  char toMod[] = "MOD";
  char toCompare[] = "COMP";
  char toQuit[] = "QUIT";
  char toStart[] = ".start:";
  char newstr[100];
  k = 0;
  printf("\n");
  while ((scanf(" %[^\n]s",instruction)) != EOF){
  size = split(instruction, instructionAfterParsing);
  newstr[0] = '\0';
  for ( i = 0; i < size; i++){
          if ( i == size - 1){
          strcat(newstr,strcat(instructionAfterParsing[i]," "));
          }
          else{
              strcat(newstr,strcat(instructionAfterParsing[i]," "));
          }
      }
      strcpy(wholeProgram[k++],newstr);
    }
  for ( i = 0; i < k; i++){
      printf("%s\n",wholeProgram[i]);
  }
  printf("This is the size = %d\n",k);
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
  printf("\n");
}
/*this function tokenizes a string */
int split(char a[], char c[100][100]){
  int k = 0;//number of tokens including comments
  int ctr = 0;//number of comments excluding comments
  char b[100][100];
  int i;
  char* token = strtok(a," ,\n");
  while (token){
    strcpy(b[k],token);
    token = strtok(NULL," ,\n");
    k++;
  }
  for ( i = 0; i < k ; i++){
      if (b[i][0] == '#'){
               break;
        }
      else{
          strcpy(c[ctr], b[i]);
          ctr++;
      }
    }
    return ctr;
}
/*this function is used to implement the read command */
void read(int a[],int pos,int num){
  if ( num > 127 || num < -127){
    printf("???\n");
  }
  else{
  a[pos] = num;
  }
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
void add(int flags[],int a[], int b[], int num1, int c[], int num2){
  if ( b[num1] + c[num2] > 127 || b[num1] + c[num2] < -128){
    a[0] = 128;
    flags[2] = 1;
  }
  else{
  a[0] = b[num1] + c[num2];
  flags[2] = 0;
  }
}
/*this function is used to implement the subtract command*/
void subtract(int flags[],int a[], int b[], int num1, int c[], int num2){
 if ( c[num2] - b[num1] > 127 || c[num2] - b[num1] < -128){
   a[0] = 128;
   flags[2] = 1;
 }
 else{
   a[0] = c[num2] - b[num1];
   flags[2] = 0;
 }
}
/*this function is used to implement the multiply command */
void multiply(int flags[],int a[], int b[], int num1, int c[], int num2){
 if ((b[num1]*c[num2]) > 127 || (c[num2] * b[num1]) < -128){
   a[0] = 128;
   flags[2] = 1;
 }
 else{
   a[0] = b[num1] * c[num2];
   flags[2] = 0;
 }
}
/*this function is used to implement the divide command */
void divide(int flags[],int a[], int b[], int num1, int c[], int num2){
 if ((b[num1] / c[num2]) > 127 || (c[num2] / b[num1]) < -128){
   a[0] = 128;
   flags[2] = 1;
 }
 else{
   a[0] = b[num1] / c[num2];
   flags[2] = 0;
 }
}
/*this function is used to implement the mod command */
void mod(int flags[],int a[], int b[], int num1, int c[], int num2){
 if ((b[num1] % c[num2]) > 127 || (c[num2] % b[num1]) < -128){
   a[0] = 128;
   flags[2] = 1;
 }
 else{
   a[0] = b[num1] % c[num2];
   flags[2] = 0;
 }
}
/*this function is used to implement the move command */
void move(int b[], int num1, int c[], int num2){
 if ( b[num1] > 127 || b[num1] < -128){
   c[num2] = 128;
 }
 else{
 c[num2] = b[num1];
 }
}
/*this function is used to implement the comp command */
void comp(int flags[], int registers[], int pos1, int pos2){
  if (registers[pos1] > registers[pos2]){
    flags[0] = 0;
    flags[1] = 1;
  }
  else if (registers[pos1] < registers[pos2]){
    flags[0] = 0;
    flags[1] = 0;
  }
  else if (registers[pos1] == registers[pos2]){
    flags[0] = 1;
    flags[1] = 0;
  }
}

