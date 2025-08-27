SRC     = main.cpp BitcoinExchange.cpp
OBJ     = $(SRC:.cpp=.o)
DEP     = $(SRC:.cpp=.d)
CC      = c++
NAME    = btc
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

.PHONY: all re clean fclean
