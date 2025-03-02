/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exec_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:04:32 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/02 18:09:43 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	take_split_len(char **splitted)
{
	size_t	cont;

	if (!splitted || !(*splitted))
		return (0);
	cont = 0;
	while (splitted[cont])
		cont++;
	return (cont);
}

char	*init_command(char *command, char *path)
{
	char	*ret;
	size_t	len;
	size_t	command_len;
	size_t	path_len;

	path_len = ft_strlen(path);
	command_len = ft_strlen(command);
	len = path_len + command_len + 1 + 1;
	ret = (char *)ft_calloc(1, len);
	if (!ret)
		return (perror("Error with calloc at init command"), NULL);
	ft_strlcat(ret, path, path_len + 1);
	ft_strlcat(ret, "/", path_len + 2);
	ft_strlcat(ret, command, command_len + ft_strlen(ret) + 1);
	return (ret);
}

char	**concat_splitted_command(size_t split_len, char **ret, char **splitted,
		char *command_path)
{
	size_t	i;

	ret[0] = command_path;
	i = 1;
	while (i < split_len)
	{
		ret[i] = ft_strdup(splitted[i]);
		i++;
	}
	free_back_splitted(splitted);
	return (ret);
}

char	**prepare_args_exec(char *command, char *env_path)
{
	char	**ret;
	char	**comm_sp;
	char	*com_path;
	size_t	split_len;

	if (ft_strlen(command) == 0 || !env_path)
		return (NULL);
	comm_sp = ft_split(command, ' ');
	if (!comm_sp)
		return (perror("Error at split"), NULL);
	split_len = take_split_len(comm_sp);
	com_path = find_command_exec(comm_sp[0], env_path);
	if (!com_path)
		return (free_back_splitted(comm_sp), perror("Com doesn't exist"), NULL);
	ret = (char **)ft_calloc(split_len + 1, sizeof(char *));
	if (!ret)
		return (perror("Error with calloc for args_exec"), NULL);
	return (concat_splitted_command(split_len, ret, comm_sp, com_path));
}

pid_t	exec_params(int argc, char **argv, char *env_path, int *exit_status)
{
	int		i;
	pid_t	id;
	char	**args_exec;

	i = 2;
	while (i < (argc - 1))
	{
		args_exec = prepare_args_exec(argv[i], env_path);
		if (args_exec)
		{
			id = fork_and_exec(args_exec);
			free_back_splitted(args_exec);
		}
		else
			command_err(exit_status);
		i++;
	}
	return (id);
}
