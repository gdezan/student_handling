#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "grades.h"

void initAdded() {
    FILE *fp;
    student s1;
    fp = fopen("students.dat", "rb");
    fread(&s1, sizeof(s1), 1, fp);
    for (int i = 0; i <= 6; i++){
        added[i] = 0;
    }
    if (s1.test[0] != -1){ added[0] = 1;}
    if (s1.test[1] != -1){ added[1] = 1;}
    if (s1.work[0] != -1){ added[2] = 1;}
    if (s1.work[1] != -1){ added[3] = 1;}
    if (s1.work[2] != -1){ added[4] = 1;}
    if (s1.work[3] != -1){ added[5] = 1;}
    fclose(fp);
}

void removeNL(char *input){
    size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[--len] = '\0';
    }
}

int intInput() {
    int number;
    char inputString[127];
    char *endBuff;
    fgets(inputString, 127, stdin);
    removeNL(inputString);
    number = strtol(inputString, &endBuff, 10);
    while (*endBuff != '\0'){
        printf("Please enter a valid number: ");
        fgets(inputString, 127, stdin);
        removeNL(inputString);
        number = strtol(inputString, &endBuff, 10);
    }
    return number;
}

float floatInput() {
    float number;
    char inputString[127];
    char *endBuff;
    fgets(inputString, 127, stdin);
    removeNL(inputString);
    number = strtod(inputString, &endBuff);
    while (*endBuff != '\0'){
        printf("Please enter a valid number: ");
        fgets(inputString, 127, stdin);
        removeNL(inputString);
        number = strtod(inputString, &endBuff);
    }
    return number;
}

int writeStudents() {
    
    printf("\nThis will delete everything in your file and start a new one.\nAre you sure you want to do this? (Y/N)\n");
    char prompt;
    while (1){
        fflush(stdin);
        prompt = getchar();
        if (prompt == 'Y' || prompt == 'y' || prompt == 'n' || prompt == 'N'){
            break;
        }
        printf("\nPlease type \"Y\" or \"N\"\n");
    }
    if (prompt == 'N' || prompt == 'n'){
        return 0;
    }
    fflush(stdin);
    FILE *fp;
    fp  = fopen("students.dat", "wb");
    student s1;
    int i  = 0;
    while (1){
        i++;
        printf("\n[%02d] Enter the student's name: ", i);
        fgets(s1.name, 127, stdin);
        removeNL(s1.name);
        printf("[%02d] Enter the student's ID: ", i);
        s1.id = intInput();   
        s1.test[0] = -1;
        s1.test[1] = -1;
        s1.work[0] = -1;
        s1.work[1] = -1;
        s1.work[2] = -1;
        s1.work[3] = -1;       
        fwrite(&s1, sizeof(s1), 1, fp);     
        printf("\nContinue? (Y/N)\n");
        char prompt;
        while (1){
            fflush(stdin);
            prompt = getchar();
            if (prompt == 'Y' || prompt == 'y' || prompt == 'n' || prompt == 'N'){
                break;
            }
            printf("\nPlease type \"Y\" or \"N\"\n");
        }
        if (prompt == 'N' || prompt == 'n'){
            break;
        }

        fflush(stdin);

    }
    printf("\n");
    fclose(fp);
    return 0;
}


void addStudent(){
    system("cls");
    fflush(stdin);
    FILE *fp;
    fp  = fopen("students.dat", "ab");
    student s1;

    printf("\nEnter the student's name: ");
    fgets(s1.name, 127, stdin);
    removeNL(s1.name);
    printf("Enter the student's ID: ");
    s1.id = intInput();
    for (int i = 0; i <= 1; i++){
        if(added[i] == 1){
            printf("Enter the the student's grade for Test %d: ", i+1);
            s1.test[i] = floatInput();
        }
    }
    fwrite(&s1, sizeof(s1), 1, fp);     
    fflush(stdin);

    printf("\n");
    fclose(fp);
}

void printStudent(student st) {
    printf("\n============================================");
    printf("\nName: %s", st.name);
    printf("\nID: %d", st.id);
    printf("\n============================================");
}

void displayStudent() {
    fflush(stdin);
    student s1;
    FILE *fr;
    fr = fopen("students.dat", "rb");
    char search[127];
    printf("Enter the student's full name: ");
    fgets(search, 127, stdin);
    removeNL(search);
    int found = 0;
    while (1){
        fread(&s1, sizeof(s1), 1, fr);
        if(feof(fr)){
            break;
        }
        if (strcmp(search, s1.name) == 0){
            found = 1;
            printStudent(s1);
            if (added[0] == 1 || added[1] == 1){
                printf("\nTESTS \n");
                if(added[0] == 1){
                    printf("\nTest 1: %.2f", s1.test[0]);
                }
                if(added[1] == 1){
                    printf("\nTest 2: %.2f", s1.test[1]);
                }
                printf("\n============================================\n");
            }
        }
        
    }
    if (found == 0){
        printf("\nSorry. The student was not found.");
    }
    printf("\n\n");
    system("pause");
    fclose(fr);

}

void displayAllStudents() {
    fflush(stdin);
    printf(" STUDENTS\n");
    student s1;
    FILE *fr;
    fr = fopen("students.dat", "rb");
    while (1){
        fread(&s1, sizeof(s1), 1, fr);
        if(feof(fr)){
            break;
        }
        printStudent(s1);
    }
    fclose(fr);
    printf("\n");
    system("pause");
}


void deleteStudent() {
    fflush(stdin);
    FILE *fp, *ftemp;
    fp  = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");
    student s1;
    char search[127];
    printf("\nEnter the student's full name: ");
    fgets(search, 127, stdin);
    removeNL(search);
    int found = 0;
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        if (strcmp(search, s1.name) == 0){
            printStudent(s1);
            found = 1;
            printf("\nDelete this student? (Y/N)\n");
            char prompt;
            while (1){
                fflush(stdin);
                prompt = getchar();
                if (prompt == 'Y' || prompt == 'y' || prompt == 'n' || prompt == 'N'){
                    break;
                }
                printf("\nPlease type \"Y\" or \"N\"\n");
            }
            if (prompt == 'N' || prompt == 'n'){
                fwrite(&s1, sizeof(s1), 1, ftemp);
            } else {
                printf("Student deleted.\n");
            }
        } else {
            fwrite(&s1, sizeof(s1), 1, ftemp);
        } 
    }
    fclose(fp);
    fclose(ftemp);
    if (found == 0){
        printf("Sorry. The student was not found.\n");
    } else {
        fp  = fopen("students.dat", "wb");
        ftemp = fopen("temp.dat", "rb");

        while(1){
            fread(&s1, sizeof(s1), 1, ftemp);
            if(feof(ftemp)){
                break;
            }
            fwrite(&s1, sizeof(s1), 1, fp);
        }
        fclose(fp);
        fclose(ftemp);

    }
    system("pause");
}
