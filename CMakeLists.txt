cmake_minimum_required(VERSION 3.8)
project(ft_printf)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ft_printf.c)
add_executable(ft_printf ${SOURCE_FILES})
link_libraries(ft_printf ${LIBFT})