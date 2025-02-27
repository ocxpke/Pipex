/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:02:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/02/27 17:56:19 by jose-ara         ###   ########.fr       */
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

size_t	take_split_len(char **splitted);
char	*init_command(char *command, char *path);
char	**prepare_args_exec(char *command, char *command_path);
void	exec_params(int argc, char **argv, char *env_path, int *exit_status);

char	*concat_str_pipex(char *s1, char *s2);

void	write_output(char *str, char *file_out);
void	redirect_file_in(char *file_in);
char	*read_output(void);

void	fork_and_exec(char **argv, int *status);
void	exec_process(int *fildes, char **args_exec);
void	redirect_processs_output(int *fildes, pid_t id, int *status);

int		find_path_pos(char **env);
char	*find_command_exec(char *command, char *env);

#endif
