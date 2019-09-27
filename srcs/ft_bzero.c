/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:58:38 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/08 13:58:39 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*a;
	size_t			i;

	a = s;
	i = 0;
	while (a && i < n)
	{
		a[i] = 0;
		i++;
	}
}
