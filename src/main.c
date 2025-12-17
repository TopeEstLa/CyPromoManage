#include <api_student.h>
#include <stdio.h>
#include <class.h>
#include <assert.h>
#include <memory_utils.h>
#include <data_saver.h>
#include <list.h>


int main(void) {
    /**
     *How this will work
     * Create class object
     * read all student line and create their object (and put it on the class student list)
     * end whhen i find the "MATIERES" line (skip 1 line cause its the 'csv header')
     * read all existant course and make "template of it"
     * end when i find the "NOTES" line (skip 1 line cause its the 'csv header')
     * read all grade find student in the class object until the eof
     * => Check if the Student object already had the target grade
     *  => Yes just use the addGradeToCourse Method
     *  => No Find the Template Course Object and duplicate it, add it to the student object and now add the grade
     */

    /*
     * Second note this code its seem like a rabbit hole lol
     * Class -> List(Student*) -> Student* -> List(Course*) -> Course* -> List(Double*) lmao
     */

    //Default
    Class *class = API_load_students("data.txt");
    if (class == NULL) {
        printf("Failed to load class\n");
        return 1;
    }

    //- Exo 1 Start-
    API_display(class);

    bool valid = updateClassAverageGrades(class, standardization);

    if (valid) {
        printf("Update success\n");
        API_display(class);
    } else {
        printf("Update failed\n");
    }
    //- Exo 1 End -

    // Exo 2 Start -
    int size;
    char** name = listName(class, &size);
    if (name == NULL) {
        printf("No names found\n");
        API_unload(class);
        return 1;
    }

    printf("%d\n", size);
    for (int i = 0; i < size; i++) {
        if (name[i] == NULL) continue;
        printf("#%d %s\n", i, name[i]);
    }
    //- Exo 2 End -


    //- Exo 3 Start -
    uint16_t input = 0xAABB;
    uint16_t expected = 0xBBAA;

    uint16_t* result = swap_order(&input, sizeof(uint16_t), 1);

    assert(result != NULL);
    assert(*result == expected);
    assert(input == 0xAABB);
    printf("Exo 3 test 1 passed.\n");

    free(result);

    uint64_t input2 = 0x1122334455667788ULL;
    uint64_t expected2 = 0x8877665544332211ULL;

    uint64_t* result2 = swap_order(&input2, sizeof(uint64_t), 1);

    assert(result2 != NULL);
    assert(*result2 == expected2);

    free(result2);
    printf("Exo 3 test 2 passed.\n");

    uint32_t input3[3] = {0x11111111, 0xAABBCCDD, 0x12345678};
    uint32_t expected3[3] = {0x11111111, 0xDDCCBBAA, 0x78563412};

    uint32_t* result3 = swap_order(input3, sizeof(uint32_t), 3);

    assert(result3 != NULL);
    assert(result3[0] == expected3[0]);
    assert(result3[1] == expected3[1]);
    assert(result3[2] == expected3[2]);

    free(result3);
    printf("Exo 3 test 3 passed.\n");


    printf("Saving random student to binary file...\n");

    int index = rand() % class->students->size;
    Student* student = get(class->students, index);
    printf("Saving student %s\n", student->name);

    bool success = save_student_to_file(student, "student.bin");

    if (success) {
        printf("Student saved successfully.\n");
    } else {
        printf("Failed to save student to binary file.\n");
    }

}
