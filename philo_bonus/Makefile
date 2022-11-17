# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2022/05/18 15:11:26 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME	    =	philo
SRCS        =   $(shell find . -type f -name '*.c' -not -name '*_bonus*')
OBJS		=	${SRCS:.c=.o}

SRCS_B		=	$(shell find . -type f -name '*_bonus.c')
OBJS_B		=	$(SRCS_B:.c=.o)

INCLUDES  	=	-I./
LIBS         :=  -lpthread

CC			=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -O3
RM			=	rm -f
ifdef MOREFLAGS
CFLAGS		:=	$(CFLAGS) $(MOREFLAGS)
endif

%.o: %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
				
all:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_B)
			
fclean:		clean
			$(RM) $(NAME)

re:			fclean all clean

bonus:		$(OBJS_B)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_B) $(LIBS) -o $(NAME)

.PHONY:		fclean all clean re start