#pragma once
#include "base.h"

struct LevelConfig {
	int chips_count;
	int point_place_count;
	std::vector<VectFloat> coord_place;
	std::vector<int> start_place_chips;
	std::vector<int> win_place_chips;
	int connections_count;
	std::vector<VectFloat> connections;
};

