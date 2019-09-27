/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:00:45 by bnoufel           #+#    #+#             */
/*   Updated: 2019/04/10 15:20:23 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/mman.h>
# define MAP MAP_ANON | MAP_PRIVATE
# define PROT PROT_READ | PROT_WRITE
# define HEADER 32 * 32
# define TINY_SIZE  (size_t)(1024)
# define TINY_ZONE  (size_t)(TINY_SIZE * 1000)
# define SMALL_SIZE  (size_t)(TINY_ZONE)
# define SMALL_ZONE  (size_t)(SMALL_SIZE * 100)
# define LARGE_SIZE  (size_t)(SMALL_ZONE)
# define LARGE_ZONE  (size_t)(LARGE_SIZE * 100)

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct		s_zone
{
	void			*ptr;
	size_t			size;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_map
{
	void			*ptr;
	size_t			size;
	struct s_zone	*zone;
	struct s_map	*next;
}					t_map;

typedef struct		s_global
{
	struct s_map	*map;
	size_t			size;
}					t_global;

extern t_global		*g_global;

/*
** TOOLS
*/

void				*allocate(size_t size);
size_t				get_size_map(size_t size);
void				*getnextzone(t_map *map, size_t size);
size_t				malloc_size(const void *ptr);
size_t				malloc_good_size(size_t size);
void				get_header_to_move(t_zone *zone);
void				*new_map(void *ptr, size_t len, size_t size);
void				add_zone(t_map *map, void *ptr, size_t size);
/*
** LIBFT
*/

void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putchar(char c);
void				ft_putendl(char const *s);
void				ft_putlbr(size_t n);
void				ft_putstr(char const *s);
size_t				ft_strlen(const char *s);
void				hexdump(size_t ptr);
void				print_dump(t_zone *zone);
void				show_alloc_mem(void);

#endif
