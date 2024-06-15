/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 01:37:08 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/02/13 21:21:35 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h> 	/* to use 'open' */ 
# include <stdlib.h>	/* to use 'calloc', 'exit', 'free', 'malloc' */
# include <unistd.h>	/* to use 'access', 'close', 'dup', 'execve', 'pid_t',
							'pipe', 'read', 'write' */

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe creation error.\n"
# define ERR_FORK "Fork creation error.\n"
# define ERR_INFILE "Missing file1.\n"
# define ERR_MALLOC "Memory allocation error.\n"
# define ERR_ENVP "Environment pointers/path and/or command not found.\n"
# define ERR_CMD "Command not executed.\n"
# define ERR_OUTFILE "Cannot open file2.\n"

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

struct s_pipex
{
	int		arg_counter;
	int		fork_counter;
	pid_t	parent_pid;
	int		input_fd;
	int		output_fd;
};

void	close_pipe(struct s_pipex *pipex, int **pipe_fd);
int		execute_function(char argv[], char *envp[]);
int		exit_pipe(void);
char	*fn_free(char *variable);
char	*fn_free_ptr(char **ptr);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		**set_pipe(struct s_pipex *pipex);

#endif
