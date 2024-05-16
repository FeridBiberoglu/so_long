NAME	:= so_long
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ./MLX42
LIBFT := ./libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I$(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm  $(LIBFT)/libft.a
SRCS	:= main.c map.c make_2d_array.c playermovement.c \
			mapchecker.c hooks.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libft:
	make -C $(LIBFT)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@


$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build
	make clean -C $(LIBFT)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft