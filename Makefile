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

NAME	    =	philosophers
SRCS        =   $(shell find ./ -type f -name '*.c')
OBJS		=	${SRCS:.c=.o}

#Linux
# INCLUDES  	=	-I./** -I./mlx_engine/includes -I./mlx_engine/libft -I/usr/include -I./mlx_engine/mlx_linux -I/usr/include/freetype2
INCLUDES  	=	-I./
LIBS         :=  -lpthread
#Mac
#INCLUDES   :=  -I./includes -I./libft -I/usr/local/include
#MLX        :=  -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
#INCLUDES	:=	-I./mlx_engine/includes -I./mlx_engine/libft

CC			=	gcc
#CFLAGS		:=	-Wall -Wextra -Werror -O3
CFLAGS		:=	-O0 -g
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

.PHONY:		fclean all clean re start