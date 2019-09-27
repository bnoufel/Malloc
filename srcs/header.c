/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:59:44 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 13:59:45 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	get_size_zone(t_map *map)
{
	t_zone		*zone;

	zone = map->zone;
	if (zone)
	{
		while (zone->next)
			zone = zone->next;
		return ((size_t)(zone->ptr - (void *)(zone + 1)));
	}
	return (map->size);
}

static void		move_header(t_zone *zone, t_zone *next)
{
	void		*ptr;
	size_t		len;

	ptr = zone->ptr;
	len = zone->size;
	zone = zone + 1;
	zone->ptr = ptr;
	zone->size = len;
	zone->next = next;
}

void			get_header_to_move(t_zone *zone)
{
	if (zone)
	{
		if (zone->next)
			get_header_to_move(zone->next);
		move_header(zone, ((zone->next) ? zone->next + 1 : NULL));
	}
}

void			*getnextzone(t_map *map, size_t size)
{
	t_zone		*zone;

	if (!map->zone && map->size - HEADER >= size)
		return ((void *)map + map->size - size);
	if (map->size > size && get_size_zone(map) >= sizeof(t_zone))
	{
		while (map)
		{
			zone = map->zone;
			while (zone)
			{
				if (zone->next && size <= (size_t)(zone->ptr
				- (zone->next->ptr + zone->next->size)))
					return (zone->next->ptr + zone->next->size);
				else if (!zone->next && (size + sizeof(t_zone))
				<= (size_t)((zone->ptr) - (void *)(zone + 1)))
					return (zone->ptr - size);
				zone = zone->next;
			}
			map = map->next;
		}
	}
	return (NULL);
}
