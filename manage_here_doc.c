/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:13:06 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/09 15:06:05 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char *str)
{
	if (!str || (ft_strlen(str) != 8) || ft_strncmp("here_doc", str, 8))
		return (0);
	return (1);
}

void	manage_readed_here_doc(char **ptr, char **gnl, int *end, char *limiter)
{
	if (*gnl)
	{
		if (((ft_strlen(*gnl) == (ft_strlen(limiter) + 1))
				&& !ft_strncmp(limiter, *gnl, ft_strlen(limiter))))
			*end = 1;
		else
			*ptr = concat_str_pipex(*ptr, *gnl);
	}
	if (*end == 1)
		free(*gnl);
}

char	*text_here_doc(char *limiter)
{
	char	*ptr;
	char	*gnl;
	int		end;

	ptr = (char *)ft_calloc(1, 1);
	if (!ptr)
		return (perror("Error at init here_doc"), NULL);
	gnl = "a";
	end = 0;
	while (gnl && !end)
	{
		ft_printf("here_doc> ");
		gnl = get_next_line(STDIN_FILENO);
		manage_readed_here_doc(&ptr, &gnl, &end, limiter);
	}
	if (end != 1)
		return (free(ptr), free(gnl), exit(EXIT_FAILURE), NULL);
	return (ptr);
}

void	file_here_doc(char *text)
{
	int	here_doc;

	here_doc = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (here_doc == -1)
		return (free(text), perror("New here_doc"), exit(EXIT_FAILURE));
	write(here_doc, text, ft_strlen(text));
	close(here_doc);
}
