/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:39:25 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/02/13 23:02:51 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* # of pipes = argc - 4 (file_name + infile + last cmd + outfile) */

#include "pipex_bonus.h"

/**
 * @brief	Handles the first child process.
 * @param	char			*argv[] : ptr to each argument passed by the user.
 * @param	char			*envp[] : pointer to environmental variables.
 * @param	struct s_pipex	*pipex : a structure holding internal variables.
 * @return	the result of the first command execution. 
 */
int	first_child(char *argv[], char *envp[], struct s_pipex *pipex,
				int **pipe_fd)
{
	(*pipex).input_fd = open(argv[1], O_RDONLY);
	if ((*pipex).input_fd == -1)
	{
		write(2, ERR_INFILE, ft_strlen(ERR_INFILE));
		return (EXIT_FAILURE);
	}
	if (dup2((*pipex).input_fd, STDIN_FILENO) == -1)
		exit_pipe();
	close((*pipex).input_fd);
	if (dup2(pipe_fd[(*pipex).fork_counter][1], STDOUT_FILENO) == -1)
		exit_pipe();
	close_pipe(pipex, pipe_fd);
	return (execute_function(argv[2], envp));
}

/**
 * @brief	Handles the last child process.
 * @param	char			*argv[] : ptr to each argument passed by the user.
 * @param	char			*envp[] : pointer to environmental variables.
 * @param	struct s_pipex	*pipex : a structure holding internal variables.
 * @return	the result of the last command execution to outfile. 
 */
int	last_child(char *argv[], char *envp[], struct s_pipex *pipex, int **pipe_fd)
{
	(*pipex).output_fd = open(argv[(*pipex).arg_counter - 1],
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((*pipex).output_fd == -1)
	{
		write(2, ERR_OUTFILE, ft_strlen(ERR_OUTFILE));
		return (EXIT_FAILURE);
	}
	if (dup2((*pipex).output_fd, STDOUT_FILENO) == -1)
		exit_pipe();
	close((*pipex).output_fd);
	if (dup2(pipe_fd[(*pipex).fork_counter - 1][0], STDIN_FILENO) == -1)
		exit_pipe();
	close_pipe(pipex, pipe_fd);
	return (execute_function(argv[(*pipex).arg_counter - 2], envp));
}

/**
 * @brief	Takes arguments from 'fork_master' function, creates a fork and  
 * 			passes inputs to respective child function, or handles it locally.
 * @param	char			*argv[] : ptr to each argument passed by the user.
 * @param	char			*envp[] : pointer to environmental variables.
 * @param	struct s_pipex	*pipex : a structure holding internal variables.
 * @return	Parent process ID, or
 * 			the output of the respective child function, or
 * 			error message, if forking was unsuccessful. 
 */
int	fork_parent(char *argv[], char *envp[], struct s_pipex *pipex,
				int **pipe_fd)
{
	(*pipex).parent_pid = fork();
	if ((*pipex).parent_pid == -1)
		return (write(2, ERR_FORK, ft_strlen(ERR_FORK)), EXIT_FAILURE);
	else if ((*pipex).parent_pid == 0)
	{
		if ((*pipex).fork_counter == 0)
			first_child(argv, envp, pipex, pipe_fd);
		else if ((*pipex).fork_counter > 0
			&& (*pipex).fork_counter + 2 < (*pipex).arg_counter - 2)
		{
			if (dup2(pipe_fd[(*pipex).fork_counter - 1][0], STDIN_FILENO) == -1)
				exit_pipe();
			if (dup2(pipe_fd[(*pipex).fork_counter][1], STDOUT_FILENO) == -1)
				exit_pipe();
			close_pipe(pipex, pipe_fd);
			return (execute_function(argv[(*pipex).fork_counter + 2], envp));
		}
		else if ((*pipex).fork_counter + 2 == (*pipex).arg_counter - 2)
			last_child(argv, envp, pipex, pipe_fd);
		return (EXIT_SUCCESS);
	}
	else
		return ((*pipex).parent_pid);
}

/**
 * @brief	Implements the required for program execution number of forks.
 * @return	Parent process ID. 
 */
int	fork_master(char *argv[], char *envp[], struct s_pipex *pipex,
				int **pipe_fd)
{
	while ((*pipex).fork_counter + 2 < (*pipex).arg_counter - 2)
	{
		fork_parent(argv, envp, pipex, pipe_fd);
		(*pipex).fork_counter++;
	}
	return (fork_parent(argv, envp, pipex, pipe_fd));
}

/**
 * @brief	Replicates the behaviour of "< file1 cmd1 | cmd2 | cmd... > file2"
 * 			when run from the command line.
 * @param	int		argc : number of arguments passed by the user.
 * @param	char	*argv[] : pointer to each argument passed by the user.
 * @param	char	*envp[] : pointer to environmental variables.
 * @param	struct s_pipex	*pipex : a structure holding internal variables.
 * @param	int				**pipe_fd : ptr to array of pipes file descriptors.
 * @param	int				ppid : parent process ID.
 * @param	int				wstatus : stores status information.
 * @param	WIFEXITED WEXITSTATUS : if the child terminated normally,
 * 							returns the exit status of the child.
 * @param	WIFSIGNALED WTERMSIG : if the child process was terminated by a
 * 			signal, returns the number of the signal that caused termination.
 * @return	Saves in file2 the output of opearations performed by the commands. 
 */
int	main(int argc, char *argv[], char *envp[])
{
	struct s_pipex	*pipex;
	int				**pipe_fd;
	int				ppid;
	int				wstatus;

	if (argc < 5)
		return (write(2, ERR_INPUT, ft_strlen(ERR_INPUT)), EXIT_FAILURE);
	if (!envp)
		return (write(2, ERR_ENVP, ft_strlen(ERR_ENVP)), EXIT_FAILURE);
	pipex = malloc(sizeof(struct s_pipex));
	if (pipex == NULL)
		return (write(2, ERR_MALLOC, ft_strlen(ERR_MALLOC)), EXIT_FAILURE);
	*pipex = (struct s_pipex){.arg_counter = argc, .fork_counter = 0,
		.parent_pid = 0, .input_fd = 0, .output_fd = 0};
	pipe_fd = set_pipe(pipex);
	ppid = fork_master(argv, envp, pipex, pipe_fd);
	close_pipe(pipex, pipe_fd);
	fn_free((char *)pipex);
	waitpid(ppid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		exit (WTERMSIG(wstatus));
	return (EXIT_SUCCESS);
}
