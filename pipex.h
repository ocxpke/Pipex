/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:02:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/07 18:37:49 by jose-ara         ###   ########.fr       */
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

typedef struct s_waitpid
{
	pid_t				process_id;
	int					exit_status;
	struct s_waitpid	*next_process;
}						t_waitpid;

size_t					take_split_len(char **splitted);
char					*init_command(char *command, char *path);
char					**prepare_args_exec(char *command, char *command_path);
void					exec_params(int argc, char **argv, char *env_path,
							t_waitpid **group_id);

char					*concat_str_pipex(char *s1, char *s2);

void					write_output(int argc, char **argv, char **str);
void					read_output(char **str);
void					redirect_file_in(char **argv);
int						is_here_doc(char *str);

pid_t					fork_and_exec(char **argv);
void					exec_process(int *fildes, char **args_exec);
void					redirect_processs_output(int *fildes);
void					command_err(char *first_arg, int pos);

int						find_path_pos(char **env);
char					*find_command_exec(char *command, char *env);

char					*text_here_doc(char *limiter);
void					manage_readed_here_doc(char **ptr, char **gnl, int *end,
							char *limiter);
int						is_here_doc(char *str);
void					file_here_doc(char *text);

int						add_node_group_id(t_waitpid **group_id, pid_t id);
void					wait_all_proccess(t_waitpid *group_id,
							int *exit_status);
void					free_waitpid_list(t_waitpid **group_id);
int						check_last_process(char *command, char *env);

#endif
