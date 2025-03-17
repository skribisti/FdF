SRC = src/ft_is/ft_isalnum.c src/ft_is/ft_isalpha.c src/ft_is/ft_isascii.c src/ft_is/ft_isdigit.c src/ft_is/ft_isprint.c \
	src/ft_mem/ft_bzero.c src/ft_mem/ft_calloc.c src/ft_mem/ft_memchr.c src/ft_mem/ft_memmove.c src/ft_mem/ft_memcmp.c \
	src/ft_mem/ft_memset.c src/ft_mem/ft_memcpy.c \
	src/ft_put/ft_putchar_fd.c  src/ft_put/ft_putendl_fd.c src/ft_put/ft_putnbr_fd.c src/ft_put/ft_putstr_fd.c\
	src/ft_to/ft_tolower.c src/ft_to/ft_toupper.c  src/ft_to/ft_itoa.c src/ft_to/ft_atoi.c\
	src/ft_str/ft_strmapi.c src/ft_str/ft_strncmp.c src/ft_str/ft_strncpy.c src/ft_str/ft_strnstr.c \
	src/ft_str/ft_split.c src/ft_str/ft_strrchr.c src/ft_str/ft_strchr.c   src/ft_str/ft_strtrim.c \
	src/ft_str/ft_strdup.c   src/ft_str/ft_substr.c src/ft_str/ft_striteri.c src/ft_str/ft_strjoin.c \
	src/ft_str/ft_strlcat.c src/ft_str/ft_strlcpy.c src/ft_str/ft_strlen.c\
	src/ft_lst/ft_lstclear_bonus.c src/ft_lst/ft_lstdelone_bonus.c src/ft_lst/ft_lstiter_bonus.c\
	src/ft_lst/ft_lstlast_bonus.c src/ft_lst/ft_lstmap_bonus.c src/ft_lst/ft_lstnew_bonus.c \
	src/ft_lst/ft_lstsize_bonus.c src/ft_lst/ft_lstadd_front_bonus.c src/ft_lst/ft_lstadd_back_bonus.c\
	src/gnl/get_next_line.c src/gnl/get_next_line_utils.c \
	src/ft_printf/ft_printf.c src/ft_printf/ft_print_bx.c  src/ft_printf/ft_print_d.c src/ft_printf/ft_print_p.c \
	src/ft_printf/ft_print_u.c  src/ft_printf/ft_putnbr_base.c src/ft_printf/ft_strlen.c src/ft_printf/ft_print_c.c \
	src/ft_printf/ft_print_s.c  src/ft_printf/ft_print_x.c src/ft_printf/ft_size.c

NAME = libft.a
OBJ = ${SRC:.c=.o}
FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean :
	@rm -rf obj

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 