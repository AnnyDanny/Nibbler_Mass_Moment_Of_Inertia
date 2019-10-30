#include "../include/INibblerGame_NCURSES.hpp"


#define EXPORT __attribute__((visibility("default")))



using std::cout;

int screenSize = 16;

EXPORT INibblerGame_NCURSES::INibblerGame_NCURSES()
{
	mTimer = std::make_unique<Timer>();
}

EXPORT INibblerGame_NCURSES::~INibblerGame_NCURSES()
{
	delwin(mWindow);
    endwin();
}

void INibblerGame_NCURSES::redrawBackground() {
	wclear(mWindow);
	wattron(mWindow, COLOR_PAIR(1));

    for (size_t i = 0; i < ObjectTextures.size(); i++)
    {
    	Texture &elem = *ObjectTextures[i];
    	mvwaddch(mWindow, elem._posy/screenSize, elem._posx/screenSize, elem._draw);
    }

     for (size_t i = 0; i < FoodTextures.size(); i++)
    {
    	mvwaddch(mWindow, FoodTextures[i]->_posy/screenSize, FoodTextures[i]->_posx/screenSize, FoodTextures[i]->_draw);
    }

    for (size_t i = 0; i < PlayerTextures.size(); i++)
    {
    	Texture &elem = *PlayerTextures[i];
    	init_pair(13, COLOR_CYAN, COLOR_YELLOW);
    	wattron(mWindow, COLOR_PAIR(13));    	
    	mvwaddch(mWindow, elem._posy/screenSize, elem._posx/screenSize, elem._draw);
    }
    for (size_t i = 0; i < SecondPlayerTextures.size(); i++)
    {
    	init_pair(15, COLOR_GREEN, COLOR_BLUE); 
    	Texture &elem = *SecondPlayerTextures[i];
    	wattron(mWindow, COLOR_PAIR(15));
    	mvwaddch(mWindow, elem._posy/screenSize, elem._posx/screenSize, elem._draw);
    }

    wrefresh(mWindow);
}

//==================================================================================================
//	InitSystems
//--------------------------------------------------------------------------------------------------
EXPORT bool	INibblerGame_NCURSES::InitSystems(int32_t _screenWidth, int32_t _screenHeigh)
{
	setlocale(LC_ALL, "");
	mScreenWidth = _screenWidth / screenSize;
	mScreenHeight = _screenHeigh / screenSize;

	WINDOW *mainWin = initscr();
    cbreak();
    noecho();
    curs_set(0);

    int32_t height, width;
   	getmaxyx(mainWin, height, width);
	if (height < mScreenHeight || width < mScreenWidth + 20) {
    	std::cout << "FALSE created WINDOW " << height << " <-height" << width << " <-width"  << std::endl;
    	return false;
    }
     mWindow = newwin(mScreenHeight, mScreenWidth, 0, 0);


   	start_color();
    scrollok(stdscr, FALSE);
    init_color(COLOR_GREEN, 0, 500, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(155, COLOR_CYAN, COLOR_GREEN);
    keypad(mWindow, true);
    nodelay(mWindow, true);
    redrawBackground();
    return true;
}
//==================================================================================================
//	PlayStartScreen
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_NCURSES::PlayStartScreen()
{
	wclear(mWindow);
	for (size_t i = 0; i < StartScreenTextures.size(); i++)
    {
    	init_pair(15, COLOR_GREEN, COLOR_BLUE); 

    	wattron(mWindow, COLOR_PAIR(15));
    	mvwprintw(mWindow, StartScreenTextures[i]->_posx/screenSize, StartScreenTextures[i]->_posy/screenSize, "%s", StartScreenTextures[i]->_text.c_str() );
    }
    wrefresh(mWindow);

}
//==================================================================================================
//	GetDeltaTime
//--------------------------------------------------------------------------------------------------
EXPORT float	INibblerGame_NCURSES::GetDeltaTime()
{
	return mTimer->getDeltaTime();
}
//==================================================================================================
//	ResetTimer
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_NCURSES::ResetTimer()
{
	mTimer->Reset();
}
//==================================================================================================
//	UpdateTimer
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_NCURSES::UpdateTimer()
{
}
//==================================================================================================
//	Update
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_NCURSES::Update()
{

}
//==================================================================================================
//	UpdatePlayerPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::UpdatePlayerPos(float xPos, float yPos, size_t index, uint8_t playerNum)
{
	if(playerNum == 1)
	{
		PlayerTextures[index]->Pos(xPos, yPos);
	}
	else
	{
		SecondPlayerTextures[index]->Pos(xPos, yPos);
	}
	redrawBackground();
}
//==================================================================================================
//	UpdateFoodPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::UpdateFoodPos(float PosX, float PosY, size_t index)
{
	FoodTextures[index]->Pos(PosX, PosY);
}
//==================================================================================================
//	UpdatePlayerDir
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::UpdatePlayerTexture(int32_t xPos, int32_t yPos, size_t index, uint8_t playerNum)
{
	(void)xPos;
	(void)yPos;
	(void)index;
	(void)playerNum;
}
//==================================================================================================
//	UpdatePlayerScore
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::UpdatePlayerScore(const std::string& score, size_t index, uint8_t playerNum)
{
	(void)score;
	(void)index;
	(void)playerNum;
	mvprintw(playerNum, mScreenWidth, "Player %d score: %s %C", playerNum, &score[0], L'☄');
	refresh();
}
//==================================================================================================
//	UpdateScreenPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::UpdateScreenPos(float PosX, float PosY, size_t index)
{
	StartScreenTextures[index]->Pos(PosY, PosX);
}
//==================================================================================================
//	HandleInput
//--------------------------------------------------------------------------------------------------
EXPORT bool	INibblerGame_NCURSES::HandleInput(int8_t keyCode)
{
	int16_t code = 15;
    code = wgetch(mWindow);

	switch(keyCode)
	{
		case 1: 
			if (code == 'w')
				return true;
			break;
		case 2: 
			if (code == 'a')
				return true;
			break;
		case 3: 
			if (code == 's')
				return true;
			break;
		case 4: 
			if (code == 'd')
				return true;
			break;
		case 5: 
			if (code == ' ')
				return true;
			break;
		case 6: 
			if (code == '1')
				return true;
			break;
		case 7: 
			if (code == '2')
				return true;
			break;
		case 8: 
			if (code == '3')
				return true;
			break;
		case 9:
			if (code == 'i')
				return true;
			 break;
		case 10:
			if (code == 'j')
				return true;
			break;
		case 11:
			if (code == 'k')
				return true;
			break;
		case 12:
			if (code == 'l')
				return true;
			break;
	}
	ungetch(code);
	return false;
}


//==================================================================================================
//	HandleCloseEvent
//--------------------------------------------------------------------------------------------------
EXPORT bool INibblerGame_NCURSES::HandleCloseEvent()
{
	if (wgetch(mWindow) == 27) {
		return false;
	}
	return true;
}
//==================================================================================================
//	Render
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::Render()
{
}
//==================================================================================================
//	ClearBuffer
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::ClearBuffer()
{
}
//==================================================================================================
//	AddPlayerTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::AddPlayerTextureToRender(const std::string&	_filePath,
													   int32_t				x,
													   int32_t				y,
													   int32_t				textureW,
													   int32_t				textureH,
													   float				xPos,
													   float				yPos,
													   uint8_t				playerNum)
{
	(void)_filePath;
	(void)x;
	(void)y;
	(void)textureW;
	(void)textureH;
	init_pair(13, COLOR_GREEN, COLOR_YELLOW);
	init_pair(15, COLOR_GREEN, COLOR_BLUE);
	if(playerNum == 1)
	{
		PlayerTextures.push_back(std::make_unique<Texture>(mWindow, xPos, yPos, '*'));
		
	}
	else
	{
		SecondPlayerTextures.push_back(std::make_unique<Texture>(mWindow, xPos, yPos, '#'));
	
	}
}
//==================================================================================================
//	AddObjectTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::AddObjectTextureToRender(const std::string&	_filePath,
													   int32_t				x,
													   int32_t				y,
													   int32_t				textureW,
													   int32_t				textureH,
													   float				xPos,
													   float				yPos)		
{
	(void)_filePath;
	(void)x;
	(void)y;
	(void)textureH;
	(void)textureW;
	ObjectTextures.push_back(std::make_unique<Texture>(mWindow, xPos, yPos, '|'));
}
//==================================================================================================
//	AddFoodTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::AddFoodTextureToRender(const std::string&	_filePath,
													 int32_t				x,
													 int32_t				y,
													 int32_t				textureW,
													 int32_t				textureH,
													 float					xPos,
													 float					yPos)
{
	(void)_filePath;
	(void)x;
	(void)y;
	(void)textureH;
	(void)textureW;
	FoodTextures.push_back(std::make_unique<Texture>(mWindow, xPos, yPos, '@'));
	
}
//==================================================================================================
//	AddScreenTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_NCURSES::AddScreenTextureToRender(const std::string&	_filePath,
											 			int32_t				_x,
											 			int32_t				_y,
											 			int32_t				_textureW,
											 			int32_t				_textureH,
											 			float				_xPos,
											 			float				_yPos)
{
	(void)_textureH;
	(void)_textureW;
	(void)_xPos;
	(void)_yPos;
	StartScreenTextures.push_back(std::make_unique<Texture>(mWindow, _x, _y, _filePath));
}
//==================================================================================================
//	AddTextToRender
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_NCURSES::AddTextToRender(const std::string&	_text,
											   uint8_t				_fontSize,
											   uint8_t				_r,
											   uint8_t				_g,
											   uint8_t				_b,
											   float				_xPos,
											   float				_yPos)
{
	(void)_text;
	(void)_fontSize;
	(void)_r;
	(void)_g;
	(void)_b;
	(void)_xPos;
	(void)_yPos;
}

EXPORT INibblerGame* createINibblerEntity()
{
	return new INibblerGame_NCURSES();
}

EXPORT void deletINibblerEntity(INibblerGame* entity)
{
	std::cout << "destroing NCURSES!\n";
	delete entity;
}