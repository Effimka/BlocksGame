#include "ConfigParser.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

LevelConfig ConfigParser::make_config_level(const std::string& file_name)
{
	std::stringstream ss;
	std::ifstream inFile(file_name.c_str());

	std::string elem;
	while (std::getline(inFile, elem)) ss << elem << ' ';
	
	LevelConfig config;

	while (ss >> elem)
	{
		if (elem == "chip:")
			ss >> config.chips_count;
		else if (elem == "poin_place:")
			ss >> config.point_place_count;
		else if (elem == "coord:")
			make_config_point_array(ss, config.coord_place);
		else if (elem == "start_points:")
			make_config_array(ss, config.start_place_chips);
		else if (elem == "win_points:")
			make_config_array(ss, config.win_place_chips);
		else if (elem == "connections_count:")
			ss >> config.connections_count;
		else if (elem == "connections:")
			make_config_point_array(ss, config.connections);

	}
	for (int i = 0; i < config.point_place_count; ++i) {
		config.coord_place[i] = VectFloat(config.coord_place[i].x * 0.5f, config.coord_place[i].y * 0.5f);
	}


	return config;
}

void ConfigParser::make_config_point_array(std::stringstream& stream, std::vector<VectFloat>& arr)
{
	int coordX;
	int coordY;
	std::string elem;
	while (stream >> elem)
	{
		if (elem == "[" || elem == "(" || elem == ")" || elem == ",")
			continue;

		if (elem == "]")
			break;

		coordX = std::stoi(elem);
		stream >> elem;
		stream >> coordY;

		arr.push_back(VectFloat(coordX - 1, coordY - 1));
	}
}

void ConfigParser::make_config_array(std::stringstream& stream, std::vector<int>& arr)
{
	int place;
	std::string elem;
	stream >> elem;
	while (stream >> elem)
	{
		if (elem == ",")
			continue;
		if (elem == "]")
			break;

		place = std::stoi(elem);

		arr.push_back(place - 1);
	}
}
