/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:58:30 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 13:58:32 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		delete_map(t_map *map)
{
	t_map		*tmp;

	if (g_global->map != map)
	{
		tmp = g_global->map;
		while (tmp && tmp->next != map)
			tmp = tmp->next;
		if (tmp && !tmp->zone)
		{
			tmp->next = NULL;
			if ((munmap((void *)tmp, tmp->size)) == -1)
				return (0);
		}
	}
	return (1);
}

static void		delete_zone(t_map *map, void *ptr)
{
	t_zone		*zone;

	while (map->next)
	{
		if (!map->zone && delete_map(map))
			return ;
		zone = map->zone;
		if (zone && zone->ptr == ptr)
		{
			map->zone = (zone->next == NULL) ? NULL : zone->next;
			return ;
		}
		while (zone && zone->next)
		{
			if (zone->next->ptr == ptr)
			{
				zone->next = (zone->next->next) ? zone->next->next : NULL;
				return ;
			}
			zone = zone->next;
		}
		map = map->next;
	}
}

void			ft_free(void *ptr)
{
	t_map		*map;

	if (!ptr || !g_global)
		return ;
	map = g_global->map;
	delete_zone(map, ptr);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
