# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: subpark <subpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 16:59:02 by subpark           #+#    #+#              #
#    Updated: 2024/02/27 11:49:04 by subpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CCFLAGS = -Wall -Werror -Wextra

CC = cc #-fsanitize=address #-g -fsanitize=thread

SRCS = ft_atoi.c generate.c philosopher.c\
		tools.c threads.c main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
			rm -f $(OBJS)
fclean: clean
			rm -f $(NAME)
			rm -f $(LIBFT)
re: fclean all

%.o: %.c include/philo.h
			$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJS)
			$(CC) $(CCFLAGS) -o $@ $^
.PHONY: all clean fclean re
