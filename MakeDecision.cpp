
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
double Thinking( MoveDataList &ListHead, short level = 1, short type=1, double UpAns=-LOSE_SCORE );
#include "MD_Debug.cpp"
int DfsNumber[30]; 
double Thinking( MoveDataList &ListHead, short level, short type, double UpAns )
{
	
	DfsNumber[level]++;
	
	typedef std::vector<MoveData> MoveList;
	double re=LOSE_SCORE, tmp;
	MoveList moveList;
	MoveDataList *head=NULL;

	//if( level > MaxLevel || (clock() - startTime) > 0.9*CLOCKS_PER_SEC )
	if( level > MaxLevel )
	{
		re = board.GetScore( type );
		
	//	if(DEBUG_MODE)
//			cerr << "This Step2" << re << endl;
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
		double SaveScore = board.NowScore;
		board.Move( *ii );
		/*
		if( board.NowScore < LOSE_SCORE )
		{
			
			cerr << "[ERROR] at This Step1" << board.NowScore << "level of" << level << endl;
			//cerr << "Move: " << ii->x[2] << "," << ii->x[3] <<endl;
			board.FlashBack();
			DEBUG_MODE = 1;
			board.Move( *ii );
			cerr << "[ERROR] at This Step1" << board.NowScore << "level of" << level << endl;
			QUIT = 1;
		}*/
		/*
		if( DEBUG_MODE && level == 1 )
		{
			if( head->data.x[0] == 5 && head->data.y[0] == 1
				&&  head->data.x[1] == 5 && head->data.y[1] == 0 )
					{
						cerr << "catch you"	 << endl;
					}
		}
		*/
		/*
		if( head->data.x[0] == 11 && head->data.y[0] == 0
				&&  head->data.x[1] == 6 && head->data.y[1] == 0 )
					{
						cerr << "catch you1.1"	 << endl;
						DEBUG_MODE = 2;
					}
		if( DEBUG_MODE && level == 1 )
		{
			if( head->data.x[0] == 11 && head->data.y[0] == 0
				&&  head->data.x[1] == 6 && head->data.y[1] == 0 )
					{
						cerr << "catch you1.1"	 << endl;
						DEBUG_MODE = 2;
					}
			if( head->data.x[0] == 11 && head->data.y[0] == 0
				&&  head->data.x[1] == 12 && head->data.y[1] == 1 )
					{
						cerr << "catch you1.2"	 << endl;
					}
		}
		if( DEBUG_MODE==2 && level == 2 )
		{
			if( head->data.x[0] == 8 && head->data.y[0] == 0
				&&  head->data.x[1] == 11 && head->data.y[1] == 0 )
					{
						cerr << "catch you2.1"	 << endl;
					}
			else if(head->data.x[0] == 8 && head->data.y[0] == 0){
				cerr << ">>fucking move to "<< head->data.x[1] <<" "<< head->data.y[1] << endl;
			}
		}*/
		tmp = -Thinking( *head, level+1, -type, -re );
		
		if( DEBUG_MODE==2 && level == 2 )
		{
			if( head->data.x[0] == 8 && head->data.y[0] == 0
				&&  head->data.x[1] == 11 && head->data.y[1] == 0 )
					{
						cerr << "[FUCK]catch you2.1\n"	 << endl;
						//Revival();
						cerr << endl;
					}
			
		}
		board.FlashBack();
		/*
		if( SaveScore != board.NowScore )
		{
			DEBUG_MODE = 1;
			cerr << "[ERROR]" << endl;
			board.Move( *ii );
			board.FlashBack();
			
			QUIT = 1;
		}
		//tmp = tmp*0.95+board.GetScore( type );
		if(DEBUG_MODE)
		{
			if( level == 1 )
			{
				cerr << "This Step1" << tmp << endl;
				
				
			}
		}*/
		if( tmp > re + eps ){
			re = tmp;
			ListHead.Link( head );
			if(level==1&&DEBUG_MODE)
				cerr << "[Update Ans]" << endl;
		}else if( fabs(re-tmp)<eps && rand()%10==0 ){
			re = tmp;
			ListHead.Link( head );
			if(level==1&&DEBUG_MODE)
				cerr << "[Update Ans]" << endl;
		}else
			MoveDataListPool.Delete( head );
			//delete( head );
		//tmp += board.GetScore();
		#ifdef PRUNING 
		if( re > UpAns+eps )
		{
			re = UpAns+1;
			break;
		}
		if( rounds <= 3 )
		{
			if( re+eps > UpAns )
			{
				re = UpAns+1;
				break;
			}
		}else{
			if( re+eps > UpAns && rand()%10==0 )
			{
				re = UpAns+1;
				break;
			}
		}
		#endif
		if(QUIT)break;
	}
	re = re*0.95+board.GetScore( type );
	if(level == 1)
		cerr <<"Best Step:"<< re  << " Addition:" << re-board.GetScore( type ) << endl;
	return re;
}

#include "BFS_Thinking.cpp" 

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
	cerr << "Dfs Number:";
	for( int i = 1; i <= MaxLevel+1; i++ )
	{
		cerr << " [" << i << "] " << DfsNumber[i] ;
		DfsNumber[i] = 0;
	}cerr << endl; 
	if( !Head.next )
		return;
	finalMove = Head.next->data;
	x = finalMove.x[0];
	y = finalMove.y[0];
	xx = finalMove.x[1];
	yy = finalMove.y[1];
	printMove( finalMove );
	if(DEBUG_MODE)
	{
		Revival( Head );
		ReThinking( Head, 2 );
		Head.next->next->data.x[2] = -1;
		Head.next->next->data.y[2] = 0;
		Head.next->next->data.x[3] = 2;
		Head.next->next->data.y[2] = -1;
		Revival( Head );
	}
	int nowTime = clock();
	/*
	if( (nowTime - startTime) > 0.8*CLOCKS_PER_SEC && MaxLevel > 2  )
		MaxLevel--;*/
	//if( rounds > 50 && MaxLevel > 3 )
	//board.Move( x,y, xx,yy, 0 );
}

