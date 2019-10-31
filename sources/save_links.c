/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:30:05 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 17:32:45 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			make_new_link(t_general *farm, t_room *find_room, char *room_link)
{
	t_link	*links_list;

	if (!find_room->begin_links)
	{
		if (!(find_room->begin_links = (t_link*)malloc(sizeof(t_link))))
			program_end(farm, 0, NULL);
		links_list = find_room->begin_links;
	}
	else
	{
		links_list = find_room->begin_links;
		while (links_list->nxt)
		{
			if (ft_strcmp(links_list->name, room_link) == 0)
				return (0);
			links_list = links_list->nxt;
		}
		if (ft_strcmp(links_list->name, room_link) == 0)
			return (0);
		if (!(links_list->nxt = (t_link*)malloc(sizeof(t_link))))
			program_end(farm, 0, NULL);
		links_list = links_list->nxt;
	}
	init_link(links_list, room_link);
	return (1);
}

int			adding_link_to_room(t_general *farm, char *room, char *room_link)
{
	int		h;
	t_room	*find_room;

	h = hash(farm->n_rooms, room);
	find_room = farm->rooms[h];
	if (!find_room)
		return (0);
	while (find_room && ft_strcmp(find_room->name, room))
		find_room = find_room->same_hash;
	if (!find_room || !(make_new_link(farm, find_room, room_link)))
		return (0);
	find_room->link_count++;
	return (1);
}

int			save_links(t_general *farm, char *line)
{
	char	**array;

	if (!(array = ft_strsplit(line, '-')))
		program_end(farm, 0, NULL);
	if (ft_strchr(array[0], ' ') || ft_strchr(array[1], ' ')
			|| !farm->begin_rooms)
		program_end(farm, 1, NULL);
	if (!farm->rooms)
		make_rooms_hash_table(farm);
	if (!(adding_link_to_room(farm, array[0], array[1])))
	{
		del_matrix(array);
		return (0);
	}
	if (!(adding_link_to_room(farm, array[1], array[0])))
	{
		del_matrix(array);
		return (0);
	}
	del_matrix(array);
	return (1);
}
