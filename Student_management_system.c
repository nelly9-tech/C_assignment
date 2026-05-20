#include <stdio.h>
#include <string.h>

#define max_students 103
#define max_name_length 20

typedef struct {
    char name[max_name_length];
    int reg_no,age,sum;
    float exam_score[3];
    float average_exam_score;
    char grade;
} Student;

void calculate_average_and_grade(Student *s) {
    s->average_exam_score = (s->exam_score[0] + s->exam_score[1] + s->exam_score[2]) / 3.0;

    if (s->average_exam_score >= 70) {
        s->grade = 'A';
    } else if (s->average_exam_score >= 60) {
        s->grade = 'B';
    } else if (s->average_exam_score >= 50) {
        s->grade = 'C';
    } else if (s->average_exam_score >= 40) {
        s->grade = 'D';
    } else {
        s->grade = 'E';
    }
s->sum = s->exam_score[0] + s->exam_score[1] + s->exam_score[2];
s->average_exam_score = s->sum / 3.0;
}
void print_student_info(Student *s) {
    printf("Name: %s\n", s->name);
    printf("Registration Number: %d\n", s->reg_no);
    printf("Age: %d\n", s->age);
    printf("Exam Scores: %.2f, %.2f, %.2f\n", s->exam_score[0], s->exam_score[1], s->exam_score[2]);
    printf("Average Exam Score: %.2f\n", s->average_exam_score);
    printf("Grade: %c\n", s->grade);
}
int main() {
    Student students[max_students];
    int num_students;

    printf("Enter the number of students (max %d): ", max_students);
    scanf("%d", &num_students);

    for (int i = 0; i < num_students; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Registration Number: ");
        scanf("%d", &students[i].reg_no);
        printf("Age: ");
        scanf("%d", &students[i].age);
        printf("Exam Scores (3 scores): ");
        for (int j = 0; j < 3; j++) {
            scanf("%f", &students[i].exam_score[j]);
        }
        calculate_average_and_grade(&students[i]);
    }

    printf("\nStudent Information:\n");
    for (int i = 0; i < num_students; i++) {
        print_student_info(&students[i]);
        printf("\n");
    }
    return 0;
}

/* Function prototypes */
void displayallstudents(Student *students, int num_students);
void searchstudent(Student *students, int num_students, int reg_no);
void updatestudent(Student *students, int num_students, int reg_no);
void displaybestperformingstudent(Student *students, int num_students);

void displayallstudents(Student *students, int num_students) {
    if (num_students <= 0) {
        printf("Student records not found.\n");
        return;
    }

    printf("\nAll Student Records:\n");
    for (int i = 0; i < num_students; i++) {
        print_student_info(&students[i]);
        printf("\n");
    }
}

void searchstudent(Student *students, int num_students, int reg_no) {
    for (int i = 0; i < num_students; i++) {
        if (students[i].reg_no == reg_no) {
            printf("\nStudent Found:\n");
            print_student_info(&students[i]);
            return;
        }
    }
    printf("Student with registration number %d not found.\n", reg_no);
}

void updatestudent(Student *students, int num_students, int reg_no) {
    for (int i = 0; i < num_students; i++) {
        if (students[i].reg_no == reg_no) {
            printf("\nUpdating details for student with registration number %d:\n", reg_no);
            printf("Name: ");
            scanf("%s", students[i].name);
            printf("Age: ");
            scanf("%d", &students[i].age);
            printf("Exam Scores (3 scores): ");
            for (int j = 0; j < 3; j++) {
                scanf("%f", &students[i].exam_score[j]);
            }
            calculate_average_and_grade(&students[i]);
            printf("Student details updated successfully.\n");
            return;
        }
    }
    printf("Student with registration number %d not found.\n", reg_no);
}

void displaybestperformingstudent(Student *students, int num_students) {
    if (num_students <= 0) {
        printf("Student records not found.\n");
        return;
    }

    Student *best_student = &students[0];
    for (int i = 1; i < num_students; i++) {
        if (students[i].average_exam_score > best_student->average_exam_score) {
            best_student = &students[i];
        }
    }

    printf("\nBest Performing Student:\n");
    print_student_info(best_student);
    return;
}