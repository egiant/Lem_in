/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_recovery.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:40:39 by egiant            #+#    #+#             */
/*   Updated: 2019/10/24 19:25:10 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		delete_copy(t_room *room)
{
	t_link	*del_link;
	t_link	*helper;
	t_link	*temp_link;

	if (room->room_copy)
	{
		del_link = room->room_copy->begin_links;
		while (del_link)
		{
			helper = del_link->nxt;
			free(del_link->name);
			free(del_link);
			del_link = helper;
		}
		free(room->room_copy->name);
		free(room->room_copy);
		room->room_copy = NULL;
	}
	temp_link = room->begin_links;
	while (temp_link)
	{
		temp_link->weight = 1;
		temp_link->on = 1;
		temp_link = temp_link->nxt;
	}
}

void		graph_recovery(t_general *farm, t_solution *prev_sol)
{
	int		h;
	t_way	*temp_way;
	t_path	*temp_path;
	t_room	*find_room;

	temp_way = prev_sol->ways;
	while (temp_way)
	{
		temp_path = temp_way->path;
		while (temp_path)
		{
			h = hash(farm->n_rooms, temp_path->name);
			find_room = farm->rooms[h];
			while (ft_strcmp(temp_path->name, find_room->name) != 0)
				find_room = find_room->same_hash;
			delete_copy(find_room);
			temp_path = temp_path->forward;
		}
		temp_way = temp_way->next;
	}
}
