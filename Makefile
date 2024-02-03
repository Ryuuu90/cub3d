NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -O3 -Ofast -fsanitize=address -g3

SRCS = 	./src/cub3d.c\
		./src/readfile.c\
		./src/utils.c\
		./src/maparse.c\
		./src/parse_colors.c\
		./src/parse_textures.c\
		./get_next_line/get_next_line.c\
		./get_next_line/get_next_line_utils.c\
		./src/InitGame.c\


CC = cc

all: $(NAME)

$(NAME):$(SRCS)
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) ./libft/libft.a -lmlx -lXext -lX11 -lm -lmcheck -o $(NAME)

clean:
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re:	fclean all

.PHONY:	all clean fclean re