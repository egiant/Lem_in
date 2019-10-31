/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 20:25:07 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:37:31 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			save_map(t_general *farm, char *line)
{
	char		*tmp;

	if (!farm->map)
	{
		if (!(farm->map = ft_strdup(line)))
		{
			ft_strdel(&line);
			program_end(farm, 0, NULL);
		}
	}
	else
	{
		tmp = farm->map;
		if (!(farm->map = ft_strcjoin(farm->map, line, '\n')))
		{
			free(tmp);
			program_end(farm, 0, NULL);
		}
		free(tmp);
	}
}

int				save_ants(t_general *farm, char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) || (i == 0 && line[i] == 48))
			return (0);
		++i;
	}
	farm->n_ants = ft_atoi_long(line);
	if (farm->n_ants > INT_MAX || farm->n_ants < INT_MIN)
		return (0);
	return (1);
}

int				save_point(t_general *farm, char *line, t_coord *point)
{
	if (point->x == 1 || point->x == 1)
		return (0);
	if (ft_strcmp("##start", line) == 0)
	{
		if (farm->start)
			return (0);
		point->x = 1;
	}
	if (ft_strcmp("##end", line) == 0)
	{
		if (farm->end)
			return (0);
		point->y = 1;
	}
	return (1);
}

void			fill_the_farm(t_general *farm, char *line, t_coord *point)
{
	int			ret;

	ret = 1;
	if (line[0] == '\0')
	{
		ft_strdel(&line);
		program_end(farm, 1, NULL);
	}
	if (!farm->map)
		ret = save_ants(farm, line);
	else if (ft_strstr(line, "#"))
		ret = save_point(farm, line, point);
	else if (!ft_strstr(line, "-") && !ft_strstr(line, "##"))
		ret = save_room(farm, line, point);
	else
		ret = save_links(farm, line);
	save_map(farm, line);
	if (!ret)
		program_end(farm, 1, NULL);
}

int				get_info(t_general *farm)
{
	int			gnl;
	char		*line;
	t_coord		point;

	point.x = 0;
	point.y = 0;
	while ((gnl = get_next_line(0, &line)) > 0)
	{
		fill_the_farm(farm, line, &point);
		ft_strdel(&line);
	}
	if (gnl < 0)
		program_end(farm, 0, NULL);
	free(line);
	if (!farm->begin_rooms || !farm->start || !farm->end
		|| !farm->start->begin_links || !farm->end->begin_links)
		program_end(farm, 1, NULL);
	line = farm->map;
	farm->map = ft_strjoin(farm->map, "\n");
	free(line);
	return (1);
}
