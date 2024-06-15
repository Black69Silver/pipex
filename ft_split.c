/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:44:21 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/03/25 02:34:56 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Replaces the delimiter ’c’ with '\0'.
 * @param	char	*s : the string being split.
 * @param	char	*str : a copy of 's'.
 * @param	int		int_var[0] : length of 's' and 'str'.
 * @param	char	c : delimiter character.
 * @return	A pointer to 'str' - the amended version of 's'. 
 */
char	*c_to_0(char const *s, char *str, int *int_var, char c)
{
	int	i;

	i = 0;
	while (i < int_var[0])
	{
		if (s[i] == c)
			str[i] = '\0';
		else
			str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * @brief	Count the number of newly appeared sub-strings.
 * @param	char	*str : a copy of 's' string being split.
 * @param	int		int_var[2] : total number of sub-strings.
 * @return	The number of sub-strings/words. 
 */
int	sub_string_count(char *str, int *int_var)
{
	int	i;

	i = 0;
	int_var[2] = 0;
	while (i < int_var[0])
	{
		if (str[i] != '\0' && str[i + 1] == '\0')
			int_var[2]++;
		i++;
	}
	return (int_var[2]);
}

/**
 * @brief	Saves sub-strings into words, one at a time.
 * @param	char	*str : a copy of 's' string being split.
 * @param	int		int_var[1] : length of sub-string.
 * @param	int		int_var[3] : index of sub-string.
 * @param	int		int_var[4] : position within sub-string.
 * @param	int		int_var[5] : position within 'str'.
 * @param	char	**pointers : string of pointers to sub-strings.
 * @return	A pointer to the new sub-string/word. If unsuccessful at any point,
 * 			free all previously allocated spaces.
 */
char	*fill_word(char *str, int *int_var, char **pointers)
{
	char	*word;

	int_var[4] = 0;
	word = malloc(sizeof(char) * (int_var[1] + 1));
	if (word == NULL)
		fn_free_ptr(pointers);
	while (int_var[4] < int_var[1])
	{
		word[int_var[4]] = str[int_var[5] + int_var[4]];
		int_var[4]++;
	}
	word[int_var[4]] = '\0';
	return (word);
}

/**
 * @brief	Assembles the '*pointers' string of pointers.
 * @param	char	*str : a copy of 's' string being split.
 * @param	int		int_var[1] : length of sub-string.
 * @param	int		int_var[2] : total number of sub-strings.
 * @param	int		int_var[3] : index of sub-string.
 * @param	int		int_var[5] : position within 'str'.
 * @param	char	**pointers : string of pointers to sub-strings.
 * @return	A string of pointers to the new strings resulting from the split.
 * 			If an allocation fails, free 'pointers' and return NULL.
 */
char	**fill_pointers(char *str, int *int_var, char **pointers)
{
	char	*word;

	int_var[3] = 0;
	int_var[5] = 0;
	while (int_var[3] < int_var[2])
	{
		while (str[int_var[5]] == '\0')
			int_var[5]++;
		int_var[1] = ft_strlen(&str[int_var[5]]);
		word = fill_word(str, int_var, pointers);
		if (word == NULL)
			fn_free_ptr(pointers);
		pointers[int_var[3]] = word;
		int_var[5] = int_var[5] + int_var[1];
		int_var[3]++;
	}
	pointers[int_var[3]] = NULL;
	return (pointers);
}

/**
 * @brief	Splits string ’s’ into an array of sub-strings using ’c’ delimiter.
 * @param	char	*s : string to be split.
 * @param	char	c : delimiter character.
 * @param	int		int_var : array for 6 counters.
 * @param	int		int_var[0] : length of 's' and 'str'.
 * @param	int		int_var[2] : total number of sub-strings.
 * @return	A string of pointers to the new strings resulting from the split.
 * 			If an allocation fails, free 'str'/'pointers' and return NULL.
 */
char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**pointers;
	int		int_var[6];

	if (s == NULL)
		return (NULL);
	int_var[0] = ft_strlen(s);
	str = malloc(sizeof(char) * (int_var[0] + 1));
	if (str != NULL)
		str = c_to_0(s, str, int_var, c);
	else
	{
		fn_free(str);
		write(2, ERR_MALLOC, ft_strlen(ERR_MALLOC));
		return (NULL);
	}
	int_var[2] = sub_string_count(str, int_var);
	pointers = malloc(sizeof(char *) * (int_var[2] + 1));
	if (pointers != NULL)
		pointers = fill_pointers(str, int_var, pointers);
	else
		fn_free_ptr(pointers);
//		fn_free(*pointers);
	fn_free(str);
	return (pointers);
}

int	main(void)
{
//	char const	*s = "      split       this for   me  !       ";
//	char		c = ' ';
	char const	*s = "1c34ccc990";
	char		c = 'c';
	char	**pointers;

	printf("\nInput: %s\n", s);
	pointers = ft_split(s, c);
	printf("Output (pointer_to_pointers): %p\n\n", pointers);
	fn_free_ptr(pointers);
/*
	char		**split;

	split = ft_split(s, c);
	if (split == NULL)
	{
		printf("split returns NULL");
		return (-1);
	}
	while (*split != NULL)
	{
		printf("%s\n", *split);
		split++;
	}
*/	return (0);
}
