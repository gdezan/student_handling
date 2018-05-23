#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "grades.h"


int main() {
    while (1) {
        initAdded();
        system("cls");
        printf("\n============================================");
        printf("\n Student Information");
        printf("\n============================================");
        printf("\n\n [1] New Students File");
        printf("\n [2] Add Student");
        printf("\n [3] Display Student");
        printf("\n [4] Delete Student");
        printf("\n [5] Add/Update Test");
        printf("\n [6] Display Test");
        printf("\n [7] Delete Test");
        printf("\n [8] Add/Update Project");
        printf("\n [9] Display Project");
        printf("\n [10] Delete Project");
        printf("\n [11] Display All Students");
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
            case 6:
                displayTest();
                break;
            case 7:
                deleteTest();
                break;
            case 8:
                addProject();
                break;
            case 9:
                displayProject();
                break;
            case 10:
                deleteProject();
                break;
            case 11:
                displayAllStudents();
                break;
            case 0:
                return 0;
            default:
                printf("Option does not exist\n");
                system("pause");
                break;
        }
    }
}