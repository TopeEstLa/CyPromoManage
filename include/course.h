#ifndef COURSES_H
#define COURSES_H

#include <list.h>

/**
 * Represent a courses
 * @param name the name of the course
 * @param coef the coefficient of the course for the global average calculation
 * @param grades a list of grades (double*)
 * @param average the average of the course
 */
typedef struct course {
    char* name;
    double coef;
    List* grades; // List of double*
    double average;
} Course;

/**
 * Create a new course.
 * @param name the name of the course
 * @param coef the coefficient of the course
 * @return the new course NULL if an error occurred.
 */
Course* createCourse(char* name, double coef);

/**
 * Free a course.
 * @param course
 */
void freeCourse(Course* course);

/**
 * Duplicate a course.
 * @param course the course to duplicate.
 * @return the duplicated course or NULL if an error occurred.
 */
Course* duplicateCourse(Course* course);

/**
 * Add a grade to a course.
 * @param course the course to add the grade to.
 * @param grade the grade to add.
 */
void addGrade(Course* course, double grade);

/**
 * Compute the average of a course.
 * @param course the course to compute the average for all grades in the course's grades list.
 */
void computeCourseAverage(Course* course);

/**
 * Print the course information.
 * @param course
 */
void printCourse(Course* course);



#endif //COURSES_H