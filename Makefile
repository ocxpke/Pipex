NAME = pipex.a

NAME_EXEC = pipex

LIBFT_LIB = ./libft/libft.a

Sources = pipex.c\
	manage_exec_params.c

OBJ = $(Sources:.c=.o)

flags = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(OBJGNL) $(OBJPTF)
	ar rcs $(NAME) $(OBJ) $(OBJGNL) $(OBJPTF)

%.o: %.c
	cc -c $< -o $@ $(flags)

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(NAME_EXEC)

re: fclean $(NAME)

exec: $(OBJ)
	make -C ./libft
	cc $(flags) $(OBJ) $(LIBFT_LIB) -o $(NAME_EXEC)

.PHONY: all clean fclean re exec
