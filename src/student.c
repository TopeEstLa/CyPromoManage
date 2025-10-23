#include <student.h>
#include <string.h>
#include <stdio.h>

Student* createStudent(int id, char* name, char* surname, int age) {
    Student* student = malloc(sizeof(Student));
    if (student == NULL) {
        return NULL;
    }

    student->id = id;
    student->name = name;
    student->surname = surname;
    student->age = age;

    List* list = createList();
    if (list == NULL) {
        free(student);
        return NULL;
    }
    student->courses = list;
    student->average = 0.0;

    return student;
}

Student* freeStudent(Student* student) {
    if (student == NULL) return NULL;

    for (int i = 0; i < student->courses->size; i++) {
        Course* course = get(student->courses, i);
        if (course != NULL) {
            freeCourse(course);
        }
    }

    freeList(student->courses);
    free(student);
    return NULL;
}

void computeStudentAverage(Student* student) {
    if (student == NULL) return;

    double totalWeightedAverage = 0.0;
    double totalCoef = 1.0;

    for (int i = 0; i < student->courses->size; i++) {
        Course* course = get(student->courses, i);
        if (course != NULL) {
            computeCourseAverage(course);
            totalWeightedAverage += course->average * course->coef;
            totalCoef += course->coef;
        }
    }

    student->average = totalWeightedAverage / totalCoef;
}

Course* getCourseByName(Student* student, char* courseName) {
    if (student == NULL || courseName == NULL) return NULL;

    for (int i = 0; i < student->courses->size; i++) {
        Course* course = get(student->courses, i);
        if (course != NULL && strcmp(course->name, courseName) == 0) {
            return course;
        }
    }

    return NULL;
}

void addCourse(Student* student, Course* course) {
    if (student == NULL || course == NULL) return;

    append(student->courses, course);
}

void addGradeToCourse(Student *student, char *courseName, double grade) {
    Course* course = getCourseByName(student, courseName);
    if (course == NULL) return;
    addGrade(course, grade);
    computeCourseAverage(course);
}

void printStudent(Student* student) {
    if (student == NULL) return;

    printf("Student ID: %d\n", student->id);
    printf("Name: %s %s\n", student->name, student->surname);
    printf("Age: %d\n", student->age);
    printf("Average: %.2f\n", student->average);
    printf("Courses:\n");
    for (int i = 0; i < student->courses->size; i++) {
        Course* course = get(student->courses, i);
        if (course != NULL) {
            printCourse(course);
        }
    }
}