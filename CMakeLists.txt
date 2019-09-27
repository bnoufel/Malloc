cmake_minimum_required(VERSION 3.12.3)
project(malloc C)

set(CMAKE_C_STANDARD 99)

include_directories("includes")

add_executable(malloc srcs/malloc_size.c srcs/header.c srcs/zone.c srcs/malloc.c srcs/free.c srcs/realloc.c srcs/tools.c srcs/ft_putchar.c srcs/ft_putlbr.c srcs/ft_putstr.c srcs/ft_putendl.c srcs/ft_strlen.c srcs/ft_memcpy.c srcs/ft_bzero.c srcs/hexdump.c srcs/show_alloc_mem.c tests/test0.c includes/malloc.h)
