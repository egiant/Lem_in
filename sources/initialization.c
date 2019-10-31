/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:15:28 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 17:48:15 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_solution(t_solution *solutions)
{
	solutions->index = 0;
	solutions->n_ways = 0;
	solutions->steps = 0;
	solutions->next = NULL;
	solutions->ways = NULL;
}

void	init_link(t_link *links_list, char *link_name)
{
	links_list->name = ft_strdup(link_name);
	links_list->weight = 1;
	links_list->nxt = NULL;
	links_list->on = 1;
	links_list->in_way = 0;
}

void	init_room(t_room *room_list, char **array)
{
	room_list->name = ft_strdup(array[0]);
	room_list->place.x = ft_atoi(array[1]);
	room_list->place.y = ft_atoi(array[2]);
	room_list->next = NULL;
	room_list->begin_links = NULL;
	room_list->same_hash = NULL;
	room_list->room_copy = NULL;
	room_list->link_count = 0;
	room_list->prev = NULL;
	room_list->queue = NULL;
	room_list->in_q = 0;
	room_list->bf = 0;
}

void	init_farm(t_general *farm)
{
	farm->n_ants = 0;
	farm->n_rooms = 0;
	farm->map = NULL;
	farm->begin_rooms = NULL;
	farm->rooms = NULL;
	farm->start = NULL;
	farm->end = NULL;
	farm->solutions = NULL;
}
