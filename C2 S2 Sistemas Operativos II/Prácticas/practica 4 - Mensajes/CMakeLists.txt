cmake_minimum_required(VERSION 3.00)
project(soii_p4 C)

set(CMAKE_C_STANDARD 11)


add_executable(consumidor_FIFO
        consumidor_FIFO.c)

add_executable(productor_FIFO
        productor_FIFO.c)


add_executable(consumidor_LIFO
        consumidor_LIFO.c)

add_executable(productor_LIFO
        productor_LIFO.c)
