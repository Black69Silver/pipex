/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 01:37:08 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/02/13 20:40:08 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h> 	/* to use 'open' */ 
# include <stdlib.h>	/* to use 'calloc', 'exit', 'free', 'malloc' */
# include <unistd.h>	/* to use 'access', 'close', 'dup', 'execve', 'pid_t',
							'pipe', 'read', 'write' */
# include <stdio.h>		/* to use 'printf' */ 									// Delete before submitting.

# define ERR_INPUT "Invalid number of arguments or no Environment pointers.\n"	// 0, i.e. Undefined error. Or check error codes and messages, e.g. with 'echo $?'
# define ERR_PIPE "Broken pipe.\n"												// 32, i.e. Pipe creation error.
# define ERR_FORK "No child processes.\n"										// 10, i.e. Fork creation error.
# define ERR_INFILE "No such file or directory.\n"								// 2, i.e. Missing !@# file1.
# define ERR_MALLOC "Out of memory.\n"											// 12, i.e. Memory allocation error.
# define ERR_ENVP "Command not found.\n"										// 127 i.e.: No such file or directory or Environment pointers and/or path and/or command not found.
# define ERR_CMD "Command invoked cannot execute.\n"							// 126 (e.g. zsh: command not found: awkk or respective 'cmd#')	
# define ERR_OUTFILE "Permission denied.\n"										// 13 i.e.: Cannot open file2. 

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

struct s_pipex
{
//	int		arg_counter;
	int		fork_counter;
	pid_t	parent_pid;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
};

void	close_pipe(int argc, struct s_pipex *pipex, int (*pipe_fd)[2]);
int		execute_function(char argv[], char *envp[]);
void	exit_pipe(void);
char	*fn_free(char *variable);
char	*fn_free_ptr(char **ptr);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//int		(*make_pipe(int argc, int (*pipe_fd)[2], struct s_pipex *pipex))[2];

#endif
