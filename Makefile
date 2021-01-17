NAME		=	cub3d
LIBFT		=	libft.a
CCF			=	@gcc $(CFLAGS)
MKLIB		=	@ar rc
RM			=	@rm -f
CFLAGS		=	-Wall -Wextra -Werror
SRCS		=	main.c Parser/parser.c Parser/param_parser.c Parser/map_parser.c GNL/get_next_line.c \
				GNL/get_next_line_utils.c Parser/parser_utils.c Render/render.c
OBJS		=	$(SRCS:.c=.o)
LIB_DIR		=	./libft/
MLIB_DIR	=	./minilibx_mms/
MNAME		=	libmlx.dylib

HDR			=	cub3d.h

all:		$(NAME)

clean:
			@make clean -C $(LIB_DIR)
			$(RM) $(OBJS)
			@echo objs deleted

fclean:		clean
			@make fclean -C $(LIB_DIR)
			$(RM) $(NAME)
			@echo $(NAME) deleted

re:			fclean all

$(NAME):	$(OBJS)
			@make bonus -C $(LIB_DIR)
			@make -C $(MLIB_DIR)
			@cp $(MLIB_DIR)$(MNAME) $(MNAME)
			$(CCF) $(OBJS) $(LIB_DIR)$(LIBFT) -L$(MLIB_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
			@echo $(NAME) compilled

%.o:		%.c $(HDR)
			$(CCF) -I $(HDR) -o $@ -c $<
			@echo $@ compilled


.PHONY:		all clean fclean re so bonus $(NAME)
