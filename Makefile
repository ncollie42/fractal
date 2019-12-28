NAME = fractol

src = $(wildcard ./src/*.c)
obj = $(src:.c=.o)

PATH_MLX = ./minilibx/all_files
PATH_LIBFT = ./Lib/42_lib
LDFLAGS =  -lmlx -lft -framework OpenGL -framework AppKit
HEADERS = -I $(PATH_MLX) -I $(PATH_LIBFT)/includes/
LIBS = -L $(PATH_MLX)  -lmlx -L $(PATH_LIBFT) -lft

all: $(NAME)

$(NAME): $(obj)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

f: $(obj)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS) -fsanitize=address 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) -g

.PHONY: clean
clean:
	rm -f $(obj) $(NAME)