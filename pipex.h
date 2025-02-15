/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:02:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/02/15 16:48:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <aio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

char	**prepare_args_exec(char *command, char *file_in, char *exec_out,
			int first);

#endif
