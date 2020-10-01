/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:42:41 by ngragas           #+#    #+#             */
/*   Updated: 2020/09/30 17:05:01 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

typedef struct		s_buf
{
	char			*data;
	struct s_buf	*next;
}					t_buf;

t_buf				*ft_list_add(char *data, t_buf **begin);
char				*ft_lcomb(char *dst, t_buf *begin);
int					ft_atoi(char *str, int len);
int					ft_isprint(char c);
int					ft_isspace(char c);

int					map_main(void);
char				*stdin_read(void);
char				*stdin_free(t_buf *list, char *data_buffer);
void				free_memory(void);
int					print_error(char *text);

char				*map_get(char *map_file);
int					map_filesize(char *map_file);
int					map_check(char *map);
int					map_check_lines(char *map, int i);
int					map_format(void);

void				map_parse(void);
int					point_check(int x, int y, int size, int to_fill);
#endif
