/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:45:51 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 17:13:35 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				main(void)
{
	t_general	*farm;

	if (!(farm = (t_general*)malloc(sizeof(t_general))))
		program_end(farm, 0, NULL);
	init_farm(farm);
	if (!get_info(farm))
		program_end(farm, 1, NULL);
	algorithm(farm);
	program_end(farm, 0, NULL);
	free(farm);
	return (0);
}
