# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 11:24:00 by mlavergn          #+#    #+#              #
#    Updated: 2025/04/05 15:56:57 by mlavergn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
DIR         = srcs/
GNL         = gnl/
CC          = gcc
FLAGS       = -Wall -Werror -Wextra
MLX         = libmlx.a
MFLAGS      = -L. $(MLX) -lXext -lX11 -lm -fsanitize=address -g
PARSER		= srcs/parser/
ERROR		= srcs/error/
SRCS =      $(GNL)get_next_line.c $(GNL)get_next_line_utils.c $(DIR)main.c\
			$(PARSER)getInfos.c  $(PARSER)utils.c $(ERROR)error.c
OBJS =      $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I$(GNL) -I$(DIR) -I$(DIR)parser -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(MFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
