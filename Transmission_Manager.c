#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define buffer 80
#define Taglength 80

//Author: Emmanuel Edward Ray
//today's date: 4/14/2025
//Instructor: Najib Saylani
//Course: COP2220c
//Description: This assignment Allows the user to select from
//a variety of options, such as adding a transmission, writing or reading to a file, searching for a tag, or quitting the program.
struct Transmission
{
    char Tag[6]; //letters and digits only  try for the exam to declare a char *   eg. char* Tag;
    int miles;  //digits only
    double failureRate; //a real number for 4% we will enter 0.04 format 0.##
}typedef Transmission; // gives another name for  this transmission.

//prototypes:
int menu(int choice);
void populateTransmissions(struct Transmission* pTrans,int totalTrans);
void getSearchTag(char*pinput, char*psearchTag);
void GetTransmissionTag(struct Transmission*pTrans, int Current);
void GetMiles(struct Transmission*pTrans,int Current);
void GetFailureRate(struct Transmission*pTrans, int Current);
void DisplayTransmissions(struct Transmission* pTrans, int totalTrans);
void AddTransmission(struct Transmission*pTrans, int totalTrans, int Current);
int SearchForTag(struct Transmission*pTrans, char*psearchID, int totalTrans);
void writeTransmissions(struct Transmission* pTrans, int totalTrans);
void readTransmissions();

//--------------------------Input Validations:
bool checkTag(char* pinput);
bool CheckMiles (char*pinput);
bool CheckFailureRate(char* pinput);


int main()
{
    //Declarations:
    int Current = 0;
    int totalTrans = 5;
    int choice = 0;
    char input[buffer] = " ";
    char* pinput = NULL;
    char searchTag[Taglength] = " ";
    char* psearchTag = searchTag;
    int Found = -1;
    int option = 0;
    Transmission*pTrans =(Transmission*)malloc(100*sizeof(Transmission)); //Dynamically allocate memory for 100 Transmissions
    populateTransmissions(pTrans,totalTrans); // populates transmissions
//-------------input/Output:
      while(choice != 5) {
            choice = menu(choice);
             switch(choice) {
           case 1: AddTransmission(pTrans,totalTrans,Current);
                   totalTrans++;
                       break;
           case 2: printf("Press Any key to search for a Tag...\n"); getchar();
                   system("cls");
               getSearchTag(input,psearchTag);
               Found = SearchForTag(pTrans, psearchTag, totalTrans);
               if(Found == -1)
                printf("%s", " %s was not found!\n");
                 else
                   DisplayTransmissions(pTrans, totalTrans + Found);
                  break;

           case 3: printf("\nHit any key to write all  to file...\n");getchar();
                   printf("Successfully written to the file Transmissions!");
                   writeTransmissions(pTrans, totalTrans);
                        break;
           case 4: printf("\nHit any key to readd all engine from file...\n");getchar();
                   printf("Data has been succesfully read from a file!");
                     readTransmissions(pTrans, totalTrans);
                        break;
           case 5: printf("Goodbye!");
                   exit(1);
                   default: printf("%s", "Wrong selection! re-enter...\n");

             }
      }
      return 0;
      }
//processing---------------------------------------------------------------
// this function generates the menu
int menu(int choice)
{
  choice = 0;
  char input[buffer] = " ";
  char* pinput = NULL;
    printf( "\n-1-Add new Transmission"
            "\n-2-Find Transmission by Tag Number\n"
            "\n-3-Write all Transmissions to file\n"
            "\n-4-Read all Transmissions from file\n"
            "\n-5-Quit Program\n"
            "\n===>Enter choice: ");
            pinput = fgets(input, buffer, stdin);
         strtok(pinput, "\n");
choice = atoi(pinput);
    return choice;
}//end menu
// this function populates the transmissions
void populateTransmissions(struct Transmission* pTrans, int totalTrans)
{


    strcpy((pTrans + 0)->Tag, "111QWE");
    (pTrans + 0)->miles = 25967;
    (pTrans + 0)->failureRate = 0.02;

    //------------------------------------
    strcpy((pTrans + 1)->Tag, "222ASD");
    (pTrans + 1)->miles = 84739;
    (pTrans + 1)->failureRate = .04;
    //------------------------------------
    strcpy((pTrans + 2)->Tag, "333JKL");
    (pTrans + 2)->miles = 100967;
    (pTrans + 2)->failureRate = 0.07;
    //------------------------------------
    strcpy((pTrans + 3)->Tag, "444ZXC");
    (pTrans + 3)->miles = 25841 ;
    (pTrans + 3)->failureRate = 0.05;
    //------------------------------------
    strcpy((pTrans + 4)->Tag, "555FGH");
    (pTrans + 4)->miles = 24000;
    (pTrans + 4)->failureRate = 0.01;
}//end populateTransmissions

//----------------------------Input Validations:
 bool checkTag(char*pinput) {
if(strlen(pinput) != 6)
return false;
// the first for loop iterates through the first 3 characters and checks if they are a digit from 0-3
//and checks if the first 3 are not digits.
  for(int i = 0; i < 3; i++){
    if(!isdigit(*(pinput + i)))
      return false;
      else
  // this Second for loop carries on from the first for loop. Now that the first for loop when from 0-3,
  //this one goes from characters 3-6. This checks if the digits are not letters
       for(int i = 3; i < (strlen(pinput)); i++)
         if(!isalpha(*(pinput+i)))
         return false;
  }
       return true;
 }

// this checks if the Miles is == to 5 characters. If not, the program will return false
// this also makes sure that this function is a whole number.
bool CheckMiles (char*pinput) {
if(strlen(pinput) != 5 )
return false;
for(int i = 0; i < 5; i++) {

    if(!isdigit(*(pinput+i)))
        return false;
}
  for(int i = 0; i < 5; i++) { // this checks to make sure that this is not a decimal and makes sure its a whole number..
    if(isdigit < 0)
         return false;
  }

return true;
}

 //end else if(strlen(pinput) != 3)
 //This function checks the failure rate, and makes sure that this is in the format #.##
bool CheckFailureRate(char* pinput) {
int dotCount = 0;
if(strlen(pinput) != 4)
return false;
for( int i = 0; i < strlen(pinput); i++)
if(!isdigit(*(pinput + i)) && *(pinput + i) != '.')
return false;
for(int i = 0; i < strlen(pinput); i++)
if(*(pinput + i) == '.')
dotCount++;
if(dotCount != 1)
return false;
if(*(pinput + 1) != '.') //##.#
return false;
return true;

}

// This function gets the search Tag f the user, and prompts the user to reenter if they type an invalid character/
void getSearchTag(char*pinput, char*psearchTag)
{
printf("%s", "Enter the ID to search for: ");
fgets(pinput, buffer, stdin);
strtok(pinput, "\n");
while(!checkTag(pinput)) // as long as the tag format is not correct, the user will have to keep reentering the tag.
{
printf("%s", "Invalid! re-Enter the ID to search for: ");
pinput = fgets(pinput, buffer, stdin);
strtok(pinput, "\n");
}//end while checkID
strcpy(psearchTag, pinput);
return psearchTag;
}

// This function gets the transmission tag, and
void GetTransmissionTag(struct Transmission*pTrans, int Current) {

   char input[buffer] = " ";
   char* pinput = NULL;
   printf("%s", "\nEnter this engine Tag: ");
pinput = fgets(input, buffer, stdin);
strtok(pinput, "\n");
   while(!checkTag(pinput)){
   printf("%s", "Invalid! Enter this engine tag!: ");
pinput = fgets(input, buffer, stdin);
strtok(pinput, "\n");

}
 strcpy((pTrans + Current)->Tag, pinput);
}
//This converts the string input from the user into an integer and gets the miles.
void GetMiles(struct Transmission*pTrans,int Current) {
    char input[buffer] = " ";
   char* pinput = NULL;
    printf("%s", "\nEnter this Transmission Miles: ");
    pinput = fgets(input, buffer, stdin);
 strtok(pinput, "\n");
 while(!CheckMiles(pinput)){
   printf("%s", "Invalid! Enter the amount of Transmission Miles!: ");
   pinput = fgets(input, buffer, stdin);
   strtok(pinput, "\n");
}
(pTrans + Current)->miles = atof(pinput);

}
//Gets the failure rate entered by the user.
void GetFailureRate(struct Transmission*pTrans, int Current) {
    char input[buffer] = " ";
   char* pinput = NULL;
    printf("%s", "\nEnter the failure Rate: ");
 pinput = fgets(input, buffer, stdin);
strtok(pinput, "\n");
while(!CheckFailureRate(pinput)){ //as long as the failure rate format is not correct, the user has to keep reentering.
   printf("%s", "Invalid! Enter the Failure rate!: ");
pinput = fgets(input, buffer, stdin);
strtok(pinput, "\n");
 }
(pTrans + Current)->failureRate = atof(pinput);

}
// Displays the Transmissions
void DisplayTransmissions(struct Transmission* pTrans, int totalTrans) {

  printf("\nTransmission ID: %s\n"
         "\nMiles: %d\n"
         "\nFailure Rate: %lf\n ",
pTrans->Tag, pTrans ->miles, pTrans->failureRate); //accesses the ID, size, and Hp.
}
//Adds a transmission.
 void AddTransmission(struct Transmission*pTrans, int totalTrans, int Current) {
     printf("\nHere are the already built Transmissions:");
        for(int i = 0; i < totalTrans; i++) {
                         DisplayTransmissions(pTrans,i); // Displays Transmissions
printf("---------------------------------------------------------");
}
        GetTransmissionTag(pTrans,Current);
        GetMiles(pTrans,Current);
        GetFailureRate(pTrans,Current);

 }
//searches for a tag given the user's input.
int SearchForTag(struct Transmission*pTrans, char*psearchID, int totalTrans) {
    int i = 0;
while(i < totalTrans)
{
if(strcmp((pTrans + i)->Tag, psearchID) == 0)
{
return i;
}//end if strcmp
else
i++;
}//end while(i < totalTrans)
return -1;

}
// writes the values to the value.
void writeTransmissions(struct Transmission* pTrans, int totalTrans){
FILE* pwrite;
pwrite = fopen("Transmissions", "w");
if(pwrite == NULL)
{
printf("Cannot create file for writing!\n");
exit(1); //should send control back to main to continue program
}//end if(pwrite == NULL)
for(int i = 0; i < totalTrans; i++)
{
fwrite((pTrans + i), sizeof(Transmission), 1, pwrite);
}//end for i
fclose(pwrite);

}


// reads transmissions written to the file
void readTransmissions()
{
int Records = 0;
FILE* pread;
pread = fopen("Transmissions", "r");
if(pread == NULL)
{
printf("Cannot create file for reading!\n");
exit(1); //should send control back to main to continue program
}//end if(pread == NULL)
//------------------
//count how many records were saved
Transmission* Trans = (Transmission*)malloc(sizeof(Transmission));
if(Trans == NULL)
{
printf("Failed to allocate memory for Transmissions...\n");
printf("Any key to exit...\n");
exit(1);
}//end if(Trans == NULL)
while(!feof(pread))
{
fread(Trans, sizeof(Transmission), 1, pread);
if(!feof(pread))
Records++;
}//end while(!feof(pread))
fseek(pread, 0, SEEK_SET); //position to start of file
//rewind(pread);//better
//let's allocate memory to store all record
Transmission* preadTrans = (Transmission*)malloc(Records * sizeof(Transmission));
if(preadTrans == NULL)
{
printf("Failed to allocate memory for read Transmissions...\n");
printf("Any key to exit...\n");
exit(1);
}//end if(preadTrans == NULL)
int i = 0;
while(!feof(pread))
{
fread((preadTrans + i), sizeof(Transmission), 1, pread);
i++;
}//end while(!feof(pread))
//let's display all read engines
DisplayTransmissions(preadTrans, Records);
}//end readTrans
//=====================================
