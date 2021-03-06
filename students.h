#ifndef students_H_
#define students_H_


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif


typedef struct stud {
    char name[127];
    int id;
    float test[2];
    float work[4];
} student;

void clearScreen();
void removeNL(char *input);
int intInput();
float floatInput();
int writeStudents(int confirm);
void addStudent();
void printStudent(student st);
void displayStudent();
void displayAllStudents();
void deleteStudent();
int initAdded();

#endif