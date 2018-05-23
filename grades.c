#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "grades.h"



int testsMenu(){
    system("cls");
    printf("\n============================================");
    printf("\n Choose the test");
    printf("\n============================================");
    printf("\n\n [1] Test 1");
    printf("\n [2] Test 2");
    printf("\n\n\n [0] Go Back");
    printf("\n\n============================================\n\n");
    int choice = intInput();
    switch(choice){
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 0:
            return 0;
            break;
        default:
            printf("Option does not exist\n");
            system("pause");
            break;
    }
    fflush(stdin);
    return -1;
}

int addTest(){
    FILE *fp, *ftemp;
    student s1;
    fp = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");

    int chosenTest = testsMenu() - 1;
    if (chosenTest == -1) { return 0; };
    if (added[chosenTest] == 1) {
        printf("\nThis test has already been added. Are you sure you want to overwrite it? (Y/N)\n");
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
    }
    fflush(stdin);
    printf("\n============================================");
    printf("\n Test %d", chosenTest+1);
    printf("\n============================================\n");
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        printf("\nPlease enter the grade for %s: ", s1.name);
        s1.test[chosenTest] = floatInput();
        fwrite(&s1, sizeof(s1), 1, ftemp);
    }
    fclose(ftemp);
    fclose(fp);

    fp = fopen("students.dat", "wb");
    ftemp = fopen("temp.dat", "rb");

    while(1){
        fread(&s1, sizeof(s1), 1, ftemp);
        if(feof(ftemp)){
            break;
        }
        fwrite(&s1, sizeof(s1), 1, fp);
    }

    fclose(ftemp);
    fclose(fp);
    added[chosenTest] = 1;
    return 0;
}

int deleteTest(){
    FILE *fp, *ftemp;
    student s1;
    fp = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");

    int chosenTest = testsMenu() - 1;
    if (chosenTest == -1) { return 0; };
    printf("\nAre you sure you want to delete Test %d? (Y/N)\n", chosenTest+1);
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
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        s1.test[chosenTest] = -1;
        fwrite(&s1, sizeof(s1), 1, ftemp);
    }
    fclose(ftemp);
    fclose(fp);

    fp = fopen("students.dat", "wb");
    ftemp = fopen("temp.dat", "rb");

    while(1){
        fread(&s1, sizeof(s1), 1, ftemp);
        if(feof(ftemp)){
            break;
        }
        fwrite(&s1, sizeof(s1), 1, fp);
    }

    fclose(ftemp);
    fclose(fp);
    added[chosenTest] = 0;
    return 0;
}

void displayTest(){
    FILE *fp;
    fp = fopen("students.dat", "rb");
    student s1;
    int chosenTest = testsMenu() - 1;
    if (added[chosenTest] == 1){
        printf("\n============================================");
        printf("\n Test %d", chosenTest+1);
        printf("\n============================================\n");
        while(1){
            fread(&s1, sizeof(s1), 1, fp);
            if (feof(fp)){
                break;
            }
            printf("\n%s: %.2f", s1.name, s1.test[chosenTest]);
        }
    } else {
        printf("\nSorry. This test was not added.");
    }
    printf("\n \n");
    system("pause");
    fclose(fp);
}

int projectsMenu(){
    system("cls");
    printf("\n============================================");
    printf("\n Choose the project");
    printf("\n============================================");
    printf("\n\n [1] Project 1");
    printf("\n [2] Project 2");
    printf("\n [3] Project 3");
    printf("\n [4] Project 4");
    printf("\n\n\n [0] Go Back");
    printf("\n\n============================================\n\n");
    int choice = intInput();
    switch(choice){
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 4;
            break;
        case 0:
            return 0;
            break;
        default:
            printf("Option does not exist\n");
            system("pause");
            break;
    }
    fflush(stdin);
    return -1;
}

int addProject(){
    FILE *fp, *ftemp;
    student s1;
    fp = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");

    int chosenProject = projectsMenu() - 1;
    if (chosenProject == -1) { return 0; };
    if (added[chosenProject + 2] == 1) {
        printf("\nThis project has already been added. Are you sure you want to overwrite it? (Y/N)\n");
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
    }
    fflush(stdin);
    printf("\n============================================");
    printf("\n Project %d", chosenProject+1);
    printf("\n============================================\n");
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        printf("\nPlease enter the grade for %s: ", s1.name);
        s1.work[chosenProject] = floatInput();
        fwrite(&s1, sizeof(s1), 1, ftemp);
    }
    fclose(ftemp);
    fclose(fp);

    fp = fopen("students.dat", "wb");
    ftemp = fopen("temp.dat", "rb");

    while(1){
        fread(&s1, sizeof(s1), 1, ftemp);
        if(feof(ftemp)){
            break;
        }
        fwrite(&s1, sizeof(s1), 1, fp);
    }

    fclose(ftemp);
    fclose(fp);
    added[chosenProject+2] = 1;
    return 0;
}

void displayProject(){
    FILE *fp;
    fp = fopen("students.dat", "rb");
    student s1;
    int chosenProject = projectsMenu() - 1;
    if (added[chosenProject+2] == 1){
        printf("\n============================================");
        printf("\n Project %d", chosenProject+1);
        printf("\n============================================\n");
        while(1){
            fread(&s1, sizeof(s1), 1, fp);
            if (feof(fp)){
                break;
            }
            printf("\n%s: %.2f", s1.name, s1.work[chosenProject]);
        }
    } else {
        printf("\nSorry. This project was not added.");
    }
    printf("\n \n");
    system("pause");
    fclose(fp);
}

int deleteProject(){
    FILE *fp, *ftemp;
    student s1;
    fp = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");

    int chosenProject = projectsMenu() - 1;
    if (chosenProject == -1) { return 0; };
    printf("\nAre you sure you want to delete Project %d? (Y/N)\n", chosenProject+1);
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
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        s1.work[chosenProject] = -1;
        fwrite(&s1, sizeof(s1), 1, ftemp);
    }
    fclose(ftemp);
    fclose(fp);

    fp = fopen("students.dat", "wb");
    ftemp = fopen("temp.dat", "rb");

    while(1){
        fread(&s1, sizeof(s1), 1, ftemp);
        if(feof(ftemp)){
            break;
        }
        fwrite(&s1, sizeof(s1), 1, fp);
    }

    fclose(ftemp);
    fclose(fp);
    added[chosenProject+2] = 0;
    return 0;
}
