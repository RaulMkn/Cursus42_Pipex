/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:36:22 by rmakende          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:06 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd_printf(char *s, int fd)
{
	int		i;
	int		j;
	int		result;

	i = 0;
	j = 0;
	if (!s)
		return (ft_putstr_fd_printf("(null)", 1));
	while (s[i] != '\0')
	{
		result = ft_putchar_fd_printf(s[i], fd);
		if (result == -1)
		{
			return (-1);
		}
		j += result;
		i++;
	}
	return (j);
}
