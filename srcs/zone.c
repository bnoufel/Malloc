/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:00:39 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 14:00:39 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_zone	*new_zone(void *addr, void *ptr, size_t zonelen)
{
	t_zone		*zone;

	zone = (t_zone *)addr;
	zone->ptr = ptr;
	zone->size = zonelen;
	zone->next = NULL;
	return (zone);
}

static int		add_new_zone(t_zone *zone, void *ptr, size_t size)
{
	t_zone		*tmp;

	get_header_to_move(zone->next);
	tmp = new_zone(zone + 1, ptr, size);
	if (zone->next)
		tmp->next = zone->next + 1;
	else
		tmp->next = NULL;
	zone->next = tmp;
	return (1);
}

void			*new_map(void *ptr, size_t len, size_t size)
{
	t_map		*head;
	t_map		*map;

	head = ptr;
	head->size = len;
	head->next = NULL;
	head->zone = new_zone(ptr + sizeof(t_map), ptr + len - size, size);
	if (g_global->map)
	{
		map = g_global->map;
		while (map->next)
			map = map->next;
		map->next = head;
	}
	else
		g_global->map = head;
	return (head->zone->ptr);
}

void			add_zone(t_map *map, void *ptr, size_t size)
{
	t_map		*head;
	t_zone		*z;
	void		*tmp;

	head = map;
	while (head)
	{
		z = head->zone;
		if (!head->zone && (void *)head + head->size - size == ptr)
		{
			head->zone = new_zone((void *)head + sizeof(t_map), ptr, size);
			return ;
		}
		while (z)
		{
			tmp = (z->next) ? z->next->ptr + z->next->size : z->ptr - size;
			if (tmp == ptr && add_new_zone(z, ptr, size))
				return ;
			z = z->next;
		}
		head = head->next;
	}
}
