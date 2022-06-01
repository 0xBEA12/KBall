#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct KnightsBallLottoPlayer 
{  	
  char firstName[20];  
	char lastName[20];  	
  int numbers[6]; 
} KBLottoPlayer; 

 typedef enum 
 {
   M0 = 0,
   M1 = 0, 
   M2 = 0, 
   M3 = 10, 
   M4 = 100, 
   M5 = 10000, 
   M6 = 1000000
  } MatchingNumbers;

//Reads string stored by fgets() until specified character
//and stores into specified structure member
//saves space since having to use this many times throughout program
int ReadUntil(char* toRead, char* readInto, char stopAtChar, int startPosition, int maxLength)
{
  int amtRead = 0;
  for (int i = startPosition; toRead[i] != stopAtChar && i < maxLength; amtRead++, i++)
  {
    readInto[amtRead] = toRead[i];
  }
  return amtRead;
}

int GetAllocationNum()
{
  char FirstLine[20];
  FILE* KBL;
  //Opens and reads first line of the file
  //to initialize required structs
  KBL = fopen("KnightsBall.in", "r");
  fgets(FirstLine, 20, KBL);
  return atoi(FirstLine);
}

KBLottoPlayer* Initialize(int N)
{
  char BodyText[20];
  fpos_t position;
  FILE* KBL;
  //Opens and reads first line of the file
  //to initialize required structs
  KBL = fopen("KnightsBall.in", "r");
  fgets(BodyText, 20, KBL);
  fgetpos(KBL, &position);
  fsetpos(KBL, &position);
  KBLottoPlayer* KBArray = malloc(N * sizeof(KBLottoPlayer));
  //Iterates N times to store player information
  //into the array of structs 
  for(int i = 0; i < N; i++)
  {
    if(isupper(fgetc(KBL)) != 0)
    {
      fseek(KBL, -1, SEEK_CUR);
      fgets(BodyText, 20, KBL);
      fgetpos(KBL, &position);
      fsetpos(KBL, &position);
     
      int n = 0;
      n += ReadUntil(BodyText, KBArray[i].lastName, ' ', 0, 20);
      ReadUntil(BodyText, KBArray[i].firstName, '\n', n+1, 20);
      fgets(BodyText, 20, KBL);
      fgetpos(KBL, &position);
      fsetpos(KBL, &position);
      //reads lotto numbers into number array
      //and then stores it into numbers member of struct
      n = 0;
      char number[3];
      number[2] = ' ';

      for(int j = 0; j < 6; j++)
      {
        number[0] = ' ';
        number[1] = ' ';
        n += ReadUntil(BodyText, number, ' ', n, 20);
        n++;
        KBArray[i].numbers[j] = atoi(number);
      }

    }
  
  }

  return KBArray;
}
//Writes in scanned numbers into WinningNums array
//and compares for matches for each Array[i].numbers
//and then uses that with enum values to write the results to KnightsBall.out
int Write(KBLottoPlayer* Array, int* MatchArray, int m, MatchingNumbers x)
{
  FILE* KBL2;
  int prize;
  int WinningNums[6];
  printf("Enter the winning Lottery numbers: ");

  for(int k = 0; k < 6; k++)
  {
    scanf( "%d", &WinningNums[k]);
  }

  KBL2 = fopen("KnightsBall.out", "w");

  for (int i = 0; i < m; i++)
  { 
    int matches = 0;
    int winningNumsIterator = 0;
    int arrayIterator = 0;
    while (winningNumsIterator < 6)
    {
      if (WinningNums[winningNumsIterator] == Array[i].numbers[arrayIterator])
      {
        matches++;
        winningNumsIterator++;
        continue;
      }

      arrayIterator++;

      if (arrayIterator == m)
      {
        winningNumsIterator++;
        arrayIterator = 0;
      }
    }
    
     MatchArray[i] = matches;
     //Associates payout to numbers matched
     if(MatchArray[i] == 0) prize = M0;
     else if(MatchArray[i] == 1) prize = M1;
     else if(MatchArray[i] ==2) prize = M2;
     else if(MatchArray[i] == 3) prize = M3;
     else if(MatchArray[i] == 4) prize = M4;
     else if(MatchArray[i] == 5) prize = M5;
     else if(MatchArray[i] == 6) prize = M6;
     fprintf(KBL2, "%s " "%s " "%s " "%d " "%s " "%s" "%d" "%s" "\n", Array[i].firstName, 
             Array[i].lastName, "matched", MatchArray[i], "numbers and won", "$", prize, ".");
     
}
  
  return 0;
}




int main()
{ 
  MatchingNumbers Match;
  int n = GetAllocationNum();
  KBLottoPlayer* Array = Initialize(n);
  int* MatchArray = malloc(n * sizeof(int));
  Write(Array, MatchArray, n, Match);
  free(Array);
  free(MatchArray);
  return 0;
}
