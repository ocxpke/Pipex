/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:02:22 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/09 15:18:15 by jose-ara         ###   ########.fr       */
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

/**
 * @brief Structure that will contain all the process id's
 */
typedef struct s_waitpid
{
	pid_t				process_id;
	struct s_waitpid	*next_process;
}						t_waitpid;

/**		_____________________________
 *		|							|
 *		|	PIPEX.C FILE			|
 *		|___________________________|
 */
/**
 * @brief Concats 2 allocated strings, then frees both of them
 *
 * @param s1 First string, the first part of the new string
 * @param s1 Second string, the second part of the new string
 * @return The new string allocated, or NULL
 */
char					*concat_str_pipex(char *s1, char *s2);

/**		________________________________
 *		|								|
 *		|	MANAGE_EXEC_PARAMS.C FILE	|
 *		|_______________________________|
 */
/**
 * @brief Return the lenght of the splitted struct
 *
 * @param splitted The splitted struct
 * @return The size of the struct or 0 if something went wrong
 */
size_t					take_split_len(char **splitted);
/**
 * @brief Creates the command to be executed, only the command without params,
 *  this is donde for checking if it's executable
 *
 * @param command The name of the executable
 * @param path A substring of PATH enviroment
 * @return The new string concatenated or NULL if something went wrong
 */
char					*init_command(char *command, char *path);
/**
 * @brief Concats 2 allocated strings, then frees both of them
 *
 * @param commmand All the componets of the command passed by the user
 * @param env_path The enviroment path of the executable
 * @return A splitted struct with the main command and params passed,
 * or NULL if something went wrong
 */
char					**prepare_args_exec(char *command, char *env_path);
/**
 * @brief The script of this projects, roams all args passed by the user.
 * Then checks if it's executable, if it's calls fork_and_exec.
 * If it's not calls err and prints the errors associated with it.
 *
 * @param argc The total arguments of the program
 * @param argv All program's arguments
 * @param env_path All the envirometn PATH of the system
 * @param group_id Linked list that will store the id's of the proccess exec.
 */
void					exec_params(int argc, char **argv, char *env_path,
							t_waitpid **group_id);

/**		________________________________
 *		|								|
 *		|	MANAGE_INPUT_OUTPUT.C FILE	|
 *		|_______________________________|
 */
/**
 * @brief Redirects the file in selected by the user,
 * o makes the script for the here_doc file.
 * In case of error redirects /dev/null to the STDIN_FILENO
 *
 * @param argv All argumets passed by the user
 */
void					redirect_file_in(char **argv);
/**
 * @brief Reads all characters, with get_next_line, from the previous command
 *
 * @param str The pointer where we will save all information
 */
void					read_output(char **str);
/**
 * @brief Writes the final output to a file. It can be the norma output '>',
 * or the append output '>>'.
 * Also delete the here_doc tmp file if it has been created.
 *
 * @param argc The total number of arguments passed by the user
 * @param argv All argumets passed by the user
 * @param str All characters readed from the last command executed
 */
void					write_output(int argc, char **argv, char **str);

/**		________________________________
 *		|								|
 *		|	MANAGE_PROCESS.C FILE		|
 *		|_______________________________|
 */
/**
 * @brief The main function of the program.
 * Creates the pipes and fork the program.
 * In child process executes the command passed, in parent process
 * redirects the output of child.
 *
 * @param args_exec A splitted structure with the command and
 * arguments to execute
 * @return The pid_t of the process forked.
 */
pid_t					fork_and_exec(char **args_exec);
/**
 * @brief Child proccess script, just close pipes unused,
 * redirects the output, and execute the commnad.
 *
 * @param fildes The files descriptor of the pipes
 * @param args_exec A splitted structure with the command and
 * arguments to execute
 */
void					exec_process(int *fildes, char **args_exec);
/**
 * @brief Parent proccess script, just close pipes unused,
 * and redirects the output.
 *
 * @param fildes The files descriptor of the pipes.
 */
void					redirect_processs_output(int *fildes);

/**		________________________________
 *		|								|
 *		|	MANAGE_ENV.C FILE			|
 *		|_______________________________|
 */
/**
 * @brief Finds the path position inside enviroment.
 *
 * @param env The enviroment variables of the system.
 * @return The position of the path or -1 if something went wrong.
 */
int						find_path_pos(char **env);
/**
 * @brief Checks where the command is executable inside path.
 *
 * @param command Command to be executed.
 * @param env The enviroment variables of the system.
 * @return The position of the path where command is executable or
 * NULL if the command is not executable
 */
char					*find_command_exec(char *command, char *env);

/**		________________________________
 *		|								|
 *		|	MANAGE_HERE_DOC.C FILE		|
 *		|_______________________________|
 */
/**
 * @brief Checks if the user has called here_doc to write a document
 *
 * @param str The first argument that checks if we called here_doc
 * @return 1 if it's here_doc; 0 if it's not
 */
int						is_here_doc(char *str);
/**
 * @brief Reads from user input.
 *
 * @param limiter The final string to be readed.
 * @return All readed characters from user, or NULL if something went wrong.
 */
char					*text_here_doc(char *limiter);
/**
 * @brief Here we manage the readed information from get_next_line.
 * We concat ptr with gnl and check if user entered the limiter command
 *
 * @param ptr The total charcaters readed from input
 * @param gnl String readed with get_next_line.
 * @param end Indicates if the user entered the limiter string
 * @param limiter The final string to be readed.
 */
void					manage_readed_here_doc(char **ptr, char **gnl, int *end,
							char *limiter);
/**
 * @brief Creates the here_doc tmp file and
 * writes the information readed from user.
 *
 * @param text All characters readed from user.
 */
void					file_here_doc(char *text);

/**		________________________________
 *		|								|
 *		|	MANAGE_WAIT.C FILE			|
 *		|_______________________________|
 */
/**
 * @brief Initialise the structre or adds a new node at the end of the list.
 *
 * @param group_id The poiter of the head of the list.
 * @param id The id that will be added to the list.
 * @return 0 if we added correctly the process id; -1 if something went wrong
 */
int						add_node_group_id(t_waitpid **group_id, pid_t id);
/**
 * @brief Waits for all the called process to end.
 *
 * @param group_id The poiter of the head of the list.
 * @param exit_status The exit status of the last process that will be evaluated
 */
void					wait_all_proccess(t_waitpid *group_id,
							int *exit_status);
/**
 * @brief Frees all the process id's list.
 *
 * @param group_id The poiter of the head of the list.
 */
void					free_waitpid_list(t_waitpid **group_id);

/**		________________________________
 *		|								|
 *		|	MANAGE_ERRORS.C FILE		|
 *		|_______________________________|
 */
/**
 * @brief Prints the command errors when command or
 * when file_in or file_out are accesible
 *
 * @param argc Total amount of params.
 * @param argv All params passed by the user.
 * @param pos Position of command executed.
 */
void					command_err(int argc, char **argv, int pos);

#endif
