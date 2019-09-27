/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:00:08 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 14:00:09 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		malloc_good_size(size_t size)
{
	return ((size + 15) & ~15);
}

size_t		malloc_size(const void *ptr)
{
	t_map	*map;
	t_zone	*zone;

	map = g_global->map;
	while (map)
	{
		zone = map->zone;
		while (zone)
		{
			if (ptr == zone->ptr)
				return (zone->size);
			zone = zone->next;
		}
		map = map->next;
	}
	return (0);
}
