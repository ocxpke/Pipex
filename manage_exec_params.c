/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exec_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:04:32 by jose-ara          #+#    #+#             */
/*   Updated: 2025/02/15 17:00:19 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	take_split_len(char **splitted)
{
	size_t	cont;

	if (!splitted)
		return (0);
	cont = 0;
	while (splitted[cont])
		cont++;
	return (cont);
}

char	*init_command(char *command)
{
	char	*ret;
	size_t	len;
	size_t	command_len;

	command_len = ft_strlen(command);
	len = 5 + command_len + 1;
	ret = (char *)ft_calloc(1, len);
	if (!ret)
		return (perror("Error with calloc at init command"), NULL);
	ft_strlcat(ret, "/bin/", 6);
	ft_strlcat(ret, command, command_len + ft_strlen(ret) + 1);
	return (ret);
}

char	**prepare_args_exec(char *command, char *file_in, char *exec_out,
		int first)
{
	char	**ret;
	char	**splitted;
	size_t	i;
	size_t	split_len;

	splitted = ft_split(command, ' ');
	split_len = take_split_len(splitted);
	if (!splitted)
		return (perror("Error at split"), NULL);
	ret = (char **)ft_calloc(split_len + 1 + 1, sizeof(char *));
	if (!ret)
		return (perror("Error with calloc for args_exec"), NULL);
	ret[0] = init_command(splitted[0]);
	i = 1;
	while (i < split_len)
	{
		ret[i] = ft_strdup(splitted[i]);
		i++;
	}
	if (first)
		ret[i] = ft_strdup(file_in);
	else
		ret[i] = ft_strdup(exec_out);
	free_back_splitted(splitted);
	return (ret);
}
