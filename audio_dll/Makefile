NAME = audio.so

FLAGS		=	-std=c++14 -Wall -Wextra -Werror -g3 -fsanitize="address,undefined"

SDL_DIR		=	./SDL
SDL_FRM		=	-F $(SDL_DIR)
SDL_LINK	=	-framework SDL2

PWD			= 	$(shell pwd)
LIB_FLAG	=	-rpath $(PWD)/$(SDL_DIR) -nostartfiles -dynamiclib

SRC_FILES	=	./src/AudioManager.cpp \


INC_FILES	=	AudioManager.hpp	\


INC_DIR		=	./include \
				-I./SDL/SDL2.framework/Versions/A/Headers \
				-I./SDL/SDL2_mixer.framework/Versions/A/Headers \

FRAMEWORKS	=	-F./SDL \
				-rpath ./SDL \
				-framework OpenGL -framework AppKit\
				-framework SDL2 -framework SDL2_mixer\

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
	@ curl -o sdl2_mixer.dmg https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.dmg

	@ hdiutil attach sdl2.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2/SDL2.framework $(PWD)/$(SDL_DIR)/SDL2.framework; #hdiutil eject ../../../Volumes/SDL2;
	@ hdiutil attach sdl2_mixer.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2_mixer/SDL2_mixer.framework $(PWD)/$(SDL_DIR)/SDL2_mixer.framework; hdiutil eject ../../../Volumes/SDL2_mixer;

clean:
	@ rm -rf $(OBJ_FILES)
	@ rm -fr $(SDL_DIR)
	@ echo "\033[33mcleaned (SDL)\033[39m"

fclean:	clean
	@ rm -rf $(NAME)
	@ echo "\033[33mcleaned all (SDL)\033[39m"
	
re:	fclean all

.PHONY: all sdl clean fclean re




# NAME = audio.so

# CLANG++		=	clang++
# FLAGS 		=	-std=c++14  -O3

# SFML_DIR 	=	SFML/
# SFML_INC 	=	$(SFML_DIR)/SFML-2.5.1-macOS-clang/include
# SFML_FRM	=	$(SFML_DIR)/SFML-2.5.1-macOS-clang/Frameworks
# SFML_LINK 	=	-F$(SFML_FRM) -shared -framework sfml-audio

# PWD 		=	$(shell pwd)
# LIB_FLAG	=	-shared -rpath $(PWD)/$(SFML_FRM) -nostartfiles -dynamiclib

# SRC_FILES =	./src/AudioManager.cpp				\

# INC_FILES =	./include/AudioManager.hpp			\

# INC_DIR		=	./include

# OBJ_FILES 	=	$(SRC_FILES:.cpp=.cpp.o)

# all: sfml $(NAME)

# $(NAME): $(OBJ_FILES)
# 	@ $(CLANG++) $(FLAGS) -o $@ $(OBJ_FILES) $(SFML_LINK) $(LIB_FLAG) -I $(SFML_INC)

# %.cpp.o:%.cpp
# 	@ $(CLANG++) $(FLAGS) -c -o $@ $< -I $(INC_DIR) -I $(SFML_INC)

# sfml_dl:
# 	echo "\033[32m... loading SFML\033[39m"
# 	curl -OL http://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz
# 	tar zxvfC 'SFML-2.5.1-macOS-clang.tar.gz' $(SFML_DIR)
# 	rm -rf SFML-2.5.1-macOS-clang.tar.gz
# 	cd $(SFML_FRM) && ln -s ../extlibs/freetype.framework

# sfml:
# 	mkdir -p $(SFML_DIR)
# 	test -d SFML/SFML-2.5.1-macOS-clang && echo "$(YELLOW)File SFML already exist$(RESET)" || make sfml_dl

# clean:
# 	@ rm -rf $(OBJ_FILES)
# 	@ rm -rf $(SFML_DIR)
# 	@ echo "\033[33mcleaned (SFML)\033[39m"

# fclean: clean
# 	@ rm -rf $(NAME)
# 	@ echo "\033[33mcleaned all (SFML)\033[39m"

# re: fclean all

