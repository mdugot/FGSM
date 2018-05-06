NAME= attack

CC= g++
CFLAGS= -std=c++11 -Wall -Wextra -g3
SRC_NAME= main.cpp\
		  matrix.cpp\
		  vector.cpp\
		  pgm.cpp\
		  data.cpp\
		  neuralNetwork.cpp\
		  tools.cpp\
		  unitest.cpp\
		  fgsmException.cpp
SRC_PATH= ./src/
INC_PATH= ./inc/
OBJ_NAME= $(SRC_NAME:.cpp=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all
all: $(NAME) end
	
end:
	@printf "$(NAME) successfully created\n"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) -I$(INC_PATH) $(OBJ)
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $< \r"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@$(CC) -I$(INC_PATH) $(CFLAGS) -o $@ -c $<
	@printf " \033[2K[ \033[31mcompiling\033[0m ] $< \r"

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@printf "[ \033[36mdelete\033[0m ] objects from $(NAME)\n"
	@rm -rf $(OBJ_PATH)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NAME)\n"
	@rm -f $(NAME)

.PHONY: re
re: fclean all

