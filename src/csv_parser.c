#include <csv_parser.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DELIM ";"

void strip_newline(char *str) {
    if (str == NULL) return;

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

Class *process_csv_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    Class *class = createClass();
    if (class == NULL) {
        fclose(file);
        return NULL;
    }
    ParsingStep parsing_step = STUDENT;

    int max_line_length = 3024;
    char line[max_line_length];

    fgets(line, max_line_length, file);
    fgets(line, max_line_length, file);

    while (fgets(line, max_line_length, file)) {
        strip_newline(line);

        if (strcmp(line, "MATIERES") == 0) {
            parsing_step = COURSE;
            fgets(line, max_line_length, file);
            continue;
        }

        if (strcmp(line, "NOTES") == 0) {
            parsing_step = STUDENT_GRADE;
            fgets(line, max_line_length, file);
            continue;
        }

        if (strlen(line) == 0) {
            continue;
        }

        switch (parsing_step) {
            case STUDENT: {
                Student *student = parse_student_record(line);
                if (student == NULL) continue;
                addStudentToClass(class, student);
                break;
            };
            case COURSE: {
                Course *course = parse_course_record(line);
                if (course == NULL) continue;
                addCourseToClass(class, course);
                break;
            }
            case STUDENT_GRADE: {
                StudentGradeRecord *record = parse_student_grade_record(line);
                if (record == NULL) continue;
                Student *student = getStudentById(class, record->id);
                if (student == NULL) {
                    printf("Warning: Student with ID %d not found.\n", record->id);
                    free(record->course_name);
                    free(record);
                    continue;
                }
                char *course_name = record->course_name;
                Course *course = getCourseByName(student, course_name);
                if (course == NULL) {
                    Course *template_course = getCourseByNameInClass(class, course_name);
                    if (template_course == NULL) {
                        printf("Warning: Course '%s' not found for student ID %d.\n", course_name, record->id);
                        free(record->course_name);
                        free(record);
                        continue;
                    }
                    course = duplicateCourse(template_course);
                    addCourse(student, course);
                }

                addGradeToCourse(student, course_name, record->grade);
                computeStudentAverage(student);
                computeStudentValidation(student);

                free(record->course_name);
                free(record);
            }
        }
    }


    fclose(file);
    return class;
}

Student *parse_student_record(char *line) {
    //numero;prenom;nom;age

    char *token;
    int field = 0;

    token = strtok(line, DELIM);

    int id;
    char *name;
    char *surname;
    int age;

    while (token != NULL) {
        char *value;

        if (strcmp(token, "-") == 0) {
            value = NULL;
        } else {
            value = malloc(strlen(token) + 1);
            if (value == NULL) {
                free(value);
                return NULL;
            }

            strcpy(value, token);
        }

        switch (field) {
            case 0:
                id = atoi(value);
                break;
            case 1:
                name = malloc(strlen(value) + 1);
                if (name == NULL) {
                    free(value);
                    return NULL;
                }
                strcpy(name, value);
                break;
            case 2:
                surname = malloc(strlen(value) + 1);
                if (surname == NULL) {
                    free(name);
                    free(value);
                    return NULL;
                }
                strcpy(surname, value);
                break;
            case 3:
                age = atoi(value);
                break;
        }

        token = strtok(NULL, DELIM);
        field++;
    }

    Student *student = createStudent(id, name, surname, age);
    return student;
}

Course* parse_course_record(char* line) {
    //nom;coef
    char *token;
    int field = 0;

    token = strtok(line, DELIM);

    char* name;
    double coef = 0.0;

    while (token != NULL) {
        char *value;

        if (strcmp(token, "-") == 0) {
            value = NULL;
        } else {
            value = malloc(strlen(token) + 1);
            if (value == NULL) {
                free(value);
                return NULL;
            }

            strcpy(value, token);
        }

        switch (field) {
            case 0:
                name = malloc(strlen(value) + 1);
                if (name == NULL) {
                    free(value);
                    return NULL;
                }
                strcpy(name, value);
                break;
            case 1:
                char *endptr = NULL;
                coef = strtod(value, &endptr);
                if (endptr == value) {
                    coef = 0.0;
                }
                break;
        }

        token = strtok(NULL, DELIM);
        field++;
    }

    Course* course = createCourse(name, coef);
    return course;
}

StudentGradeRecord* parse_student_grade_record(char* line) {
    //id;nom;note

    char *token;
    int field = 0;

    token = strtok(line, DELIM);

    int studentId;
    char* courseName;
    double grade;

    while (token != NULL) {
        char *value;

        if (strcmp(token, "-") == 0) {
            value = NULL;
        } else {
            value = malloc(strlen(token) + 1);
            if (value == NULL) {
                free(value);
                return NULL;
            }

            strcpy(value, token);
        }

        switch (field) {
            case 0:
                studentId = atoi(value); //not really secure
                break;
            case 1:
                courseName = malloc(strlen(value) + 1);
                if (courseName == NULL) {
                    free(value);
                    return NULL;
                }
                strcpy(courseName, value);
                break;
            case 2:
                char *endptr = NULL;
                grade = strtod(value, &endptr);
                if (endptr == value) {
                    grade = 0.0;
                }
                break;
        }

        token = strtok(NULL, DELIM);
        field++;
    }

    StudentGradeRecord* record = malloc(sizeof(StudentGradeRecord));
    if (record == NULL) {
        free(courseName);
        return NULL;
    }

    record->id = studentId;
    record->course_name = courseName;
    record->grade = grade;

    return record;
}