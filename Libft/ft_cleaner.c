/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:26:04 by rmakende          #+#    #+#             */
/*   Updated: 2024/12/29 15:37:08 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cleaner(char *str, char remover)
{
	char	*tmp;
	char	*to_free;
	int		i;

	if (!str || !*str)
		return (NULL);
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != remover)
		{
			to_free = tmp;
			tmp = ft_strjoin(tmp, ((char []){str[i], '\0'}));
			free(to_free);
			if (!tmp)
				return (NULL);
		}
		i++;
	}
	return (tmp);
}
