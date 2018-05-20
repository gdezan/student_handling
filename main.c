#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tst {
    char name[127];
        char student[127];
    float grade;
} test;

typedef struct stud {
    char name[127];
    int id;
} student;

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

void writeStudents() {
    system("cls");
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
}

void addTest() {
    system("cls");
    fflush(stdin);
    test p1;
    student s1;
    FILE *fp, *ftest;
    fp  = fopen("students.dat", "rb");
    printf("\nEnter the name of the test (Ex: P1): \n");
    fgets(p1.name, 127, stdin);
    removeNL(p1.name);
    ftest = fopen("tests.dat", "ab");
    while (1) {
        fread(&s1, sizeof(s1), 1, fp);
        if (feof(fp)){
            break;
        }
        printf("Enter the grade for \"%s\": ", s1.name);
        strcpy(p1.student, s1.name);
        p1.grade = floatInput();
        fwrite(&p1, sizeof(p1), 1, ftest);   
    }
    fclose(ftest);
    fclose(fp);
    system("pause");
}

int testMenu() {
    FILE *ftest;
    test p1;
    ftest  = fopen("tests.dat", "rb");
    printf("Tests\n");
    int i = 0;
    while (1){
        fread(&p1, sizeof(p1), 1, ftest);
        if (feof(ftest)){
            break;
        }
        char menutitle[127];
        if (strcmp(menutitle, p1.name) != 0){
            i++;
            printf("\n[%d] %s", i, p1.name);
            strcpy(menutitle, p1.name);
        }
    }
    printf("\nChoose the test: ");
    fflush(stdin);
    int num = intInput();
    switch (num){
        case 1:
            if (i > 0){
                return 1;
                break;
            }
        case 2:
            if (i > 1){
                return 2;
                break;
            }
        case 3:
            if (i > 2){
                return 3;
                break;
            }
        case 4:
            if (i > 3){
                return 4;
                break;
            }
        default:
            printf("\nTest not available");
            break;
    }
    return -1;
}

void addStudent(){
    system("cls");
    fflush(stdin);
    FILE *fp;
    fp  = fopen("students.dat", "ab");
    student s1;
    int i  = 0;
    while (1){
        i++;
        printf("\n[%02d] Enter the student's name: ", i);
        fgets(s1.name, 127, stdin);
        removeNL(s1.name);
        printf("[%02d] Enter the student's ID: ", i);
        s1.id = intInput();
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
    test p1;
    FILE *fr, *ftest;
    fr = fopen("students.dat", "rb");
    ftest = fopen("tests.dat", "rb");
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
            printStudent(s1);
            found = 1;
            printf("\n\nTESTS\n");
            while (1){
                fread(&p1, sizeof(p1), 1, ftest);
                if (feof(ftest)){
                    break;
                }
                if (strcmp(s1.name,p1.student) == 0){
                    printf("\n%s: %.2f", p1.name, p1.grade);
                }
            }
        }
        
    }
    if (found == 0){
        printf("\nSorry. The student was not found.");
    }
    printf("\n\n============================================\n\n");
    system("pause");
    fclose(fr);
    fclose(ftest);

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

int main() {
    while (1) {
        system("cls");
        printf("\n============================================");
        printf("\n Student Information");
        printf("\n============================================");
        printf("\n\n [1] New Students File");
        printf("\n [2] Add Student");
        printf("\n [3] Display Student");
        printf("\n [4] Delete Student");
        printf("\n [5] Add Test");
        printf("\n [6] Display Test");
        printf("\n [7] Delete Test");
        printf("\n [8] Display All Students");
        printf("\n\n\n [0] Exit");
        printf("\n\n============================================\n\n");

        fflush(stdin);
        int prompt = intInput();

        printf("\n============================================\n\n");

        switch(prompt){
            case 1:
                writeStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                addTest();
                break;
            case 8:
                displayAllStudents();
                break;
            case 0:
                return 0;
            default:
                printf("Option does not exist");
                system("pause");
                break;
        }
    }
}