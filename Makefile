#PATHS
APP				= ./app
BIN				= ./bin
SRC				= ./src
OBJ				= ./obj
LIB				= ./lib
MAIN			= $(APP)/main.c
FOLDERS		= $(BIN) $(OBJ)
LIBFT			= $(LIB)/libft/bin/libft.a
INCLUDE		= ./include
NAME			= $(BIN)/minishell

#VARIABLES
SRCS		= ft_str.c fk_fork_utils.c tml_functions.c fl_file.c \
			  ft_clear_memory.c ft_exit.c tml_clear_memory.c rd_redirection.c \
			  ft_error.c pp_pipe.c sa_sigaction.c sa_hooks.c vr_linked_list.c \
				vr_vars.c vr_replace.c ft_checks.c

OBJS		= $(addprefix $(OBJ)/,$(SRCS:%.c=%.o))
HEADER	= -I $(LIB)/libft/include -I $(INCLUDE)
LIBS		= -lreadline -lcurses -L $(LIB)/libft/bin -lft
FLAGS		= -Wall -Wextra -Werror -g3
CC			= cc
VAL_FLAGS	= --leak-check=full --show-leak-kinds=definite -s

all: $(FOLDERS) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(MAIN)
	$(CC) $(FLAGS) $(HEADER) $(OBJS) $(MAIN) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(FLAGS) $(HEADER) $< -o $@

$(LIBFT):
	make -C $(LIB)/libft

$(FOLDERS):
	mkdir $@

run: all
	$(NAME)

test:
	gcc $(HEADER) test/main.c $(OBJS) -o test/main $(LIBS); ./test/main

check_gen: all
	valgrind $(VAL_FLAGS) --log-file=valg/valgrind-suppressions-out.txt --gen-suppressions=yes $(NAME)

check: all
	valgrind $(VAL_FLAGS) --log-file=valg/valgrind-out.txt --suppressions=valg/supressoes.txt $(NAME)

norm:
	norminette -R CheckForbiddenSourceHeader

clean:
	rm -rf $(OBJ)
	make clean -C $(LIB)/libft

fclean: clean
	rm -rf $(BIN)
	rm -rf $(LIB)/libminishell.a
	make fclean -C $(LIB)/libft

re: fclean all

.PHONY: all check_gen check run norm clean fclean re test

