/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/02/15 18:14:46 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*concat_str_pipex(char *s1, char *s2)
{
	size_t	i;
	size_t	len_s1;
	size_t	tot_len;
	char	*ret;

	i = 0;
	len_s1 = ft_strlen(s1);
	tot_len = len_s1 + ft_strlen(s2);
	ret = (char *)ft_calloc(1, tot_len + 1);
	if (!ret)
		return (perror("Error with calloc at cc_str"), NULL);
	while (i < tot_len)
	{
		if (i < len_s1)
			ret[i] = s1[i];
		else
			ret[i] = s2[i - len_s1];
		i++;
	}
	free(s1);
	free(s2);
	return (ret);
}

char	*take_processs_output(int *fildes, char *prev_out, pid_t id)
{
	int		status;
	char	*readed;

	status = 0;
	waitpid(id, &status, 0);
	close(fildes[1]);
	readed = "a";
	while (readed)
	{
		readed = get_next_line(fildes[0]);
		if (readed)
			prev_out = concat_str_pipex(prev_out, readed);
		ft_printf("---> %s\n", prev_out);
	}
	close(fildes[0]);
	return (prev_out);
}

void	exec_process(int *fildes, char **args_exec)
{
	close(fildes[0]);
	ft_printf("exe -> %s\n", args_exec[0]);
	dup2(fildes[1], 1);
	execve(args_exec[0], args_exec, NULL);
	return (close(fildes[1]), perror("Error execve"), exit(EXIT_FAILURE));
}

char	*fork_and_exec(char **argv, char *prev_out)
{
	int		fildes[2];
	pid_t	id;

	if (pipe(fildes) == -1)
		return (perror("Error calling pipe"), NULL);
	id = fork();
	if (id == -1)
		return (perror("Error calling fork"), NULL);
	if (id == 0)
		exec_process(fildes, argv);
	else
		prev_out = take_processs_output(fildes, prev_out, id);
	ft_printf("Hola%s\n", prev_out);
	return (prev_out);
}

int	main(int argc, char **argv)
{
	int		command_cont;
	char	*to_write;
	char	**argv_exec;

	if (argc < 5)
		return (errno = 22, perror("Not enough arguments"), -1);
	command_cont = 2;
	to_write = (char *)ft_calloc(1, 1);
	if (!to_write)
		return (perror("Error with calloc at to write"), -1);
	while (command_cont < (argc - 1))
	{
		argv_exec = prepare_args_exec(argv[command_cont], argv[1], to_write,
				command_cont == 2);
		to_write = fork_and_exec(argv_exec, to_write);
		if (!to_write)
			return (perror("Error coming from main"), -1);
		command_cont++;
		free_back_splitted(argv_exec);
	}
}
