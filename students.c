#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "grades.h"


int initAdded() {                                        // Função para inicializar o vetor 'added'  
    FILE *fp;                                             // Ela lê o arquivo students.dat e vê quais 
    student s1;                                           // provas e/ou trabalhos foram adicionados
    fp = fopen("students.dat", "rb");
    if(feof(fp)){
        fclose(fp);
        return 0;
    }                       
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
    return 0;
}

void removeNL(char *input){                             // Função para remover o \n do fgets
    size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[--len] = '\0';
    }
}

int intInput() {                                        // Recebe um input com fgets, confere se é
    int number;                                         // um inteiro e o converte com a função strtol
    char inputString[127];
    char *endBuff;
    fgets(inputString, 127, stdin);
    removeNL(inputString);
    number = strtol(inputString, &endBuff, 10);
    while (*endBuff != '\0'){
        printf("Por favor digite um numero valido: ");
        fgets(inputString, 127, stdin);
        removeNL(inputString);
        number = strtol(inputString, &endBuff, 10);
    }
    return number;
}

float floatInput() {                                    // Similar a função intInput(), porém
    float number;                                       // validando um float
    char inputString[127];
    char *endBuff;
    fgets(inputString, 127, stdin);
    removeNL(inputString);
    number = strtod(inputString, &endBuff);
    while (*endBuff != '\0'){
        printf("Por favor digite um numero valido: ");
        fgets(inputString, 127, stdin);
        removeNL(inputString);
        number = strtod(inputString, &endBuff);
    }
    return number;
}

int writeStudents(int confirm) {
    if (confirm == 1){
        printf("\nEsse procedimento ira deletar seu arquivo antigo (caso ele exista) e criar um novo.\nTem certeza que quer fazer isso? (S/N)\n");
        char prompt;
        while (1){
            fflush(stdin);
            prompt = getchar();
            getchar();
            if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
                break;
            }
            printf("\nPor favor digite \"S\" ou \"N\"\n");                      // Função que inicializa o arquivo students.dat
        }                                                                       // Cria um arquivo students.dat novo, havendo
        if (prompt == 'N' || prompt == 'n'){                                    // um antigo ou não
            return 0;                                                           // Caso exista um antigo, ela será sobrescrito
        }                                                                      
        fflush(stdin);
    }   
    FILE *fp;
    fp  = fopen("students.dat", "wb");
    student s1;
    int i  = 0;
    while (1){
        i++;
        printf("\n[%02d] Entre o nome do aluno: ", i);
        fgets(s1.name, 127, stdin);
        removeNL(s1.name);
        printf("[%02d] Entre o NUSP do aluno: ", i);
        s1.id = intInput();   
        s1.test[0] = -1;
        s1.test[1] = -1;
        s1.work[0] = -1;
        s1.work[1] = -1;
        s1.work[2] = -1;
        s1.work[3] = -1;       
        fwrite(&s1, sizeof(s1), 1, fp);     
        printf("\nAdicionar outro aluno? (S/N)\n");
        char prompt;
        while (1){
            fflush(stdin);
            prompt = getchar();
            getchar();
            if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
                break;
            }
            printf("\nPor favor digite \"S\" ou \"N\"\n");
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


void addStudent(){                                                  // Adiciona um aluno, recebendo seu nome 
    fflush(stdin);                                                  // e número USP (NUSP)
    FILE *fp;                                                       // Caso algum trabalho ou prova já tenha
    fp  = fopen("students.dat", "ab");                              // sido adicionado, o usuário também deverá
    student s1;                                                     // colocar as notas desse aluno para a prova/
    printf("\nEntre o nome do aluno: ");                            // tralalho adicionado
    fgets(s1.name, 127, stdin);                                     // Essa checagem é feita com o vetor 'added'
    removeNL(s1.name);
    printf("Entre o NUSP do aluno: ");
    s1.id = intInput();
    for (int i = 0; i <= 1; i++){
        if(added[i] == 1){
            printf("Entre a nota do aluno na Prova %d: ", i+1);
            s1.test[i] = floatInput();
        }
    }
    for (int i = 2; i <= 5; i++){
        if(added[i] == 1){
            printf("Entre a nota do aluno no Trabalho %d: ", i-1);
            s1.work[i-2] = floatInput();
        }
    }
    fwrite(&s1, sizeof(s1), 1, fp);     
    fflush(stdin);

    printf("\n");
    fclose(fp);
}

void printStudent(student st) {                                     // Mostra o nome e NUSP do aluno
    printf("\n============================================");
    printf("\nNome: %s", st.name);
    printf("\nNUSP: %d", st.id);
    printf("\n============================================");
}

void displayStudent() {                                             // Além de mostrar o nome e NUSP do aluno,
    fflush(stdin);                                                  // essa função confere quais notas foram
    student s1;                                                     // adicionadas e as mostra, exibindo todas
    FILE *fr;                                                       // as informações disponíveis do aluno
    fr = fopen("students.dat", "rb");
    char search[127];
    printf("Entre o nome completo do aluno ou seu NUSP: ");
    fgets(search, 127, stdin);
    removeNL(search);
    char *endBuff;
    int searchID = strtol(search, &endBuff, 10);
    int found = 0;
    while (1){
        fread(&s1, sizeof(s1), 1, fr);
        if(feof(fr)){
            break;
        }
        if (strcmp(search, s1.name) == 0 || searchID == s1.id){
            found = 1;
            printStudent(s1);
            if (added[0] == 1 || added[1] == 1){
                printf("\nPROVAS \n");
                if(added[0] == 1){
                    printf("\nProva 1: %.2f", s1.test[0]);
                }
                if(added[1] == 1){
                    printf("\nProva 2: %.2f", s1.test[1]);
                }
                printf("\n============================================\n");
            }
            if (added[2] == 1 || added[3] == 1 || added[4] == 1 || added[5] == 1){
                printf("\nTRABALHOS\n");
                for (int i = 2; i <= 5; i++){
                    if(added[i] == 1){
                        printf("\nTrabalho %d: %.2f", i-1, s1.work[i-2]);
                    }
                }
                printf("\n============================================\n");
            }
        }
        
    }
    if (found == 0){
        printf("\nO aluno não foi encontrado.");
    }
    printf("\n\nPressione ENTER para continuar ");
    getchar();
    fclose(fr);

}

void displayAllStudents() {                     // Exibe os nomes e NUSPs de todos os alunos
    fflush(stdin);
    printf("ALUNOS\n");
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
    printf("\n\nPressione ENTER para continuar ");
    getchar();
}


void deleteStudent() {                                              // Deleta o aluno escolhido
    fflush(stdin);                                                  // Essa função copia todos os alunos para
    FILE *fp, *ftemp;                                               // um arquivo temporário, exceto o aluno a ser deletado
    fp  = fopen("students.dat", "rb");                              // O arquivo temporário, então, tem todos os alunos,
    ftemp = fopen("temp.dat", "wb");                                // exceto o escolhido
    student s1;                                                         
    char search[127];
    printf("Entre o nome completo do aluno ou seu NUSP: ");
    fgets(search, 127, stdin);
    removeNL(search);
    char *endBuff;
    int searchID = strtol(search, &endBuff, 10);
    int found = 0;
    while (1){
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        if (strcmp(search, s1.name) == 0 || searchID == s1.id){
            printStudent(s1);
            found = 1;
            printf("\nExcluir esse aluno? (S/N)\n");
            char prompt;
            while (1){
                fflush(stdin);
                prompt = getchar();
                getchar();
                if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
                    break;
                }
                printf("\nPor favor digite \"S\" ou \"N\"\n");
            }
            if (prompt == 'N' || prompt == 'n'){
                fwrite(&s1, sizeof(s1), 1, ftemp);
            } else {
                printf("Aluno excluido.\n");
            }
        } else {
            fwrite(&s1, sizeof(s1), 1, ftemp);
        } 
    }
    fclose(fp);
    fclose(ftemp);
    if (found == 0){
        printf("O aluno nao foi encontrado.\n");
    } else {
        fp  = fopen("students.dat", "wb");
        ftemp = fopen("temp.dat", "rb");

        while(1){
            fread(&s1, sizeof(s1), 1, ftemp);               // Apos todas as informações necessárias serem
            if(feof(ftemp)){                                // copiadas para o arquivo temporário, a função 
                break;                                      // reescreve o students.dat, usando as informações
            }                                               // do arquivo temporário
            fwrite(&s1, sizeof(s1), 1, fp);
        }
        fclose(fp);
        fclose(ftemp);

    }
    printf("\n\nPressione ENTER para continuar ");
    getchar();
}
