# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchotel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 14:37:57 by jchotel           #+#    #+#              #
#    Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =  ./mem/ft_memset.c \
		./mem/ft_bzero.c \
		./mem/ft_memcpy.c \
		./mem/ft_memccpy.c \
		./mem/ft_memmove.c \
		./mem/ft_memchr.c \
		./mem/ft_memcmp.c \
		./mem/ft_calloc.c \
		./str/ft_atoi.c \
		./str/ft_strlen.c \
		./str/ft_islower.c \
		./str/ft_isupper.c \
		./str/ft_putchar.c \
		./str/ft_putstr.c \
		./str/ft_isalpha.c \
		./str/ft_isdigit.c \
		./str/ft_isalnum.c \
		./str/ft_isascii.c \
		./str/ft_isprint.c \
		./str/ft_toupper.c \
		./str/ft_tolower.c \
		./str/ft_strcount.c \
		./str/ft_strchr.c \
		./str/ft_strrchr.c \
		./str/ft_strncmp.c \
		./str/ft_strcmp.c \
		./str/ft_strlcpy.c \
		./str/ft_strlcat.c \
		./str/ft_strnstr.c \
		./str/ft_strdup.c \
		./str/ft_substr.c \
		./str/ft_strjoin.c \
		./str/ft_strtrim.c \
		./str/ft_split.c \
		./str/ft_itoa.c \
		./str/ft_strmapi.c \
		./str/ft_putchar_fd.c \
		./str/ft_putstr_fd.c \
		./str/ft_putendl_fd.c \
		./str/ft_putnbr.c \
		./str/ft_putnbr_fd.c
SRCS_B = ./lst/ft_lstnew.c \
		./lst/ft_lstadd_front.c \
		./lst/ft_lstsize.c \
		./lst/ft_lstlast.c \
		./lst/ft_lstadd_back.c\
		./lst/ft_lstdelone.c \
		./lst/ft_lstclear.c \
		./lst/ft_lstiter.c \
		./lst/ft_lst_print.c \
		./lst/ft_lstmap.c \
		./lst/ft_lstcrea.c \
		./lst/ft_ato_lst.c
OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}
FLAGS = -Wall -Wextra -Werror

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
all: ${NAME}


.c.o: ${OBJS} ${OBJS_B}
	@printf $(CR)"[FILE : %s]" $@
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@echo ${GREEN}${CR}"Libft : Making libft\033[0;0m"

bonus: ${OBJS_B} ${OBJS}
	@ar rc ${NAME} ${OBJS_B} ${OBJS}
	@echo ${GREEN}${CR}"Libft : Making libft w/ bonus\033[0;0m"

clean:
	@rm -f ${OBJS} ${OBJS_B}
	@echo ${RED}${CR}"Libft : Removing .o files\033[0;0m"

bclean:
	@rm -f ${NAME}
	@echo ${RED}${CR}"Libft : Removing binary file\033[0;0m"

fclean: clean
	@rm -f ${NAME}
	@echo ${RED}${CR}"Libft : Removing binary file\033[0;0m"

re: fclean all
