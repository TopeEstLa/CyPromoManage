#ifndef API_STUDENT_H
#define API_STUDENT_H

#include <class.h>

#define SIZE_TOP1 10
#define SIZE_TOP2 3

#define ALPHA_FIRST_NAME 1
#define ALPHA_LAST_NAME 2
#define AVERAGE 3
#define MIN 4

Class *API_load_students(char *filePath);

int API_save_to_binary_file(Class *class_, char *filePath);

Class *API_restore_from_binary_file(char *filePath);

void API_display(Class *class);

void API_unload(Class *class);

char** API_get_best_students(Class *class);

char** API_get_best_students_in_course(Class *class, char *courseName);

int API_set_sorting_mode(Class* pClass, int mode);

char** API_sort_students(Class* pClass);

Student** API_get_sorted_students(Class *classObj);

void API_display_results_per_field(Class* pClass);

#endif //API_STUDENT_H
