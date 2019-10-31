/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ways2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:28:46 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:33:31 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			in_way_recover(t_link *next_room)
{
	while (next_room)
	{
		if (next_room->in_way == -1)
			next_room->in_way = 1;
		next_room = next_room->nxt;
	}
}

int				check_is_it_copy(t_room *cur_room, char *link_name)
{
	t_link		*l_tmp;

	l_tmp = cur_room->begin_links;
	while (l_tmp)
	{
		if (ft_strcmp(link_name, l_tmp->name) == 0)
			break ;
		l_tmp = l_tmp->nxt;
	}
	if (l_tmp->on == 0)
		return (1);
	else
		return (0);
}

t_link			*in_way_link_finder(t_room *room, int tumbler)
{
	t_link		*temp_link;

	temp_link = room->begin_links;
	while (temp_link)
	{
		if (temp_link->in_way == 1)
		{
			temp_link->in_way = tumbler;
			return (temp_link);
		}
		temp_link = temp_link->nxt;
	}
	return (NULL);
}

int				make_paths(t_general *f, t_path **new_path, t_link **next_room)
{
	t_room		*find_room;

	(*new_path)->forward = (t_path*)malloc(sizeof(t_path));
	(*new_path)->forward->backward = (*new_path);
	(*new_path) = (*new_path)->forward;
	(*new_path)->ant_name = 0;
	(*new_path)->name = ft_strdup((*next_room)->name);
	(*new_path)->forward = NULL;
	if (ft_strcmp((*next_room)->name, f->start->name) == 0)
		return (0);
	find_room = f->rooms[hash(f->n_rooms, (*new_path)->name)];
	while (ft_strcmp((*new_path)->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	*next_room = in_way_link_finder(find_room, 1);
	return (1);
}

void			find_new_ways(t_general *farm, t_link *next_room)
{
	t_way		*new_way;
	t_path		*new_path;

	while ((next_room = in_way_link_finder(farm->end, -1)))
	{
		farm->solutions->n_ways++;
		if (!farm->solutions->ways)
		{
			farm->solutions->ways = create_way(farm);
			new_way = farm->solutions->ways;
		}
		else
		{
			new_way->next = create_way(farm);
			new_way = new_way->next;
		}
		new_path = new_way->path;
		while (next_room)
		{
			new_way->len++;
			if (!make_paths(farm, &new_path, &next_room))
				break ;
		}
		new_way->path->backward = new_path;
	}
}
