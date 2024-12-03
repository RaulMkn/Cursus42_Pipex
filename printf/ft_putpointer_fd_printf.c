/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_fd_printf.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:47:54 by rmakende          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:14 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer_fd_printf(void *p, int fd)
{
	unsigned long long	addr;
	char				buffer[19];
	const char			*hex_digits = "0123456789abcdef";
	int					i;
	int					length;

	if (p == NULL)
		return (ft_putstr_fd_printf("(nil)", fd));
	i = 18;
	addr = (unsigned long long)p;
	buffer[i--] = '\0';
	while (addr != 0)
	{
		buffer[i--] = hex_digits[addr % 16];
		addr /= 16;
	}
	buffer[i--] = 'x';
	buffer[i--] = '0';
	length = ft_putstr_fd_printf(&buffer[i + 1], fd);
	return (length);
}
