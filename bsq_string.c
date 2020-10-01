/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:37:13 by ngragas           #+#    #+#             */
/*   Updated: 2020/09/30 16:36:00 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

t_buf	*ft_list_add(char *data, t_buf **begin)
{
	t_buf	*list;
	t_buf	*current;

	list = malloc(sizeof(t_buf));
	if (!list)
		return (NULL);
	list->data = data;
	list->next = NULL;
	if (*begin)
	{
		current = *begin;
		while (current->next)
			current = current->next;
		current->next = list;
	}
	else
		*begin = list;
	return (list);
}

char	*ft_lcomb(char *dst, t_buf *begin)
{
	int		i;
	int		n;
	t_buf	*prev;

	i = 0;
	while (begin)
	{
		n = 0;
		while (begin->data[n])
			dst[i++] = begin->data[n++];
		prev = begin;
		begin = begin->next;
		free(prev->data);
		free(prev);
	}
	dst[i] = 0;
	return (dst);
}

int		ft_atoi(char *str, int len)
{
	int i;
	int number;

	i = 0;
	number = 0;
	while (str[i] == '0')
		i++;
	while (i < len && '0' <= str[i] && str[i] <= '9')
	{
		number = number * 10 + str[i] - '0';
		i++;
	}
	if (i == len)
		return (number);
	else
		return (0);
}

int		ft_isprint(char c)
{
	if (32 <= c && c <= 126)
		return (1);
	return (0);
}

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
