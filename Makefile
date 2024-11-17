CC = cc 
FLAGS = -Wall -Wextra -Werror
READLINE_FLAG = -lreadline
NAME = minishell
SRC = src/main.c src/utils.c src/export.c src/export2.c src/env.c 
LIBFT_PATH=libft/
LIBFT=libft.a
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(LIBFT): 
		@make -C $(LIBFT_PATH)
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(READLINE_FLAG) $(LIBFT_PATH)/libft.a -o $(NAME)

clean : 
		@make clean -C $(LIBFT_PATH)
		rm -rf $(OBJ)
fclean : clean
		@make fclean -C $(LIBFT_PATH)
		rm -rf $(NAME)
re : fclean all
.PHONY : all clean fclean re