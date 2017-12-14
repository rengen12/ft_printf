cmake_minimum_required(VERSION 3.8)
project(ft_printf)
set(CMAKE_C_STANDARD 99)
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wconversion")
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
set(SOURCE_FILES test.c ft_printf.c chars.c ft_convert_base.c ft_putchar.c ft_putstr.c ft_strlen.c
        ft_memdel.c ft_strchr.c  ft_strncat.c ft_strnew.c ft_memset.c ft_putnbr.c ft_strdel.c ft_strdup.c ft_putendl.c modificators.c ft_atoi_printf.c)
add_executable(ft_printf ${SOURCE_FILES})
target_link_libraries(ft_printf)