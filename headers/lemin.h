/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:46:01 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:39:54 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <libftprintf.h>

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_link
{
	char			*name;
	int				weight;
	struct s_link	*nxt;
	int				on;
	int				in_way;
}					t_link;

typedef struct		s_room
{
	char			*name;
	t_coord			place;
	struct s_room	*next;
	t_link			*begin_links;
	struct s_room	*same_hash;
	struct s_room	*room_copy;
	int				link_count;

	struct s_room	*prev;
	struct s_room	*queue;
	int				in_q;
	int				bf;
}					t_room;

typedef struct		s_path
{
	char			*name;
	int				ant_name;
	struct s_path	*forward;
	struct s_path	*backward;
}					t_path;

typedef struct		s_way
{
	int				len;
	int				ants;
	int				on;
	struct s_way	*next;
	t_path			*path;
}					t_way;

typedef struct		s_sol
{
	int				index;
	int				n_ways;
	int				steps;
	struct s_sol	*next;
	t_way			*ways;
}					t_solution;

typedef struct		s_general
{
	long			n_ants;
	int				n_rooms;
	char			*map;
	t_room			*begin_rooms;
	t_room			**rooms;
	t_room			*start;
	t_room			*end;
	t_solution		*solutions;
}					t_general;

void				init_farm(t_general *farm);
void				init_room(t_room *room_list, char **array);
void				init_link(t_link *links_list, char *link_name);
void				init_solution(t_solution *solutions);
int					get_info(t_general *farm);
int					save_room(t_general *farm, char *line, t_coord *point);
int					save_links(t_general *farm, char *line);
void				make_rooms_hash_table(t_general *farm);
int					hash(int size, char *name);
int					algorithm(t_general *farm);
t_room				*copy_room(t_general *farm, t_room *original);
t_link				*copy_links(t_general *farm, t_link *copy_link,
									t_link *original_link);
void				suurballe(t_general *farm);
int					bellman_ford(t_general *farm);
void				clean_queue(t_general *farm);
void				get_shortest_way(t_general *farm);
int					find_crossover(t_general *farm, t_way *way);
void				graph_recovery(t_general *farm, t_solution *prev_sol);
void				program_end(t_general *farm, int err, char **arr);
void				run_ants(t_general *farm, t_way *w, int i);
void				free_way(t_way *way_tmp, t_path *path_tmp);
int					check_is_it_copy(t_room *cur_room, char *link_name);
void				find_new_ways(t_general *farm, t_link *next_room);
void				in_way_recover(t_link *next_room);
t_way				*create_way(t_general *farm);

#endif
