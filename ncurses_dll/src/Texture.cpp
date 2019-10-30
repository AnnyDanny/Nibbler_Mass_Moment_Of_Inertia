#include "../include/Texture.hpp"
#include <iostream>

Texture::Texture(WINDOW* win, int x, int y, wchar_t draw) : _win(win), _posx(x), _posy(y), _draw(draw)
{

}

Texture::Texture(WINDOW* win, int x, int y, const std::string& text) : _win(win), _posx(x), _posy(y), _text(text)
{

}

void Texture::Render()
{
	mvwprintw(_win, _posy, _posx, "%C", _draw);
}

