/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:37:13 by ngragas           #+#    #+#             */
/*   Updated: 2020/09/30 16:37:03 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

extern char	*g_mapf;
extern char	**g_map;
extern int	g_mapsize[2];
extern char	g_empty;
extern char	g_obst;
extern char	g_full;
extern int	g_bestsize;
extern int	g_bestpos[2];

void	map_parse(void)
{
	int cur_x;
	int cur_y;
	int max_sq;

	cur_y = 0;
	while (cur_y < g_mapsize[1] - g_bestsize)
	{
		cur_x = 0;
		while (cur_x < g_mapsize[0] - g_bestsize)
		{
			if (g_map[cur_y][cur_x] == g_empty)
			{
				max_sq = point_check(cur_x, cur_y, 1, 0);
				if (g_bestsize < max_sq)
				{
					g_bestsize = max_sq;
					g_bestpos[0] = cur_x;
					g_bestpos[1] = cur_y;
				}
			}
			cur_x++;
		}
		cur_y++;
	}
}

int		point_check(int x, int y, int size, int to_fill)
{
	int x_check;
	int	y_check;

	y_check = 0;
	while (y_check < size)
	{
		if (to_fill || y_check == size - 1)
			x_check = 0;
		else
			x_check = size - 1;
		while (x_check < size)
		{
			if (x + x_check == g_mapsize[0] || (y + y_check == g_mapsize[1]))
				return (size - 1);
			if (g_map[y + y_check][x + x_check] != g_empty)
				return (size - 1);
			if (to_fill)
				g_map[y + y_check][x + x_check] = g_full;
			x_check++;
		}
		y_check++;
	}
	return (point_check(x, y, size + 1, 0));
}

void	free_memory(void)
{
	if (g_mapf)
	{
		free(g_mapf);
		g_mapf = NULL;
		if (g_map)
			free(g_map);
		g_map = NULL;
	}
	g_mapsize[0] = 0;
	g_mapsize[1] = 0;
	g_empty = 0;
	g_obst = 0;
	g_full = 0;
	g_bestsize = 0;
	g_bestpos[0] = -1;
	g_bestpos[1] = -1;
}
