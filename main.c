#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "grades.h"


int main() {
    while (1) {
        initAdded();
        system(CLEAR);
        printf("\n============================================");
        printf("\n Informacao de Alunos");
        printf("\n============================================");
        printf("\n\n-------------------ALUNOS-------------------");
        printf("\n [1] Novo Arquivo de Alunos");
        printf("\n\n [2] Adicionar Alunos");
        printf("\n [3] Consultar Aluno");
        printf("\n [4] Excluir Aluno");
        printf("\n--------------------------------------------");
        printf("\n\n-------------------PROVAS-------------------");
        printf("\n [5] Adicionar/Atualizar Prova");
        printf("\n [6] Consultar Prova");
        printf("\n [7] Excluir Prova");
        printf("\n--------------------------------------------");
        printf("\n\n-----------------TRABALHOS------------------");
        printf("\n [8] Adicionar/Atualizar Trabalho");
        printf("\n [9] Consultar Trabalho");
        printf("\n [10] Deletar Trabalho");
        printf("\n--------------------------------------------");
        printf("\n\n [11] Mostrar Todos Alunos");
        printf("\n\n\n [0] Sair");
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
                printf("Essa opcao nao existe.\n");
                system("pause");
                break;
        }
    }
}