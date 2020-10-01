/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:37:13 by ngragas           #+#    #+#             */
/*   Updated: 2020/09/30 17:04:31 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

extern char	*g_mapf;
extern char	**g_map;
extern int	g_mapsize[2];
extern char	g_empty;
extern char	g_obst;
extern char	g_full;

char	*map_get(char *map_file)
{
	int		file;
	int		bytes_read;
	char	*map;
	int		bytes_total;

	bytes_total = map_filesize(map_file);
	if (!bytes_total || !(map = malloc(bytes_total + 1)))
		return (NULL);
	if (!(file = open(map_file, O_RDONLY)))
	{
		free(map);
		return (NULL);
	}
	bytes_read = read(file, map, bytes_total);
	map[bytes_total] = 0;
	close(file);
	if (bytes_read == -1 || !map_check(map))
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int		map_filesize(char *map_file)
{
	int		file;
	int		bytes_total;
	int		bytes_read;
	char	buffer[256000];

	bytes_total = 0;
	if (!(file = open(map_file, O_RDONLY)))
		return (0);
	while ((bytes_read = read(file, buffer, 256000)) > 0)
		bytes_total += bytes_read;
	if (close(file) == -1 || bytes_read == -1)
		return (0);
	return (bytes_total);
}

int		map_check(char *map)
{
	int l;

	l = 0;
	while (map[l] && map[l] != '\n')
		l++;
	if (!map[l] || l < 4)
		return (0);
	g_full = map[--l];
	g_obst = map[--l];
	g_empty = map[--l];
	if (g_full == g_obst || g_obst == g_empty || g_full == g_empty)
		return (0);
	if (!ft_isprint(g_full) || !ft_isprint(g_obst) || !ft_isprint(g_empty))
		return (0);
	g_mapsize[1] = ft_atoi(map, l);
	if (!g_mapsize[1] || !map_check_lines(map + (l + 3) + 1, 0))
		return (0);
	return (1);
}

int		map_check_lines(char *map, int i)
{
	int	cur_x;
	int	cur_y;

	i = 0;
	cur_y = 0;
	while (map[i] && cur_y++ < g_mapsize[1])
	{
		cur_x = 0;
		while (map[i] && map[i] != '\n')
		{
			if ((map[i] != g_obst) && (map[i] != g_empty))
				return (0);
			cur_x++;
			i++;
		}
		if (!cur_x || !map[i++])
			return (0);
		if (!g_mapsize[0])
			g_mapsize[0] = cur_x;
		else if (cur_x != g_mapsize[0])
			return (0);
	}
	if (cur_y < g_mapsize[1] || map[i])
		return (0);
	return (1);
}

int		map_format(void)
{
	int		offset;
	int		y;

	if (!(g_map = malloc(g_mapsize[1] * sizeof(g_map))))
		return (0);
	offset = 0;
	while (g_mapf[offset] != '\n')
		offset++;
	y = -1;
	while (++y < g_mapsize[1])
		g_map[y] = g_mapf + (offset + 1) + y * (g_mapsize[0] + 1);
	return (1);
}
