/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:44:29 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/07 20:00:37 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_path_pos(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			return (i);
		i++;
	}
	return (-1);
}

char	*find_command_exec(char *command, char *env)
{
	char	**env_splitted;
	char	*check_exec;
	int		i;
	int		size_sp;

	//Arreglar
	if (!access(command, X_OK))
		return (ft_strdup(" "));
	env_splitted = ft_split(&env[5], ':');
	if (!env_splitted)
		return (NULL);
	size_sp = take_split_len(env_splitted);
	i = 0;
	while (i < size_sp)
	{
		check_exec = init_command(command, env_splitted[i]);
		if (!access(check_exec, X_OK))
			return (free_back_splitted(env_splitted), check_exec);
		free(check_exec);
		i++;
	}
	free_back_splitted(env_splitted);
	return (NULL);
}
