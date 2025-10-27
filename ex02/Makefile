SRC     = main.cpp PmergeMe.cpp
SRC_TEST = test.cpp PmergeMe.cpp
OBJ     = $(SRC:.cpp=.o)
DEP     = $(SRC:.cpp=.d)
OBJ_TEST     = $(SRC_TEST:.cpp=.o)
DEP_TEST     = $(SRC_TEST:.cpp=.d)
CC      = c++
NAME    = PmergeMe
TEST	= tester
CFLAGS  = -Wall -Wextra -Werror -Wpedantic -std=c++98 -MMD -MP

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(TEST): $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) -o $(TEST)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP) $(DEP_TEST)

clean:
	rm -f $(OBJ) $(DEP) $(OBJ_TEST) $(DEP_TEST)

fclean: clean
	rm -f $(NAME) $(TEST)

re: fclean all

test: $(TEST)

test1: $(TEST)
	./$(TEST) `shuf -i 1-100000 -n 3000 | tr "\n" " "`

.PHONY: all re clean fclean test
