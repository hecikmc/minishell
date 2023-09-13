NAME			=	minishell

CC				=	gcc -g
CFLAGS			=	-Wall -Werror -Wextra -I "/Users/$(USER)/.brew/opt/readline/include/"
RM				=	rm -f

SRCS			=	src/minishell.c \
					src/executor/pipes.c \
					src/executor/pipe_utils.c \
					src/executor/signals.c \
					src/general_utils/error.c \
					src/general_utils/free.c \
					src/general_utils/split_minishell.c \
					src/general_utils/utils.c \
					src/parser/checker.c \
					src/parser/sintax_pipe.c \
					src/parser/utils_checker.c \
					src/parser/sintax_redirect.c \
					src/parser/get_input.c \
					src/parser/utils_getinput.c \
					src/parser/expand.c \
					src/builtins/built.c \
					src/builtins/echo.c \
					src/builtins/pwd.c \
					src/builtins/cd.c \
					src/builtins/export.c \
					src/builtins/unset.c \
					src/builtins/env.c \
					src/builtins/exit.c \

OBJS			=	$(SRCS:.c=.o)

LIBFT = libft/libft.a

%.o: %.c
				@$(CC) $(CFLAGS) -c $< -o $@

all:			$(LIBFT) $(NAME)

$(LIBFT):
				@make -C ./libft

$(NAME):		$(OBJS)
				@$(CC) $(FLAGS) $(LIBFT) $(OBJS) -L"/Users/$(USER)/.brew/opt/readline/lib/" -o $(NAME) -lreadline
				@echo "\n$(CYELLOW)$(NAME) $(PURPLE)-> $(CGREEN) compiled$(CRESET)"

clean:
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_B)
				@make -C ./libft clean
				@echo "${CYELLOW}${NAME} $(PURPLE)-> ${CRED} objects files were deleted.${CRESET}"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(NAME_B)
				@make -C ./libft fclean
				@echo "${CYELLOW}${NAME} $(PURPLE)-> ${CRED} was deleted.${CRESET}"

re:				fclean all

.PHONY:			all clean fclean re

#		COLORS		#
CYELLOW			=\033[1;33m
CGREEN			=\033[0;32m
CRED			=\033[0;91m
PURPLE			=\033[0;35m
CRESET			=\033[0m