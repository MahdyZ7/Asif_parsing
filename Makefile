NAME = fillparsing

SRC = IO_parsing.cpp

CC = c++

CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRC:.cpp=.o)

all : $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

install:
	bash FILLBLOCK_install.sh
