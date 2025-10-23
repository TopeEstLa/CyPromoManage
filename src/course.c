#include <course.h>
#include <stdio.h>

Course* createCourse(char* name, double coef) {
    Course* course = malloc(sizeof(Course));
    if (course == NULL) {
        return NULL;
    }

    course->name = name;
    course->coef = coef;
    List* list = createList();
    if (list == NULL) {
        free(course);
        return NULL;
    }
    course->grades = list;
    course->average = 0.0;

    return course;
}

void freeCourse(Course* course) {
    if (course == NULL) return;

    for (int i = 0; i < course->grades->size; i++) {
        double* gradePtr = get(course->grades, i);
        if (gradePtr != NULL) {
            free(gradePtr);
        }
    }

    freeList(course->grades);
    free(course);
}

Course* duplicateCourse(Course* course) {
    if (course == NULL) return NULL;

    Course* newCourse = createCourse(course->name, course->coef);
    if (newCourse == NULL) return NULL;

    for (int i = 0; i < course->grades->size; i++) {
        double* gradePtr = get(course->grades, i);
        if (gradePtr != NULL) {
            addGrade(newCourse, *gradePtr);
        }
    }

    newCourse->average = course->average;

    return newCourse;
}

void addGrade(Course* course, double grade) {
    if (course == NULL) return;

    double* gradePtr = malloc(sizeof(double));
    if (gradePtr == NULL) return;

    *gradePtr = grade;
    append(course->grades, gradePtr);
}

void computeCourseAverage(Course* course) {
    if (course == NULL) return;
    if (course->grades == NULL) return;

    double sum = 0.0;
    for (int i = 0; i < course->grades->size; i++) {
        double* gradePtr = get(course->grades, i);
        if (gradePtr != NULL) {
            sum += *gradePtr;
        }
    }

    course->average = sum / course->grades->size;
}

void printCourse(Course* course) {
    if (course == NULL) return;

    printf("Course Name: %s\n", course->name);
    printf("Coefficient: %.2f\n", course->coef);
    printf("Grades: ");
    for (int i = 0; i < course->grades->size; i++) {
        double* gradePtr = get(course->grades, i);
        if (gradePtr != NULL) {
            printf("%.2f ", *gradePtr);
        }
    }
    printf("\nAverage: %.2f\n", course->average);
}