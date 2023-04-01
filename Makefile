# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: terabu <terabu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 14:24:24 by subarunrun        #+#    #+#              #
#    Updated: 2023/04/01 14:07:40 by terabu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES_DIR = ./srcs
UTILS_DIR = ./srcs/utils
BUILTIN_DIR = ./srcs/builtin
LIBFT_DIR = ./srcs/lib/libft

SOURCES = $(SOURCES_DIR)/main.c\
		  $(SOURCES_DIR)/str_matches_cmd.c\
		  $(BUILTIN_DIR)/echo.c\
		  $(BUILTIN_DIR)/pwd.c\
		  $(BUILTIN_DIR)/unset.c\
		  $(UTILS_DIR)/get_cmd_line.c\

OBJS = $(SOURCES:.c=.o)
LIBFT = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ${LIBFT_DIR}
	$(CC) $(OBJS) -o $(NAME) $(LIBFT) -Iincludes -lreadline

clean:
	rm -f $(OBJS)
	$(MAKE) -C ${LIBFT_DIR} clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ${LIBFT_DIR} fclean

re: fclean all
