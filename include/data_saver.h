#ifndef DATA_SAVER_H
#define DATA_SAVER_H

#include "class.h"
#include <stdbool.h>

/**
 * Save the class data to a file
 * @param class the class to save
 * @param filename the file to save to
 * @return
 */
bool save_class_to_file(Class* class, char* filename);

/**
 * Load the class data from a file
 * @param filename the file to load from
 * @return the loaded class
 */
Class* load_class_from_file(char* filename);

#endif //DATA_SAVER_H