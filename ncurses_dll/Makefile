NAME = libncurses.so

CLANG++		=	clang++
FLAGS 		=	-Wall -Wextra -Werror -std=c++14 -g3 -fsanitize="address,undefined"

PWD 		=	$(shell pwd)
LIB_FLAG	=	-lncurses

SRC_FILES =	./src/Texture.cpp				\
			./src/Timer.cpp					\
			./src/INibblerGame_NCURSES.cpp		\

INC_FILES =	./include/Texture.hpp			\
			./include/Timer.hpp				\
			./include/INibblerGame_NCURSES.hpp	\

INC_DIR		=	./include

OBJ_FILES 	=	$(SRC_FILES:.cpp=.cpp.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ $(CLANG++) $(FLAGS) -shared -o $@ $(OBJ_FILES) $(LIB_FLAG)

%.cpp.o:%.cpp
	@ $(CLANG++) $(FLAGS) -c -o $@ $< -I $(INC_DIR)

clean:
	@ rm -rf $(OBJ_FILES)
	@ echo "\033[33mcleaned (NCURSES)\033[39m"

fclean: clean
	@ rm -rf $(NAME)
	@ echo "\033[33mcleaned all (NCURSES)\033[39m"

re: fclean all
