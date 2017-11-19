cmake_minimum_required(VERSION 3.8)
project(ft_printf)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ft_printf.c main.c
        libft/ft_putstr.c
        libft/ft_putchar.c
        libft/ft_putnbr.c
        libft/ft_putendl.c
        )
add_executable(ft_printf ${SOURCE_FILES})