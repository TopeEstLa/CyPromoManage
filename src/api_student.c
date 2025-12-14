#include <api_student.h>
#include <csv_parser.h>
#include <data_saver.h>
#include <stdio.h>

Class *API_load_students(char *filePath) {
    return process_csv_file(filePath);
}

int API_save_to_binary_file(Class *class_, char *filePath) {
    return save_class_to_file(class_, filePath);
}

Class *API_restore_from_binary_file(char *filePath) {
    return load_class_from_file(filePath);
}

void API_display(Class *class) {
    if (class == NULL) {
        printf("Class is NULL\n");
        return;
    }

    ListNode *studentNode = class->students->head;
    while (studentNode != NULL) {
        Student *student = (Student *) studentNode->data;
        printf("Student ID: %d, Name: %s %s, Age: %d, Average: %.2f\n",
               student->id, student->name, student->surname, student->age, student->average);
        ListNode *courseNode = student->courses->head;
        while (courseNode != NULL) {
            Course *course = (Course *) courseNode->data;
            //printf("  Course: %s, Coefficient: %.2f, Average: %.2f\n",
            //       course->name, course->coef, course->average);
            courseNode = courseNode->next;
        }

        studentNode = studentNode->next;
    }
}

void API_unload(Class *class) {
    freeClass(class);
}
