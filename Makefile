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
LIBS 		= ./libs/libft/libft.a

# SOURCE ********************************************************************* #			  
INC			= includes/
SRCSDIR		= srcs
SRCSDIRB	= srcs/bonus
SRCS		= ft_pipes.c\
			  ft_quotes.c\
			  ft_parse.c\
			  ft_replace.c \
			  ft_checkread.c \
			  echo_cd_pwd.c \
			  env_unset.c\
			  bin_exec.c \
			  export.c \
			  main.c \
			  utils_pipes.c \
			  utils_pipes2.c \
			  utils_minishell.c \
			  utils_minishell2.c \
			  ft_list_split.c

SRCB		= ft_pipes.c\
			  ft_replace.c \
			  ft_checkread.c \
			  echo_cd_pwd.c \
			  env_unset.c\
			  bin_exec.c \
			  export.c \
			  utils_pipes.c \
			  utils_pipes2.c \
			  utils_minishell.c \
			  utils_minishell2.c \
			  ft_list_split.c \
			  bonus/main_bonus.c \
			  bonus/ft_parse_bonus.c\
			  bonus/ft_quotes_bonus.c\
			  bonus/ft_wildcard_bonus.c \
			  bonus/ft_checkquotes_bonus.c

GNLDIR 		= libs/gnl
GNL 		= get_next_line.c \
			  get_next_line_utils.c

OBJSDIR		= objs
OBJSDIRB	= objs/bonus
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:%.c=%.o))
OBJSB		= $(addprefix $(OBJSDIR)/, $(SRCB:%.c=%.o))
OBJS2		= $(addprefix $(OBJSDIR)/, $(GNL:%.c=%.o))



# COMMANDES ****************************************************************** #
FLAGS		= -Iincludes/ -g -fsanitize=address -Wall -Wextra -Werror
CC			= gcc

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

$(OBJSDIR)/%.o : $(SRCSDIR)/%.c | $(OBJSDIR)
	@printf ${CR}"[FILE : %s]" $@
	@${CC} ${FLAGS} -c $< -o $@

$(OBJSDIR)/%.o : $(GNLDIR)/%.c | $(OBJSDIR)
	@printf ${CR}"[FILE : %s]" $@
	@${CC} ${FLAGS} -c $< -o $@

$(OBJSDIR):
			mkdir -p ${OBJSDIR}
			mkdir -p ${OBJSDIRB}

$(NAME):	lib_make ${OBJS} ${OBJS2}
			@${CC} -I ${INC} ${FLAGS} ${OBJS} ${OBJS2} ${LIBS} -o ${NAME}
			@echo ${GREEN}${CR}"┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo 		  	   "└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo 		  	   "└─┘└─┘└─┘└─┘└─┘└─┘└─┘"
			@echo ${NAME}" generated successfully." ${WHITE}

bonus:		lib_make ${OBJS2} ${OBJSB}
			@${CC} -I ${INC} ${FLAGS} ${OBJS2} ${OBJSB} ${LIBS} -o ${NAME}
			@echo ${GREEN}${CR}"┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo 		  	   "└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo 		  	   "└─┘└─┘└─┘└─┘└─┘└─┘└─┘"
			@echo ${NAME}" generated successfully with bonus." ${WHITE}

run:
			@make
			@./${NAME}

runb:
			@make bonus
			@./${NAME}

lib_make:	${SRCSH}
			@printf $(CR)
			@make bonus -C libs/libft

clean:
			@make clean -C libs/libft
			@rm -rf ${OBJS} ${OBJSDIR}
			@echo ${RED}${NAME}" : Removing .o files" ${WHITE}

fclean:		clean
			@make bclean -C libs/libft
			@rm -f ${NAME}
			@echo ${RED}${NAME}" : Removing binary file" ${WHITE}

re:			fclean all

.PHONY:		all clean fclean re bonus run
