cmake_minimum_required(VERSION 3.00)
SET(CMAKE_GENERATOR "Ninja")
message("generator is set to ${CMAKE_GENERATOR}")

#set (project_name ap5) #project_name <- ap5

project(Letras_y_numeros C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wformat=2)

add_executable(Letras_y_numeros letrasynumeros.c)