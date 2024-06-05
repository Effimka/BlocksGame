#pragma once
#include "LevelConfig.h"

class ConfigParser
{
public:
	LevelConfig make_config_level(const std::string& file_name);
private:
	void make_config_point_array(std::stringstream& stream, std::vector<VectFloat>& arr);
	void make_config_array(std::stringstream& stream, std::vector<int>& arr);

};

