#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <string>

//**************************************************************************************************
//	Texture
//--------------------------------------------------------------------------------------------------
class Texture
{
public:
	Texture(const std::string&	path,
			sf::Vector2f		position,
			sf::Vector2f		textureSize,
			sf::IntRect);

	Texture(const std::string&	text,
			int					fontSize,
			sf::Color,
			sf::Vector2f		position);

	virtual ~Texture();

	virtual void	Render(sf::RenderTarget* window);
	void			RenderText(sf::RenderTarget* window);
	// actuallt it's now a rotating, it's just changing rendering rect
	void			Rotate(const sf::IntRect& rect)			{ mRenderRect.setTextureRect(rect);		}
	void			Move(const sf::Vector2f& amount)		{ mRenderRect.move(amount);				}
	void			MoveText(const sf::Vector2f& amount)	{ text.move(amount);					}
	void			Pos(const sf::Vector2f& pos)			{ mRenderRect.setPosition(pos);			}
	sf::Vector2f	Pos() const								{ return mRenderRect.getPosition();		}
	void			Scale(const sf::Vector2f& scale)		{ mRenderRect.setScale(scale);			}
	void			SetTextString(const std::string& t)		{ text.setString(t);					}

protected:

	sf::RectangleShape				mRenderRect;
	std::unique_ptr<sf::Texture>	mTexture;
	sf::Text						text;
	sf::Font						font;

};

#endif