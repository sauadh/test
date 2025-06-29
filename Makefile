UNAME_S = $(shell uname -s)

NAME = cub3D

CC = cc

RM = rm -f

SRC = \
	$(wildcard src/*.c) \
	$(wildcard parsing/*.c) \
	$(wildcard execution/*.c)

	
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3 -g #-fsanitize=address

LIBFT:= libft/libft.a

MLX = mlx/libmlx.a
#MLX = mlx_linux/libmlx_Linux.a


LIBS :=
ifeq ($(UNAME_S),Darwin) # MacOS
    FLAGS += -Imlx
    LIBS +=  -Lmlx -lmlx -framework OpenGL -framework AppKit
	
else ifeq ($(UNAME_S),Linux) # Linux
    FLAGS += -I/usr/include -Imlx_linux
    LIBS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
endif

%.o: %.c
	 $(CC) $(FLAGS) -c $< -o $@ 
#>/dev/null

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@ $(CC) $(OBJ) $(LIBS) -o $(NAME) $(LIBFT) $(MLX)
#-fsanitize=address -g3
$(LIBFT):
	@ make -C libft/ >/dev/null

$(MLX):
	@ make -C mlx/ >/dev/null
#@ make -C mlx_linux/ >/dev/null
clean: 
	@ $(RM) $(OBJ)
	@ make -C libft/ clean >/dev/null

fclean: clean
	@ $(RM) $(NAME)
	@ make -C libft/ fclean >/dev/null

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean all

.PHONY: all libft clean fclean re