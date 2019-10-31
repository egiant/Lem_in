/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:14:03 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:37:19 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			distribute_ants(t_general *farm, t_solution *sol, int max_len)
{
	int			n;
	int			s;
	t_way		*tmp;

	s = max_len - 1;
	n = farm->n_ants;
	tmp = sol->ways;
	while (tmp && n > 0 && sol->n_ways != 1)
	{
		if (tmp->on)
		{
			tmp->ants = (n < max_len - tmp->len) ? n : max_len - tmp->len;
			n -= tmp->ants;
		}
		tmp = tmp->next;
	}
	s += (n % sol->n_ways == 0) ? n / sol->n_ways : n / sol->n_ways + 1;
	tmp = sol->ways;
	while (n-- > 0)
	{
		++tmp->ants;
		tmp = (tmp->next) ? tmp->next : sol->ways;
	}
	sol->steps = s;
}

void			count_steps(t_general *farm, t_solution *sol)
{
	int			max_len;
	int			valid_space;
	t_way		*tmp;

	valid_space = 0;
	tmp = sol->ways;
	max_len = tmp->len;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->len > max_len)
			max_len = tmp->len;
		tmp = tmp->next;
	}
	tmp = sol->ways;
	while (tmp)
	{
		valid_space += max_len - tmp->len;
		tmp = tmp->next;
	}
	distribute_ants(farm, sol, max_len);
}

int				compare_solutions(t_general *farm)
{
	t_solution	*s_tmp;
	t_way		*w_tmp;
	t_way		*w_ptr;

	if (!farm->solutions || !farm->solutions->next)
		return (1);
	else if (farm->solutions->steps < farm->solutions->next->steps)
		return (1);
	else
	{
		s_tmp = farm->solutions;
		w_tmp = s_tmp->ways;
		while (w_tmp)
		{
			w_ptr = w_tmp->next;
			free_way(w_tmp, w_tmp->path);
			w_tmp = w_ptr;
		}
		farm->solutions = farm->solutions->next;
		free(s_tmp);
		return (0);
	}
}

int				algorithm(t_general *farm)
{
	while (compare_solutions(farm))
	{
		if (farm->solutions)
			suurballe(farm);
		if (!(bellman_ford(farm)))
			break ;
		get_shortest_way(farm);
		if (!farm->solutions->next)
			clean_queue(farm);
		count_steps(farm, farm->solutions);
	}
	if (!farm->solutions)
		program_end(farm, 1, NULL);
	ft_printf("%s\n", farm->map);
	run_ants(farm, farm->solutions->ways, 0);
	return (1);
}
