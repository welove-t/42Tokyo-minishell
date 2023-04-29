# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: terabu <terabu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 14:24:24 by subarunrun        #+#    #+#              #
#    Updated: 2023/04/29 12:00:36 by terabu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RL_FLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib
INCLUDE = -I include -I $(LIBFT_DIR) -I $(shell brew --prefix readline)/include -I/usr/local/opt/readline/include
CFLAGS = -Wall -Werror -Wextra $(INCLUDE)

SOURCES_DIR = ./srcs
UTILS_DIR = ./srcs/utils
BUILTIN_DIR = ./srcs/builtin
LIBFT_DIR = ./srcs/lib/libft
SOURCES = $(SOURCES_DIR)/main.c\
		  $(SOURCES_DIR)/str_matches_cmd.c\
		  $(SOURCES_DIR)/init_environ_list.c\
		  $(SOURCES_DIR)/error_general.c\
		  $(SOURCES_DIR)/error_special.c\
		  $(SOURCES_DIR)/error_tokenizer.c\
		  $(SOURCES_DIR)/error_put.c\
		  $(SOURCES_DIR)/error_cmd.c\
		  $(SOURCES_DIR)/error_file.c\
		  $(SOURCES_DIR)/destructors.c\
		  $(SOURCES_DIR)/signal.c\
		  $(BUILTIN_DIR)/cd.c\
		  $(BUILTIN_DIR)/echo.c\
		  $(BUILTIN_DIR)/env.c\
		  $(BUILTIN_DIR)/exit.c\
		  $(BUILTIN_DIR)/export.c\
		  $(BUILTIN_DIR)/export_utils.c\
		  $(BUILTIN_DIR)/pwd.c\
		  $(BUILTIN_DIR)/unset.c\
		  $(UTILS_DIR)/dollar_sign.c\
		  $(UTILS_DIR)/get_cmd_line.c\
		  $(UTILS_DIR)/process_word.c\
		  $(UTILS_DIR)/tokenizer.c\
		  $(UTILS_DIR)/tokenizer_check_literal.c\
		  $(UTILS_DIR)/tokenizer_check_quote.c\
		  $(UTILS_DIR)/tokenizer_utils.c\
		  $(UTILS_DIR)/search_bi_cmd.c\
		  $(UTILS_DIR)/parser.c\
		  $(UTILS_DIR)/parser_node_redirect.c\
		  $(UTILS_DIR)/parser_make_tok.c\
		  $(UTILS_DIR)/parser_check.c\
		  $(UTILS_DIR)/expantion.c\
		  $(UTILS_DIR)/heredoc.c\
		  $(UTILS_DIR)/redirect.c\
		  $(UTILS_DIR)/redirect_open.c\
		  $(UTILS_DIR)/exec.c\
		  $(UTILS_DIR)/pipe.c\

VPATH = $(SOURCES_DIR) $(UTILS_DIR) $(BUILTIN_DIR)
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SOURCES:.c=.o)))
LIBFT = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $^ $(RL_FLAGS) $(LIBFT) -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C ${LIBFT_DIR} clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ${LIBFT_DIR} fclean

re: fclean all
