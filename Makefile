# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egiant <egiant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/26 21:15:02 by egiant            #+#    #+#              #
#    Updated: 2019/10/25 18:45:38 by egiant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

NAME = lem-in

LIBPRDIR = libftprintf
LIBDIR = libftprintf/libft
FLAGS = -g -Wall -Wextra -Werror
HEADER = -I headers/ -I $(LIBPRDIR)/headers -I $(LIBDIR)/headers

OBJ_DIR = objectives/
SRC_DIR = sources/

SRCS =	main.c initialization.c get_info.c make_rooms_hash_table.c hash.c program_end.c \
		save_room.c save_links.c algorithm.c suurballe.c copy.c bellman_ford.c \
		handle_ways.c graph_recovery.c find_crossover.c run_ants.c\
		handle_ways2.c

OBJS 	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) | mklibpr
	
	gcc $(FLAGS) $(OBJS) -L $(LIBPRDIR) -lftprintf $(HEADER) -o $(NAME)

$(OBJS) : $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@ $(HEADER)

mklibpr:
		@make -C $(LIBPRDIR) --no-print-directory

clean:
			@/bin/rm -f $(OBJS)
			@rm -rf $(OBJ_DIR)
			@make clean -C $(LIBPRDIR) --no-print-directory

fclean: 	clean
			@/bin/rm -f $(NAME)
			@make fclean -C $(LIBPRDIR) --no-print-directory

re: 		fclean all