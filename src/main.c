#include <csv_parser.h>
#include <stdio.h>
#include <data_saver.h>

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

    //Class *class = process_csv_file("data.txt");

    //Student *student = getStudentById(class, 226889900);

    // printStudent(student);

    printf("SAVING\n");
    //bool saved = save_class_to_file(class, "class_data.bin");
    printf("LOADING\n");
    Class *loaded_class = load_class_from_file("class_data.bin");
    if (loaded_class) {
        printf("LOADED\n");
        Student *studenat = getStudentById(loaded_class, 226889900);
        printStudent(studenat);
    }
}
