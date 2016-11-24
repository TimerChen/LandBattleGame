#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
char tmp[10000],tmp2[10000];
const char* GetName( char aline[] )
{
	int l,r;
	strcpy( tmp2, strstr( aline, "\"" )+1 );
	*(strstr( tmp2, "\"" )) = 0;
	return tmp2;
}
void MergeIt( const char InName[], FILE* fout )
{
	FILE *fin;
	fin = fopen(InName,"r");
	short re;
	
	fscanf(fin,"%[\n]",tmp);
	while( fscanf(fin,"%[^\n]",tmp) !=EOF )
	{
		if( strstr( tmp, "#include" )!=NULL && strstr( tmp, "\"")!=NULL )
		{
			MergeIt( GetName(tmp), fout );
		}else{
			fprintf( fout, "%s\n",tmp);
		}
		fscanf(fin,"%[\n]",tmp);
	}
	fclose(fin);
}
int main( int argc, char *argv[] )
{
	if(argc<2)
	{
		printf("Form Error!\n");
		return 1;
		argv[1] = "testing.cpp";
	}
	int i,j;
	//printf("%d %s\n",argc,argv[1]);
	printf( "Merge file [%s] ......",argv[1] );
	char OutName[100];
	if(argc==3)
	{
		sprintf(OutName,"%s",argv[2]);
	}else{
		sprintf(OutName,"M_%s",argv[1]);
	}
	FILE 
		*fout=fopen(OutName,"w");
	MergeIt( argv[1], fout );
	fclose(fout);
	printf( "succeeded at [%s].\n", OutName );
	return 0;
}
