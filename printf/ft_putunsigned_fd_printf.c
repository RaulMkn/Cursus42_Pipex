/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_fd_printf.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:43:11 by rmakende          #+#    #+#             */
/*   Updated: 2024/09/20 17:28:48 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned_fd_printf(unsigned int n, int fd)
{
	char	str[10];
	int		i;
	int		result;

	if (n == 0)
	{
		return (ft_putchar_fd_printf('0', fd));
	}
	i = 0;
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	result = 0;
	while (i > 0)
	{
		result += ft_putchar_fd_printf(str[--i], fd);
	}
	return (result);
}
