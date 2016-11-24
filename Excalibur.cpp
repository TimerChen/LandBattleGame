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
#include "Variable.cpp"
#include "MemoryPool.cpp"
bool exist(int x, int y) {
    return (LOWER_RANGE_L <= x && x <= LOWER_RANGE_R && 0 <= y && y < W)
		|| (UPPER_RANGE_L <= x && x <= UPPER_RANGE_R && 0 <= y && y < W)
		|| ((x == 6 || x == 8 || x == 10) && (y == 0 || y == 2 || y == 4));
}
bool exist2(int x, int y) {
    return (LOWER_RANGE_L <= x && x <= UPPER_RANGE_R && 0 <= y && y < W);
}

#include "GetInit.cpp" 

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
#include "ChessBoard.cpp" 
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
#include "MakeDecision.cpp"

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
