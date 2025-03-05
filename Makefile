NAME = pipex.a

NAME_EXEC = pipex

LIBFT_LIB = ./libft/libft.a

Sources = pipex.c\
	manage_env.c\
	manage_process.c\
	manage_here_doc.c\
	manage_exec_params.c\
	manage_input_output.c

OBJ = $(Sources:.c=.o)

flags = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ) $(OBJGNL) $(OBJPTF)
	ar rcs $(NAME) $(OBJ) $(OBJGNL) $(OBJPTF)

%.o: %.c
	cc -c $< -o $@ $(flags)

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME) $(NAME_EXEC)

re: fclean $(NAME)

exec: $(OBJ)
	make -C ./libft
	cc $(flags) $(OBJ) $(LIBFT_LIB) -o $(NAME_EXEC)

test: exec
	./pipex in cat ls out

valgrind:
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./pipex "aaa" "cat -e" "cat -e" "cat -e" "wc" "outfile"

.PHONY: all clean fclean re
