#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <ncurses.h>
#include <string>

//**************************************************************************************************
//	Texture
//--------------------------------------------------------------------------------------------------
class Texture
{
public:
	Texture(WINDOW* win, int x, int y, wchar_t draw);
	Texture(WINDOW* win, int x, int y, const std::string& text);
	virtual ~Texture() {}

	virtual void	Render();
	void			Pos(int posx, int posy)			
	{
		mvwaddch(_win, _posy, _posx, ' ');
		_posx = posx;
		_posy = posy;
	}

public:
	WINDOW* 		_win;
	int 			_posx;
	int 			_posy;
	wchar_t 		_draw;
	std::string 	_text;
	

};

#endif