NAME	=	Cub3D

MLX		=	minilibx-linux

MLXFLAGS	=	-L $(MLX)/ -lmlx -lXext -lX11 -lm

LIBFT	=	libft

SRCS	=	sources/bitmap.c \
			sources/check_walls.c \
			sources/draw.c \
			sources/draw_forms.c \
			sources/errors_exits/code_error.c \
			sources/errors_exits/exit.c \
			sources/errors_exits/exit_two.c \
			sources/errors_exits/handle_error.c \
			sources/errors_exits/handle_error_two.c \
			sources/floor_cast.c \
			sources/initialisation.c \
			sources/initilialisation_two.c \
			sources/keys/handle_camera.c \
			sources/keys/handle_move.c \
			sources/keys/key_press.c \
			sources/keys/key_press_two.c \
			sources/main.c \
			sources/process.c \
			sources/raycastin_utils.c \
			sources/raycasting.c \
			sources/read_file.c \
			sources/read_file_struct.c \
			sources/read_map.c \
			sources/sprite.c \
			sources/sprite_list.c \
			sources/utils.c \
			sources/utils/assign_struct.c \
			sources/utils/partials.c \
			sources/utils/read_file_utils.c \
			includes/Get-Next-Line/get_next_line.c \
			includes/Get-Next-Line/get_next_line_utils.c

SRCS_BONUS = 	bonus/bonus_init.c \
				bonus/bonus_utils.c \
				bonus/bonus_gun.c \
				bonus/bonus_minimap.c

OBJSRCS			=	$(SRCS:.c=.o)
OBJSRCSBONUS	=	$(SRCS_BONUS:.c=.o)

$(NAME) : $(OBJSRCS) $(OBJSRCSBONUS)
	@echo "\033[33m[Clean old Cub3D...]"
	@rm -rf Cub3D
	@echo "\033[32m[Compile Libft...]"
	@$(MAKE) -C $(LIBFT) 
	@echo "\033[32m[Compile MLX...]"
	@$(MAKE) -C $(MLX)
	@echo "\033[32m[Compile Cub3D...]"
	@gcc -fsanitize=address  $(OBJSRCSBONUS) $(OBJSRCS) -I./sources/header.h -Wall -Wextra -Werror $(MLX)/libmlx.a $(MLXFLAGS)  $(LIBFT)/libft.a -o $(NAME)
	@echo "\033[32m[Success !]"

all : $(NAME)

clean :
	rm -rf $(OBJSRCS) $(OBJSRCSBONUS)
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(MLX)

fclean : clean
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) clean $(MlX)
	rm -rf $(NAME)
	rm -rf Cub3D.bmp

re : fclean all

bonus : $(NAME)

.PHONY : all fclean re
