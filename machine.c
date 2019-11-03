#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define NumRegisters 4
#define NumMemoryLocations 8
#define MaxInstructionLength 8
#define numFlags 3
void print(int a[],int b[], int c[]);
int split(char a[],char b[100][100], char c[100][100]);//where a is the original string and b is the tokenized string
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
  char instruction[100];//inputted raw instruction
  char inter[100][100];//intermediate array to store tokens with comments
  char instructionAfterParsing[100][100];//instruction stored after parsing and removing comments
  int size;
  int i;
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
  printf("\n");
  numlines = 0;
  while (1){//infinite loop until user quits
    scanf(" %[^\n]s",instruction);
    size = split(instruction,inter,instructionAfterParsing);
    numlines++;
    //handle the case for the first line 
    //on the first line, you can only print, quit and write - nothing else makes sense
    if (numlines == 1){
        if ( strcasecmp(instructionAfterParsing[0], toStart) != 0){
            printf("hello1???\n");
        }
    //quit  command
    else if ((strcasecmp(instructionAfterParsing[1],toQuit) == 0) && size == 2){//if the command is to quit
      break;
    }
    else if ((strcasecmp(instructionAfterParsing[1],toQuit) == 0) && size != 2){//syntax error if there is any argument to quit
      printf("hello2??\n");
      printf("\n");
    }
    //print command
    else if ((strcasecmp(instructionAfterParsing[1],toPrint) == 0) && size == 2){//if the command is to print
      print(registers,memory,flags);
    }
    else if ((strcasecmp(instructionAfterParsing[1],toPrint) == 0) && size != 2){//syntax error if there is any argument to print
      printf("hello3???\n");
      printf("\n");
    }
    //read command
    else if ((strcasecmp(instructionAfterParsing[1],toRead) == 0) && size == 4){//if the command is to print
      if ( tolower(instructionAfterParsing[3][0]) == 'm'){
        read(memory,(instructionAfterParsing[3][1]-'0'),atoi(instructionAfterParsing[2]));//goes array,position,num
      }
      else if ( tolower(instructionAfterParsing[3][0]) == 'r'){
        read(registers,(instructionAfterParsing[3][1]-'0'),atoi(instructionAfterParsing[2]));//goes array,position,num
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0],toRead) == 0) && size != 4){//if there is an illegal number of arguments
        printf("hello4???\n");
        printf("\n");
    }
    //write command
    else if ((strcasecmp(instructionAfterParsing[1],toWrite)) == 0 && size == 3){//if the input command is to write
      if (tolower(instructionAfterParsing[2][0]) == 'm'){
        write(memory,(instructionAfterParsing[2][1] - '0'));
      }
      else if (tolower(instructionAfterParsing[2][0]) == 'r'){
        write(registers, (instructionAfterParsing[2][1] - '0'));
      }
    }
    else if ((strcasecmp(instructionAfterParsing[1],toWrite)) == 0 && size != 3){//illegal number of arguments
      printf("hello5???\n");
      printf("\n");
    }
    //else invalid command
    else{
      printf("hello6???\n");
      printf("\n");
      }
    }
    //end of first line checking
    else {
    //quit command
    if ((strcasecmp(instructionAfterParsing[0],toQuit) == 0) && size == 1){//if the command is to quit
      break;
    }
    else if ((strcasecmp(instructionAfterParsing[0],toQuit) == 0) && size != 1){//syntax error if there is any argument to quit
      printf("hello7???\n");
      printf("\n");
    }
    //print command
    else if ((strcasecmp(instructionAfterParsing[0],toPrint) == 0) && size == 1){//if the command is to print
      print(registers,memory,flags);
    }
    else if ((strcasecmp(instructionAfterParsing[0],toPrint) == 0) && size != 1){//syntax error if there is any argument to print
      printf("hello8???\n");
      printf("\n");
    }
    //read command
    else if ((strcasecmp(instructionAfterParsing[0],toRead) == 0) && size == 3){//if the command is to print
      if ( tolower(instructionAfterParsing[2][0]) == 'm'){
        read(memory,(instructionAfterParsing[2][1]-'0'),atoi(instructionAfterParsing[1]));//goes array,position,num
      }
      else if ( tolower(instructionAfterParsing[2][0]) == 'r'){
        read(registers,(instructionAfterParsing[2][1]-'0'),atoi(instructionAfterParsing[1]));//goes array,position,num
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0],toRead) == 0) && size != 3){//if there is an illegal number of arguments
        printf("hello9???\n");
        printf("\n");
    }
    //write command
    else if ((strcasecmp(instructionAfterParsing[0],toWrite)) == 0 && size == 2){//if the input command is to write
      if (tolower(instructionAfterParsing[1][0]) == 'm'){
        write(memory,(instructionAfterParsing[1][1] - '0'));
      }
      else if (tolower(instructionAfterParsing[1][0]) == 'r'){
        write(registers, (instructionAfterParsing[1][1] - '0'));
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0],toWrite)) == 0 && size != 2){//illegal number of arguments
      printf("hello10???\n");
      printf("\n");
    }
    //add command
    else if ((strcasecmp(instructionAfterParsing[0], toAdd) == 0) && size == 3){
      if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'r'){
        add(flags,registers, memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'm'){
        add(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'r'){
        add(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'm'){
        printf("hello11???\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toAdd) == 0) && size != 3){//if the number of arguments are off
       printf("hello12???\n");
       printf("\n");
    }
    //subtract command
    else if ((strcasecmp(instructionAfterParsing[0], toSubtract) == 0) && size == 3){
      if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'r'){
        subtract(flags,registers, memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'm'){
        subtract(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0])== 'r' && tolower(instructionAfterParsing[2][0]) == 'r'){
        subtract(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'm'){
        printf("hello13???\n");
        printf("\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toSubtract) == 0) && size != 3){//if the number of arguments are off
       printf("hello14???\n");
       printf("\n");
    }
    //multiply command
    else if ((strcasecmp(instructionAfterParsing[0], toMultiply) == 0) && size == 3){
      if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'r'){
        multiply(flags,registers, memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'm'){
        multiply(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'r'){
        multiply(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'm'){
        printf("hello15???\n");
        printf("\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toMultiply) == 0) && size != 3){//if the number of arguments are off
       printf("hello16???\n");
       printf("\n");
    }
    //divide command
    else if ((strcasecmp(instructionAfterParsing[0], toDivide) == 0) && size == 3){
      if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'r'){
        divide(flags,registers, memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'm'){
        divide(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'r'){
        divide(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'm'){
        printf("hello17???\n");
        printf("\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toDivide) == 0) && size != 3){//if the number of arguments are off
       printf("hello18???\n");
       printf("\n");
    }
    //mod command
    else if ((strcasecmp(instructionAfterParsing[0], toMod) == 0) && size == 3){
      if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'r'){
        mod(flags,registers, memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'm'){
        mod(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'r'){
        mod(flags,registers,registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'm'){
        printf("hello19???\n");
        printf("\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toMod) == 0) && size != 3){//if the number of arguments are off
       printf("hello20???\n");
       printf("\n");
    }
    //move command
    else if ((strcasecmp(instructionAfterParsing[0], toMove) == 0) && size == 3){
      if ( tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'r'){
        move(memory, (instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'm'){
        move(registers,(instructionAfterParsing[1][1] - '0'), memory, (instructionAfterParsing[2][1] - '0'));
      }
      else if  ( tolower(instructionAfterParsing[1][0]) == 'r' && tolower(instructionAfterParsing[2][0]) == 'r'){
        move(registers,(instructionAfterParsing[1][1] - '0'), registers, (instructionAfterParsing[2][1] - '0'));
      }
      else if (tolower(instructionAfterParsing[1][0]) == 'm' && tolower(instructionAfterParsing[2][0]) == 'm'){
        printf("hello21???\n");
        printf("\n");
      }
    }
    else if ((strcasecmp(instructionAfterParsing[0], toMove) == 0) && size != 3){//if the number of arguments are off
       if ( size != 0){
       printf("hello22???\n");
       printf("\n");
       }
    }
    //comp command
    else if ((strcasecmp(instructionAfterParsing[0], toCompare) == 0) && size == 3){
        comp(flags, registers, (instructionAfterParsing[1][1] - '0'),(instructionAfterParsing[2][1] - '0'));
    }
    //else invalid command
    else {  
            printf("hello23???\n");
            printf("\n");
        }
    }//if not on the first line
  }//end of while loop
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
  printf("\n");
}
/*this function tokenizes a string */
int split(char a[], char b[100][100], char c[100][100]){
  int k = 0;//number of tokens including comments
  int ctr = 0;//number of comments excluding comments
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

