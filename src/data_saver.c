#include <class.h>
#include <student.h>
#include <course.h>
#include <list.h>
#include <string.h>
#include <memory_utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static bool write_string(FILE *f, const char *s) {
    if (s == NULL) {
        int len = 0;
        return fwrite(&len, sizeof(len), 1, f) == 1;
    }
    int len = (int) strlen(s);
    if (fwrite(&len, sizeof(len), 1, f) != 1) return false;
    return len == 0 || fwrite(s, 1, len, f) == len;
}

static char *read_string(FILE *f) {
    int len;
    if (fread(&len, sizeof(len), 1, f) != 1) return NULL;
    char *buf = malloc(len + 1);
    if (buf == NULL) return NULL;
    if (len > 0) {
        if (fread(buf, 1, len, f) != len) {
            free(buf);
            return NULL;
        }
    }
    buf[len] = '\0';
    return buf;
}

//The next 2 functions *seem* work but as probably a loooooooot of issue
bool save_class_to_file(Class *class, char *filename) {
    if (class == NULL || filename == NULL) return false;
    FILE *f = fopen(filename, "wb");
    if (!f) return false;

    int student_count = 0;
    if (class->students) student_count = class->students->size;
    if (fwrite(&student_count, sizeof(student_count), 1, f) != 1) {
        fclose(f);
        return false;
    }

    for (int i = 0; i < student_count; ++i) {
        Student *s = get(class->students, i);
        if (!s) {
            fclose(f);
            return false;
        }

        int id = s->id;
        int age = s->age;
        if (fwrite(&id, sizeof(id), 1, f) != 1) {
            fclose(f);
            return false;
        }
        if (fwrite(&age, sizeof(age), 1, f) != 1) {
            fclose(f);
            return false;
        }

        if (!write_string(f, s->name)) {
            fclose(f);
            return false;
        }
        if (!write_string(f, s->surname)) {
            fclose(f);
            return false;
        }

        double avg = s->average;
        if (fwrite(&avg, sizeof(avg), 1, f) != 1) {
            fclose(f);
            return false;
        }

        int course_count = 0;
        if (s->courses) course_count = s->courses->size;
        if (fwrite(&course_count, sizeof(course_count), 1, f) != 1) {
            fclose(f);
            return false;
        }

        for (int j = 0; j < course_count; ++j) {
            Course *c = get(s->courses, j);
            if (!c) {
                fclose(f);
                return false;
            }

            if (!write_string(f, c->name)) {
                fclose(f);
                return false;
            }

            if (fwrite(&c->coef, sizeof(c->coef), 1, f) != 1) {
                fclose(f);
                return false;
            }
            if (fwrite(&c->average, sizeof(c->average), 1, f) != 1) {
                fclose(f);
                return false;
            }

            int grade_count = 0;
            if (c->grades) grade_count = c->grades->size;
            if (fwrite(&grade_count, sizeof(grade_count), 1, f) != 1) {
                fclose(f);
                return false;
            }

            for (int k = 0; k < grade_count; ++k) {
                double *gp = get(c->grades, k);
                double g = gp ? *gp : 0.0;
                if (fwrite(&g, sizeof(g), 1, f) != 1) {
                    fclose(f);
                    return false;
                }
            }
        }
    }

    fclose(f);
    return true;
}

bool save_student_to_file(Student* student, char* filename) {
    if (student == NULL || filename == NULL) return false;
    FILE *f = fopen(filename, "wb");
    if (!f) return false;


    printf("Surname : %s\n", student->surname);
    printf("Name : %s\n", student->name);
    fwrite(student->surname, 1, strlen(student->surname) + 1, f); //no swap need
    fwrite(student->name, 1, strlen(student->name) + 1, f); //no swap need

    printf("Id hexa before swap: %X\n", student->id);
    int* swp_id = swap_order(&student->id, sizeof(int), 1);
    if (swp_id == NULL) {
        fclose(f);
        return false;
    }

    printf("Id hexa after swap: %X\n", *swp_id);
    fwrite(swp_id, sizeof(int), 1, f);
    free(swp_id);

    printf("Age hexa before swap: %X\n", student->age);
    int* swp_age = swap_order(&student->age, sizeof(int), 1);
    if (swp_age == NULL) {
        fclose(f);
        return false;
    }

    printf("Age hexa after swap: %X\n", *swp_age);
    fwrite(swp_age, sizeof(int), 1, f);
    free(swp_age);

    printf("Average hexa before swap: %lX\n", *(unsigned long*)&student->average);
    int* swp_avg = swap_order(&student->average, sizeof(double), 1);
    if (swp_avg == NULL) {
        fclose(f);
        return false;
    }

    printf("Average hexa after swap: %lX\n", *(unsigned long*)swp_avg);
    fwrite(swp_avg, sizeof(double), 1, f);
    free(swp_avg);

    for (int i = 0; i < student->courses->size; i++) {
        Course* course = get(student->courses, i);
        if (course == NULL) continue;

        fwrite(course->name, 1, strlen(course->name) + 1, f); //no swap need

        printf("Average of course %s hexa before swap: %lX\n", course->name, *(unsigned long*)&course->average);
        int* swp_c_avg = swap_order(&course->average, sizeof(double), 1);
        if (swp_c_avg == NULL) {
            fclose(f);
            return false;
        }

        printf("Average of course %s hexa after swap: %lX\n", course->name, *(unsigned long*)swp_c_avg);
        fwrite(swp_c_avg, sizeof(double), 1, f);
        free(swp_c_avg);
    }

    fclose(f);
    return true;
}

Class *load_class_from_file(char *filename) {
    if (filename == NULL) return NULL;
    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;

    Class *cls = malloc(sizeof(Class));
    if (!cls) {
        fclose(f);
        return NULL;
    }
    cls->students = createList();
    if (!cls->students) {
        free(cls);
        fclose(f);
        return NULL;
    }

    int student_count = 0;
    if (fread(&student_count, sizeof(student_count), 1, f) != 1) {
        fclose(f);
        free(cls);
        return NULL;
    }

    for (int i = 0; i < student_count; ++i) {
        int id, age;
        if (fread(&id, sizeof(id), 1, f) != 1) {
            free(cls);
            fclose(f);
            return NULL;
        }
        if (fread(&age, sizeof(age), 1, f) != 1) {
            free(cls);
            fclose(f);
            return NULL;
        }

        char *name = read_string(f);
        char *surname = read_string(f);
        if (!name || !surname) {
            free(name);
            free(surname);
            free(cls);
            fclose(f);
            return NULL;
        }

        double avg = 0.0;
        if (fread(&avg, sizeof(avg), 1, f) != 1) {
            free(name);
            free(surname);
            free(cls);
            fclose(f);
            return NULL;
        }

        Student *s = createStudent(id, name, surname, age);
        if (!s) {
            free(name);
            free(surname);
            free(cls);
            fclose(f);
            return NULL;
        }
        s->average = avg;

        append(cls->students, s);

        int course_count = 0;
        if (fread(&course_count, sizeof(course_count), 1, f) != 1) {
            fclose(f);
            return cls;
        }

        for (int j = 0; j < course_count; ++j) {
            char *cname = read_string(f);
            if (!cname) {
                fclose(f);
                return cls;
            }

            double coef = 0.0;
            double cavg = 0.0;
            if (fread(&coef, sizeof(coef), 1, f) != 1) {
                free(cname);
                fclose(f);
                return cls;
            }
            if (fread(&cavg, sizeof(cavg), 1, f) != 1) {
                free(cname);
                fclose(f);
                return cls;
            }

            char *name = malloc(strlen(cname) + 1);
            strcpy(name, cname);
            Course *c = createCourse(name, coef);
            free(cname);
            if (!c) {
                fclose(f);
                return cls;
            }
            c->average = cavg;

            int grade_count = 0;
            if (fread(&grade_count, sizeof(grade_count), 1, f) != 1) {
                fclose(f);
                return cls;
            }

            for (int k = 0; k < grade_count; ++k) {
                double g = 0.0;
                if (fread(&g, sizeof(g), 1, f) != 1) {
                    fclose(f);
                    return cls;
                }
                addGrade(c, g);
            }
            computeCourseAverage(c);
            addCourse(s, c);
        }
    }

    fclose(f);
    return cls;
}
