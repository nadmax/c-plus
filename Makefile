CC   =  gcc

SRC  = 	src/main.c   \
		src/int.c    \
		src/list.c   \
		src/new.c    \
		src/point.c  \
		src/vertex.c

OBJ  =  $(SRC:.c=.o)

TARGET = a.out

CFLAGS = -I./include/ -Wall -Wextra -Wpedantic

all: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re