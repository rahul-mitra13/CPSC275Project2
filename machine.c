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
int executeInstruction(char instruction[],int i, int memory[], int registers[], int flags[], char wholeProgram[100][100]);
int findInstruction(char instruction[],char wholeProgram[100][100]);
int isLabel(char string[]);

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
  int j;
  int numlines;
  char newstr[100];
  k = 0;
  printf("\n");
  while ((scanf(" %[^\n]s",instruction)) != EOF){
  size = split(instruction, instructionAfterParsing);
  newstr[0] = '\0';
  for ( i = 0; i < size; i++){
          strcat(newstr,strcat(instructionAfterParsing[i]," "));
        }
      strcpy(wholeProgram[k++],newstr);
    }
  i = 0;
  while ( i < k){
    j = executeInstruction(wholeProgram[i], i, memory,registers,flags, wholeProgram);
    i = j;
  }
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
/*this function takes an instruction and executes it */
int executeInstruction(char instruction[],int i, int memory[], int registers[], int flags[], char wholeProgram[100][100]){
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
  char unconJump[] = "JMP";
  char jumpEq[] = "JE";
  char jumpNEq[] = "JNE";
  char jumpG[] = "JG";
  char jumpGEq[] = "JGE";
  char jumpL[] = "JL";
  char jumpLE[] = "JLE";
  char parsedIntstruction[100][100];
  char* token = strtok(instruction," ");
  int j;
  int k;
  k = 0;
  while (token){
    strcpy(parsedIntstruction[k],token);
    token = strtok(NULL," ");
    k++;
  }
    if ( i == 0){//handle the case for the first line
       //if the first label is not quit throw an error
       if ( strcasecmp(parsedIntstruction[0], toStart) != 0){
         printf("1???\n");
         exit(0);
       }
       //quit command
       else if (strcasecmp(parsedIntstruction[1], toQuit) == 0 && k == 2){
         exit(0);
       }
       else if ( strcasecmp(parsedIntstruction[1],toQuit) == 0 && k !=2 && k != 0){//illegal number of arguments to quit
         printf("2???\n");
         exit(0);
       }
       //print command
       else if (strcasecmp(parsedIntstruction[1], toPrint) == 0 && k == 2){
         print(registers, memory, flags);
       }
       else if ( strcasecmp(parsedIntstruction[1],toPrint) == 0 && k !=2 && k != 0){//illegal number of arguments to quit
         printf("3???\n");
         exit(0);
       }
       //read command
       else if ((strcasecmp(parsedIntstruction[1],toRead) == 0) && k == 4){//if the command is to print
      if ( tolower(parsedIntstruction[3][0]) == 'm'){
        read(memory,(parsedIntstruction[3][1]-'0'),atoi(parsedIntstruction[2]));//goes array,position,num
      }
      else if ( tolower(parsedIntstruction[3][0]) == 'r'){
        read(registers,(parsedIntstruction[3][1]-'0'),atoi(parsedIntstruction[2]));//goes array,position,num
        } 
      }
      else if ((strcasecmp(parsedIntstruction[1],toRead) == 0) && k != 4 && k != 0){//if there is an illegal number of arguments
        printf("4???\n");
        exit(0);
      }
      //write command
      else if ((strcasecmp(parsedIntstruction[1],toWrite)) == 0 && k == 3){//if the input command is to write
        if (tolower(parsedIntstruction[2][0]) == 'm'){
          write(memory,(parsedIntstruction[2][1] - '0'));
        }
        else if (tolower(parsedIntstruction[2][0]) == 'r'){
          write(registers, (parsedIntstruction[2][1] - '0'));
        }
      }
        else if ((strcasecmp(parsedIntstruction[1],toWrite)) == 0 && k != 3 && k != 0){//illegal number of arguments
          printf("5???\n");
          exit(0);
      }
      else if ( k != 0){
        printf("6???\n");
        exit(0);
        }
      }//end of first line parsing
      else{
        //quit command
        if ((strcasecmp(parsedIntstruction[0],toQuit) == 0) && k == 1){//if the command is to quit
          exit(0);
        }
      else if ((strcasecmp(parsedIntstruction[0],toQuit) == 0) && k != 1 && k != 0){//syntax error if there is any argument to quit
        printf("7???\n");
        exit(0);
      }
      //print command
      else if ((strcasecmp(parsedIntstruction[0],toPrint) == 0) && k == 1){//if the command is to print
        print(registers,memory,flags);
      }
      else if ((strcasecmp(parsedIntstruction[0],toPrint) == 0) && k != 1 && k != 0){//syntax error if there is any argument to print
        printf("8???\n");
        exit(0);
      }
      //read command
      else if ((strcasecmp(parsedIntstruction[0],toRead) == 0) && k == 3){//if the command is to print
      if ( tolower(parsedIntstruction[2][0]) == 'm'){
        read(memory,(parsedIntstruction[2][1]-'0'),atoi(parsedIntstruction[1]));//goes array,position,num
      }
      else if ( tolower(parsedIntstruction[2][0]) == 'r'){
        read(registers,(parsedIntstruction[2][1]-'0'),atoi(parsedIntstruction[1]));//goes array,position,num
      }
    }
    else if ((strcasecmp(parsedIntstruction[0],toRead) == 0) && k != 3 && k != 0){//if there is an illegal number of arguments
        printf("9???\n");
        exit(0);
    }
    //write command
    else if ((strcasecmp(parsedIntstruction[0],toWrite)) == 0 && k == 2){//if the input command is to write
      if (tolower(parsedIntstruction[1][0]) == 'm'){
        write(memory,(parsedIntstruction[1][1] - '0'));
      }
      else if (tolower(parsedIntstruction[1][0]) == 'r'){
        write(registers, (parsedIntstruction[1][1] - '0'));
      }
    }
    else if ((strcasecmp(parsedIntstruction[0],toWrite)) == 0 && k != 2 && k != 0){//illegal number of arguments
      printf("10???\n");
      exit(0);
    }
    //add command
    else if ((strcasecmp(parsedIntstruction[0], toAdd) == 0) && k == 3){
      if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'r'){
        add(flags,registers, memory, (parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'm'){
        add(flags,registers,registers,(parsedIntstruction[1][1] - '0'), memory, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'r'){
        add(flags,registers,registers,(parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'm'){
        printf("11???\n");
        exit(0);
      }
    }
    else if ((strcasecmp(parsedIntstruction[0], toAdd) == 0) && k != 3 && k != 0){//if the number of arguments are off
       printf("12???\n");
       exit(0);
    }
    //subtract command
    else if ((strcasecmp(parsedIntstruction[0], toSubtract) == 0) && k == 3){
      if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'r'){
        subtract(flags,registers, memory, (parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'm'){
        subtract(flags,registers,registers,(parsedIntstruction[1][1] - '0'), memory, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0])== 'r' && tolower(parsedIntstruction[2][0]) == 'r'){
        subtract(flags,registers,registers,(parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'm'){
        printf("13???\n");
        exit(0);
      }
    }
    else if ((strcasecmp(parsedIntstruction[0], toSubtract) == 0) && k != 3 && k != 0){//if the number of arguments are off
       printf("14???\n");
       exit(0);
    }
    //multiply command
    else if ((strcasecmp(parsedIntstruction[0], toMultiply) == 0) && k == 3){
      if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'r'){
        multiply(flags,registers, memory, (parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'm'){
        multiply(flags,registers,registers,(parsedIntstruction[1][1] - '0'), memory, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'r'){
        multiply(flags,registers,registers,(parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'm'){
        printf("15???\n");
        exit(0);
        }
      }
      else if ((strcasecmp(parsedIntstruction[0], toMultiply) == 0) && k != 3 && k != 0){//if the number of arguments are off
       printf("17???\n");
       exit(0);
      }
    //divide command
    else if ((strcasecmp(parsedIntstruction[0], toDivide) == 0) && k == 3){
      if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'r'){
        divide(flags,registers, memory, (parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'm'){
        divide(flags,registers,registers,(parsedIntstruction[1][1] - '0'), memory, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'r'){
        divide(flags,registers,registers,(parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'm'){
        printf("18???\n");
        exit(0);
      }
    }
    else if ((strcasecmp(parsedIntstruction[0], toDivide) == 0) && k != 3 && k != 0){//if the number of arguments are off
       printf("19???\n");
       exit(0);
    }
    //mod command
    else if ((strcasecmp(parsedIntstruction[0], toMod) == 0) && k == 3){
      if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'r'){
        mod(flags,registers, memory, (parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'm'){
        mod(flags,registers,registers,(parsedIntstruction[1][1] - '0'), memory, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'r'){
        mod(flags,registers,registers,(parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'm'){
        printf("20???\n");
        exit(0);
      }
    }
    else if ((strcasecmp(parsedIntstruction[0], toMod) == 0) && k != 3 && k != 0){//if the number of arguments are off
       printf("21???\n");
       exit(0);
    }
    //move command
    else if ((strcasecmp(parsedIntstruction[0], toMove) == 0) && k == 3){
      if ( tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'r'){
        move(memory, (parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'm'){
        move(registers,(parsedIntstruction[1][1] - '0'), memory, (parsedIntstruction[2][1] - '0'));
      }
      else if  ( tolower(parsedIntstruction[1][0]) == 'r' && tolower(parsedIntstruction[2][0]) == 'r'){
        move(registers,(parsedIntstruction[1][1] - '0'), registers, (parsedIntstruction[2][1] - '0'));
      }
      else if (tolower(parsedIntstruction[1][0]) == 'm' && tolower(parsedIntstruction[2][0]) == 'm'){
        printf("22???\n");
        exit(0);
      }
    }
    else if ((strcasecmp(parsedIntstruction[0], toMove) == 0) && k != 3 && k != 0){//if the number of arguments are off
       printf("23???\n");
       exit(0);
    }
    //comp command
    else if ((strcasecmp(parsedIntstruction[0], toCompare) == 0) && k == 3){
        if ( parsedIntstruction[1][0] == 'm' || parsedIntstruction[2][0] == 'm'){
          printf("24???\n");
          exit(0);
        }
        else{
        comp(flags, registers, (parsedIntstruction[1][1] - '0'),(parsedIntstruction[2][1] - '0'));
        }
    }
    else if ((strcasecmp(parsedIntstruction[0], toCompare) == 0) && k != 3 && k != 0){//illegal number of arguments to comp
      printf("25???\n");
      exit(0);
    }
    //unconditional jump
   /* else if ((strcasecmp(parsedIntstruction[0], unconJump) == 0) && k == 2){
      strcat(parsedIntstruction[1],":");
      printf("This is what I'm searching for = %s\n", parsedIntstruction[1]);
      i = findInstruction(parsedIntstruction[1],wholeProgram);
      return i;
    }*/
    //else invalid command
    else{
      if ( k != 0){
      printf("26???\n");
      printf("\n");
      }
    }

  }
  i++;
  return i;
}

/* int findInstruction(char instruction[], char wholeProgram[100][100]){
  int i;
  i = 0;
  while ( strcasecmp(wholeProgram[i], instruction) != 0){
    printf("I'm in here");
    i++;
  }
  return i;
}
*/
int isLabel(char string[]){
  if ( string[0] == '.' && string[strlen(string) - 1] == ':'){
    return 1;
  }
  else{
    return 0;
  }
}

