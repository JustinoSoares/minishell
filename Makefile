CC = cc 
FLAGS = -Wall -Wextra -Werror -g3
READLINE_FLAG = -lreadline
NAME = minishell
SRC = src/main.c src/utils.c src/echo.c src/functions.c src/free.c \
		src/aux_functions.c src/aux_echo.c src/error.c src/env.c src/cd.c \
		src/pwd.c src/export.c src/export2.c src/string_init/expanded.c \
		src/string_init/filter_string.c src/string_init/get_string.c \
		src/string_init/insert_str.c
LIBFT_PATH=libft/
LIBFT=libft.a
OBJ = $(SRC:.c=.o)
all: $(LIBFT) $(NAME)
$(LIBFT): 
		@make -C $(LIBFT_PATH)
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(READLINE_FLAG) $(LIBFT_PATH)libft.a -o $(NAME)

clean : 
		@make clean -C $(LIBFT_PATH)
		rm -rf $(OBJ)
fclean : clean
		@make fclean -C $(LIBFT_PATH)
		rm -rf $(NAME)
re : fclean all
.PHONY : all clean fclean re