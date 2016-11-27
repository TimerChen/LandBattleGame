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
void ReThinking( MoveDataList &ListHead, short deep = 1, short tMaxLevel = MaxLevel ){
	cerr << "[ReThink] Start." << endl;
		cerr << "Now Score: "<< board.NowScore << endl;
	int i=1;
	MoveDataList *p=&ListHead;
	short  type = 1;
	for( i=1; i<deep; p=p->next,i++ )
	{
		//cerr << "." << endl;
		board.Move( p->next->data );
		printMove( p->next->data );
		cerr << "Now Score: "<< board.NowScore << endl;
		type*=-1;
	}
	double tmp;
	DEBUG_MODE = 2;
	swap(tMaxLevel,MaxLevel);
	tmp = Thinking( *p, deep, type );
	Revival( *p );
	swap(tMaxLevel,MaxLevel);
	DEBUG_MODE = 1;
}
