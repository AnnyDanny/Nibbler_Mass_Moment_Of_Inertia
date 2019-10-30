NAME = libsdl.so

FLAGS		=	-std=c++14 -Wall -Wextra -Werror -O3 -g3 -fsanitize="address,undefined"

SDL_DIR		=	./SDL
SDL_FRM		=	-F $(SDL_DIR)
SDL_LINK	=	-framework SDL2

PWD			= 	$(shell pwd)
LIB_FLAG	=	-shared  -rpath $(PWD)/$(SDL_DIR) -nostartfiles -dynamiclib

SRC_FILES	=	./src/Graphics.cpp  \
				./src/InputManager.cpp   \
				./src/Texture.cpp   \
				./src/Timer.cpp  \
				./src/INibblerGame_SDL.cpp   \

INC_FILES	=	Graphics.hpp		\
				InputManager.hpp	\
				Texture.hpp			\
				Timer.hpp			\
				INibblerGame_SDL.hpp				\

INC_DIR		=	./include \
				-I./SDL/SDL2.framework/Versions/A/Headers \
				-I./SDL/SDL2_ttf.framework/Versions/A/Headers \
				-I./SDL/SDL2_image.framework/Versions/A/Headers \

FRAMEWORKS	=	-F./SDL \
				-rpath ./SDL \
				-framework OpenGL -framework AppKit\
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \

OBJ_FILES	= 	$(SRC_FILES:.cpp=.cpp.o)

SDL2 		=	SDL2

all: sdl $(NAME)

$(NAME): $(OBJ_FILES)
	@ clang++ $(FLAGS) $(SDL_FRM) $(SDL_LINK) $(LIB_FLAG) $(FRAMEWORKS) $(OBJ_FILES) -o $(NAME)

%.cpp.o:%.cpp
	@ clang++ $(FLAGS) $(SDL_FRM) -c -o $@ $< -I $(INC_DIR)


sdl:
	@ mkdir -p $(SDL_DIR)
	@ test -f SDL/SDL2.framework/SDL2 && echo "\033[33mFile $(SDL2) already exist\033[39m" || make sdl2_download

sdl2_download:
	echo "\033[32m... loading SDL\033[39m"
	@ curl -o sdl2.dmg https://www.libsdl.org/release/SDL2-2.0.8.dmg
	@ curl -o sdl2_image.dmg https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.dmg
	@ curl -o sdl2_ttf.dmg https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.dmg

	@ hdiutil attach sdl2.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2/SDL2.framework $(PWD)/$(SDL_DIR)/SDL2.framework; #hdiutil eject ../../../Volumes/SDL2;
	@ hdiutil attach sdl2_image.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2_image/SDL2_image.framework $(PWD)/$(SDL_DIR)/SDL2_image.framework; #hdiutil eject ../../../Volumes/SDL2_image;
	@ hdiutil attach sdl2_ttf.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2_ttf/SDL2_ttf.framework $(PWD)/$(SDL_DIR)/SDL2_ttf.framework; hdiutil eject ../../../Volumes/SDL2_ttf;

clean:
	@ rm -rf $(OBJ_FILES)
	@ rm -fr $(SDL_DIR)
	@ echo "\033[33mcleaned (SDL)\033[39m"

fclean:	clean
	@ rm -rf $(NAME)
	@ echo "\033[33mcleaned all (SDL)\033[39m"
	
re:	fclean all

.PHONY: all sdl clean fclean re
