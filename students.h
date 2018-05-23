#ifndef students_H_
#define students_H_

typedef struct stud {
    char name[127];
    int id;
    float test[2];
    float work[4];
} student;

void removeNL(char *input);
int intInput();
float floatInput();
void writeStudents();
void addStudent();
void printStudent(student st);
void displayStudent();
void displayAllStudents();
void deleteStudent();
void initAdded();

#endif