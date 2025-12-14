#include <class.h>
#include <string.h>
#include <stdio.h>

Class* createClass() {
    Class* classObj = malloc(sizeof(Class));
    if (classObj == NULL) {
        return NULL;
    }

    List* studentList = createList();
    if (studentList == NULL) {
        free(classObj);
        return NULL;
    }
    classObj->students = studentList;

    List* courseList = createList();
    if (courseList == NULL) {
        freeList(classObj->students);
        free(classObj);
        return NULL;
    }
    classObj->courses = courseList;

    classObj->average = 0.0;

    return classObj;
}

void freeClass(Class* classObj) {
    if (classObj == NULL) return;

    for (int i = 0; i < classObj->students->size; i++) {
        Student* student = get(classObj->students, i);
        if (student != NULL) {
            freeStudent(student);
        }
    }

    freeList(classObj->students);

    for (int i = 0; i < classObj->courses->size; i++) {
        Course* course = get(classObj->courses, i);
        if (course != NULL) {
            freeCourse(course);
        }
    }

    freeList(classObj->courses);
    free(classObj);
}

void addStudentToClass(Class* classObj, Student* student) {
    if (classObj == NULL || student == NULL) return;

    append(classObj->students, student);
}

void addCourseToClass(Class* classObj, Course* course) {
    if (classObj == NULL || course == NULL) return;

    append(classObj->courses, course);
}

Course* getCourseByNameInClass(Class* classObj, char* courseName) {
    if (classObj == NULL || courseName == NULL) return NULL;

    for (int i = 0; i < classObj->courses->size; i++) {
        Course* course = get(classObj->courses, i);
        if (course != NULL && strcmp(course->name, courseName) == 0) {
            return course;
        }
    }

    return NULL;
}

Student* getStudentById(Class* classObj, int id) {
    if (classObj == NULL) return NULL;

    for (int i = 0; i < classObj->students->size; i++) {
        Student* student = get(classObj->students, i);
        if (student != NULL && student->id == id) {
            return student;
        }
    }

    return NULL;
}

int compareByAverage(void *studentA, void *studentB, void *context) {
    Student *a = (Student *) studentA;
    Student *b = (Student *) studentB;

    if (a->average < b->average) return 1;
    if (a->average > b->average) return -1;
    return 0;
}

int compareByAverageCourse(void *studentA, void *studentB, void *context) {
    Student *a = (Student *) studentA;
    Student *b = (Student *) studentB;
    char *courseName = (char *) context;
    if (courseName == NULL) return 0;

    Course *courseA = getCourseByName(studentA, courseName);
    Course *courseB = getCourseByName(studentB, courseName);

    if (courseA == NULL && courseB == NULL) return 0;
    if (courseA == NULL) return 1;
    if (courseB == NULL) return -1;

    if (courseA->average < courseB->average) return 1;
    if (courseA->average > courseB->average) return -1;
    return 0;
}

void sortStudentsInClassByAverage(Class* classObj) {
    if (classObj == NULL) return;

    sortList(classObj->students, compareByAverage, NULL);
}

void sortStudentsInClassByAverageInCourse(Class* classObj, char* courseName) {
    if (classObj == NULL || courseName == NULL) return;

    sortList(classObj->students, compareByAverageCourse, courseName);
}

void printClass(Class* classObj) {
    if (classObj == NULL) return;

    printf("Class Students:\n");
    for (int i = 0; i < classObj->students->size; i++) {
        Student* student = get(classObj->students, i);
        if (student != NULL) {
            printStudent(student); //Mdrr recursive rabbit hole printStudent -> printCourse -> printList
        }
    }
}