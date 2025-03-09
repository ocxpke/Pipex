/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:33:14 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/09 12:54:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_err(int argc, char **argv, int pos)
{
	int	fd_null;

	if (!(!is_here_doc(argv[1]) && (access(argv[1], R_OK) == -1) && (pos == 2))
		&& !((access(argv[argc - 1], W_OK) == -1) && (pos == argc - 2)))
	{
		errno = 2;
		perror("Command not found");
	}
	fd_null = open("/dev/null", O_RDONLY);
	if (!fd_null)
		return (exit(EXIT_FAILURE));
	dup2(fd_null, STDIN_FILENO);
	close(fd_null);
}
