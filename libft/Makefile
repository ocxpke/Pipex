NAME = libft.a

SourcesGNL = get_next_line/get_next_line_utils.c\
	get_next_line/get_next_line.c\

SourcesPrintf = printf/ft_hexadecimal.c\
	printf/ft_list_manager.c\
	printf/ft_printf_func.c\
	printf/ft_printf.c\
	printf/ft_uitoa.c

Sources = ft_isdigit.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_calloc.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_strlen.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strncmp.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c

OBJ = $(Sources:.c=.o)

OBJGNL = $(SourcesGNL:.c=.o)

OBJPTF = $(SourcesPrintf:.c=.o)

flags = -Wall -Wextra -Werror

all:$(NAME)
$(NAME): $(OBJ) $(OBJGNL) $(OBJPTF)
	ar rcs $(NAME) $(OBJ) $(OBJGNL) $(OBJPTF)

%.o: %.c
	cc -c $< -o $@ $(flags)

get_next_line/%.o: get_next_line/%.c
	cc -c $< -o $@ $(flags)

printf/%.o: printf/%.c
	cc -c $< -o $@ $(flags)

clean:
	rm -f $(OBJ)
	rm -f $(OBJGNL)
	rm -f $(OBJPTF)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
