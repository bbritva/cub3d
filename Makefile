NAME			=	cub3D
LIBFT			=	libft.a
CCF				=	@gcc $(CFLAGS)
MKLIB			=	@ar rc
RM				=	@rm -f
CFLAGS			=	-Wall -Wextra -Werror -g
PARSER_PATH		=	./parser/
RENDER_PATH		=	./render/
PARSERB_PATH	=	./parser_bonus/
RENDERB_PATH	=	./render_bonus/
SRCS			=	main.c GNL/get_next_line.c GNL/get_next_line_utils.c \
					$(addprefix $(PARSER_PATH), parser.c param_parser.c map_parser.c map_split.c parser_utils.c \
					map_checker.c get_sprites.c) \
					$(addprefix $(RENDER_PATH), render_utils.c drawers.c sprites_handler.c freeing.c \
					drawers_utils.c draw_sprites.c hooks.c movers.c render.c raycast.c get_shot.c)
SRCSB			=	main_bonus.c GNL/get_next_line.c GNL/get_next_line_utils.c \
					$(addprefix $(PARSERB_PATH), parser.c param_parser.c map_parser.c map_split.c parser_utils.c \
					map_checker.c get_sprites.c) \
					$(addprefix $(RENDERB_PATH), render_utils.c drawers.c sprites_handler.c freeing.c \
					drawers_utils.c draw_sprites.c hooks.c movers.c render.c raycast.c get_shot.c draw_hud.c)
OBJSB			=	$(SRCSB:.c=.o)
OBJS			=	$(SRCS:.c=.o)
LIB_DIR			=	./libft/
MLIB_DIR		=	./minilibx_mms/
MNAME			=	libmlx.dylib
HDRB			=	./includes_bonus/
HDR				=	./includes/

all:			$(NAME)

clean:
				@make clean -C $(LIB_DIR)
				@make clean -C $(MLIB_DIR)
				$(RM) $(OBJS)
				$(RM) $(OBJSB)
				@echo objs deleted

fclean:			clean
				@make fclean -C $(LIB_DIR)
				$(RM) $(NAME)
				@echo $(NAME) deleted
				$(RM) $(MNAME)
				@echo $(MNAME) deleted

re:				fclean all

$(NAME):		$(OBJS) $(HDR) $(LIB_DIR)$(LIBFT)
				@make bonus -C $(LIB_DIR)
				@make -C $(MLIB_DIR)
				@cp $(MLIB_DIR)$(MNAME) $(MNAME)
				$(CCF) $(OBJS) -I -Iincludes -L$(LIB_DIR) -lft -L$(MLIB_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
				@echo $(NAME) compilled

bonus:			$(OBJSB) $(HDRB)
				@make bonus -C $(LIB_DIR)
				@make -C $(MLIB_DIR)
				@cp $(MLIB_DIR)$(MNAME) $(MNAME)
				$(CCF) $(OBJSB) -I -Iincludes -L$(LIB_DIR) -lft -L$(MLIB_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
				@echo $(NAME) compilled

%.o:			%.c $(HDR)
				$(CCF) -I -Iincludes -c $< -o $@
				@echo $@ compilled

norm:
				norminette main.c cub3d.h render/*c render/*h parser/*c parser/*h libft/*c libft/*h GNL/*c GNL/*h
git:
				git add main.c cub3d.h Makefile render/*c render/*h parser/*c parser/*h libft/*c libft/Makefile libft/*h \
				GNL/*c GNL/*h minilibx_mms/* render/textures/*xpm map.cub

.PHONY:			all clean fclean re so bonus norm $(NAME)
