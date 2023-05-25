# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 02:58:29 by bkamal            #+#    #+#              #
#    Updated: 2023/05/25 17:18:58 by hcharef          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = cub3D
CC       = cc
CFLAGS   = -Wall -Wextra -Werror #-fsanitize=address -g3 
 
PRSDIR   = sources/parsing
2DMDIR	 = sources/2Dmap
OBJDIR   = objects
INCDIR   = includes
SRCP	 = error_checks.c\
			checks_utils.c\
			map_loops_utils.c\
			darr_utils.c\
			map_loops.c\
			features_checks.c\
			features_utils.c\
			get_next_line.c
			
 SRC2	 = draw.c\
			mlx_func.c\
			 myfun.c\
 			 file.c\
			mouvements.c\
			utils.c\
			castray.c\
			3d.c\
			
OBJP     = $(addprefix $(OBJDIR)/,$(notdir $(SRCP:.c=.o)))
OBJ2D    = $(addprefix $(OBJDIR)/,$(notdir $(SRC2:.c=.o)))
INC		 = -I$(INCDIR)

#NEEDED FOR MLX FUNCTIONS
#2DMAP AND 3DWALLS/VISION
MLX		 = -lmlx -framework OpenGL -framework AppKit

RM       = rm -rf

all: $(NAME)

$(OBJDIR)/%.o: $(PRSDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

#2DMAP
$(OBJDIR)/%.o: $(2DMDIR)/%.c | $(OBJDIR)
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@
	@ echo "Compiling object files..."

# PARSING
# $(NAME): $(OBJP)
# 	@ $(MAKE) -C ./libft/
# 	$(CC) $(CFLAGS) $(OBJP) ./libft/libft.a -o $(NAME)

# 2DMAP
$(NAME): $(OBJ2D) $(OBJP)
	@ $(MAKE) -C ./libft/
	@ $(CC) $(CFLAGS) $(OBJ2D) $(OBJP) $(MLX) ./libft/libft.a -o $(NAME)


$(OBJDIR):
	@ mkdir -p $@

clean:
	@ $(RM) $(OBJDIR)
	@ $(MAKE) -C ./libft/ clean

fclean:	clean
	@ $(RM) $(NAME)
	@ $(MAKE) -C ./libft/ fclean

re:		fclean all

ARG		 = ./maps/map1.cub
run: re
	./cub3D $(ARG)

# Convenient for parsing and later on 
# $(ARG)

.PHONY: all clean fclean re