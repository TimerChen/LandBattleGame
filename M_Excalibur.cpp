#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <string>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;
//INCLUDE END 
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
template < class Mem >
struct MemoryPool
{
	~MemoryPool()
	{
		while( !pool.empty() )
		{
			Mem *a = pool.front();
			pool.pop();
			delete( a );
		}
	}
    std::queue<Mem*> pool;
    void Delete( Mem *&a )
    {
		//delete( a );
    		if(!a)return;
		pool.push(a);
		a = NULL;
    }
    Mem* New()
    {
		//return new Mem;
		if( pool.empty() )return new Mem;
		Mem *re;
		re = pool.front();pool.pop();
		*re = Mem();
		return re;
    }
};
bool exist(int x, int y) {
    return (LOWER_RANGE_L <= x && x <= LOWER_RANGE_R && 0 <= y && y < W)
		|| (UPPER_RANGE_L <= x && x <= UPPER_RANGE_R && 0 <= y && y < W)
		|| ((x == 6 || x == 8 || x == 10) && (y == 0 || y == 2 || y == 4));
}
bool exist2(int x, int y) {
    return (LOWER_RANGE_L <= x && x <= UPPER_RANGE_R && 0 <= y && y < W);
}

void show_init(int id)
{
	//give a initializing map here
	//this line : kind1 kind2 ... etc
	//Imagine that the chesses are listed from the bottom to the top, left to right
	//This is a stupid start:
	int opt[25] = //{9, 11, 9, 9, 2, 2, 10, 10, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 1, 0, 3, 3};
	{
		2, 8, 0, 3, 2,
		//3, 9, 7, 4, 3,
		4,   6,   10,
		//5,   7,   11,
		4, 5,   10, 5,
		//5, 6,   11, 6,
		6,   8,   6,
		//1,   9,   7,
		1, 8, 3, 9, 7,
		//2, 9, 4, 10, 8,
		7, 7, 9, 11, 9
		//8, 8, 10, 12, 10
	};
	//Final Version Add it!
	int opt2[25] = //{9, 11, 9, 9, 2, 2, 10, 10, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 1, 0, 3, 3};
	{
		2, 8, 1, 3, 2,
		//3, 9, 7, 4, 3,
		4,   10,   6,
		//5,   7,   11,
		4, 0,   10, 5,
		//5, 6,   11, 6,
		6,   8,   6,
		//1,   9,   7,
		5, 8, 3, 9, 7,
		//2, 9, 4, 10, 8,
		7, 7, 9, 11, 9
		//8, 8, 10, 12, 10
	};
	//swap( opt[2], opt[12] );
	if(SECRET[0])
	for (int i = 24; i >= 0; --i)
		cout << opt2[i] << ' ';
	else
	for (int i = 24; i >= 0; --i)
		cout << opt[i] << ' ';
	cout << endl;
}
void get_init()
{
	int arr0[25], arr1[25];
	for (int i = 0; i < 25; ++i)
	{
		cin >> arr0[i];
		arr0[i] += 1;
		if( id!=0 )arr0[i] = -arr0[i];
	}
	for (int i = 0; i < 25; ++i)
	{
		cin >> arr1[i];
		arr1[i] += 1;
		if( id!=1 )arr1[i] = -arr1[i];
	}
	chessMap[0][0] = arr0[0];
	chessMap[0][1] = arr0[1];
	chessMap[0][2] = arr0[2];
	chessMap[0][3] = arr0[3];
	chessMap[0][4] = arr0[4];
	chessMap[1][0] = arr0[5];
	chessMap[1][1] = arr0[6];
	chessMap[1][2] = arr0[7];
	chessMap[1][3] = arr0[8];
	chessMap[1][4] = arr0[9];
	chessMap[2][0] = arr0[10];
	chessMap[2][2] = arr0[11];
	chessMap[2][4] = arr0[12];
	chessMap[3][0] = arr0[13];
	chessMap[3][1] = arr0[14];
	chessMap[3][3] = arr0[15];
	chessMap[3][4] = arr0[16];
	chessMap[4][0] = arr0[17];
	chessMap[4][2] = arr0[18];
	chessMap[4][4] = arr0[19];
	chessMap[5][0] = arr0[20];
	chessMap[5][1] = arr0[21];
	chessMap[5][2] = arr0[22];
	chessMap[5][3] = arr0[23];
	chessMap[5][4] = arr0[24];

	chessMap[16][4] = arr1[0];
	chessMap[16][3] = arr1[1];
	chessMap[16][2] = arr1[2];
	chessMap[16][1] = arr1[3];
	chessMap[16][0] = arr1[4];
	chessMap[15][4] = arr1[5];
	chessMap[15][3] = arr1[6];
	chessMap[15][2] = arr1[7];
	chessMap[15][1] = arr1[8];
	chessMap[15][0] = arr1[9];
	chessMap[14][4] = arr1[10];
	chessMap[14][2] = arr1[11];
	chessMap[14][0] = arr1[12];
	chessMap[13][4] = arr1[13];
	chessMap[13][3] = arr1[14];
	chessMap[13][1] = arr1[15];
	chessMap[13][0] = arr1[16];
	chessMap[12][4] = arr1[17];
	chessMap[12][2] = arr1[18];
	chessMap[12][0] = arr1[19];
	chessMap[11][4] = arr1[20];
	chessMap[11][3] = arr1[21];
	chessMap[11][2] = arr1[22];
	chessMap[11][1] = arr1[23];
	chessMap[11][0] = arr1[24];
}

short eat( int x, int y )
{
	x = abs(x);y = abs(y);
	if( !y ) return 1;
	if( x==y ) return 0;
	if( 1<=x && x<=9 && 1<=y && y<=9 )
		return x<y? 1:-1 ;
	if( y == 12 ) return 1;
	if( x == 11 || y == 11 )return 0;

	return x == 9 ? 1 : -1;
}
struct Point{
	Point(int a=0,int b=0){x=a;y=b;}
	int x,y;
};
bool operator < (const Point&a,const Point&b)
{
	if(a.x!=b.x) return a.x < b.x;
	return a.y < b.y;
}
struct MoveData
{
	short x[4],y[4];
};
class ChessBoard
{
public:
	ChessBoard(){ map = map_back = NULL; rev = 0; }
	struct MapData
	{
		short data[H][W];
	}mapData[2], *map, *map_back;

	short rev,originCount[25],*Count;
	double NowScore; 
	std::stack<MoveData> steps;
	void init()
	{
		NowScore = 0;
		map = &mapData[0];
		map_back = &mapData[1];
		Count = originCount+12;
		for( int i = 0; i < 17; ++i )
		for( int j = 0; j < 5 ; ++j )
			map->data[i][j] = chessMap[i][j];
	}
	void shift(){ swap( map, map_back ); rev^=1; }
	MoveData getMoveData( int x0, int y0, int x1, int y1 )
	{
		MoveData re;
		short type = eat( map->data[x0][y0], map->data[x1][y1] );
		re.x[0] = x0;re.x[1] = x1;
		re.y[0] = y0;re.y[1] = y1;
		re.x[2] = map->data[x0][y0];
		re.x[3] = map->data[x1][y1];
		re.y[2] = 0;
		if( type )
			re.y[3] = type > 0 ? re.x[2] : re.x[3];
		else
			re.y[3] = 0;
		return re;
	}
	MoveData Move( int x0, int y0, int x1, int y1, short pushit=1 )
	{
		MoveData step = getMoveData( x0,y0, x1,y1 );
		if( pushit )
			steps.push( step );
		move( step );
		return step;
	}
	void Move( const MoveData& step, short pushit=1 )
	{
		if( pushit )
			steps.push( step );
		move( step );
	}
	bool FlashBack(){
		if( steps.empty() )return 0;//{ cerr << "Error." << endl;return; }

		back( steps.top() );
		steps.pop();
		return 1;
	}
	double GetScore( short type = 1 )
	{
		return type*NowScore;
		
		
		double re=0;
		int i,j;
		for( i = 0; i < 17; i++ )
		for( j = 0; j < 5 ; j++ )
		if( exist( i,j ) )
		{
			if( map->data[i][j] < 0 )re -= Score[-map->data[i][j]];
			else re += Score[map->data[i][j]];
		}
		return re*type;
	}
	inline double GScore( int chessId )
	{
		//if( chessId == 0 )return 0;
		return chessId > 0 ? Score[chessId] : -Score[-chessId];
	}
	double GetScore( const MoveData &mdata, short type = 1 )
	{
		double re=0;
		re += GScore(mdata.y[2]) + GScore(mdata.y[3]);
		re -= GScore(mdata.x[2]) + GScore(mdata.x[3]);
		return re*type;
	}
	void move( const MoveData &step )
	{
		int x,y;
		x = step.x[0];y = step.y[0];
		map->data[x][y] = step.y[2];
		x = step.x[1];y = step.y[1];
		map->data[x][y] = step.y[3];
		if(step.x[2])Count[step.x[2]]--;
		if(step.x[3])Count[step.x[3]]--;
		if(step.y[2])Count[step.y[2]]++;
		if(step.y[3])Count[step.y[3]]++;
		
		short type;
		type = step.x[2]>0?+1:-1;
		NowScore += GetScore( step, type );
	}
	void back( const MoveData &step )
	{
		int x,y;
		x = step.x[0];y = step.y[0];
		map->data[x][y] = step.x[2];
		x = step.x[1];y = step.y[1];
		map->data[x][y] = step.x[3];
		if(step.x[2])Count[step.x[2]]++;
		if(step.x[3])Count[step.x[3]]++;
		if(step.y[2])Count[step.y[2]]--;
		if(step.y[3])Count[step.y[3]]--;
		
		short type;
		type = step.x[2]>0?+1:-1;
		NowScore -= GetScore( step, type );
	}
	short checkMove( int x0, int y0, int x1, int y1 )
	{
		if( !exist(x1,y1) )return 0;
		if( !map->data[x1][y1] ) return 1;
		if( map->data[x0][y0]*map->data[x1][y1] > 0 )return 0;
		if( typeMap[x1][y1] == 2 )return 0;
		if( typeMap[x1][y1] == 3 )
			return abs(map->data[x1][y1]) == 12;
		return 1;
	}
	std::vector<Point> fly( int x0, int y0 )
	{
		std::vector<Point> re;
		std::queue<Point> dui;
		int x1,y1;
		Point start(x0,y0),nextp;
		std::map<Point,short> vis;
		dui.push(start);
		vis[start] = 1;
		short first = 0;
        while( !dui.empty() )
		{
			Point NOW = dui.front();dui.pop();
			int x,y;
			if( first ){
				re.push_back(Point(NOW.x,NOW.y));
				if( map->data[NOW.x][NOW.y] )continue;
			}
			else first = 1;
			for( int i = 0; i < 4 ; ++i )
			{
                x = NOW.x + DIR[i][0];
                y = NOW.y + DIR[i][1];
				if( !exist2(x,y) )continue;
				if( typeMap[x][y] == 4 )x+=DIR[i][0],y+=DIR[i][1];
				if( typeMap[x][y] != 1 )continue;
				if( !checkMove( x0,y0, x,y ) )continue;
				nextp = Point(x,y);
				if( vis.count(nextp) )continue;
				dui.push( nextp );
				vis[nextp] = 1;
			}

		}
		return re;
	}
	std::vector<Point> findNext( int x0, int y0 )
	{
		int x1,y1;
		std::vector<Point> re;
		if( !map->data[x0][y0] ) return re;
		if( abs(map->data[x0][y0]) == 10 || abs(map->data[x0][y0]) == 12 )return re;
		if( !exist( x0, y0 ) )
		{
			cerr << "Position Error." << endl;
			return re;
		}
		if( typeMap[x0][y0] == 3 )
			return re;
		if( typeMap[x0][y0] == 2 )
		{
			for( int i = 0 ; i < 8 ; i++ )
			{
				x1 = x0 + DIR[i][0];
				y1 = y0 + DIR[i][1];
				if( checkMove( x0,y0, x1,y1 ) )
					re.push_back( Point(x1,y1) );
			}
			return re;
		}
		if( typeMap[x0][y0] == 0 )
		{
			for( int i = 0 ; i < 8 ; i++ )
			{
				x1 = x0 + DIR[i][0];
				y1 = y0 + DIR[i][1];
				if( i > 3 && ( !exist(x1,y1) || typeMap[x1][y1]!=2 ) )continue;
				if( checkMove( x0,y0, x1,y1 ) )
					re.push_back( Point(x1,y1) );
			}
			return re;
		}
		if( typeMap[x0][y0] == 1 )
		{
			if( abs(map->data[x0][y0]) == 9 )//
			{
				re = fly( x0,y0 );
			}else{
				//dush
				for( int i = 0; i < 4; ++i )
				{
					x1 = x0;y1 = y0;
					while(1)
					{
						x1 = x1 + DIR[i][0];
						y1 = y1 + DIR[i][1];
						if( !exist2(x1,y1) )break;
						if( typeMap[x1][y1] == 4 )continue;
						if( typeMap[x1][y1] != 1 )break;
						if( !checkMove( x0,y0, x1,y1 ) )break;
						re.push_back( Point(x1,y1) );
						if( map->data[x1][y1] != 0 )break;
					}
				}

			}
			//normal go
			for( int i = 0 ; i < 8 ; i++ )
			{
				x1 = x0 + DIR[i][0];
				y1 = y0 + DIR[i][1];
				if( typeMap[x1][y1] == 4 || typeMap[x1][y1] == 1 )continue;
				if( i > 3 && ( !exist(x1,y1) || typeMap[x1][y1]!=2 ) )continue;
				if( checkMove( x0,y0, x1,y1 ) )
					re.push_back( Point(x1,y1) );
			}

			return re;
		}
		cerr<<"<<< ERROR: No return >>>" <<endl;
		return re;
	}
}board;
void initialize()
{
	board.init();

}
void change() {
    int x, y, xx, yy, col, kind;
    cin >> x >> y >> xx >> yy >> col >> kind;
	//cerr << "Get updates:"  << endl;
	//cerr << x << ' ' << y << ' ' << xx << ' ' << yy << ' ' << col << ' ' << kind << endl;
	board.Move( x,y, xx,yy, 0 );

}

std::vector<MoveData> GetAllMove( short type=1 )
{
	std::vector<MoveData> moveList;
	std::vector<Point> stepsList;
	short lose=1;
	for( int i = 0; i < 17; ++i )
	for( int j = 0; j < 5; ++j )
	if( board.map->data[i][j]*type > 0 ){
		if( abs(board.map->data[i][j]) == 12 )lose = 0;
		
		stepsList = board.findNext( i, j );
		for( std::vector<Point>::iterator ii = stepsList.begin(); ii!=stepsList.end(); ++ii )
		{
			moveList.push_back( board.getMoveData( i,j, (*ii).x,(*ii).y ) );
		}
	}
	if( lose )moveList.clear();
	return moveList;
}
struct MoveDataList;
MemoryPool<MoveDataList> MoveDataListPool;
struct MoveDataList
{
	MoveDataList(){ next=NULL; }
	~MoveDataList(){ clear(); }
	MoveDataList *next;
	MoveData data;
	void push( const MoveData &d )
	{
		MoveDataList *l;
		l = MoveDataListPool.New();
//		l = new MoveDataList;
		l->data = d;
		l->next = next;next = l;
	}
	void clear()
	{
		if(next)MoveDataListPool.Delete(next);
			//delete( next );
	}
	void Link( MoveDataList *newList )
	{
		clear();
		next=newList;
	}
};
MoveDataList ThinkingHead;
void printMove( const MoveData& move )
{
	cerr << move.x[0] << "," << move.y[0] << " to " << move.x[1] << "," << move.y[1] << endl;
	cerr << move.x[3] << " change to " << move.y[3] << endl;
}
void Revival( MoveDataList &ListHead )
{
	cerr << "[Revival] Start." << endl;
		cerr << "Now Score: "<< board.NowScore << endl;
	for( MoveDataList *p = ListHead.next; p; p=p->next )
	{
		//cerr << "." << endl;
		board.Move( p->data );
		printMove( p->data );
		cerr << "Now Score: "<< board.NowScore << endl;
	}
	while( board.FlashBack() );
}
double Thinking( MoveDataList &ListHead, short level = 1, short type=1 )
{
	typedef std::vector<MoveData> MoveList;
	double re=LOSE_SCORE, tmp;
	MoveList moveList;
	MoveDataList *head=NULL;

	//if( level > MaxLevel || (clock() - startTime) > 0.9*CLOCKS_PER_SEC )
	if( level > MaxLevel )
	{
		re = board.GetScore( type );
		/*
		if(DEBUG_MODE)
			cerr << "This Step2" << re << endl;*/
		return re;
	}
	moveList = GetAllMove( type );
	if( moveList.empty() )
		return LOSE_SCORE;

	for( MoveList::iterator ii = moveList.begin(); ii != moveList.end(); ++ii )
	{

		//if((clock() - startTime) > 0.9*CLOCKS_PER_SEC) break;

		head = MoveDataListPool.New();
		//head = new MoveDataList;
		head->data = *ii;
		//if(ii->x[2] == -9 && ii->x[3]==)
		board.Move( *ii );
		tmp = -Thinking( *head, level+1, -type );
		board.FlashBack();

		tmp = tmp*0.95+board.GetScore( type );
		/*
		if(DEBUG_MODE)
			cerr << "This Step1" << tmp << endl;*/
		if( tmp > re + eps ){
			re = tmp;
			ListHead.Link( head );
		}else if( fabs(re-tmp)<eps && rand()%10==0 ){
			re = tmp;
			ListHead.Link( head );
		}else
			MoveDataListPool.Delete( head );
			//delete( head );
		//tmp += board.GetScore();



	}
	if(level == 1)
		cerr <<"Best Step:"<< re << "\n";
	return re;
}
void make_decision(int &x, int &y, int &xx, int &yy) {
	
	if(SECRET[0])
	{
		if( (rounds-1) / 2 == 0 )
		{
			if(id == 0)
			{
				x = 4;y = 2;
				xx = x;yy = y-1;
			}else{
				x = 16-4;y = 2;
				xx = x;yy = y+1;
			}
			return;
		}

	}else if(SECRET[1]){
		if( (rounds-1) / 2 == 0 )
		{
			if(id == 0)
			{
				x = 4;y = 0;
				xx = x;yy = y+1;
			}else{
				x = 16-4;y = 4-0;
				xx = x;yy = y-1;
			}
			return;
		}

	}
	MoveData finalMove;
	MoveDataList Head;
	double tmp;
	tmp = Thinking( Head );

	finalMove = Head.next->data;
	x = finalMove.x[0];
	y = finalMove.y[0];
	xx = finalMove.x[1];
	yy = finalMove.y[1];
	printMove( finalMove );
	if(DEBUG_MODE)
		Revival( Head );
	int nowTime = clock();
	if( (nowTime - startTime) > 0.8*CLOCKS_PER_SEC && MaxLevel > 2  )
	//if( rounds > 50 && MaxLevel > 3 )
		MaxLevel--;
	//board.Move( x,y, xx,yy, 0 );
}

inline void end() {
    std::cout << "END\n" << std::flush;
}


int main(int argc, char** argv) {
		//freopen("ai1_stdin.log","r",stdin);
		//freopen("in.txt","r",stdin);
    unsigned seed = time(0);
    if (argc == 2) {
        //cerr << "Excited! Get given seed = " << argv[1] << endl;
        seed = 0;
        for (char *pc = argv[1]; *pc; ++pc)
            seed = seed * 10 + (*pc - '0');
    }

    cerr << "Seed = " << seed << endl;
    //seed = 7933440417;
    srand(seed);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            chessMap[i][j] = 0;
        }
    }
    string op;
    while (true) {
        cin >> op;
        startTime = clock();
        if (op == "id") {
            cin >> id;
			cerr << id << endl;
            cout << "Excalibur ver2.1 [Faker]" << endl;
            end();
		} else if (op == "refresh") {
			get_init();
			initialize();
        } else if (op == "init") {
			show_init(id);
			end();
		} else if (op == "message") {
            change();
            rounds++;
        } else if (op == "action") {
        	//board.Move( 11,2, 10,2 );
        	cerr<<'<'<< MaxLevel<<'>' << endl;
            int x, y, xx, yy;
            make_decision(x, y, xx, yy);
		cerr << x << " " << y << " " << xx << " " << yy << endl;
            cout << x << " " << y << " " << xx << " " << yy << endl;
            end();
        } else if (op == "debug") {
        	DEBUG_MODE=1;
        	MaxLevel = 3;
            int x, y, xx, yy;
            make_decision(x, y, xx, yy);
            //board.Move( x,y, xx,yy, 0 );
            DEBUG_MODE=0;
        } else if (op == "flag") {
        	cerr << "<<<<<<<<<<<<<<<<<<<<<< flag" << endl;
        }
    }
}
