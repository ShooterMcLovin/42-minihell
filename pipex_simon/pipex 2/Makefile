# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 13:28:25 by siroulea          #+#    #+#              #
#    Updated: 2023/09/28 13:54:01 by siroulea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  pipex

SRC =		main.c		\
		utils2.c	\
		ft_split.c	\
		utils.c 		

OBJS = ${SRC:.c=.o}

CC = clang
CFLAGS = -Wextra -Wall -Werror -g

CLEAN = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(CLEAN) $(OBJS)
	$(CLEAN) *.o

fclean: clean
	$(CLEAN) $(NAME)

re: fclean all


leaks: all
	leaks -atExit -- ./pipex ft_split.c "ls -l" "wc -l" caca 

