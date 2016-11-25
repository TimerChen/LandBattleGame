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
