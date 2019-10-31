/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:10:50 by egiant            #+#    #+#             */
/*   Updated: 2019/10/24 17:18:04 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			out_links(t_general *farm, char *name)
{
	int			room_hash;
	t_room		*find_room;
	t_link		*ptr;

	room_hash = hash(farm->n_rooms, name);
	find_room = farm->rooms[room_hash];
	while (ft_strcmp(name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_room->room_copy = copy_room(farm, find_room);
	ptr = find_room->begin_links;
	find_room->room_copy->begin_links = (t_link *)malloc(sizeof(t_link));
	find_room->room_copy->begin_links->name = ft_strdup(find_room->name);
	find_room->room_copy->begin_links->weight = 0;
	find_room->room_copy->begin_links->nxt = NULL;
	find_room->room_copy->begin_links->on = 1;
	while (ptr)
	{
		if (ptr->on && ptr->weight != -1)
		{
			copy_links(farm, find_room->room_copy->begin_links, ptr);
			ptr->on = 0;
		}
		ptr = ptr->nxt;
	}
}

void			inverse_edges(t_general *farm, t_path *room1, t_path *room2)
{
	int			room_hash;
	t_room		*find_room;
	t_link		*find_link;

	room_hash = hash(farm->n_rooms, room1->name);
	find_room = farm->rooms[room_hash];
	while (ft_strcmp(room1->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_links;
	while (ft_strcmp(find_link->name, room2->name) != 0)
		find_link = find_link->nxt;
	find_link->weight = -1;
	room_hash = hash(farm->n_rooms, room2->name);
	find_room = farm->rooms[room_hash];
	while (ft_strcmp(room2->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_links;
	while (ft_strcmp(find_link->name, room1->name) != 0)
		find_link = find_link->nxt;
	find_link->on = 0;
}

void			suurballe(t_general *farm)
{
	t_way		*way;
	t_path		*path;

	way = farm->solutions->ways;
	while (way)
	{
		path = way->path;
		while (path->forward)
		{
			inverse_edges(farm, path, path->forward);
			path = path->forward;
		}
		way = way->next;
	}
	way = farm->solutions->ways;
	while (way)
	{
		path = way->path->forward;
		while (path->forward)
		{
			out_links(farm, path->name);
			path = path->forward;
		}
		way = way->next;
	}
}
