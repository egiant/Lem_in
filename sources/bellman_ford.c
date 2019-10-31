/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:24:56 by egiant            #+#    #+#             */
/*   Updated: 2019/10/24 14:50:00 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		clean_queue(t_general *farm)
{
	t_room	*tmp;
	t_room	*next;

	tmp = farm->start;
	while (tmp)
	{
		next = tmp->queue;
		tmp->prev = NULL;
		tmp->queue = NULL;
		tmp->in_q = 0;
		tmp->bf = 0;
		tmp = next;
	}
}

void		add_link_to_queue(t_general *farm, t_room *add, t_room *cur_room,
								t_link *room_links)
{
	int		h;
	t_room	*find_room;

	h = hash(farm->n_rooms, room_links->name);
	find_room = farm->rooms[h];
	while (ft_strcmp(room_links->name, find_room->name) != 0)
		find_room = find_room->same_hash;
	if (room_links->weight == -1
		&& ft_strcmp(room_links->name, farm->start->name) != 0
			&& ft_strcmp(room_links->name, farm->end->name) != 0)
		find_room = find_room->room_copy;
	if (find_room->in_q == 0 && room_links->on)
	{
		add->queue = find_room;
		find_room->prev = cur_room;
		if (!cur_room->prev)
			find_room->bf = room_links->weight;
		else
			find_room->bf = find_room->prev->bf + room_links->weight;
		add = add->queue;
		add->in_q = 1;
	}
}

void		find_next_room_for_queue(t_general *farm, t_room *cur_room)
{
	t_room	*add;
	t_link	*cur_room_links;

	add = cur_room;
	while (add->queue)
		add = add->queue;
	cur_room_links = cur_room->begin_links;
	while (cur_room_links)
	{
		add_link_to_queue(farm, add, cur_room, cur_room_links);
		if (add->queue)
			add = add->queue;
		cur_room_links = cur_room_links->nxt;
	}
}

int			all_rooms_in_queue(t_room *begin)
{
	while (begin)
	{
		if (begin->in_q == 0)
			return (0);
		begin = begin->next;
	}
	return (1);
}

int			bellman_ford(t_general *farm)
{
	t_room	*q_tmp;

	q_tmp = farm->start;
	q_tmp->in_q = 1;
	while (!all_rooms_in_queue(farm->begin_rooms))
	{
		find_next_room_for_queue(farm, q_tmp);
		q_tmp->in_q = -1;
		if (!q_tmp->queue && farm->end->in_q == 0)
			return (0);
		else if (!q_tmp->queue && farm->end->in_q != 0)
			return (1);
		q_tmp = q_tmp->queue;
	}
	return (1);
}
