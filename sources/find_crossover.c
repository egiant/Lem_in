/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_crossover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:41:42 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:27:47 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_reverse_link(t_general *farm, char *room_name,
								char *link_name)
{
	int		h;
	t_room	*find_room;
	t_link	*find_link;

	h = hash(farm->n_rooms, room_name);
	find_room = farm->rooms[h];
	while (ft_strcmp(room_name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_links;
	while (ft_strcmp(find_link->name, link_name) != 0)
		find_link = find_link->nxt;
	if (find_link->in_way >= 1)
		return (1);
	return (0);
}

int			check_links_for_in_way(t_room *room)
{
	int		sum;
	t_link	*find_link;

	sum = 0;
	find_link = room->begin_links;
	while (find_link)
	{
		if (find_link->in_way > 0)
			sum += find_link->in_way;
		find_link = find_link->nxt;
	}
	return (sum);
}

void		remove_crossed_links(t_general *farm, t_room *find_room,
						t_link *find_link, t_path *temp_path)
{
	int		h;

	find_link->on = 0;
	find_link->in_way = 0;
	h = hash(farm->n_rooms, temp_path->forward->name);
	find_room = farm->rooms[h];
	while (ft_strcmp(temp_path->forward->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	find_link = find_room->begin_links;
	while (ft_strcmp(find_link->name, temp_path->name) != 0)
		find_link = find_link->nxt;
	find_link->on = 0;
	find_link->in_way = 0;
}

int			find_crossover(t_general *farm, t_way *way)
{
	int		ret;
	t_room	*find_room;
	t_link	*find_link;
	t_path	*temp_path;

	ret = 0;
	temp_path = way->path;
	while (temp_path->forward)
	{
		find_room = farm->rooms[hash(farm->n_rooms, temp_path->name)];
		while (ft_strcmp(temp_path->name, find_room->name) != 0)
			find_room = find_room->same_hash;
		find_link = find_room->begin_links;
		while (ft_strcmp(find_link->name, temp_path->forward->name) != 0)
			find_link = find_link->nxt;
		if (find_link->in_way > 1 || (find_link->in_way >= 1
				&& check_reverse_link(farm, find_link->name, find_room->name)))
		{
			ret = 1;
			remove_crossed_links(farm, find_room, find_link, temp_path);
		}
		temp_path = temp_path->forward;
	}
	return (ret);
}
