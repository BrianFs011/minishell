#PATHS
BIN			= ./bin
SRC			= ./src
OBJ			= ./obj
BONUS		= ./bonus
INCLUDE		= ./include
NAME		= $(BIN)/libft.a

#VARIABLES
CC			= cc
FLAGS		= -Wall -Wextra -Werror
HEADER		= -I $(INCLUDE)
SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
			  ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			  ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

OBJS		= $(addprefix $(OBJ)/,$(SRCS:%.c=%.o))

BONUS_SRC	= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			  ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

BONUS_OBJ	= $(addprefix $(OBJ)/, $(BONUS_SRC:%.c=%.o))

all: $(OBJ) $(BIN) $(NAME)

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(FLAGS) $(HEADER) $< -o $@

bonus: $(OBJ) $(BIN) $(NAME) $(BONUS_OBJ)
	ar -rsc $(NAME) $(BONUS_OBJ)

$(OBJ)/%.o: $(BONUS)/%.c
	$(CC) -c $(FLAGS) $(HEADER) $< -o $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

