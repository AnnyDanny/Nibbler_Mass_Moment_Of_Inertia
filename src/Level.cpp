#include "Level.hpp"
#include "Collider.hpp"
#include <fstream>
#include <string>

//=================================================================================================
//	LoadLevel
//-------------------------------------------------------------------------------------------------
bool Level::LoadLevel(const std::string& _fileName)
{
	std::string fullpath;
	fullpath.append("resourses/maps/" + _fileName);
	std::ifstream file;

	file.open(fullpath.c_str());
	if(file.fail())
	{
		perror(fullpath.c_str());
		return false;
	}
	std::string line;
	while(std::getline(file, line))
	{
		if(!line.empty())
		{
			levelMap.push_back(line);
		}
	}
	file.close();
	return true;
}
//=================================================================================================
//	ParseLevel
//-------------------------------------------------------------------------------------------------
bool Level::ParseLevel()
{
	// $todo remove magic numbers
	char tile;
	for(size_t y = 0; y < levelMap.size(); ++y)
	{
		for(size_t x = 0; x < levelMap[y].size(); ++x)
		{
			tile = levelMap[y][x];
			switch(tile)
			{
			case 'W':
				wallsPosition.push_back(std::make_pair(Vector2(static_cast<float>(x * Collider::TEXTURE_SIZE), static_cast<float>(y * Collider::TEXTURE_SIZE)), "st.bmp"));
				break;
			case 'X':	firstPlayerPositions.push_back(Vector2(static_cast<float>(x * Collider::TEXTURE_SIZE), static_cast<float>(y * Collider::TEXTURE_SIZE)));	break;
			case 'Y':	secondPlayerPositions.push_back(Vector2(static_cast<float>(x * Collider::TEXTURE_SIZE), static_cast<float>(y * Collider::TEXTURE_SIZE)));	break;
			case 'P':
				wallsPosition.push_back(std::make_pair(Vector2(static_cast<float>(x * Collider::TEXTURE_SIZE), static_cast<float>(y * Collider::TEXTURE_SIZE)), "pine.png"));
				break;
			case 'T':
				wallsPosition.push_back(std::make_pair(Vector2(static_cast<float>(x * Collider::TEXTURE_SIZE), static_cast<float>(y * Collider::TEXTURE_SIZE)), "tree.png"));
				break;
			case '.':
			case ' ':	break;
			default:
				std::cout << "Unexpected Symbol: " << tile << " at x:" << x << ", y:" << y << "\n";
			break;
			}
		}
	}
	return true;
}
//=================================================================================================
//	FirstPlayerPositions
//-------------------------------------------------------------------------------------------------
const std::vector<Vector2>& Level::FirstPlayerPositions() const
{
	return firstPlayerPositions;
}
//=================================================================================================
//	SecondPlayerPositions
//-------------------------------------------------------------------------------------------------
const std::vector<Vector2>& Level::SecondPlayerPositions() const
{
	return secondPlayerPositions;
}
//=================================================================================================
//	WallsPosition
//-------------------------------------------------------------------------------------------------
const std::vector<std::pair<Vector2, std::string>>&  Level::WallsPosition() const
{
	return wallsPosition;
}
//=================================================================================================
//	LevelMap
//---------------------------------------------------------------------------------------------
const std::vector<std::string>&	Level::LevelMap() const
{
	return levelMap;
}
//=================================================================================================
//	LevelWidth
//-------------------------------------------------------------------------------------------------
int32_t Level::LevelWidth() const
{
	if (!levelMap.empty())
	{
		return levelMap.front().size() * Collider::TEXTURE_SIZE;
	}
	return 0;
}
//=================================================================================================
//	LevelHeight
//-------------------------------------------------------------------------------------------------
int32_t Level::LevelHeight() const
{
	if (!levelMap.empty())
	{
		return levelMap.size() * Collider::TEXTURE_SIZE;
	}
	return 0;
}
