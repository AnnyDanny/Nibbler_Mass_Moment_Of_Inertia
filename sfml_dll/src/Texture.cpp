#include "../include/Texture.hpp"
#include <iostream>

//==================================================================================================
//	Texture
//--------------------------------------------------------------------------------------------------
Texture::Texture(const std::string&	_path,
				 sf::Vector2f		_position,
				 sf::Vector2f		_textureSize,
				 sf::IntRect		_intRect)
{
	mTexture = std::make_unique<sf::Texture>();
	
	std::string fullpath = "resourses/sprites/" + _path;
	if (!mTexture->loadFromFile(fullpath))
	{
		std::cout << "Error loading texture on path:" << fullpath<< "\n";
	}
	mRenderRect.setPosition(_position);
	mRenderRect.setSize(_textureSize);
	mRenderRect.setTexture(mTexture.get());
	mRenderRect.setTextureRect(_intRect);
}
//==================================================================================================
//	Texture
//--------------------------------------------------------------------------------------------------
Texture::Texture(const std::string&		_text,
				 int					_fontSize,
				 sf::Color				_color,
				 sf::Vector2f			_position)
{
	if (!font.loadFromFile("resourses/fonts/8bit.ttf"))
	{
		std::cout << "Error loading font in Texture ctor\n";
	}
	text.setFont(font);
	text.setString(_text);
	text.setCharacterSize(_fontSize);
	text.setFillColor(_color);
	text.setPosition(_position);
}
//==================================================================================================
//	~Texture
//--------------------------------------------------------------------------------------------------
Texture::~Texture()
{
}
//==================================================================================================
//	Render
//--------------------------------------------------------------------------------------------------
void Texture::Render(sf::RenderTarget* _window)
{
	_window->draw(mRenderRect);
}
//==================================================================================================
//	RenderText
//--------------------------------------------------------------------------------------------------
void Texture::RenderText(sf::RenderTarget* _window)
{
	_window->draw(text);
}