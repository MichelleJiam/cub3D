# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mjiam <mjiam@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/05 18:36:52 by mjiam         #+#    #+#                  #
#    Updated: 2020/06/18 17:26:01 by mjiam         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= 	cub3D

SRC		= 	bmp.c check.c colour.c config.c cub3d.c exit.c init.c input.c \
			map.c parser.c raycaster.c render.c sort.c sprite.c \
			ui.c utils.c utils2.c

GNL		=	gnl/get_next_line.c gnl/get_next_line_utils.c

SDIR 	= 	$(addprefix src/, $(SRC))

SOBJ	= 	$(SDIR:.c=.o) $(GNL:.c=.o)

ifdef WITH_BONUS
OBJ 	= 	$(SOBJ)
else
OBJ 	= 	$(SOBJ)
endif

HEADER	=	cub3d.h

CC		= 	gcc

FLAGS	= 	-Wall -Wextra -Werror -O3

ifdef DEBUG
FLAGS	+=	-fsanitize=address -fno-omit-frame-pointer
endif

# for Mac compilation
LIB		= 	-framework OpenGL -framework AppKit

MLX		= 	-L$(MLXDIR) -lmlx

DYLIB	=	libmlx.dylib

MLXDIR	=	minilibx

# for Linux compilation
# LIB		= 	-Lmlx_linux -lmlx -lXext -lX11 -lm -lz -AppKit
# MLX		= 	-L$(MLXDIR) -lmlx
# DYLIB	=	libmlx.a
# MLXDIR	= 	mlx_linux

# COLORS
BLUE	= 	\033[38;5;27m
CYAN	= 	\033[38;5;51m
PINK	=	 \033[38;5;211m
GREEN	= 	\033[38;5;72m
TURQ	= 	\033[38;5;37m
WHITE	= 	\033[38;5;15m
YELLOW	= 	\033[38;5;220m
C		=	\033[38;5;
O		=	72
L		=	m
SHIFT	=	$(eval O=$(shell echo $$((($(O)%15)+1))))

LBOR	=	"▌│█║▌║▌║ "
RBOR	= 	" ║▌║▌║█│▌"

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	@$(MAKE) subzero
	@$(CC) $(FLAGS) $(OBJ) $(MLX) $(LIB) -o $(NAME)
	@echo "\n\t   $(TURQ)$(LBOR)Game compiled$(RBOR)$(WHITE)\n"

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

$(MLX):
	@make -C $(MLXDIR)
	@cp -rf $(MLXDIR)/$(DYLIB) .
	@echo "\n\t   $(TURQ)$(LBOR)minilibx compiled$(RBOR)$(WHITE)\n"

debug: $(OBJ)
	@echo "\n\t   $(GREEN)$(LBOR)Debug mode$(RBOR)$(WHITE)\n"
	@$(MAKE) DEBUG=1

bonus: $(OBJ)
	@echo "\n\t   $(YELLOW)$(LBOR)Bonus mode$(RBOR)$(WHITE)\n"
	@$(MAKE) WITH_BONUS=1 all

clean:
	@echo "\n\t   $(PINK)$(LBOR)Cleaning$(RBOR)$(WHITE)\n"
	@rm -rf $(OBJ)
	@make -C $(MLXDIR) clean

fclean: clean
	@echo "\n\t   $(CYAN)$(LBOR)Clean af$(RBOR)$(WHITE)\n"
	@rm -rf $(NAME)
	@rm -rf libmlx.dylib
	@rm -rf screenshot.bmp

re:
	@echo "\n\t   $(BLUE)$(LBOR)Aww here we go again$(RBOR)$(WHITE)\n"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re

subzero:
	@echo "$(C)$(O)$(L) ______     __  __     ______     ______     _____    ";
	@echo "$(C)$(O)$(L)/\  ___\   /\ \/\ \   /\  == \   /\___  \   /\  __ \  ";
	$(SHIFT)
	@echo "$(C)$(O)$(L)\ \ \____  \ \ \_\ \  \ \  __<   \/_\___ \  \ \ \_\ \ ";
	@echo "$(C)$(O)$(L) \ \_____\  \ \_____\  \ \_____\  /\______\  \ \____/ ";
	$(SHIFT)
	@echo "$(C)$(O)$(L)  \/_____/   \/_____/   \/_____/  \/______/   \/____/ ";
	@echo "$(C)$(O)$(L)                                                      ";
