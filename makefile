# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: praders <praders@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 12:09:56 by praders           #+#    #+#              #
#    Updated: 2025/11/12 15:31:53 by praders          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT_DIR = ./libraries/libft
MLX_DIR = ./libraries/minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

SRCS = cub3d.c exec/cub_init_everything.c exec/cub_error.c exec/cub_hook.c \
exec/cub_pixel.c exec/cub_move_player.c exec/cub_ray_cast.c exec/cub_ray_cast_utils.c \
exec/cub_ray_cast_cf.c exec/cub_sprite_rendering.c exec/cub_move_enemy.c \
exec/cub_doors.c exec/cub_coins.c exec/cub_draw_screen.c exec/cub_draw_levels.c\
exec/cub_check_wall.c exec/cub_sprite_rendering_utils.c\
\
parsing/parsing.c parsing/parsing_utils.c parsing/parse_set_values.c \
parsing/parse_map_utils.c parsing/parse_map_matrix.c parsing/parse_header.c \
parsing/parse_header_utils.c parsing/parse_flood_fill.c parsing/parse_file.c \
\
game_features/lvls/cub_lvls.c game_features/lvls/cub_lvls_set_values.c\
game_features/lvls/cub_lev_1a5.c game_features/lvls/cub_lev_6a10.c game_features/lvls/cub_lvls_utils.c\
game_features/lvls/cub_initiate_lvl.c \
game_features/mouse/mouse_move.c game_features/mouse/mouse_clicks.c \
game_features/mouse/mouse_click_lvls.c \
\
game_features/minimap/minimap.c game_features/minimap/minimap_draws.c \
game_features/minimap/minimap_icons.c game_features/minimap/minimap_utils.c \
game_features/minimap/minimap_compass.c \
game_features/hud/bitmap.c game_features/hud/bitmap_utils.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Ilibraries -Ilibraries/minilibx-linux
AR = ar rcs

GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
PURPLE = \033[0;35m
WHITE = \033[0;37m
RESET = \033[0m
BOLD_GREEN = \033[1;32m
BOLD_BLUE = \033[1;34m
BOLD_RED = \033[1;31m
BOLD_YELLOW = \033[1;33m
BOLD_MAGENTA = \033[1;35m
BOLD_CYAN = \033[1;36m
BOLD_WHITE = \033[1;97m

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "$(CYAN)Compilando libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓ libft compilada!$(RESET)"

$(MLX):
	@echo "$(CYAN)Compilando MinilibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓ MinilibX compilada!$(RESET)"

$(OBJ_DIR) $(OBJ_DIR)/exec:
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)                             # <-- cria subpastas conforme necessário
	@echo "$(BOLD_BLUE)Compilando $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/exec/%.o: exec/%.c | $(OBJ_DIR)/exec
	@echo "$(BOLD_BLUE)Compilando $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo ""
	@echo "$(BOLD_BLUE)   ██████╗██╗   ██╗██████╗ $(BOLD_CYAN) ██████╗ ██████╗ $(RESET)"
	@echo "$(BOLD_BLUE)  ██╔════╝██║   ██║██╔══██╗ $(BOLD_CYAN)╚════██╗██╔══██╗$(RESET)"
	@echo "$(BOLD_BLUE)  ██║     ██║   ██║██████╔╝ $(BOLD_CYAN) █████╔╝██║  ██║$(RESET)"
	@echo "$(BOLD_BLUE)  ██║     ██║   ██║██╔══██╗ $(BOLD_CYAN) ╚═══██╗██║  ██║$(RESET)"
	@echo "$(BOLD_BLUE)  ╚██████╗╚██████╔╝██████╔╝ $(BOLD_CYAN)██████╔╝██████╔╝$(RESET)"
	@echo "$(BOLD_BLUE)   ╚═════╝ ╚═════╝ ╚═════╝ $(BOLD_CYAN) ╚═════╝ ╚═════╝ $(RESET)"
	@echo "$(BOLD_MAGENTA)  ╔══════════════════════════════════════╗$(RESET)"
	@echo "$(BOLD_MAGENTA)  ║  🎮  Raycasting Engine Ready!  🎮    ║$(RESET)"
	@echo "$(BOLD_MAGENTA)  ╚══════════════════════════════════════╝$(RESET)"

mlx_download:
	@if [ ! -d $(MLX_DIR) ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	else \
		echo "MinilibX já existe em $(MLX_DIR)"; \
	fi

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@echo "$(YELLOW)✗ Objetos limpos!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@echo "$(RED)✗ Tudo limpo!$(RESET)"

re: fclean all

.PHONY: all clean fclean re mlx_download