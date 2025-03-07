/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/07 14:38:05 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_last_process(char *command, char *env)
{
	char	**args_exec;

	args_exec = prepare_args_exec(command, env);
	if (!args_exec)
		return (-1);
	free_back_splitted(args_exec);
	return (0);
}

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
	int			exit_status;
	int			path_pos;
	char		*output;
	t_waitpid	*group_id;

	if (argc < 5)
		return (errno = 22, perror("Not enough arguments"), -1);
	group_id = NULL;
	path_pos = find_path_pos(env);
	redirect_file_in(argv);
	exec_params(argc, argv, env[path_pos], &group_id);
	wait_all_proccess(group_id, &exit_status);
	free_waitpid_list(&group_id);
	read_output(&output);
	write_output(argc, argv, &output);
	if (check_last_process(argv[argc - 2], env[path_pos]) == -1)
		return (exit(127), -1);
	return (WEXITSTATUS(exit_status));
}
