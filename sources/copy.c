/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:12:36 by egiant            #+#    #+#             */
/*   Updated: 2019/10/24 17:27:09 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_link		*copy_links(t_general *farm, t_link *copy_link,
							t_link *original_link)
{
	t_link	*tmp;

	tmp = copy_link;
	while (tmp->nxt)
		tmp = tmp->nxt;
	if (!(tmp->nxt = (t_link *)malloc(sizeof(t_link))))
		program_end(farm, 0, NULL);
	tmp = tmp->nxt;
	tmp->name = ft_strdup(original_link->name);
	tmp->weight = original_link->weight;
	tmp->on = 1;
	tmp->nxt = NULL;
	return (tmp);
}

t_room		*copy_room(t_general *farm, t_room *original)
{
	t_room	*copy;

	if (!(copy = (t_room*)malloc(sizeof(t_room))))
		program_end(farm, 0, NULL);
	copy->name = ft_strdup(original->name);
	copy->place = original->place;
	copy->next = NULL;
	copy->begin_links = NULL;
	copy->same_hash = NULL;
	copy->room_copy = NULL;
	copy->link_count = original->link_count;
	copy->prev = NULL;
	copy->queue = NULL;
	copy->in_q = 0;
	copy->bf = 0;
	return (copy);
}
