/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:28:48 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:31:05 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_way			*create_way(t_general *farm)
{
	t_way		*w_tmp;

	if (!(w_tmp = (t_way*)malloc(sizeof(t_way)))
			|| !(w_tmp->path = (t_path*)malloc(sizeof(t_path))))
		program_end(farm, 0, NULL);
	w_tmp->path->name = ft_strdup(farm->end->name);
	w_tmp->path->backward = NULL;
	w_tmp->path->forward = NULL;
	w_tmp->next = NULL;
	w_tmp->len = 0;
	w_tmp->ants = 0;
	w_tmp->on = 1;
	w_tmp->path->ant_name = 0;
	return (w_tmp);
}

void			mark_link_is_in_way(t_general *farm, char *room1, char *room2)
{
	int			h;
	t_room		*find_room;
	t_link		*find_link;

	h = hash(farm->n_rooms, room2);
	find_room = farm->rooms[h];
	while (ft_strcmp(find_room->name, room2) != 0)
		find_room = find_room->same_hash;
	if (ft_strcmp(room1, room2) == 0)
		find_room = find_room->room_copy;
	find_link = find_room->begin_links;
	while (ft_strcmp(find_link->name, room1) != 0)
		find_link = find_link->nxt;
	find_link->in_way++;
}

void			create_path(t_general *farm, t_way *cur_way, t_path *p_tmp)
{
	t_room		*find_room;
	t_path		*back;

	while (ft_strcmp(p_tmp->name, farm->start->name) != 0)
	{
		p_tmp->forward = (t_path*)malloc(sizeof(t_path));
		p_tmp->forward->ant_name = 0;
		back = p_tmp;
		p_tmp = p_tmp->forward;
		p_tmp->backward = back;
		find_room = farm->rooms[hash(farm->n_rooms, back->name)];
		while (ft_strcmp(back->name, find_room->name) != 0)
			find_room = find_room->same_hash;
		if (find_room->room_copy
			&& check_is_it_copy(find_room, p_tmp->backward->backward->name))
			find_room = find_room->room_copy;
		if (ft_strcmp(find_room->prev->name, find_room->name) == 0)
			p_tmp->name = ft_strdup(find_room->prev->prev->name);
		else
			p_tmp->name = ft_strdup(find_room->prev->name);
		mark_link_is_in_way(farm, p_tmp->name, p_tmp->backward->name);
		p_tmp->forward = NULL;
		cur_way->len++;
	}
	cur_way->path->backward = p_tmp;
}

void			add_new_way(t_general *farm, t_way *temp_way)
{
	create_path(farm, temp_way, temp_way->path);
	clean_queue(farm);
	graph_recovery(farm, farm->solutions->next);
	find_crossover(farm, temp_way);
	free_way(temp_way, temp_way->path);
	find_new_ways(farm, NULL);
	in_way_recover(farm->end->begin_links);
}

void			get_shortest_way(t_general *farm)
{
	t_way		*way;
	t_way		*temp_way;
	t_solution	*new_sol;

	if (!farm->solutions)
	{
		farm->solutions = (t_solution*)malloc(sizeof(t_solution));
		init_solution(farm->solutions);
		way = create_way(farm);
		create_path(farm, way, way->path);
		farm->solutions->ways = way;
		farm->solutions->n_ways = 1;
		farm->solutions->index = 1;
	}
	else
	{
		new_sol = (t_solution*)malloc(sizeof(t_solution));
		init_solution(new_sol);
		new_sol->next = farm->solutions;
		farm->solutions = new_sol;
		farm->solutions->index = farm->solutions->next->index + 1;
		temp_way = create_way(farm);
		add_new_way(farm, temp_way);
	}
}
