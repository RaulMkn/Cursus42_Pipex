/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:30:03 by rmakende          #+#    #+#             */
/*   Updated: 2024/12/29 15:30:03 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**asign_memory(char const *s, char c, int i, int k)
{
	char	**str;
	char	quote;

	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			k++;
			quote = '\0';
			while ((s[i] != c || quote != '\0') && s[i] != '\0')
			{
				if ((s[i] == '\'' || s[i] == '\"') && quote == '\0')
					quote = s[i];
				else if (s[i] == quote)
					quote = '\0';
				i++;
			}
		}
	}
	str = (char **)malloc((k + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (str);
}

static void	*free_memory(char **str, int k)
{
	while (k >= 0)
	{
		free(str[k]);
		k--;
	}
	free(str);
	return (NULL);
}

static int	asign_j(const char *s, char c, int i)
{
	int		j;
	char	quote;

	j = i;
	if (s[i] == '\'' || s[i] == '\"')
	{
		quote = s[i];
		j++;
		while (s[j] != quote && s[j] != '\0')
		{
			if (s[j] == '\\' && (s[j + 1] == quote || s[j + 1] == '\\'))
				j++;
			j++;
		}
		if (s[j] == quote)
			j++;
	}
	else
	{
		while (s[j] != c && s[j] != '\0')
			j++;
	}
	return (j);
}

static char	**true_split(char **str, char const *s, char c)
{
	int	k;
	int	j;
	int	l;
	int	i;

	k = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			j = asign_j(s, c, i);
			str[k] = (char *)malloc((j - i + 1) * sizeof(char));
			if (!str[k])
				return (free_memory(str, k));
			l = 0;
			while (i < j)
				str[k][l++] = s[i++];
			str[k++][l] = '\0';
		}
	}
	str[k] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	char	**str;

	i = 0;
	k = 0;
	str = asign_memory(s, c, i, k);
	if (!str)
		return (NULL);
	str = true_split(str, s, c);
	return (str);
}
#include <stdio.h>
#include <stdlib.h>

void	free_array(char **array)
{
	if (!array)
		return;
	for (int i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

int	main(void)
{
	char	**result = ft_split("this is a test string", ' ');

	if (!result)
		return (1);
	for (int i = 0; result[i]; i++)
		printf("result[%d]: %s\n", i, result[i]);

	free_array(result);
	return (0);
}
