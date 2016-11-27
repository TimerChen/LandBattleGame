
	struct MapData
	{
		short data[H][W];
	}mapData[2], *map, *map_back;

	short rev,originCount[25],*Count;
	double NowScore; 
	std::stack<MoveData> steps;
