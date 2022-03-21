# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 14:22:44 by saaltone          #+#    #+#              #
#    Updated: 2022/03/21 14:40:01 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol
LIBFT=./libft
LIBFT_INCLUDES=./libft/includes
LIBMLX=./libmlx
LIBMLX_INCLUDES=./libmlx
SOURCES_FILES=main.c error.c conf.c app.c events.c graphics.c image.c \
				iteration.c
SOURCES=$(SOURCES_FILES:%.c=srcs/%.c)
OBJECTS=$(SOURCES:.c=.o)
INCLUDES=./includes

$(NAME):
	make -C $(LIBFT)
	make -C $(LIBMLX)
	gcc -Wall -Wextra -Werror $(SOURCES) -o $(NAME) \
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
	gcc -Wall -Wextra -Werror $(SOURCES) -o $(NAME) \
	-I $(INCLUDES) \
	-I $(LIBFT_INCLUDES) \
	-I $(LIBMLX_INCLUDES) \
	-L $(LIBFT) \
	-L $(LIBMLX) \
	-lft -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re comp
