#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "grades.h"



int testsMenu(){
    system(CLEAR);
    printf("\n============================================");               // Exibe um menu com as provas e retorna qual
    printf("\n Escolha a prova");                                           // prova foi selecionada
    printf("\n============================================");
    printf("\n\n [1] Prova 1");
    if (added[0] == 0){ printf(" (Prova nao adicionada ainda)");} // Caso a prova não tenha sido adicionada, o menu irá avisar
    printf("\n [2] Prova 2");
    if (added[1] == 0){ printf(" (Prova nao adicionada ainda)");}
    printf("\n\n\n [0] Voltar");
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
            printf("Essa opcao nao existe\n");
            system("pause");
            break;
    }
    fflush(stdin);
    return -1;
}

int addTest(){                                          // Adiciona uma prova
    FILE *fp, *ftemp;                                   // Caso a prova ja tenha sido adicionada previamente,
    student s1;                                         // o usuário deve confirmar que quer substituir os valores
    fp = fopen("students.dat", "rb");                   // O uso de um arquivo temporário é similar à função deleteStudent()
    ftemp = fopen("temp.dat", "wb");

    int chosenTest = testsMenu() - 1;
    if (chosenTest == -1) { return 0; };
    if (added[chosenTest] == 1) {
        printf("\nEssa prova ja foi adicionada. Tem certeza que quer substitui-la? (S/N)\n");
        char prompt;
        while (1){
            fflush(stdin);
            prompt = getchar();
            if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
                break;
            }
            printf("\nPor favor digite \"S\" ou \"N\"\n");
        }
        if (prompt == 'N' || prompt == 'n'){
            return 0;
        }
    }
    fflush(stdin);
    printf("\n============================================");
    printf("\n Prova %d", chosenTest+1);
    printf("\n============================================\n");
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        if (added[chosenTest] == 1){
            printf("\nEntre com a nova nota para %s (Nota antiga: %.2f): ", s1.name, s1.test[chosenTest]);
        } else {
            printf("\nEntre com a nota para %s: ", s1.name);
        }
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

int deleteTest(){                               // Exclui um teste com o mesmo princípio da função deleteStudent()
    FILE *fp, *ftemp;
    student s1;
    fp = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");

    int chosenTest = testsMenu() - 1;
    if (chosenTest == -1) { return 0; };
    printf("\nVoce tem certeza que gostaria de excluir a Prova %d? (S/N)\n", chosenTest+1);
    char prompt;
    while (1){
        fflush(stdin);
        prompt = getchar();
        if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
            break;
        }
        printf("\nPor favor digite \"S\" ou \"N\"\n");
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

int displayTest(){                                      // Exibe a prova selecionada no menu
    FILE *fp;
    fp = fopen("students.dat", "rb");
    student s1;
    int chosenTest = testsMenu() - 1;
    if (chosenTest == -1) { return 0; }
    if (added[chosenTest] == 1){
        printf("\n============================================");
        printf("\n Prova %d", chosenTest+1);
        printf("\n============================================\n");
        while(1){
            fread(&s1, sizeof(s1), 1, fp);
            if (feof(fp)){
                break;
            }
            printf("\n%s: %.2f", s1.name, s1.test[chosenTest]);
        }
    } else {
        printf("\nEssa prova nao foi adicionada.");
    }
    printf("\n \n");
    system("pause");
    fclose(fp);
    return 0;
}

/* As funções abaixo funcionam das mesma forma que as acima, porém são utilizadas com trabalhos ao invés de provas */

int projectsMenu(){
    system(CLEAR);
    printf("\n============================================");
    printf("\n Escolha o Trabalho");
    printf("\n============================================");
    printf("\n\n [1] Trabalho 1");
    if (added[2] == 0){ printf(" (Trabalho nao adicionado ainda)");}
    printf("\n [2] Trabalho 2");
    if (added[3] == 0){ printf(" (Trabalho nao adicionado ainda)");}
    printf("\n [3] Trabalho 3");
    if (added[4] == 0){ printf(" (Trabalho nao adicionado ainda)");}
    printf("\n [4] Trabalho 4");
    if (added[5] == 0){ printf(" (Trabalho nao adicionado ainda)");}
    printf("\n\n\n [0] Voltar");
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
            printf("Essa opcao nao existe.\n");
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
    if (chosenProject == -1) { return 0; }
    if (added[chosenProject + 2] == 1) {
        printf("\nEsse trabalho ja foi adicionado. Tem certeza que quer substitui-lo? (S/N)\n");
        char prompt;
        while (1){
            fflush(stdin);
            prompt = getchar();
            if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
                break;
            }
            printf("\nPor favor digite \"S\" ou \"N\"\n");
        }
        if (prompt == 'N' || prompt == 'n'){
            return 0;
        }
    }
    fflush(stdin);
    printf("\n============================================");
    printf("\n Trabalho %d", chosenProject+1);
    printf("\n============================================\n");
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        if (added[chosenProject+2] == 1){
            printf("\nEntre com a nova nota para %s (Nota antiga: %.2f): ", s1.name, s1.work[chosenProject]);
        } else {
            printf("\nEntre com a nota para %s: ", s1.name);
        }
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

int displayProject(){
    FILE *fp;
    fp = fopen("students.dat", "rb");
    student s1;
    int chosenProject = projectsMenu() - 1;
    if (chosenProject == -1) { return 0; }
    if (added[chosenProject+2] == 1){
        printf("\n============================================");
        printf("\n Trabalho %d", chosenProject+1);
        printf("\n============================================\n");
        while(1){
            fread(&s1, sizeof(s1), 1, fp);
            if (feof(fp)){
                break;
            }
            printf("\n%s: %.2f", s1.name, s1.work[chosenProject]);
        }
    } else {
        printf("\nEsse trabalho nao foi adicionado.");
    }
    printf("\n \n");
    system("pause");
    fclose(fp);
    return 0;
}

int deleteProject(){
    FILE *fp, *ftemp;
    student s1;
    fp = fopen("students.dat", "rb");
    ftemp = fopen("temp.dat", "wb");

    int chosenProject = projectsMenu() - 1;
    if (chosenProject == -1) { return 0; };
    printf("\nVoce tem certeza que gostaria de excluir o trabalho %d? (S/N)\n", chosenProject+1);
    char prompt;
    while (1){
        fflush(stdin);
        prompt = getchar();
        if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
            break;
        }
        printf("\nPor favor digite \"S\" ou \"N\"\n");
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
