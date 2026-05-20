#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100
#define NAME_SIZE 20

typedef struct {
    int regNo;
    char name[NAME_SIZE];
    int age;
    int mark1;
    int mark2;
    int mark3;
    float average;
    char grade;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void flushInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int findStudent(int regNo) {
    for (int i = 0; i < studentCount; i++)
        if (students[i].regNo == regNo)
            return i;
    return -1;
}

void calculateGrade(int i) {
    float avg = (students[i].mark1 + students[i].mark2 + students[i].mark3) / 3.0f;
    students[i].average = avg;
    if (avg >= 70) students[i].grade = 'A';
    else if (avg >= 60) students[i].grade = 'B';
    else if (avg >= 50) students[i].grade = 'C';
    else if (avg >= 40) students[i].grade = 'D';
    else students[i].grade = 'E';
}

void printStudent(int i) {
    Student *s = &students[i];
    printf("Reg:%d Name:%s Age:%d Marks:%d %d %d Avg:%.1f Grade:%c\n",
           s->regNo, s->name, s->age, s->mark1, s->mark2, s->mark3, s->average, s->grade);
}

void addStudent(void) {
    Student s;
    if (studentCount >= MAX_STUDENTS) { puts("Student list full."); return; }
    printf("Reg no: ");
    if (scanf("%d", &s.regNo) != 1) { puts("Invalid number."); flushInput(); return; }
    flushInput();
    if (findStudent(s.regNo) != -1) { puts("Already exists."); return; }
    printf("Name: ");
    if (fgets(s.name, sizeof s.name, stdin) == NULL) { puts("Invalid name."); return; }
    s.name[strcspn(s.name, "\n")] = '\0';
    printf("Age: ");
    if (scanf("%d", &s.age) != 1) { puts("Invalid age."); flushInput(); return; }
    printf("Mark 1: "); if (scanf("%d", &s.mark1) != 1) { puts("Invalid mark."); flushInput(); return; }
    printf("Mark 2: "); if (scanf("%d", &s.mark2) != 1) { puts("Invalid mark."); flushInput(); return; }
    printf("Mark 3: "); if (scanf("%d", &s.mark3) != 1) { puts("Invalid mark."); flushInput(); return; }
    flushInput();
    if (s.mark1 < 0 || s.mark1 > 100 || s.mark2 < 0 || s.mark2 > 100 || s.mark3 < 0 || s.mark3 > 100) { puts("Invalid mark."); return; }
    students[studentCount] = s;
    calculateGrade(studentCount);
    studentCount++;
    puts("Added student.");
}

void listStudents(void) {
    if (studentCount == 0) { puts("No students."); return; }
    for (int i = 0; i < studentCount; i++) printStudent(i);
}

void searchStudent(void) {
    int regNo;
    printf("Reg no: ");
    if (scanf("%d", &regNo) != 1) { puts("Invalid number."); flushInput(); return; }
    flushInput();
    int i = findStudent(regNo);
    if (i == -1) { puts("Not found."); return; }
    printStudent(i);
}

void updateStudent(void) {
    int regNo;
    printf("Reg no: ");
    if (scanf("%d", &regNo) != 1) { puts("Invalid number."); flushInput(); return; }
    flushInput();
    int i = findStudent(regNo);
    if (i == -1) { puts("Not found."); return; }
    printf("Mark 1: "); if (scanf("%d", &students[i].mark1) != 1) { puts("Invalid mark."); flushInput(); return; }
    printf("Mark 2: "); if (scanf("%d", &students[i].mark2) != 1) { puts("Invalid mark."); flushInput(); return; }
    printf("Mark 3: "); if (scanf("%d", &students[i].mark3) != 1) { puts("Invalid mark."); flushInput(); return; }
    flushInput();
    if (students[i].mark1 < 0 || students[i].mark1 > 100 || students[i].mark2 < 0 || students[i].mark2 > 100 || students[i].mark3 < 0 || students[i].mark3 > 100) { puts("Invalid mark."); return; }
    calculateGrade(i);
    puts("Updated student.");
}

void topStudent(void) {
    if (studentCount == 0) { puts("No students."); return; }
    int best = 0;
    for (int i = 1; i < studentCount; i++) if (students[i].average > students[best].average) best = i;
    printStudent(best);
}

int main(void) {
    int option;
    do {
        puts("\n1.Add student");
        puts("2.List students");
        puts("3.Search student");
        puts("4.Update marks");
        puts("5.Top average");
        puts("6.Exit");
        printf("Choice: ");
        if (scanf("%d", &option) != 1) { puts("Invalid."); flushInput(); continue; }
        flushInput();
        if (option == 1) addStudent();
        else if (option == 2) listStudents();
        else if (option == 3) searchStudent();
        else if (option == 4) updateStudent();
        else if (option == 5) topStudent();
        else if (option == 6) puts("Bye.");
        else puts("Choose 1-6.");
    } while (option != 6);
    return 0;
}
