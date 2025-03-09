/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:20:08 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/09 14:34:28 by jose-ara         ###   ########.fr       */
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

pid_t	fork_and_exec(char **args_exec)
{
	int		fildes[2];
	pid_t	id;

	if (pipe(fildes) == -1)
		return (perror("Error calling pipe"), exit(EXIT_FAILURE), -1);
	id = fork();
	if (id == -1)
		return (perror("Error calling fork"), exit(EXIT_FAILURE), -1);
	if (id == 0)
		exec_process(fildes, args_exec);
	else
		redirect_processs_output(fildes);
	return (id);
}
