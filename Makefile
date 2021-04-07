NAME			=	cub3D
LIBFT			=	libft.a
CCF				=	@gcc $(CFLAGS)
MKLIB			=	@ar rc
RM				=	@rm -f
CFLAGS			=	-Wall -Wextra -Werror -O2
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
					drawers_utils.c draw_sprites.c hooks.c movers.c render.c raycast.c get_shot.c draw_hud.c \
					draw_minimap.c draw_sky.c draw_txtr_floor.c draw_gun.c draw_sprites_utils.c z_movers.c doors.c)
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

$(NAME):		$(OBJS) $(HDR)
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

%.o:			%.c $(HDR) $(HDRB)
				$(CCF) -I -Iincludes -c $< -o $@
				@echo $@ compilled

norm:
				norminette main.c $(RENDER_PATH)*c $(HDR)*h $(PARSER_PATH)*c $(LIB_DIR)*c $(LIB_DIR)*h GNL/*c GNL/*h

norm_b:
				norminette main_bonus.c $(RENDERB_PATH)*c $(HDRB)*h $(PARSERB_PATH)*c $(LIB_DIR)*c $(LIB_DIR)*h GNL/*c GNL/*h

git:			fclean
				git add main.c Makefile $(RENDER_PATH)*c $(HDR)*h $(PARSER_PATH)*c $(LIB_DIR)*c $(LIB_DIR)Makefile $(LIB_DIR)*h \
				GNL/*c GNL/*h minilibx_mms/* resources/textures/*xpm map.cub

git_b:			git
				git add main_bonus.c Makefile $(RENDERB_PATH)*c $(HDRB)*h $(PARSERB_PATH)*c resources/sounds/* map_b.cub

.PHONY:			all clean fclean re so bonus norm
#for commit
