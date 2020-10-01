# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngragas <ngragas@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/19 20:29:14 by ngragas           #+#    #+#              #
#    Updated: 2020/09/30 21:28:34 by bmicheal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCES = bsq.c bsq_input.c bsq_string.c bsq_parse.c
OBJECTS = $(SOURCES:.c=.o)
NAME = BSQ
HEADER = bsq.h
RM = rm -f

.PHONY: all
all: $(NAME)
.PHONY: clean
clean:
	@$(RM) $(OBJECTS)
.PHONY: fclean
fclean: clean
	@$(RM) $(NAME)
.PHONY: re
re: fclean all
%.o: %.c $(INCL) $(HEADER)
	@$(CC) $(CFLAGS) -o $@ -c $<
$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)
