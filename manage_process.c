/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:20:08 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/07 20:01:06 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_processs_output(int *fildes)
{
	close(fildes[1]);
	dup2(fildes[0], STDIN_FILENO);
	close(fildes[0]);
}

void	exec_process(int *fildes, char **args_exec)
{
	close(fildes[0]);
	dup2(fildes[1], STDOUT_FILENO);
	close(fildes[1]);
	execve(args_exec[0], args_exec, NULL);
	free_back_splitted(args_exec);
	return (perror("Error execve in child process"), exit(errno));
}

pid_t	fork_and_exec(char **argv)
{
	int		fildes[2];
	pid_t	id;

	if (pipe(fildes) == -1)
		return (perror("Error calling pipe"), exit(EXIT_FAILURE), -1);
	id = fork();
	if (id == -1)
		return (perror("Error calling fork"), exit(EXIT_FAILURE), -1);
	if (id == 0)
		exec_process(fildes, argv);
	else
		redirect_processs_output(fildes);
	return (id);
}

void	command_err(char *first_arg, int pos)
{
	int	fd_null;

	if (!((access(first_arg, R_OK) == -1) && pos == 2))
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
