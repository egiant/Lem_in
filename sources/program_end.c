/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 20:07:49 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:33:53 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			free_way(t_way *way_tmp, t_path *path_tmp)
{
	t_path		*p_ptr;

	p_ptr = path_tmp;
	while (path_tmp)
	{
		p_ptr = path_tmp->forward;
		free(path_tmp->name);
		free(path_tmp);
		path_tmp = p_ptr;
	}
	free(way_tmp);
}

void			free_solutions(t_solution *sol)
{
	t_solution	*sol_tmp;
	t_solution	*s_ptr;
	t_way		*way_tmp;
	t_way		*w_ptr;

	sol_tmp = sol;
	while (sol_tmp)
	{
		way_tmp = sol_tmp->ways;
		while (way_tmp)
		{
			w_ptr = way_tmp->next;
			free_way(way_tmp, way_tmp->path);
			way_tmp = w_ptr;
		}
		s_ptr = sol_tmp->next;
		free(sol_tmp);
		sol_tmp = s_ptr;
	}
}

void			free_links(t_link *links)
{
	t_link *l_ptr;

	while (links)
	{
		l_ptr = links->nxt;
		free(links->name);
		free(links);
		links = l_ptr;
	}
}

void			free_room_list(t_room **rooms)
{
	t_room		*tmp;

	while (*rooms)
	{
		tmp = (*rooms)->next;
		free((*rooms)->name);
		if ((*rooms)->room_copy)
		{
			free_links((*rooms)->room_copy->begin_links);
			free((*rooms)->room_copy->name);
			free((*rooms)->room_copy);
		}
		free_links((*rooms)->begin_links);
		free((*rooms));
		(*rooms) = tmp;
	}
}

void			program_end(t_general *farm, int err, char **arr)
{
	if (farm)
	{
		if (farm->map)
			ft_strdel(&farm->map);
		if (farm->begin_rooms)
			free_room_list(&farm->begin_rooms);
		if (farm->rooms)
			free(farm->rooms);
		if (farm->solutions)
			free_solutions(farm->solutions);
		free(farm);
	}
	if (arr)
		del_matrix(arr);
	if (err)
		write(1, "ERROR\n", 6);
	exit(0);
}
