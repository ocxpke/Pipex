/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:02:10 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/07 18:54:27 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_output(char **str)
{
	char	*out;
	char	*readed;

	out = ft_calloc(1, 1);
	if (!out)
		return (perror("Error with calloc -> out"), exit(EXIT_FAILURE));
	readed = "a";
	while (readed)
	{
		readed = get_next_line(0);
		if (readed)
			out = concat_str_pipex(out, readed);
	}
	*str = out;
}

void	write_output(int argc, char **argv, char **str)
{
	int	fd;

	if (is_here_doc(argv[1]))
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (free(*str), perror("Error opening fout"), exit(EXIT_FAILURE));
	write(fd, *str, ft_strlen(*str));
	free(*str);
	*str = NULL;
	close(fd);
	if (is_here_doc(argv[1]))
		unlink("here_doc");
}

void	redirect_file_in(char **argv)
{
	int		fd_in;
	char	*text_readed;

	if (is_here_doc(argv[1]))
	{
		text_readed = text_here_doc(argv[2]);
		if (!text_readed)
			return (perror("Error reading here_doc"), exit(EXIT_FAILURE));
		file_here_doc(text_readed);
		free(text_readed);
		fd_in = open("here_doc", O_RDONLY);
	}
	else
		fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		if (errno == 0)
			errno = 2;
		perror("Error with infile");
		fd_in = open("/dev/null", O_RDONLY);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}
