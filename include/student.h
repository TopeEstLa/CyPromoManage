#ifndef STUDENT_H
#define STUDENT_H

#include <course.h>
#include <list.h>

/**
 * Represent a student
 * @param id the student's id
 * @param name the student's name
 * @param surname the student's surname
 * @param age the student's age
 * @param courses a list of courses (Course*)
 * @param average the student's average
 */
typedef struct student {
    int id;
    char *name;
    char *surname;
    int age;
    List *courses; // List of Course*
    double average;
} Student;

/**
 * Create a new student.
 * @param id the student's id
 * @param name the student's name
 * @param surname the student's surname
 * @param age the student's age
 * @return the new student NULL if an error occurred.
 */
Student *createStudent(int id, char *name, char *surname, int age);

/**
 * Free a student.
 * @param student the student to free.
 */
Student *freeStudent(Student *student);

/**
 * Compute the average of a student based on his courses and their coefficients.
 * @param student the student to compute the average for.
 */
void computeStudentAverage(Student *student);

/**
 * Get a course by its name from a student's course list.
 * @param student the student whose course list to search.
 * @param courseName the name of the course to find.
 * @return the course if found, NULL otherwise.
 */
Course *getCourseByName(Student *student, char *courseName);

/**
 * Add a course to a student's course list.
 * @param student the student to add the course to.
 * @param course the course to add.
 */
void addCourse(Student *student, Course *course);

/**
 * Add a grade to a course in a student's course list.
 * @param student the student whose course to add the grade to.
 * @param courseName the name of the course to add the grade to.
 * @param grade the grade to add.
 */
void addGradeToCourse(Student *student, char *courseName, double grade); //TODO we will see during the parsing part

/**
* Get the worst course average for a student.
* @param student the student to get the worst course average for.
* @return the worst course average.
*/
double getMinCourseAverageForStudent(Student *student);

/**
 * Print the student information.
 * @param student the student to print.
 */
void printStudent(Student *student);

#endif //STUDENT_H
