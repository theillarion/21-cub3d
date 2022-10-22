NAME		=	cub3d
NAME_D		=	$(NAME)_debug

CC 				=	cc
CC_FLAGS		=	-Wall -Werror -Wextra
CC_FLAGS_D		=	-g

LINK			=	

SRCS_DIR		=	srcs
SRCS			=	action.c destroy.c draw.c events.c exit.c fill.c image_utilities.c init.c main.c mlx_utilities.c point_utilities.c render_utilities.c \
					render.c srgb_utilities.c temp_map.c map.c get_next_line.c map_parse_utilities.c map_utilities.c map_params_utilities.c map_params.c \
					map_common_utilities.c map_params_color_utilities.c utilities.c

HEADERS_DIR		=	includes
ifeq (${HEADERS_DIR},)
        HEADERS_DIR = ./
endif
HEADERS			=	$(addprefix $(HEADERS_DIR)/,\
					cub3d.h keys.h\
					)

OBJS_DIR		=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/,$(SRCS:%.c=%.o))
OBJS_D			=	$(addprefix $(OBJS_DIR)/,$(SRCS:%.c=%_debug.o))

LIBFT_NAME		=	libft.a
LIBFT_NAME_D	=	libft_debug.a
LIBFT_NAME_S	=	ft
LIBFT_NAME_S_D	=	$(LIBFT_NAME_S)_debug
LIBFT_PATH		=	libs/libft
LIBFT			=	$(LIBFT_PATH)/$(LIBFT_NAME)
LIBFT_D			=	$(LIBFT_PATH)/$(LIBFT_NAME_D)

LIBMLX_NAME		=	libmlx.a
LIBMLX_NAME_S	=	mlx

CC_FLAGS_LINK	=	-L$(LIBFT_PATH) -l$(LIBFT_NAME_S) -L$(LIBMLX_PATH) -l$(LIBMLX_NAME_S)
CC_FLAGS_LINK_D	=	-L$(LIBFT_PATH) -l${LIBFT_NAME_S_D} -L$(LIBMLX_PATH) -l$(LIBMLX_NAME_S)

OS				=	${shell uname -s}

ifeq ($(OS),Darwin)
	LIBMLX_PATH		=	libs/minilibx-macos
	CC_FLAGS		+=	-D CURRENT_OS_MACOS
	CC_FLAGS_LINK	+=	-framework OpenGL -framework AppKit
	CC_FLAGS_LINK_D	+=	-framework OpenGL -framework AppKit
else
	LIBMLX_PATH		=	libs/minilibx-linux
	CC_FLAGS		+=	-D CURRENT_OS_LINUX
	CC_FLAGS_LINK	+=	-lXext -lX11 -lm -lz
	CC_FLAGS_LINK_D	+=	-lXext -lX11 -lm -lz
endif

LIBMLX			=	$(LIBMLX_PATH)/$(LIBMLX_NAME)

INCLUDES		=	-Iincludes -I$(LIBMLX_PATH) -I$(LIBFT_PATH)
RM				=	rm -rf

NOCOLOR			=	\033[0m
COLOR_LGREEN	=	\033[92m
COLOR_LYELLOW	=	\033[93m
COLOR_LCYAN		=	\033[96m
NEWLINE			=	\n

$(OBJS_DIR)/%.o			:	$(SRCS_DIR)/%.c $(HEADERS)
							@mkdir -p $(OBJS_DIR) 
							@$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@
							@printf "$(COLOR_LCYAN)build object$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
							@printf "ready $(COLOR_LYELLOW)$@$(NOCOLOR)$(NEWLINE)"

$(OBJS_DIR)/%_debug.o	:	$(SRCS_DIR)/%.c $(HEADERS)
							@$(CC) $(CC_FLAGS_D) $(CC_FLAGS) $(INCLUDES) -c $< -o $@
							@printf "$(COLOR_LCYAN)build debug object$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
							@printf "ready $(COLOR_LYELLOW)$@$(NOCOLOR)$(NEWLINE)"

print-%  		: ; @echo $* = $($*)

all				:	$(NAME) $(NAME_D)
debug			:	$(NAME_D)
bonus			:	all

.PHONY			:	all debug bonus clean fclean re

$(NAME)			:	$(LIBMLX) $(LIBFT) $(OBJS)
					@$(CC) $(INCLUDES) $(LINK) $(OBJS) $(CC_FLAGS_LINK) -o $(NAME)
					@printf "$(COLOR_LCYAN)linking objects$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

$(NAME_D)		:	$(LIBMLX) $(LIBFT_D) $(OBJS_D)
					@$(CC) $(INCLUDES) $(LINK) $(OBJS_D) $(CC_FLAGS_LINK_D) -o $(NAME_D)
					@printf "$(COLOR_LCYAN)linking debug objects$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(NAME_D)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

$(LIBFT)		:
					@printf "$(COLOR_LCYAN)build $(LIBFT_NAME)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "cd $(COLOR_LYELLOW)$(LIBFT_PATH)$(NOCOLOR)$(NEWLINE)"
					@$(MAKE) -s -C $(LIBFT_PATH)
					@printf "$(COLOR_LCYAN)build $(LIBFT_NAME)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "cd $(COLOR_LYELLOW).$(NOCOLOR)$(NEWLINE)"
					@printf "$(COLOR_LCYAN)build $(LIBFT_NAME)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(LIBFT_NAME)$(NOCOLOR)$(NEWLINE)"
$(LIBFT_D)		:	
					@$(MAKE) -s debug -C $(LIBFT_PATH)
					@printf "$(COLOR_LCYAN)build $(LIBFT_NAME_D)$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(LIBFT_NAME_D)$(NOCOLOR)$(NEWLINE)"

$(LIBMLX)		:	
					@$(MAKE) -s -C $(LIBMLX_PATH)

clean			:
					@$(RM) $(OBJS) $(OBJS_D)
					@$(MAKE) -s clean -C $(LIBFT_PATH)
					@$(MAKE) -s clean -C $(LIBMLX_PATH)
					@printf "$(COLOR_LCYAN)$@$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

fclean			:	clean 
					@$(RM) $(NAME) $(NAME_D)
					@$(MAKE) -s fclean -C $(LIBFT_PATH)
					@printf "$(COLOR_LCYAN)full clean$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"

re				:	fclean all
					@printf "$(COLOR_LCYAN)rebuild all$(NOCOLOR) [$(COLOR_LGREEN)info$(NOCOLOR)]: "
					@printf "ready $(COLOR_LYELLOW)$(NAME)$(NOCOLOR) for $(COLOR_LYELLOW)$(OS)$(NOCOLOR)$(NEWLINE)"
