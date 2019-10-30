#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "MathHelper.hpp"
#include <iostream>
#include <vector>
#include <utility>

//**************************************************************************************************
//	Level
//--------------------------------------------------------------------------------------------------
class Level
{
public:
	Level()													= default;
	Level(const Level&)										= default;
	virtual ~Level()										= default;

	Level&							operator=(const Level&) = default;

	bool							LoadLevel(const std::string& fileName);
	int32_t							LevelWidth()			const;
	int32_t							LevelHeight()			const;
	bool							ParseLevel();

	const std::vector<Vector2>&		FirstPlayerPositions()	const;
	const std::vector<Vector2>&		SecondPlayerPositions()	const;
	const std::vector<std::string>&	LevelMap()				const;

	const std::vector<std::pair<Vector2, std::string>>& WallsPosition() 	const;
	

protected:
	std::vector<Vector2>					firstPlayerPositions;
	std::vector<Vector2>					secondPlayerPositions;
	std::vector<std::pair<Vector2, std::string>> wallsPosition;
	std::vector<std::string>				levelMap;
};

#endif
