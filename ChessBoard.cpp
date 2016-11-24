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
	void FlashBack(){
		if( steps.empty() ){ cerr << "Error." << endl;return; }

		back( steps.top() );
		steps.pop();
	}
	double GetScore( short type = 1 )
	{
		return NowScore;
		
		
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
	double GetScore( const MoveData &mdata, short type = 1 )
	{
		double re=0;
		re += Score[(int)abs(mdata.y[2])] + Score[(int)abs(mdata.y[3])];
		re -= Score[(int)abs(mdata.x[2])] + Score[(int)abs(mdata.x[3])];
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
		cerr<<"No return" <<endl;
	}
}board;
