/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:37:13 by ngragas           #+#    #+#             */
/*   Updated: 2020/09/30 16:39:38 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

char	*g_mapf = NULL;
char	**g_map = NULL;
int		g_mapsize[2] = {0, 0};
char	g_empty;
char	g_obst;
char	g_full;
int		g_bestsize = 0;
int		g_bestpos[2] = {-1, -1};

int		main(int argc, char *argv[])
{
	int		i;

	if (argc == 1)
	{
		if (!(g_mapf = stdin_read()))
			return (print_error("map error"));
		else if (!map_main())
			return (EXIT_FAILURE);
	}
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (!(g_mapf = map_get(argv[i])))
				print_error("map error");
			else if (!map_main())
				return (EXIT_FAILURE);
			if (i < argc - 1)
				write(1, "\n", 1);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int		map_main(void)
{
	if (!map_format())
		return (0);
	map_parse();
	if (g_bestpos[0] != -1)
		point_check(g_bestpos[0], g_bestpos[1], g_bestsize, 1);
	write(1, g_map[0], g_mapsize[1] * (g_mapsize[0] + 1));
	free_memory();
	return (1);
}

char	*stdin_read(void)
{
	int		bytes_read;
	int		bytes_total;
	char	*data_buf;
	char	*all_buf;
	t_buf	*all_lists;

	all_lists = NULL;
	bytes_total = 0;
	if (!(data_buf = malloc(65536 + 1)))
		return (NULL);
	while ((bytes_read = read(0, data_buf, 65536)) > 0)
	{
		data_buf[bytes_read] = 0;
		if (!(ft_list_add(data_buf, &all_lists)))
			return (stdin_free(all_lists, data_buf));
		bytes_total += bytes_read;
		if (!(data_buf = malloc(65536 + 1)))
			return (stdin_free(all_lists, NULL));
	}
	free(data_buf);
	if (!(all_buf = malloc(bytes_total + 1)) || !ft_lcomb(all_buf, all_lists))
		return (stdin_free(all_lists, NULL));
	if (bytes_read < 0 || !map_check(all_buf))
		return (NULL);
	return (all_buf);
}

char	*stdin_free(t_buf *list, char *data_buffer)
{
	t_buf	*prev_list;

	while (list)
	{
		prev_list = list;
		list = list->next;
		free(prev_list->data);
		free(prev_list);
	}
	if (data_buffer)
		free(data_buffer);
	return (NULL);
}

int		print_error(char *text)
{
	if (*text)
	{
		while (*text)
			write(2, text++, 1);
		write(2, "\n", 1);
	}
	free_memory();
	return (EXIT_FAILURE);
}
