# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchotel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 11:15:39 by jchotel           #+#    #+#              #
#    Updated: 2020/03/06 16:34:05 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL ******************************************************************** #
NAME		= minishell
LIBS 		= ./libs/ft_printf/printf.a\
			  ./libs/libft/libft.a

# SOURCE ********************************************************************* #			  
SRCSC		= libs/gnl/get_next_line.c\
			  libs/gnl/get_next_line_utils.c\
			  srcs/ft_pipes.c\
			  srcs/ft_quotes.c\
			  srcs/ft_list_split.c
			  #srcs/main.c
SRCSH		= includes/minishell.h
OBJS		= $(SRCSC:%.c=%.o)

# COMMANDES ****************************************************************** #
FLAGS		= #-fsanitize=address
CC			= gcc
MKDIR		= mkdir

# COLORS ********************************************************************* #
CR			= "\r"$(CLEAR)
CLEAR       = "\\033[0K"
BLACK		= "\033[0;30m"
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
YELLOW		= "\033[1;33m"
DARKBLUE	= "\033[0;34m"
VIOLET		= "\033[0;35m"
BLUE		= "\033[0;36m"

GREY		= "\033[0;2m"
BOLDWHITE	= "\033[0;1m"
WHITE		= "\033[0;0m"

REDB		= "\033[0;41m"

# RULES ********************************************************************** #
all:		${NAME}

.c.o:
	@printf $(CR)"[FILE : %s]" $@
	@${CC} ${FLAGS} -c $< -o $@

$(NAME):	lib_make ${OBJS}
			@${CC} ${FLAGS} ${OBJS} ${LIBS} -o ${NAME}
			@echo ${GREEN}${CR}"┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo 		  	   "└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo 		  	   "└─┘└─┘└─┘└─┘└─┘└─┘└─┘"
			@echo ${NAME}".a generated successfully." ${WHITE}

bonus:		${NAME}

run:
			@make
			@./${NAME}

lib_make:	${SRCSH}
			@printf $(CR)
			@make bonus -C libs/libft
			@make -C libs/ft_printf

clean:
			@make clean -C libs/libft
			@make clean -C libs/ft_printf
			@rm -rf ${OBJS}
			@echo ${RED}${NAME}" : Removing .o files" ${WHITE}

fclean:		clean
			@make bclean -C libs/libft
			@make bclean -C libs/ft_printf
			@rm -f ${NAME}
			@echo ${RED}${NAME}" : Removing binary file" ${WHITE}

re:			fclean all

.PHONY:		all clean fclean re bonus run
