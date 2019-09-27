/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:00:31 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 14:00:32 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		get_size_map(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY_ZONE + HEADER);
	else if (size <= SMALL_SIZE)
		return (SMALL_ZONE + HEADER);
	else
		return (LARGE_ZONE + HEADER);
}

void		*allocate(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if ((ptr = mmap(0, size, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (ptr);
}
