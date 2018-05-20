#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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

void writeStudents() {
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
        scanf("%d", &s1.id);
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

void displayStudents() {
    fflush(stdin);
    struct student s1;
    FILE *fr;
    fr = fopen("students.dat", "rb");
    while (1){
        fread(&s1, sizeof(s1), 1, fr);
        if(feof(fr)){
            break;
        }
        float media = (s1.grade[0] + s1.grade[1])/2.0;
        printf("\n============================================");
        printf("\nName: %s", s1.name);
        printf("\nID: %d", s1.id);
        printf("\nAverage: %.2f", media);
    }
    printf("\n============================================");
    fclose(fr);
    printf("\n");
    system("pause");
}

int main() {
    while (1) {
        system("cls");
        printf("\n============================================");
        printf("\n Student Information");
        printf("\n============================================");
        printf("\n\n [1] Write Students");
        printf("\n [2] Display Students");
        printf("\n [0] Exit");
        printf("\n\n============================================\n\n");

        char prompt = getchar();

        if(prompt == '1'){
            writeStudents();
        } else if (prompt == '2'){
            displayStudents();
        } else if (prompt == '0'){
            return 0;
        }
    }
}