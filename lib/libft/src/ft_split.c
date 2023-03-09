/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 09:53:47 by briferre          #+#    #+#             */
/*   Updated: 2022/06/26 20:55:31 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cont_words(char const *s, char c)
{
	int		i;
	int		word;
	size_t	words;

	words = 0;
	word = 0;
	i = 0;
	while (s[i])
	{
		if (!word && s[i] != c)
		{
			word = 1;
			words++;
		}
		else if (word && s[i] == c)
			word = 0;
		i++;
	}
	return (words);
}

static size_t	ft_get_word_size(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i++);
}

static char	*ft_create_word(char const *s, size_t size)
{
	char		*new_s;
	size_t		i;

	new_s = (char *)malloc(size + 1);
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static void	*ft_delete_split(char **split, size_t end)
{
	size_t	i;

	i = 0;
	while (i < end)
		free(split[i]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	size;
	size_t	words;
	size_t	cont;

	if (s == NULL)
		return (NULL);
	words = ft_cont_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	cont = 0;
	while (cont < words)
	{
		size = ft_get_word_size(s, c);
		if (size)
		{
			split[cont] = ft_create_word(s, size);
			if (split[cont++] == NULL)
				return (ft_delete_split(split, cont - 1));
		}
		s += size + 1;
	}
	split[cont] = NULL;
	return (split);
}
