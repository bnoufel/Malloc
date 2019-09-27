/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:00:17 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 14:00:20 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new;
	size_t	len;

	new = NULL;
	if (!ptr)
		return (malloc(size));
	else if (!size)
	{
		free(ptr);
		return (malloc(16));
	}
	if (malloc_size(ptr) == 0 || !(new = malloc(size)))
	{
		free(ptr);
		return (NULL);
	}
	len = (malloc_size(ptr) > size) ? size : malloc_size(ptr);
	ft_memcpy(new, ptr, len);
	free(ptr);
	return (new);
}

void		*realloc(void *ptr, size_t size)
{
	void	*new;

	if (size > LARGE_ZONE)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	new = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new);
}

void		*reallocf(void *ptr, size_t size)
{
	void	*new;

	if (!(new = realloc(ptr, size)))
		free(ptr);
	return (new);
}
