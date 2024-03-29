# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 14:22:44 by saaltone          #+#    #+#              #
#    Updated: 2022/05/12 11:58:39 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol
COMP_FLAGS=-Wall -Wextra -Werror -O3
LIBFT=./libft
LIBFT_INCLUDES=./libft/includes
LIBMLX=./libmlx
LIBMLX_INCLUDES=./libmlx
SOURCES_FILES=main.c error.c conf.c app.c events_key.c events_loop.c \
				events_mouse.c graphics.c image.c parser.c colors.c \
				iteration_burning_ship.c iteration_julia.c \
				iteration_mandelbrot.c iteration_newton_chains.c \
				iteration_newton_blackhole.c gallery_load.c gallery_display.c \
				gallery_mouse.c gallery_update.c
SOURCES=$(SOURCES_FILES:%.c=srcs/%.c)
OBJECTS=$(SOURCES:.c=.o)
INCLUDES=./includes

$(NAME):
	make -C $(LIBFT)
	make -C $(LIBMLX)
	gcc $(COMP_FLAGS) $(SOURCES) -o $(NAME) \
	-I $(INCLUDES) \
	-I $(LIBFT_INCLUDES) \
	-I $(LIBMLX_INCLUDES) \
	-L $(LIBFT) \
	-L $(LIBMLX) \
	-lft -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

clean:
	/bin/rm -f $(OBJECTS)
	make -C $(LIBFT) clean
	make -C $(LIBMLX) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

comp:
	gcc $(COMP_FLAGS) $(SOURCES) -o $(NAME) \
	-I $(INCLUDES) \
	-I $(LIBFT_INCLUDES) \
	-I $(LIBMLX_INCLUDES) \
	-L $(LIBFT) \
	-L $(LIBMLX) \
	-lft -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re comp
