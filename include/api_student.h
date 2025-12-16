#ifndef API_STUDENT_H
#define API_STUDENT_H

#include <class.h>

#define SIZE_TOP1 10
#define SIZE_TOP2 3

#define ALPHA_FIRST_NAME 1
#define ALPHA_LAST_NAME 2
#define AVERAGE 3
#define MIN 4

/**
 * Load a class from csv file
 * @param filePath path to the csv file
 * @return a Class pointer or NULL if an error append
 */
Class *API_load_students(char *filePath);

/**
 * Save a class pointer to a binary file
 * @param class_
 * @param filePath
 * @return
 */
int API_save_to_binary_file(Class *class_, char *filePath);

/**
 * Restore a class pointer from a binary file
 * @param filePath path to the binary file
 * @return a Class pointer or NULL if an error append
 */
Class *API_restore_from_binary_file(char *filePath);

/**
 * Display the class information
 * @param class
 */
void API_display(Class *class);

/**
 * Unload a class pointer and free all its memory
 * @param class the class to unload
 */
void API_unload(Class *class);

/**
 * Get the SIZE_TOP1 best students in the class
 * @param class the class to get the best students from
 * @return an array of strings containing the best students' names & last names
 */
char** API_get_best_students(Class *class);

/**
 * Get the SIZE_TOP2 best students in a specific course
 * @param class the class to get the best students from
 * @param courseName the course name to get the best students from
 * @return an array of strings containing the best students' names & last names
 */
char** API_get_best_students_in_course(Class *class, char *courseName);

/**
 * Set the sorting mode for the class
 * @param pClass class to save the sorting mode
 * @param mode ALPHA_FIRST_NAME, ALPHA_LAST_NAME, AVERAGE, MIN
 * @return 1 if the mode is valid, 0 otherwise
 */
int API_set_sorting_mode(Class* pClass, int mode);

/**
 * Sort the students in the class according to the set sorting mode of the class
 * @param pClass class to sort
 * @return return SIZE_TOP1 sorted students' names & last names
 */
char** API_sort_students(Class* pClass);

/**
 * Get an array of sorted students according to the class sorting mode
 * @param classObj class to get sorted students from
 * @return return a SIZE_TOP1 array of Student* pointers
 */
Student** API_get_sorted_students(Class *classObj);

/**
 * Display the validation_flags per field using mask of all students in the class
 * @param pClass class to display results from
 */
void API_display_results_per_field(Class* pClass);

#endif //API_STUDENT_H
