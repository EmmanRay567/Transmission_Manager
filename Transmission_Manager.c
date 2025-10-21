#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BUFFER 80
#define TAG_LENGTH 80

// Author: Emmanuel Edward Ray
// Date: 4/14/2025
// Instructor: Najib Saylani
// Course: COP2220C
// Description: 
// Menu-driven program that manages transmission data, 
// allowing users to add, search, write, and read records from files.

typedef struct Transmission {
    char Tag[6];        // letters and digits only
    int miles;          // digits only
    double failureRate; // decimal format 0.##
} Transmission;

// Prototypes
int menu();
void populateTransmissions(Transmission *pTrans, int totalTrans);
void getSearchTag(char *pinput, char *psearchTag);
void GetTransmissionTag(Transmission *pTrans, int Current);
void GetMiles(Transmission *pTrans, int Current);
void GetFailureRate(Transmission *pTrans, int Current);
void DisplayTransmissions(Transmission *pTrans, int totalTrans);
void AddTransmission(Transmission *pTrans, int *totalTrans);
int SearchForTag(Transmission *pTrans, char *psearchID, int totalTrans);
void writeTransmissions(Transmission *pTrans, int totalTrans);
void readTransmissions();

// Validation prototypes
bool checkTag(char *pinput);
bool CheckMiles(char *pinput);
bool CheckFailureRate(char *pinput);

// Main program
int main() {
    int totalTrans = 5;
    int choice = 0;
    char input[BUFFER] = " ";
    char searchTag[TAG_LENGTH] = " ";
    Transmission *pTrans = malloc(100 * sizeof(Transmission));
    if (!pTrans) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    populateTransmissions(pTrans, totalTrans);

    while (choice != 5) {
        choice = menu();
        switch (choice) {
            case 1:
                AddTransmission(pTrans, &totalTrans);
                break;
            case 2:
                printf("\nSearching for a Tag...\n");
                getSearchTag(input, searchTag);
                int Found = SearchForTag(pTrans, searchTag, totalTrans);
                if (Found == -1)
                    printf("%s was not found!\n", searchTag);
                else
                    printf("\nRecord Found:\n\nTransmission ID: %s\nMiles: %d\nFailure Rate: %.2lf\n",
                           pTrans[Found].Tag, pTrans[Found].miles, pTrans[Found].failureRate);
                break;
            case 3:
                printf("\nWriting transmissions to file...\n");
                writeTransmissions(pTrans, totalTrans);
                printf("Successfully written to file!\n");
                break;
            case 4:
                printf("\nReading transmissions from file...\n");
                readTransmissions();
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid selection! Please re-enter.\n");
        }
    }

    free(pTrans);
    return 0;
}

// Menu
int menu() {
    int choice;
    char input[BUFFER];
    printf("\n-1- Add new Transmission"
           "\n-2- Find Transmission by Tag Number"
           "\n-3- Write all Transmissions to file"
           "\n-4- Read all Transmissions from file"
           "\n-5- Quit Program"
           "\n===> Enter choice: ");
    fgets(input, BUFFER, stdin);
    choice = atoi(input);
    return choice;
}

// Initial data population
void populateTransmissions(Transmission *pTrans, int totalTrans) {
    strcpy(pTrans[0].Tag, "111QWE");
    pTrans[0].miles = 25967;
    pTrans[0].failureRate = 0.02;

    strcpy(pTrans[1].Tag, "222ASD");
    pTrans[1].miles = 84739;
    pTrans[1].failureRate = 0.04;

    strcpy(pTrans[2].Tag, "333JKL");
    pTrans[2].miles = 100967;
    pTrans[2].failureRate = 0.07;

    strcpy(pTrans[3].Tag, "444ZXC");
    pTrans[3].miles = 25841;
    pTrans[3].failureRate = 0.05;

    strcpy(pTrans[4].Tag, "555FGH");
    pTrans[4].miles = 24000;
    pTrans[4].failureRate = 0.01;
}

// Input Validations
bool checkTag(char *pinput) {
    if (strlen(pinput) != 6) return false;
    for (int i = 0; i < 3; i++)
        if (!isdigit(pinput[i])) return false;
    for (int i = 3; i < 6; i++)
        if (!isalpha(pinput[i])) return false;
    return true;
}

bool CheckMiles(char *pinput) {
    for (int i = 0; i < strlen(pinput); i++)
        if (!isdigit(pinput[i])) return false;
    return true;
}

bool CheckFailureRate(char *pinput) {
    int dotCount = 0;
    for (int i = 0; i < strlen(pinput); i++) {
        if (!isdigit(pinput[i]) && pinput[i] != '.') return false;
        if (pinput[i] == '.') dotCount++;
    }
    return (dotCount == 1);
}

// Get user input functions
void getSearchTag(char *pinput, char *psearchTag) {
    printf("Enter the ID to search for: ");
    fgets(pinput, BUFFER, stdin);
    strtok(pinput, "\n");
    while (!checkTag(pinput)) {
        printf("Invalid! Re-enter the ID to search for: ");
        fgets(pinput, BUFFER, stdin);
        strtok(pinput, "\n");
    }
    strcpy(psearchTag, pinput);
}

void GetTransmissionTag(Transmission *pTrans, int Current) {
    char input[BUFFER];
    printf("\nEnter Transmission Tag (3 digits followed by 3 letters): ");
    fgets(input, BUFFER, stdin);
    strtok(input, "\n");
    while (!checkTag(input)) {
        printf("Invalid format! Try again: ");
        fgets(input, BUFFER, stdin);
        strtok(input, "\n");
    }
    strcpy(pTrans[Current].Tag, input);
}

void GetMiles(Transmission *pTrans, int Current) {
    char input[BUFFER];
    printf("Enter Transmission Miles: ");
    fgets(input, BUFFER, stdin);
    strtok(input, "\n");
    while (!CheckMiles(input)) {
        printf("Invalid! Enter whole numbers only: ");
        fgets(input, BUFFER, stdin);
        strtok(input, "\n");
    }
    pTrans[Current].miles = atoi(input);
}

void GetFailureRate(Transmission *pTrans, int Current) {
    char input[BUFFER];
    printf("Enter Failure Rate (0.##): ");
    fgets(input, BUFFER, stdin);
    strtok(input, "\n");
    while (!CheckFailureRate(input)) {
        printf("Invalid! Enter rate in format 0.##: ");
        fgets(input, BUFFER, stdin);
        strtok(input, "\n");
    }
    pTrans[Current].failureRate = atof(input);
}

// Add new record
void AddTransmission(Transmission *pTrans, int *totalTrans) {
    int Current = *totalTrans;
    GetTransmissionTag(pTrans, Current);
    GetMiles(pTrans, Current);
    GetFailureRate(pTrans, Current);
    (*totalTrans)++;
    printf("\nTransmission added successfully!\n");
}

// Search for a tag
int SearchForTag(Transmission *pTrans, char *psearchID, int totalTrans) {
    for (int i = 0; i < totalTrans; i++) {
        if (strcmp(pTrans[i].Tag, psearchID) == 0)
            return i;
    }
    return -1;
}

// Display transmissions
void DisplayTransmissions(Transmission *pTrans, int totalTrans) {
    for (int i = 0; i < totalTrans; i++) {
        printf("\nTransmission ID: %s", pTrans[i].Tag);
        printf("\nMiles: %d", pTrans[i].miles);
        printf("\nFailure Rate: %.2lf\n", pTrans[i].failureRate);
        printf("----------------------------------------\n");
    }
}

// Write to file
void writeTransmissions(Transmission *pTrans, int totalTrans) {
    FILE *pwrite = fopen("Transmissions.dat", "wb");
    if (!pwrite) {
        printf("Error creating file for writing.\n");
        return;
    }
    fwrite(pTrans, sizeof(Transmission), totalTrans, pwrite);
    fclose(pwrite);
}

// Read from file
void readTransmissions() {
    FILE *pread = fopen("Transmissions.dat", "rb");
    if (!pread) {
        printf("File not found.\n");
        return;
    }

    Transmission trans;
    printf("\n--- Transmissions from File ---\n");
    while (fread(&trans, sizeof(Transmission), 1, pread))
        printf("ID: %s | Miles: %d | Failure Rate: %.2lf\n",
               trans.Tag, trans.miles, trans.failureRate);

    fclose(pread);
}
