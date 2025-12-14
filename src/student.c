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
    student->validation_flags = 0;

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

int getCourseIndex(char* name) {
    if (strcmp(name, "Mathematiques") == 0) return MATHEMATIQUES;
    if (strcmp(name, "Physique") == 0) return PHYSIQUE;
    if (strcmp(name, "Informatique") == 0) return INFORMATIQUE;
    if (strcmp(name, "Chimie") == 0) return CHIMIE;
    if (strcmp(name, "Biologie") == 0) return BIOLOGIE;
    if (strcmp(name, "Histoire") == 0) return HISTOIRE;
    if (strcmp(name, "Geographie") == 0) return GEOGRAPHIE;
    if (strcmp(name, "Français") == 0) return FRANCAIS;
    if (strcmp(name, "Anglais") == 0) return ANGLAIS;
    if (strcmp(name, "EPS") == 0) return EPS;
    if (strcmp(name, "Philosophie") == 0) return PHILOSOPHIE;
    if (strcmp(name, "Economie") == 0) return ECONOMIE;
    if (strcmp(name, "Sociologie") == 0) return SOCIOLOGIE;
    if (strcmp(name, "Arts Plastiques") == 0) return ARTS_PLASTIQUES;
    if (strcmp(name, "Musique") == 0) return MUSIQUE;
    if (strcmp(name, "Technologie") == 0) return TECHNOLOGIE;
    if (strcmp(name, "Latin") == 0) return LATIN;
    if (strcmp(name, "Espagnol") == 0) return ESPAGNOL;
    if (strcmp(name, "Allemand") == 0) return ALLEMAND;
    if (strcmp(name, "Sciences Sociales") == 0) return SCIENCES_SOCIALES;

    return -1;
}

void computeStudentValidation(Student *student) {
    if (student == NULL) return;

    uint64_t flags = 0;

    for (int i = 0; i < student->courses->size; i++) {
        Course* course = get(student->courses, i);
        if (course != NULL) {
            if (course->average >= 10.0) {
                int index = getCourseIndex(course->name);
                if (index != -1) {
                    flags |= (1ULL << index);
                }
            }
        }
    }

    student->validation_flags = flags;
}

int checkValidation(Student *student, uint64_t mask) {
    if (student == NULL) return 0;

    return (student->validation_flags & mask) == mask;
}

void computeStudentAverage(Student* student) {
    if (student == NULL) return;

    double totalWeightedAverage = 0.0;
    double totalCoef = 0.0;

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

double getMinCourseAverageForStudent(Student *student) {
    if (student == NULL || student->courses->size == 0) return -1;

    double minAverage = 101.0;

    for (int i = 0; i < student->courses->size; i++) {
        Course* course = get(student->courses, i);
        if (course != NULL) {
            computeCourseAverage(course);
            if (course->average < minAverage) {
                minAverage = course->average;
            }
        }
    }

    return minAverage;
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