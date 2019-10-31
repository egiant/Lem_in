/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:53:59 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:42:34 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_path(int ant_name, char *path_name, int n)
{
	if (n)
		write(1, " ", 1);
	ft_printf("L%d-%s", ant_name, path_name);
}

void		print_ways(t_general *farm, int n)
{
	t_way	*way;
	t_path	*path;

	way = farm->solutions->ways;
	while (way)
	{
		path = way->path;
		while (path->ant_name <= 0 && path->forward != way->path->backward)
			path = path->forward;
		while (path->ant_name > 0)
		{
			print_path(path->ant_name, path->name, n++);
			path = path->forward;
		}
		way = way->next;
	}
	write(1, "\n", 1);
}

int			last_ant_not_finished(t_way *ways)
{
	t_way	*tmp;
	int		ret;

	ret = 1;
	tmp = ways;
	while (tmp)
	{
		if (tmp->path->forward->ant_name == -1 ||
		(tmp->path->forward == tmp->path->backward && tmp->ants <= 0))
			ret = 0;
		else
			return (1);
		tmp = tmp->next;
	}
	return (ret);
}

void		run_ants(t_general *farm, t_way *w, int i)
{
	t_path	*pwalk;

	while (last_ant_not_finished(farm->solutions->ways))
	{
		w = farm->solutions->ways;
		while (w)
		{
			pwalk = w->path;
			while (pwalk != w->path->backward)
			{
				if (pwalk->forward == w->path->backward && w->ants > 0)
				{
					pwalk->ant_name = ++i;
					w->ants--;
				}
				else if (pwalk->forward == w->path->backward && w->ants <= 0)
					pwalk->ant_name = -1;
				else
					pwalk->ant_name = pwalk->forward->ant_name;
				pwalk = pwalk->forward;
			}
			w = w->next;
		}
		print_ways(farm, 0);
	}
}
