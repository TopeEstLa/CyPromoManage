#ifndef API_STUDENT_H
#define API_STUDENT_H

#include <class.h>

#define SIZE_TOP1 10
#define SIZE_TOP2 3

Class *API_load_students(char *filePath);

int API_save_to_binary_file(Class *class_, char *filePath);

Class *API_restore_from_binary_file(char *filePath);

void API_display(Class *class);

void API_unload(Class *class);

char** API_get_best_students(Class *class);

char** API_get_best_students_in_course(Class *class, char *courseName);

#endif //API_STUDENT_H
