/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:59:55 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 13:59:55 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_global			*g_global = NULL;

static t_global		*init_global(void)
{
	t_global		*ptr;
	size_t			len;

	len = (size_t)getpagesize();
	if ((ptr = mmap(NULL, len, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (NULL);
	ptr->map = NULL;
	ptr->size = len;
	return (ptr);
}

static void			*ft_malloc(size_t size)
{
	void			*ptr;
	size_t			len;
	void			*map;

	size = malloc_good_size(size);
	if (!g_global)
	{
		if (!(g_global = init_global()))
			return (NULL);
	}
	if (g_global->map && (ptr = getnextzone(g_global->map, size)))
		add_zone(g_global->map, ptr, size);
	else
	{
		len = get_size_map(size);
		if (!(map = allocate(len)))
			return (NULL);
		return (new_map(map, len, size));
	}
	return (ptr);
}

void				*malloc(size_t size)
{
	void			*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void				*calloc(size_t count, size_t size)
{
	void			*ptr;

	if (!(ptr = malloc(count * size)))
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
