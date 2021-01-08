NAME		=	cub3d.out
LIBFT		=	libft.a
CCF			=	@gcc $(CFLAGS)
MKLIB		=	@ar rc
RM			=	@rm -f
CFLAGS		=	-Wall -Wextra -Werror -c
SRCS		=	main.c
OBJS		=	$(SRCS:.c=.o)
LIB_DIR		=	./libft/
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
			@cp $(LIB_DIR)$(LIBFT) $(NAME)
			$(MKLIB) $(NAME) $(OBJS)
			@echo $(NAME) compilled

%.o:		%.c $(HDR)
			$(CCF) -I $(HDR) -o $@ -c $<
			@echo $@ compilled


.PHONY:		all clean fclean re so bonus $(NAME)
