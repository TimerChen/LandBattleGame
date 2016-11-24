const int TOTALNUM = 25;
const int TOTALKIND = 12;
const int UPPER_RANGE_L = 11, UPPER_RANGE_R = 16;
const int LOWER_RANGE_L = 0, LOWER_RANGE_R = 5;
const int H = 17;
const int W = 5;
const double eps = 1e-5;
const double LOSE_SCORE = -1e7;
const int DIR[8][2] = {{-1,0},{+1,0},{0,-1},{0,+1},{-1,-1},{-1,1},{1,-1},{1,1}};
const double Score[20] = { 0, 40, 35, 9, 8, 7, 6, 2, 1, 9, 30, 11, 1000 };
const short SECRET[10] = {0,0};
const int typeMap[H][W]=
{
	{ 0,3,0,3,0 },
	{ 1,1,1,1,1 },
	{ 1,2,0,2,1 },
	{ 1,0,2,0,1 },
	{ 1,2,0,2,1 },
	{ 1,1,1,1,1 },
	{ 1,4,1,4,1 },
	{ 4,3,4,3,4 },
	{ 1,4,1,4,1 },
	{ 4,3,4,3,4 },
	{ 1,4,1,4,1 },
	{ 1,1,1,1,1 },
	{ 1,2,0,2,1 },
	{ 1,0,2,0,1 },
	{ 1,2,0,2,1 },
	{ 1,1,1,1,1 },
	{ 0,3,0,3,0 },
};
int rounds = 1;
int id;
int chessMap[H][W];
int startTime;
short DEBUG_MODE;

short MaxLevel = 3;
