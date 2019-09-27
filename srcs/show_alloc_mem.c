/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:00:25 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 14:00:26 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		get_first_alloc(int limit)
{
	t_map		*map;
	t_zone		*zone;

	map = g_global->map;
	while (map)
	{
		zone = map->zone;
		while (zone)
		{
			if ((limit == TINY_SIZE && zone->size <= TINY_ZONE)
			|| (limit == SMALL_SIZE
			&& zone->size >= SMALL_SIZE && zone->size <= LARGE_SIZE)
			|| (limit == LARGE_SIZE && zone->size >= LARGE_SIZE))
			{
				hexdump((size_t)zone->ptr);
				return ;
			}
			zone = zone->next;
		}
		map = map->next;
	}
}

static void		write_tiny(t_map *map)
{
	t_zone		*zone;

	write(1, "TINY : ", 7);
	get_first_alloc(TINY_SIZE);
	ft_putchar('\n');
	while (map)
	{
		zone = map->zone;
		while (zone)
		{
			if (zone->size <= TINY_SIZE)
				print_dump(zone);
			zone = zone->next;
		}
		map = map->next;
	}
}

static void		write_small(t_map *map)
{
	t_zone		*zone;

	write(1, "SMALL : ", 8);
	get_first_alloc(SMALL_SIZE);
	ft_putchar('\n');
	while (map)
	{
		zone = map->zone;
		while (zone)
		{
			if (zone->size >= SMALL_SIZE && zone->size <= LARGE_SIZE)
				print_dump(zone);
			zone = zone->next;
		}
		map = map->next;
	}
}

static void		write_large(t_map *map)
{
	t_zone		*zone;

	write(1, "LARGE : ", 8);
	get_first_alloc(LARGE_SIZE);
	ft_putchar('\n');
	while (map)
	{
		zone = map->zone;
		while (zone)
		{
			if (zone->size >= LARGE_SIZE)
				print_dump(zone);
			zone = zone->next;
		}
		map = map->next;
	}
}

void			show_alloc_mem(void)
{
	t_map		*map;

	pthread_mutex_lock(&g_mutex);
	map = g_global->map;
	write_tiny(map);
	write_small(map);
	write_large(map);
	pthread_mutex_unlock(&g_mutex);
}
