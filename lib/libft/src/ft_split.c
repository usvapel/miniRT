/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:22:23 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 17:22:56 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_word_len(const char *arr, char c)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (arr[i] != '\0' && arr[i] == c)
		i++;
	while (arr[i] != '\0' && arr[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

static size_t	ft_words_in_s(const char *s, char c)
{
	size_t	count;
	size_t	i;
	int		in_word;

	if (c == '\0')
	{
		if (*s != '\0')
			return (1);
		else
			return (0);
	}
	count = 0;
	i = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static void	ft_free(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*ft_find_char(const char **arr, char c)
{
	char	*buffer;
	size_t	i;

	while (**arr != '\0' && **arr == c)
		(*arr)++;
	i = ft_get_word_len(*arr, c);
	buffer = ft_calloc(i + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (**arr != '\0' && **arr != c)
	{
		buffer[i] = **arr;
		i++;
		(*arr)++;
	}
	buffer[i] = '\0';
	while (**arr != '\0' && **arr == c)
		(*arr)++;
	return (buffer);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	i;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_words_in_s(s, c);
	result = ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (word_count == 0)
		return (result);
	i = 0;
	while (*s && i < word_count)
	{
		result[i] = ft_find_char(&s, c);
		if (!result[i])
		{
			ft_free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
