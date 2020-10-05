# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/16 21:47:29 by jalvaro           #+#    #+#              #
#    Updated: 2020/08/17 00:39:55 by jalvaro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

FILES = atol init lst main puts sim sim_utils strjoin utils
H_FILE = philo.h

COMPILLER = clang
FLAGS = -Wall -Werror -Wextra
LIBS = -lpthread

SRC_DIR = ./srcs/
SRC_FILE = $(FILES:=.c)
SRC = $(addprefix $(SRC_DIR), $(SRC_FILE))
SRC_TEMP = $(addprefix $(SRC_DIR), %.c)


OBJ_DIR = ./obj/
OBJ_FILE = $(FILES:=.o)
OBJ = $(addprefix $(OBJ_DIR), $(FILES:=.o))
OBJ_TEMP = $(addprefix $(OBJ_DIR), %.o)

INCLUDES = ./includes/
HEADER = $(addprefix $(INCLUDES), $(H_FILE))

.PHONY: all clean fclean re bonus

all: $(OBJ_DIR) $(NAME) $(SRC)

$(NAME): $(OBJ)
	@$(COMPILLER) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME) 
	@echo Программа $(NAME) готова

$(OBJ_TEMP): $(SRC_TEMP) $(HEADER)
	@echo Собираю $@ из $<
	@$(COMPILLER) $(FLAGS) -c $< -I $(INCLUDES) -o $@ 

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	@rm -f $(LIB)
	@rm -f $(OBJ) $(BONUS_OBJ)
	@echo $(NAME): удаляю *.o

fclean: clean
	@rm -f $(NAME)
	@echo $(NAME): программа удалена

re: fclean all