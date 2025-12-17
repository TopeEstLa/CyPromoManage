#include <class.h>
#include <string.h>
#include <ctype.h>
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

void sortStudent(Class* class, void* context) {
    if (class == NULL) return;

    sortList(class->students, class->sortingFunction, context);
}

void sortStudentsInClassByAverage(Class* classObj) {
    if (classObj == NULL) return;

    sortList(classObj->students, compareByAverage, NULL);
}

void sortStudentsInClassByAverageInCourse(Class* classObj, char* courseName) {
    if (classObj == NULL || courseName == NULL) return;

    sortList(classObj->students, compareByAverageCourse, courseName);
}

double searchMaxAverageInClass(Class* class) {
    if (class == NULL) return -1.0;

    double maxAverage = -1.0;
    for (int i = 0; i < class->students->size; i++) {
        Student* student = get(class->students, i);
        if (student != NULL && student->average > maxAverage) {
            maxAverage = student->average;
        }
    }

    return maxAverage;
}

double searchMinAverageInClass(Class* class) {
    if (class == NULL) return -1.0;

    double minAverage = 101.0;
    for (int i = 0; i < class->students->size; i++) {
        Student* student = get(class->students, i);
        if (student != NULL && student->average < minAverage) {
            minAverage = student->average;
        }
    }

    return minAverage;
}

void standardization(Student* student, double min, double max) {
    if (max - min == 0) {
        printf("Can't run standardization cause max-min=0.\n");
        exit(1);
    }

    student->average = (student->average - min) / (max - min) * 20.0;
}

bool updateClassAverageGrades(Class* class, RecalcFunction recalc_function) {
    if (class == NULL) return false;

    double maxAverage = searchMaxAverageInClass(class);
    if (maxAverage == -1.0) return false;

    double minAverage = searchMinAverageInClass(class);
    if (minAverage == -1.0) return false;

    ListNode* current = class->students->head;
    while (current != NULL) {
        Student* s = (Student*)current->data;
        recalc_function(s, minAverage, maxAverage);
        current = current->next;
    }

    return true;
}

char** listName(Class* class, int* outSize) {
    if (class == NULL || class->students == NULL || outSize == NULL) return NULL;

    int count = class->students->size;
    *outSize = count;

    if (count == 0) return NULL;

    int totalChars = 0;
    ListNode* current = class->students->head;
    while (current != NULL) {
        Student* student = current->data;
        if (student && student->name) {
            totalChars += strlen(student->name) + 1;
        }
        current = current->next;
    }

    char** array = malloc(sizeof(char*) * count);
    if (!array) return NULL;

    char* bigBuffer = malloc(sizeof(char) * totalChars);
    if (!bigBuffer) {
        free(array);
        return NULL;
    }

    char* cursor = bigBuffer;
    current = class->students->head;
    int i = 0;
    while (current != NULL && i < count) {
        Student* student = current->data;
        if (student != NULL && student->name != NULL) {
            array[i] = cursor;

            char* srcName = student->name;
            while (*srcName) {
                *cursor = (char)toupper((unsigned char)*srcName);
                cursor++;
                srcName++;
            }
            *cursor = '\0';
            cursor++;
        } else {
            array[i] = NULL;
        }

        current = current->next;
        i++;
    }

    return array;
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