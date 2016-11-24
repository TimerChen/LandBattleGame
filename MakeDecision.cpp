
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
#include "MD_Debug.cpp"
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
