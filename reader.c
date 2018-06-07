#include <stdio.h>
#include <stdlib.h>
#include "students.c"

int main(void){
    student s1;
    FILE *fp;
    fp = fopen("students.dat", "rb");
    if (!fp){
        printf("Arquivo nao encontrado");
        getchar();
        return 0;
    }
    printf("\n");
   
    while (1) {
        fread(&s1, sizeof(s1), 1, fp);
        if(feof(fp)){
            break;
        }
        printf("\n\nNome: %s \nNUSP: %d\n", s1.name, s1.id);
        printf("P1: %.2f \t P2: %.2f\n", s1.test[0], s1.test[1]);
        printf("T1: %.2f \t T2: %.2f \t T3: %.2f \t T4: %.2f\n", s1.work[0], s1.work[1], s1.work[2], s1.work[3]);
    }
    fclose(fp);


    getchar();
    return 0;
}