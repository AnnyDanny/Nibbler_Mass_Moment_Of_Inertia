NAME = libsfml.so

CLANG++		=	clang++
FLAGS 		=	-std=c++14  -O3 -g3 -fsanitize="address,undefined"

SFML_DIR 	=	SFML/
SFML_INC 	=	$(SFML_DIR)/SFML-2.5.1-macOS-clang/include
SFML_FRM	=	$(SFML_DIR)/SFML-2.5.1-macOS-clang/Frameworks
SFML_LINK 	=	-F$(SFML_FRM) -framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system 

PWD 		=	$(shell pwd)
LIB_FLAG	=	-shared -rpath $(PWD)/$(SFML_FRM) -nostartfiles -dynamiclib

SRC_FILES =	./src/Texture.cpp				\
			./src/Timer.cpp					\
			./src/INibblerGame_SFML.cpp		\

INC_FILES =	./include/Texture.hpp			\
			./include/Timer.hpp				\
			./include/INibblerGame_SFML.hpp	\

INC_DIR		=	./include

OBJ_FILES 	=	$(SRC_FILES:.cpp=.cpp.o)

all: sfml $(NAME)

$(NAME): $(OBJ_FILES)
	@ $(CLANG++) $(FLAGS) -o $@ $(OBJ_FILES) $(SFML_LINK) $(LIB_FLAG) -I $(SFML_INC)

%.cpp.o:%.cpp
	@ $(CLANG++) $(FLAGS) -c -o $@ $< -I $(INC_DIR) -I $(SFML_INC)

sfml_dl:
	echo "\033[32m... loading SFML\033[39m"
	curl -OL http://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz
	tar zxvfC 'SFML-2.5.1-macOS-clang.tar.gz' $(SFML_DIR)
	rm -rf SFML-2.5.1-macOS-clang.tar.gz
	cd $(SFML_FRM) && ln -s ../extlibs/freetype.framework

sfml:
	mkdir -p $(SFML_DIR)
	test -d SFML/SFML-2.5.1-macOS-clang && echo "$(YELLOW)File SFML already exist$(RESET)" || make sfml_dl

clean:
	@ rm -rf $(OBJ_FILES)
	@ rm -rf $(SFML_DIR)
	@ echo "\033[33mcleaned (SFML)\033[39m"

fclean: clean
	@ rm -rf $(NAME)
	@ echo "\033[33mcleaned all (SFML)\033[39m"

re: fclean all
