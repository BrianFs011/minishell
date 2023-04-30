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

#SRC FILES
VARIABLES = vr_linked_list.c vr_linked_list_delete.c
LIBFTE		= ft_atoi_llint.c
BUILTINS	= bt_exit.c bt_cd.c bt_echo.c bt_pwd.c bt_env.c bt_unset.c bt_export.c bt_export_unset_utils.c
CHECKS		= ck_cmd.c ck_compress.c ck_redirect.c ck_llong_int.c

#VARIABLES
SRCS		= ft_str.c fk_fork_utils.c tml_functions.c fl_file.c \
			  ft_clear_memory.c tml_clear_memory.c rd_redirection.c \
			  pp_pipe.c sa_sigaction.c sa_hooks.c \
				vr_vars.c tml_init.c ft_str2.c \
				vr_descompress.c vr_descompress_utils.c \
				vr_local_vars.c tml_functions_utils.c \
				ft_utils.c tml_exit_status.c ft_error_msg.c fd_handler.c\
				tml_prompt.c $(BUILTINS) $(CHECKS) $(LIBFTE) $(VARIABLES)

OBJS		= $(addprefix $(OBJ)/,$(SRCS:%.c=%.o))
HEADER	= -I $(LIB)/libft/include -I $(INCLUDE)
LIBS		= -lreadline -lcurses -L $(LIB)/libft/bin -lft
FLAGS		= -Wall -Wextra -Werror -g3 -g
CC			= cc
VAL_FLAGS	= --leak-check=full --show-leak-kinds=definite -s --track-origins=yes

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
	gcc $(HEADER) main.c -o main $(LIBS); ./main; rm main

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
#make fclean -C $(LIB)/libft

re: fclean all

.PHONY: all check_gen check run norm clean fclean re test

