/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:37:03 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/02/11 18:21:55 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Free a pointer and prevent double-freeing.
 * @param	char	*variable : a pointer to heap memory address.
 * @return	NULL.
 */
char	*fn_free(char *variable)
{
	free(variable);
	variable = NULL;
	return (NULL);
}

/**
 * @brief	Free a double pointer and the pointers it points to.
 * @param	char	**ptr : a pointer to pointers.
 * @return	NULL.
 */
char	*fn_free_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		fn_free(ptr[i]);
		i++;
	}
	fn_free(*ptr);
	write(2, ERR_MALLOC, ft_strlen(ERR_MALLOC));
	exit (EXIT_FAILURE);
}
