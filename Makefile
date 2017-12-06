# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amichak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/11 13:15:45 by amichak           #+#    #+#              #
#    Updated: 2017/12/05 16:43:12 by amichak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
HEADER = -I ./
OBJFOLD = ./obj/
SRC = ft_printf.c chars.c ft_convert_base.c ft_putchar.c \
	  ft_putstr.c ft_strlen.c ft_memdel.c ft_strncat.c ft_strnew.c ft_memset.c \
	  ft_putnbr.c ft_strdel.c ft_strdup.c

OBJ = $(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRC)))

all:				$(NAME)

$(NAME):			$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "ft_printf: done"
	
$(OBJFOLD)%.o: %.c
	@mkdir -p $(OBJFOLD)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@rm -rf $(OBJFOLD)

fclean:				clean
	@rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
