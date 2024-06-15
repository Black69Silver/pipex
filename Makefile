NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc

CFLAGS = -Wall -Wextra -Werror

SOURCES = pipex.c \
		pipex_execute.c \
		pipex_utils.c \
		ft_split.c \
		ft_memory_control.c

SOURCES_BONUS = pipex_bonus.c \
		pipe_control_bonus.c \
		pipex_execute_bonus.c \
		pipex_utils_bonus.c \
		ft_split_bonus.c \
		ft_memory_control_bonus.c

OBJECTS = $(SOURCES:.c=.o)

OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

all: $(NAME) 

bonus: $(NAME_BONUS)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(NAME_BONUS): $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
