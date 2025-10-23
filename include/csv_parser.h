#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "course.h"
#include "student.h"
#include "class.h"

typedef struct student_grade_record {
    int id;
    char* course_name;
    double grade;
} StudentGradeRecord;

typedef enum parsing_step {
    STUDENT,
    COURSE,
    STUDENT_GRADE
} ParsingStep;

/**
 * Process a CSV file and populate a Class structure with Students and Courses.
 * @param filename The path to the CSV file.
 * @return A pointer to the populated Class structure.
 */
Class* process_csv_file(char* filename);

/**
 * Parse a line of CSV representing a student record.
 * @param line The line of CSV text.
 * @return A pointer to a Student structure.
 */
Student* parse_student_record(char* line);

/**
 * Parse a line of CSV representing a course record.
 * @param line The line of CSV text.
 * @return A pointer to a Course structure.
 */
Course* parse_course_record(char* line);

/**
 * Parse a line of CSV representing a student grade record.
 * @param line The line of CSV text.
 * @return A pointer to a StudentGradeRecord structure.
 */
StudentGradeRecord* parse_student_grade_record(char* line);


#endif //CSV_PARSER_H