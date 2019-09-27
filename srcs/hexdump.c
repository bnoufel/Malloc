/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:59:50 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 13:59:51 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		hexdump(size_t ptr)
{
	int		len;
	char	str[14];

	len = 12;
	str[len + 1] = '\0';
	while (len--)
	{
		str[len] = ptr % 16 + ((ptr % 16 > 9) ? ('A' - 10) : ('0'));
		ptr = ptr / 16;
	}
	str[1] = 'x';
	str[0] = '0';
	ft_putstr(str);
}

void		print_dump(t_zone *zone)
{
	hexdump((size_t)zone->ptr);
	write(1, " - ", 3);
	hexdump((size_t)(zone->ptr + zone->size));
	ft_putstr(" : ");
	ft_putlbr(zone->size);
	ft_putendl(" octets");
}
