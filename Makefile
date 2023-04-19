# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: terabu <terabu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 14:24:24 by subarunrun        #+#    #+#              #
#    Updated: 2023/04/19 13:36:22 by susasaki         ###   ########.fr        #
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
		  $(SOURCES_DIR)/init_environ_list.c\
		  $(SOURCES_DIR)/error.c\
		  $(BUILTIN_DIR)/echo.c\
		  $(BUILTIN_DIR)/env.c\
		  $(BUILTIN_DIR)/export.c\
		  $(BUILTIN_DIR)/export_utils.c\
		  $(BUILTIN_DIR)/pwd.c\
		  $(BUILTIN_DIR)/unset.c\
		  $(UTILS_DIR)/get_cmd_line.c\
		  $(UTILS_DIR)/tokenizer.c\
		  $(UTILS_DIR)/expantion.c\
		  $(UTILS_DIR)/heredoc.c\
		  $(UTILS_DIR)/parser.c\
		  $(UTILS_DIR)/redirect.c\
		  $(UTILS_DIR)/exec.c\
		  $(UTILS_DIR)/pipe.c\

OBJS = $(SOURCES:.c=.o)
LIBFT = -L$(LIBFT_DIR) -lft
# READLINE = -lreadline -L $(brew --prefix readline)/lib -I $(brew --prefix readline)/include

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ${LIBFT_DIR}
	$(CC) $(OBJS) -o $(NAME) $(LIBFT) -L$(HOME)/.brew/opt/readline/include -L$(HOME)/.brew/opt/readline/lib -lreadline

clean:
	rm -f $(OBJS)
	$(MAKE) -C ${LIBFT_DIR} clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ${LIBFT_DIR} fclean

re: fclean all
