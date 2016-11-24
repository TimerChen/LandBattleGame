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
