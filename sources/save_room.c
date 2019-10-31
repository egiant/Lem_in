/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:06:31 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:17:52 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			find_repeats(t_room *begin_rooms, char **array)
{
	t_room	*tmp;

	tmp = begin_rooms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, array[0]))
			return (1);
		if (tmp->place.x == ft_atoi(array[1])
			&& tmp->place.y == ft_atoi(array[2]))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		create_room(t_general *farm, char **array, t_coord *point)
{
	t_room	*room_list;

	if (!farm->begin_rooms)
	{
		if (!(farm->begin_rooms = (t_room *)malloc(sizeof(t_room))))
			program_end(farm, 0, array);
		room_list = farm->begin_rooms;
	}
	else
	{
		room_list = farm->begin_rooms;
		while (room_list->next)
			room_list = room_list->next;
		if (!(room_list->next = (t_room *)malloc(sizeof(t_room))))
			program_end(farm, 0, array);
		room_list = room_list->next;
	}
	init_room(room_list, array);
	farm->start = (point->x) ? room_list : farm->start;
	farm->end = (point->y) ? room_list : farm->end;
	point->x = 0;
	point->y = 0;
}

int			valid_coords(char *coord1, char *coord2)
{
	int		i;

	i = 0;
	while (coord1[i])
	{
		if (!ft_isdigit(coord1[i++]))
			return (0);
	}
	i = 0;
	while (coord2[i])
	{
		if (!ft_isdigit(coord2[i++]))
			return (0);
	}
	return (1);
}

int			valid_room(char **array)
{
	int		i;
	int		j;

	i = 0;
	if (!array[2] || array[3])
		return (0);
	while (array[i])
	{
		j = 0;
		if (array[0][0] == 'L' || array[0][0] == '#')
			return (0);
		while (i > 0 && array[i][j])
		{
			if (!ft_isdigit(array[i][j]))
				return (0);
			++j;
		}
		++i;
	}
	if (!valid_coords(array[1], array[2]))
		return (0);
	if (ft_atoi_long(array[1]) > INT_MAX || ft_atoi_long(array[1]) < INT_MIN
		|| ft_atoi_long(array[2]) > INT_MAX || ft_atoi_long(array[2]) < INT_MIN)
		return (0);
	return (1);
}

int			save_room(t_general *farm, char *line, t_coord *point)
{
	char	**array;

	if (farm->rooms)
		program_end(farm, 1, NULL);
	if (!(array = ft_strsplit(line, ' ')))
		return (0);
	if (!valid_room(array) || find_repeats(farm->begin_rooms, array))
		program_end(farm, 1, array);
	create_room(farm, array, point);
	farm->n_rooms++;
	del_matrix(array);
	return (1);
}
