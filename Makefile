NAME = pipex.a

NAME_EXEC = pipex

LIBFT_LIB = ./libft/libft.a

Sources = pipex.c\
	manage_env.c\
	manage_wait.c\
	manage_errors.c\
	manage_process.c\
	manage_here_doc.c\
	manage_exec_params.c\
	manage_input_output.c

OBJ = $(Sources:.c=.o)

flags = -Wall -Wextra -Werror -g

all: $(OBJ)
	make -C ./libft
	cc $(flags) $(OBJ) $(LIBFT_LIB) -o $(NAME_EXEC)

%.o: %.c
	cc -c $< -o $@ $(flags)

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME_EXEC)

re: fclean all

test: all
	./pipex in cat ls out

valgrind: all
	valgrind -s --leak-check=full --trace-children=yes --track-fds=yes ./pipex "aaa" "cat -e" "cat -e" "cat -e" "wc" "outfile"

.PHONY: all clean fclean re
