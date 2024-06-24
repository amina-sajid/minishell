# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 13:49:49 by asajid            #+#    #+#              #
#    Updated: 2023/12/08 12:06:50 by iganiev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	minishelll.c \
		parser/mini.c \
		parser/lexer.c\
		parser/error_check.c\
		parser/parser.c\
		parser/nodes.c\
		parser/count_quotes.c\
		parser/lexer_utils.c\
		parser/expander.c \
		parser/expander_utils.c \
		parser/parser_utils.c\
		parser/pipe_nodes.c\
		parser/test.c\
		executor/find_path.c \
		executor/process.c \
		executor/utils.c \
		executor/run_cmdline.c \
		executor/heredoc.c \
		executor/pipex_utils.c \
		executor/handle_input.c \
		executor/handle_output.c \
		executor/run_pipex.c \
		executor/run_redircmd.c \
		executor/fd_utils.c \
		executor/check_builtin.c \
		executor/cleaning_functions.c \
		executor/clean_env_struct.c \
		executor/signals.c \
		executor/fill_struct.c \
		env/get_env.c \
		builtins/ft_export.c builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c \
		builtins/ft_exit.c builtins/ft_pwd.c builtins/ft_unset.c builtins/handle_exit_args.c\
		builtins/exit_utils.c builtins/env_utils.c builtins/export_utils.c\



OBJS = ${SRCS:.c=.o}
CHECK_OBJS = ${CHECK_SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${MAKE} -C libft
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -lreadline  -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -o ${NAME}

clean:
	@${MAKE} -C libft clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C libft fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re


