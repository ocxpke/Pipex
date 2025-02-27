/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/02/27 17:56:13 by jose-ara         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	int		exit_info;
	int		path_pos;
	char	*output;

	if (argc < 5)
		return (errno = 22, perror("Not enough arguments"), -1);
	path_pos = find_path_pos(env);
	redirect_file_in(argv[1]);
	exec_params(argc, argv, env[path_pos], &exit_info);
	output = read_output();
	write_output(output, argv[argc - 1]);
	free(output);
	if (exit_info == ENOENT)
		return (exit(127), -1);
	return (WEXITSTATUS(exit_info));
}
