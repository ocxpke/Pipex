/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:02:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/02 18:03:52 by jose-ara         ###   ########.fr       */
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
pid_t	exec_params(int argc, char **argv, char *env_path, int *exit_status);

char	*concat_str_pipex(char *s1, char *s2);

void	write_output(char *str, char *file_out);
char	*read_output(void);
void	redirect_file_in(char *file_in);

pid_t	fork_and_exec(char **argv);
void	exec_process(int *fildes, char **args_exec);
void	redirect_processs_output(int *fildes);
void	command_err(int *exit_status);

int		find_path_pos(char **env);
char	*find_command_exec(char *command, char *env);

#endif
