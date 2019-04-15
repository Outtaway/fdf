.PHONY: all re fclean clean

CC=clang
FLAGS=-Wextra -Wall -Werror
NAME=fdf
FILENAMES=main read_map rotations matrix
SRCS=$(addsuffix .c,$(FILENAMES))
OBJS=$(addsuffix .o,$(FILENAMES))
FRAMEWORKS= -framework OpenGL -framework AppKit -lmlx
LIB_NAME=libftprintf/libftprintf.a
LIB=libftprintf

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB)
	$(CC) $(FLAGS) $(OBJS) $(FRAMEWORKS) $(LIB_NAME) -o $(NAME)

%.o: %.c
	$(CC) -c $< $(FLAGS)

clean:
	make clean -C libftprintf
	/bin/rm -f $(OBJS)

fclean: clean
	make fclean -C libftprintf
	/bin/rm -f $(NAME)