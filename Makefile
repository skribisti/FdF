NAME = fdf
CC = cc
SRC = src/fdf.c \
	src/ft_check_args.c \
	src/ft_init_map.c \
	src/ft_split.c \
	src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c 
WALL = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(WALL) -I/usr/include -I./includes -Imlx_linux -Ift -O3 -g -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(WALL) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

dev :
	make fclean
	git add .; git commit -m "dev"; git push
	make all

PHONY: all clean fclean re dev