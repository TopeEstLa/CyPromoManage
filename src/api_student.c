#include <api_student.h>
#include <csv_parser.h>
#include <data_saver.h>
#include <stdio.h>
#include <string.h>
#include <student.h>


Class *API_load_students(char *filePath) {
    return process_csv_file(filePath);
}

int API_save_to_binary_file(Class *class_, char *filePath) {
    return save_class_to_file(class_, filePath);
}

Class *API_restore_from_binary_file(char *filePath) {
    return load_class_from_file(filePath);
}

void API_display(Class *class) {
    if (class == NULL) {
        printf("Class is NULL\n");
        return;
    }

    ListNode *studentNode = class->students->head;
    while (studentNode != NULL) {
        Student *student = (Student *) studentNode->data;
        printf("Student ID: %d, Name: %s %s, Age: %d, Average: %.2f\n",
               student->id, student->name, student->surname, student->age, student->average);
        ListNode *courseNode = student->courses->head;
        while (courseNode != NULL) {
            Course *course = (Course *) courseNode->data;
            printf("  Course: %s, Coefficient: %.2f, Average: %.2f\n",
                   course->name, course->coef, course->average);
            courseNode = courseNode->next;
        }

        studentNode = studentNode->next;
    }
}

void API_unload(Class *class) {
    freeClass(class);
}

char** API_get_best_students(Class *class) {
    sortStudentsInClassByAverage(class);

    char** bestStudents = malloc(SIZE_TOP1 * sizeof(char*));
    if (bestStudents == NULL) return NULL;

    for (int i = 0; i < SIZE_TOP1 && i < class->students->size; i++) {
        Student* student = get(class->students, i);
        if (student != NULL) {
            char* name = malloc(strlen(student->name)+strlen(student->surname) * sizeof(char));
            if (name != NULL) {
                //name = student->name + " " + student->surname;
                strcpy(name, student->name);
                strcat(name, " ");
                strcat(name, student->surname);
                bestStudents[i] = name;
            } else {
                bestStudents[i] = NULL;
            }
        } else {
            bestStudents[i] = NULL;
        }
    }

    return bestStudents;
}

char** API_get_best_students_in_course(Class *class, char *courseName) {
    sortStudentsInClassByAverageInCourse(class, courseName);

    char** bestStudents = malloc(SIZE_TOP2 * sizeof(char*));
    if (bestStudents == NULL) return NULL;

    for (int i = 0; i < SIZE_TOP2 && i < class->students->size; i++) {
        Student* student = get(class->students, i);
        if (student != NULL) {
            char* name = malloc(strlen(student->name)+strlen(student->surname) * sizeof(char));
            if (name != NULL) {
                strcpy(name, student->name);
                strcat(name, " ");
                strcat(name, student->surname);
                bestStudents[i] = name;
            } else {
                bestStudents[i] = NULL;
            }
        } else {
            bestStudents[i] = NULL;
        }
    }

    return bestStudents;
}

int compareByName(void *studentA, void *studentB, void *context) {
    Student *a = (Student *) studentA;
    Student *b = (Student *) studentB;

    //le tri se fait par ordre croissant du nom de famille
    return strcmp(a->surname, b->surname);
}

int compareByFirstName(void *studentA, void *studentB, void *context) {
    Student *a = (Student *) studentA;
    Student *b = (Student *) studentB;

    //le tri se fait par ordre croissant du prénom
    return strcmp(a->name, b->name);
}

int compareByAverage2(void *studentA, void *studentB, void *context) {
    Student *a = (Student *) studentA;
    Student *b = (Student *) studentB;

    if (a->average < b->average) return 1;
    if (a->average > b->average) return -1;
    return 0;
}

int compareByMin(void *studentA, void *studentB, void *context) {
    Student *a = (Student *) studentA;
    Student *b = (Student *) studentB;

    int aMin = getMinCourseAverageForStudent(studentA);
    int bMin = getMinCourseAverageForStudent(studentB);

    if (aMin < bMin) return 1;
    if (aMin > bMin) return -1;
    return 0;
}

//function ptr to the selected compare function save it here

int API_set_sorting_mode(Class* pClass, int mode) {
    switch (mode) {
        case ALPHA_FIRST_NAME:
            pClass->sortingFunction = &compareByFirstName;
            break;
        case ALPHA_LAST_NAME:
            pClass->sortingFunction = &compareByName;
            break;
        case AVERAGE:
            pClass->sortingFunction = &compareByAverage2;
            break;
        case MIN:
            pClass->sortingFunction = &compareByMin;
            break;
        default:
            return 0;
    }

    return 1;
}

char** API_sort_students(Class* pClass) {
    sortStudent(pClass, NULL);

    char** sortedStudents = malloc(SIZE_TOP1 * sizeof(char*));
    if (sortedStudents == NULL) return NULL;

    for (int i = 0; i < SIZE_TOP1; i++) {
        Student* student = get(pClass->students, i);
        if (student != NULL) {
            char* name = malloc(strlen(student->name)+strlen(student->surname) * sizeof(char));
            if (name != NULL) {
                strcpy(name, student->name);
                strcat(name, " ");
                strcat(name, student->surname);
                sortedStudents[i] = name;
            } else {
                sortedStudents[i] = NULL;
            }
        } else {
            sortedStudents[i] = NULL;
        }
    }

    return sortedStudents;
}

Student** API_get_sorted_students(Class *classObj) {
    if (classObj == NULL) return NULL;
    sortStudent(classObj, NULL);

    int count = SIZE_TOP1;
    Student **studentsArray = malloc(count * sizeof(Student *));
    if (studentsArray == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        studentsArray[i] = get(classObj->students, i);
    }

    return studentsArray;
}