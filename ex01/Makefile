SRC     = main.cpp RPN.cpp
OBJ     = $(SRC:.cpp=.o)
DEP     = $(SRC:.cpp=.d)
CC      = c++
NAME    = RPN
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


test: $(NAME)
	@echo "Running RPN tests from input.txt..."
	@while read -r line || [ -n "$$line" ]; do \
		if [ -z "$$line" ]; then continue; fi; \
		if echo "$$line" | grep -q '^###'; then \
			echo ""; \
			echo "$$line"; \
			echo "----------------------"; \
			continue; \
		fi; \
		echo "Input: $$line"; \
		./$(NAME) "$$line"; \
		echo "----------------------"; \
	done < input.txt

.PHONY: all re clean fclean test
