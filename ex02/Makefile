SRC     = main.cpp PmergeMe.cpp
OBJ     = $(SRC:.cpp=.o)
DEP     = $(SRC:.cpp=.d)
CC      = c++
NAME    = PmergeMe
CFLAGS  = -Wall -Wextra -Werror -Wpedantic -std=c++98 -MMD -MP

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

N ?=3000
U ?=100000

test: $(NAME)
	./$(NAME) `shuf -i 1-$(U) -r -n $(N) | tr "\n" " "`

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME) `shuf -i 1-$(U) -r -n $(N) | tr "\n" " "`


.PHONY: all re clean fclean test valgrind
