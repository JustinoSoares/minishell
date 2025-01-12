CC = gcc -g
#-fsanitize=leak
#-fsanitize=address 
FLAGS = -Wall -Wextra -Werror
READLINE_FLAG = -lreadline
NAME = minishell
SRC = src/main.c src/utils.c src/echo.c src/functions.c src/free.c  src/redirection/redir.c src/redirection/redir2.c\
		src/redirection/redir_aux.c src/aux_functions.c src/aux_echo.c src/error.c src/env.c src/cd.c \
		src/pwd.c src/export/export.c src/export/export2.c  src/export/print_export.c src/export/aux_export.c\
		src/string_init/expanded.c src/string_init/filter_string.c src/string_init/get_string.c \
		src/string_init/insert_str.c src/string_init/aux_expanded.c src/string_init/ft_quotes.c \
		src/pipes.c src/functions_aux.c src/redirection/redirect_error.c

LIBFT_PATH=libft/
LIBFT=libft.a
OBJ = $(SRC:.c=.o)
all: $(LIBFT) $(NAME)
$(LIBFT): 
		@make -C $(LIBFT_PATH)
$(NAME): $(LIBFT) $(OBJ)
	$(CC)  $(FLAGS) $(OBJ) $(READLINE_FLAG) $(LIBFT_PATH)libft.a -o $(NAME)

clean : 
		@make clean -C $(LIBFT_PATH)
		rm -rf $(OBJ)
fclean : clean
		@make fclean -C $(LIBFT_PATH)
		rm -rf $(NAME)
leak : re
		clear;
		valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./leak_supression.supp ./minishell
re : fclean all
.PHONY : all clean fclean re