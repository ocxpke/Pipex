/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:20:08 by jose-ara          #+#    #+#             */
/*   Updated: 2025/02/27 12:58:57 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_processs_output(int *fildes, pid_t id, int *status)
{
	if (waitpid(id, status, 0) == -1)
		return (perror("Error waiting for child process"), exit(EXIT_FAILURE));
	close(fildes[1]);
	dup2(fildes[0], 0);
	close(fildes[0]);
}

void	exec_process(int *fildes, char **args_exec)
{
	close(fildes[0]);
	dup2(fildes[1], 1);
	close(fildes[1]);
	execve(args_exec[0], args_exec, NULL);
	free_back_splitted(args_exec);
	return (perror("Error execve in child process"), exit(errno));
}

void	fork_and_exec(char **argv, int *status)
{
	int		fildes[2];
	pid_t	id;

	if (!argv)
		return ;
	if (pipe(fildes) == -1)
		return (perror("Error calling pipe"));
	id = fork();
	if (id == -1)
		return (perror("Error calling fork"));
	if (id == 0)
		exec_process(fildes, argv);
	else
		redirect_processs_output(fildes, id, status);
}
