/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_control_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:11:09 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/06/15 14:56:43 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/** 
 * Exit from a child to 'main' and return an error message. 
*/
int	exit_pipe(void)
{
	write(2, ERR_PIPE, ft_strlen(ERR_PIPE));
	exit (EXIT_FAILURE);
}

/** 
 * Close all pipes. 
*/
void	close_pipe(struct s_pipex *pipex, int **pipe_fd)
{
	int	i;

	i = 0;
	while (i < (*pipex).arg_counter - 4)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

/**
 * @brief	Opens pipes and saves the file descriptors in 'pipe_fd' array.
 * 			# of pipes = argc - 4 (file_name + infile + last cmd + outfile)
 * @param	struct s_pipex	*pipex : a structure holding internal variables.
 * @param	int				**pipe_fd : ptr to array of pipes file descriptors.
 * @return	pointer to 'pipe_fd' array, or
 * 			error message, if forking was unsuccessful. 
 */
int	**set_pipe(struct s_pipex *pipex)
{
	int	**pipe_fd;
	int	i;

	pipe_fd = (int **)malloc(sizeof(int *) * ((*pipex).arg_counter - 3));
	if (pipe_fd == NULL)
		fn_free_ptr((char **)pipe_fd);
	i = 0;
	while (i < (*pipex).arg_counter - 4)
	{
		pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe_fd[i] == NULL)
			fn_free_ptr((char **)pipe_fd);
		if (pipe(pipe_fd[i]) == -1)
		{
			fn_free((char *)pipe_fd);
			fn_free((char *)pipex);
			exit_pipe();
		}
		i++;
	}
	return (pipe_fd);
}
