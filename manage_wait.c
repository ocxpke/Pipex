/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:08:46 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/07 14:30:21 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	add_node_group_id(t_waitpid **group_id, pid_t id)
{
	t_waitpid	*new_node;
	t_waitpid	*iter;

	new_node = (t_waitpid *)ft_calloc(1, sizeof(t_waitpid));
	if (!new_node)
		return (-1);
	new_node->process_id = id;
	new_node->next_process = NULL;
	if (!(*group_id))
		*group_id = new_node;
	else
	{
		iter = *group_id;
		while (iter->next_process)
			iter = iter->next_process;
		iter->next_process = new_node;
	}
	return (0);
}

void	wait_all_proccess(t_waitpid *group_id, int *exit_status)
{
	t_waitpid	*iter;

	iter = group_id;
	while (iter)
	{
		if (waitpid(iter->process_id, exit_status, 0) == -1)
			return (perror("Error waiting process"), exit(EXIT_FAILURE));
		iter = iter->next_process;
	}
}

void	free_waitpid_list(t_waitpid **group_id)
{
	t_waitpid	*to_free;

	while (*group_id)
	{
		to_free = *group_id;
		*group_id = (*group_id)->next_process;
		free(to_free);
	}
	*group_id = NULL;
}
