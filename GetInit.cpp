void show_init(int id)
{
	//give a initializing map here
	//this line : kind1 kind2 ... etc
	//Imagine that the chesses are listed from the bottom to the top, left to right
	//This is a stupid start:
	int opt_old[25] = //{9, 11, 9, 9, 2, 2, 10, 10, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 1, 0, 3, 3};
	{
		1, 8, 0, 3, 2,
		//3, 9, 7, 4, 3,
		4,   6,   10,
		//5,   7,   11,
		4, 10,   5, 5,
		//5, 6,   11, 6,
		6,   8,   6,
		//1,   9,   7,
		2, 8, 3, 9, 7,
		//2, 9, 4, 10, 8,
		7, 7, 9, 11, 9
		//8, 8, 10, 12, 10
	};
	int opt[25] = //{9, 11, 9, 9, 2, 2, 10, 10, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 1, 0, 3, 3};
	{
		2, 8, 0, 3, 2,
		//3, 9, 7, 4, 3,
		4,   6,   10,
		//5,   7,   11,
		4, 10,   5, 5,
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
