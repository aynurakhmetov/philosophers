# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 17:31:34 by gmarva            #+#    #+#              #
#    Updated: 2021/03/13 20:24:12 by gmarva           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
FILES_C = main.c ft_lib.c ft_ph_life.c ft_ph_eat.c ft_ph_die.c ft_exit.c
FILES_O = $(FILES_C:.c=.o)
GCC = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(FILES_O)
	@$(GCC) $(FILES_O) -o $(NAME) 
	@echo "All ready"

%.o: %.c
	@$(GCC) -c $< -o $@
	@echo "$@ ready"

run: all

norms:
	norminette .

test0:
	./$(NAME) 2 400 200 200 1

test1:
	./$(NAME) 5 800 200 200

test2:
	./$(NAME) 5 800 200 200 7

test3:
	./$(NAME) 4 410 200 200

test4:
	./$(NAME) 4 310 200 100

clean:
	@rm -rf $(FILES_O)
	@echo "O-files deleted"

fclean: clean
	@rm -rf $(NAME)
	@echo "All files delete"

re: fclean all

.PHONY: clean fclean all re run