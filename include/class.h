#ifndef CLASS_H
#define CLASS_H

#include "list.h"
#include "student.h"
#include "course.h"

/**
 * Represent a class
 * @param students a list of students (Student*)
 * @param average the average of the class
 * @param courses a list of all available courses in the class (Course*)
 */
typedef struct class {
    List* students; // List of Student*
    double average;
    List* courses; // List of all available Course* in the class (class = .csv file)
} Class;

/**
 * Create a new class.
 * @return the new class NULL if an error occurred.
 */
Class* createClass();

/**
 * Free a class.
 * @param classObj the class to free.
 */
void freeClass(Class* classObj);

/**
 * Add a student to a class's student list.
 * @param classObj the class to add the student to.
 * @param student the student to add.
 */
void addStudentToClass(Class* classObj, Student* student);

/**
 * Add a course to a class's course list.
 * @param classObj the class to add the course to.
 * @param course the course to add.
 */
void addCourseToClass(Class* classObj, Course* course);

/**
 * Get a course by its name from the class's course list.
 * @param classObj the class whose course list to search.
 * @param courseName the name of the course to find.
 * @return the course if found, NULL otherwise.
 */
Course* getCourseByNameInClass(Class* classObj, char* courseName);

/**
 * Get a student by its id from the class's student list.
 * @param classObj the class whose student list to search.
 * @param id the id of the student to find.
 * @return the student if found, NULL otherwise.
 */
Student* getStudentById(Class* classObj, int id);

/**
 * Sort the students in the class by their average.
 * @param classObj
 */
void sortStudentsInClassByAverage(Class* classObj);

/**
 * Sort the students in the class by their average in a specific course.
 * @param classObj
 * @param courseName
 */
void sortStudentsInClassByAverageInCourse(Class* classObj, char* courseName);

/**
 * Print the class information.
 * @param classObj the class to print.
 */
void printClass(Class* classObj);


#endif //CLASS_H