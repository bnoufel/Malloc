NAME = libft_malloc_$(HOSTTYPE).so
NAME2 = libft_malloc_$(HOSTTYPE).a
SHORTNAME = libft_malloc.so

ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

###############################
####### GLOBAL VARIABLE #######
###############################
RED 		= 	\x1b[31m
YELLOW	 	= 	\x1b[33m
GREEN 		= 	\x1b[32m
RESET 		= 	\x1b[0m
SRCSDIR 	= 	srcs
OBJSDIR 	= 	objects
INCLUDES 	= 	includes
DEBUG		=	-g3
CFLAGS 		=  	-Wall -Werror -Wextra -Wpadded
CC 			= 	gcc $(CFLAGS) $(DEBUG)
HEADER		=	malloc.h
HEADERS		=	$(addprefix $(INCLUDES)/, $(HEADER))
###############################
######## CREATE FOLDER ########
####### C FILE BY FOLDER ######
###############################

SRC     =		malloc_size.c header.c zone.c malloc.c free.c realloc.c tools.c ft_putchar.c ft_putlbr.c ft_putstr.c ft_putendl.c ft_strlen.c ft_memcpy.c ft_bzero.c hexdump.c show_alloc_mem.c
###############################
######### ADD PREFIX ##########
###### ALL SRC/OBJ FILE #######
###############################

OBJ 		= 	$(SRC:%.c=%.o)

SRCS 		= 	$(addprefix $(SRCSDIR)/, $(SRC))
OBJS 		= 	$(addprefix $(OBJSDIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS)
	@printf "Compiling $(NAME)${RESET}"
	@$(CC) -shared -o $(NAME) $(OBJS)
	@rm -rf libft_malloc.so
	@ln -s $(NAME) libft_malloc.so
	@echo " done [${GREEN}✔${RESET}]"

compile:
	@gcc tests/test0.c  -Iincludes/ -o tests/test0
	@gcc tests/test1.c -Iincludes/ -o tests/test1
	@gcc tests/test2.c -Iincludes/ -o tests/test2
	@gcc tests/test3.c -Iincludes/ -o tests/test3
	@gcc tests/test3++.c -Iincludes/ -o tests/test3++
	@gcc tests/test4.c -Iincludes/ -o tests/test4
	@gcc tests/test5.c -Iincludes/ -L. -lft_malloc -o tests/test5
	@echo "${RED}Compiling tests ${RESET} [${GREEN}✔${RESET}]"

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HEADERS)
	@$(CC) -c -o $@ $< -I$(INCLUDES)


$(OBJSDIR):
	@mkdir -p $(OBJSDIR)/$(DIRCORE)
	@sed -i -e "/add_executable/d" CMakeLists.txt
	@rm CMakeLists.txt-e
	@echo "add_executable(malloc $(SRCS) tests/test0.c $(HEADERS))" | sed -e "s/\.\.\///g" >> CMakeLists.txt

clean:
	@echo "${RED}Cleaning $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -rf $(OBJSDIR);

fclean: clean
	@echo "${RED}Purge $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -f $(NAME) $(SHORTNAME)
	@rm -rf $(NAME).dSYM

re: fclean all

.PHONY: all, clean, fclean, re, $(OBJSDIR)/$(DIRCORE), $(compile)

.SUFFIXES: .c .o
