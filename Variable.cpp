const int TOTALNUM = 25;
const int TOTALKIND = 12;
const int UPPER_RANGE_L = 11, UPPER_RANGE_R = 16;
const int LOWER_RANGE_L = 0, LOWER_RANGE_R = 5;
const int H = 17;
const int W = 5;
const double eps = 1e-5;
const double LOSE_SCORE = -1e17;
const int DIR[8][2] = {{-1,0},{+1,0},{0,-1},{0,+1},{-1,-1},{-1,1},{1,-1},{1,1}};
const double Score[20] = { 0, 2000, 1000, 500, 100, 50, 10, 2, 1, 500, 1500, 2000, 10000 };
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
short QUIT;
//#define OLDSCORE
//#define DIRECTSOCRE_CHECK
#define PRUNING

#ifdef DEBUG
	//#define SKIP
#endif

#ifdef SKIP
short MaxLevel = 1;
#else
short MaxLevel = 4;
#endif
