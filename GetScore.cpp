
	inline double GScore( int chessId )
	{
		//if( chessId == 0 )return 0;
		return chessId > 0 ? Score[chessId] : -Score[-chessId];
	}
	double GetScore( const MoveData &mdata )
	{
		#ifdef OLDSCORE
		return DirectGetScore( mdata );
		#endif
		
		if( abs(mdata.x[2]) == 11 )
			return MissileGetScore( mdata );
		else if( abs(mdata.x[3]) == 11 )
		{
			MoveData revMdata;
			revMdata = mdata;
			swap( revMdata.x[3], revMdata.x[2] );
			return MissileGetScore( revMdata );//??
		}
		return DirectGetScore( mdata );
	}
	double DirectGetScore( const MoveData &mdata )
	{
		double re=0;
		re += GScore(mdata.y[2]) + GScore(mdata.y[3]);
		re -= GScore(mdata.x[2]) + GScore(mdata.x[3]);
		return re;
	}
	double MissileGetScore( const MoveData &mdata )
	{
		if(mdata.x[3] == 0)return 0;
		
		short type = mdata.x[2] > 0 ? +1 : -1;
		if( abs(mdata.x[3]) == 10 ) return GScore( mdata.x[3] );
		if( abs(mdata.x[3]) == 12 ) return GScore( mdata.x[3] );
		if( abs(mdata.x[3]) == 11 )//...
		{
			if( Count[ mdata.x[2] ] > Count[ mdata.x[3] ] )
				return Score[11]*type;
			else 
				return -Score[11]*type;
		}
		if( abs(mdata.x[3]) == 1  )
		{
			return Score[1]*type;
		}else if( abs(mdata.x[3]) == 2 ){
			if( Count[ mdata.x[2] ] == 2 )
				//return 70*type;
				return -GScore( mdata.x[3] );
			else if( Count[ mdata.x[2] ] == 1  )
			{ 
				if( Count[-type*1] )
					return -GScore( mdata.x[3] )/10;
				else 
					return -GScore( mdata.x[3] );
					//return 100*type;
				//return -0.5*GScore( mdata.x[2] )-GScore( mdata.x[3] ); 
			}
		}else if( abs(mdata.x[3]) <= 8 )
		{
			if( abs(mdata.x[3]) >=1 && Count[ -type*1 ] + Count[ -type*2 ] == 0 )
			{
				int i;
				for( i = 3; i <= 8; i++ )
					if( Count[ -type*i ] )break;
				if( i == abs( mdata.x[3] ) )
					return -GScore( mdata.x[3] )/10;//?
			}
			return -GScore( mdata.x[2] );
		}else if( abs(mdata.x[3]) == 9 ){
			//...
			/*
			if( Count[ mdata.x[2] ] == 2 )
				return -0.7*GScore( mdata.x[2] )-GScore( mdata.x[3] );
			else if( Count[ mdata.x[2] ] == 1 )
				return -1.0*GScore( mdata.x[2] )-GScore( mdata.x[3] ); 
			*/
		}
		
		return DirectGetScore( mdata );
	}

