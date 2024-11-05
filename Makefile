CC = cc 
FLAGS = -Wall -Wextra -Werror
READLINE_FLAG = -lreadline
NAME = minishell
SRC = src/main.c
LIBFT_PATH=libft/ 
LIBFT=libft.a
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(LIBFT): 
	@make -C $(LIBFT_PATH)
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(READLINE_FLAG) -o $(NAME)

clean : 
		@make clean -C $(LIBFT_PATH)
		rm -rf $(OBJ)
fclean : clean
		@make fclean -C $(LIBFT_PATH)
		rm -rf $(NAME)
re : fclean all
.PHONY : all clean fclean re