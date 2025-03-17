NAME = fdf
SRC = src/main.c \
	src/ft_check_args.c \
	src/ft_init_map.c \
	src/ft_init_fdf_and_img.c \
	src/ft_offset.c \
	src/ft_split.c \
	src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c \
	src/draw.c src/hook.c
WALL = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(WALL) -I/usr/include -I./includes -Imlx_linux -Ilibft/includes -O3 -g -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	@cc $(WALL) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Llibft -lft -o $(NAME)

clean:
	rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

dev :
	make fclean
	git add .; git commit -m "dev"; git push

PHONY: all clean fclean re dev