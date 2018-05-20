#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct student {
    char name[127];
    int id;
    float grade[2];
};

void writeStudents() {
    FILE *fp;
    fp  = fopen("students.dat", "wb");
    struct student s1;
    int i  = 0;
    while (1){
        i++;
        printf("\n[%02d] Enter the student's name: ", i);
        fgets(s1.name, 127, stdin);
        size_t len = strlen(s1.name);
        if (len > 0 && s1.name[len-1] == '\n') {
            s1.name[--len] = '\0';
        }
        printf("[%02d] Enter the student's ID: ", i);
        scanf("%d", &s1.id);
        for (int j = 1; j <= 2; j++){
            printf("[%02d] Enter the student's grade for test %d: ", i, j);
            scanf("%f", &s1.grade[j-1]);
        }

        fwrite(&s1, sizeof(s1), 1, fp);     



        printf("\nContinue? (Y/N)\n");
        fflush(stdin);
        char prompt = getch();
        if (prompt =='N' || prompt == 'n'){
            break;
        }
        fflush(stdin);

    }
    printf("\n");
    fclose(fp);
}

void displayStudents() {
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
}

int main() {

    writeStudents();
    displayStudents();
    return 0;

}