/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:02:10 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/02 14:52:21 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_output(void)
{
	char	*out;
	char	*readed;

	out = ft_calloc(1, 1);
	if (!out)
		return (perror("Error with calloc -> out"), NULL);
	readed = "a";
	while (readed)
	{
		readed = get_next_line(0);
		if (readed)
			out = concat_str_pipex(out, readed);
	}
	return (out);
}

void	write_output(char *str, char *file_out)
{
	int	fd;

	fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(str), exit(EXIT_FAILURE));
	write(fd, str, ft_strlen(str));
	close(fd);
}

void	redirect_file_in(char *file_in)
{
	int	fd_in;

	fd_in = open(file_in, O_RDONLY);
	if (fd_in == -1)
		fd_in = open("/dev/null", O_RDONLY);
	dup2(fd_in, 0);
	close(fd_in);
}
