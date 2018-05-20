#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[127];
    int id;
    float grade[2];
};

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
    while (number == 0 || *endBuff != '\0'){
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
    while (number == 0 || *endBuff != '\0'){
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
    struct student s1;
    int i  = 0;
    while (1){
        i++;
        printf("\n[%02d] Enter the student's name: ", i);
        fgets(s1.name, 127, stdin);
        removeNL(s1.name);
        printf("[%02d] Enter the student's ID: ", i);
        s1.id = intInput();          
        for (int j = 1; j <= 2; j++){
            printf("[%02d] Enter the student's grade for test %d: ", i, j);
            s1.grade[j-1] = floatInput();
        }

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

void addStudent(){
    system("cls");
    fflush(stdin);
    FILE *fp;
    fp  = fopen("students.dat", "ab");
    struct student s1;
    int i  = 0;
    while (1){
        i++;
        printf("\n[%02d] Enter the student's name: ", i);
        fgets(s1.name, 127, stdin);
        removeNL(s1.name);
        printf("[%02d] Enter the student's ID: ", i);
        s1.id = intInput();
        for (int j = 1; j <= 2; j++){
            printf("[%02d] Enter the student's grade for test %d: ", i, j);
            scanf("%f", &s1.grade[j-1]);
        }

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

void printStudent(struct student st) {
    printf("\n============================================");
    printf("\nName: %s", st.name);
    printf("\nID: %d", st.id);
    printf("\nTest 1: %.2f", st.grade[0]);
    printf("\nTest 2: %.2f", st.grade[1]);
    printf("\n============================================");
}

void displayStudent() {
    system("cls");
    fflush(stdin);
    struct student s1;
    FILE *fr;
    fr = fopen("students.dat", "rb");
    char search[127];
    printf("\nEnter the student's full name: ");
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
        }
    }
    if (found == 0){
        printf("\nSorry. The student was not found.");
    }
    printf("\n");
    system("pause");

}

void displayAllStudents() {
    system("cls");
    fflush(stdin);
    printf(" STUDENTS\n");
    struct student s1;
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

void updateStudent() {
    system("cls");
    fflush(stdin);
    FILE *fp, *ftemp;
    fp  = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");
    struct student s1;
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
            printf("\nEnter the student's new name: ");
            fgets(s1.name, 127, stdin);
            removeNL(s1.name);
            printf("Enter the student's new ID: ");
            s1.id = intInput();
            for (int j = 1; j <= 2; j++){
                printf("Enter the student's new grade for test %d: ", j);
                scanf("%f", &s1.grade[j-1]);
            }
            fwrite(&s1, sizeof(s1), 1, ftemp); 
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
        printf("Student updated.\n");
    }
    system("pause");
}

void deleteStudent() {
    system("cls");
    fflush(stdin);
    FILE *fp, *ftemp;
    fp  = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");
    struct student s1;
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
        printf("\n [2] Display Student");
        printf("\n [3] Display All Students");
        printf("\n [4] Add Student");
        printf("\n [5] Modify Student");
        printf("\n [6] Delete Student");
        printf("\n\n\n [0] Exit");
        printf("\n\n============================================\n\n");

        char prompt = getchar();

        printf("\n============================================\n\n");

        if(prompt == '1'){
            writeStudents();
        } else if (prompt == '2'){
            displayStudent();
        } else if (prompt == '3'){
            displayAllStudents();
        } else if (prompt == '4'){
            addStudent();
        } else if (prompt == '5'){
            updateStudent();
        } else if (prompt == '6'){
            deleteStudent();
        } else if (prompt == '0'){
            return 0;
        }
    }
}