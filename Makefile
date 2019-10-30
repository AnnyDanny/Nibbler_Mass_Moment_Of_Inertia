NAME = nibbler

CPP =	main		\
		Collider	\
		Food		\
		gManager	\
		Level		\
		Player		\
		StartScreen	\
		Wall		\
		
HPP =	Collider.hpp	\
		Food.hpp		\
		gManager.hpp	\
		Level.hpp		\
		Player.hpp		\
		MathHelper.hpp	\
		StartScreen.hpp	\
		Wall.hpp		\

SRC = $(addprefix src/, $(addsuffix .cpp, $(CPP)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(CPP)))
HDR = $(addprefix includes/, $(HPP))
FLAGS = -Wall -Wextra -Werror -std=c++14 -g3 -fsanitize="address,undefined"

HEADERS = -I./includes

all: $(NAME) SDL NCURSES SFML

$(NAME): $(OBJ) $(HDR)
	make -C ./audio_dll
	clang++ $(FLAGS) $(OBJ) -lm $(HEADERS) -o $(NAME) -ldl

SDL:
	make -C ./sdl_dll 

NCURSES:
	make -C ./ncurses_dll

SFML:
	make -C ./sfml_dll

$(OBJ): obj/%.o : src/%.cpp $(HDR)
	mkdir -p obj/
	clang++ -o $@ $ -c $(FLAGS) $(HEADERS) $<

clean:
	rm -f $(OBJ)
	make clean -C ./ncurses_dll
	make clean -C ./sdl_dll
	make clean -C ./audio_dll
	make clean -C ./sfml_dll

fclean :
	make fclean -C ./ncurses_dll
	make fclean -C ./sdl_dll
	make fclean -C ./audio_dll
	make fclean -C ./sfml_dll
	rm -f $(NAME)
	rm -rf $(OBJ)
	
re: fclean all
