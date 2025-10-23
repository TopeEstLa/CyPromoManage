cmake_minimum_required(VERSION 4.0)
project(PromoManage C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include/
)

add_executable(PromoManage
        src/main.c
        include/list.h
        src/list.c

        include/course.h
        src/course.c
        include/student.h
        src/student.c
        include/class.h
        src/class.c
        include/csv_parser.h
        src/csv_parser.c
)
