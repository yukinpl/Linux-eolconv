#include <iostream>
#include <filesystem>
#include <fstream>


void ShowUsage( char const * name ) ;
bool const IsExisted( char const * target ) ;
bool const Conv( char const * target ) ;


int main( int argc , char * argv[] )
{
	if( 2 != argc )
	{
		ShowUsage( argv[ 0 ] ) ;
		return 0 ;
	}

	if( false == IsExisted( argv[ 1 ] ) )
	{
		std::cout << "The file [" << argv[1] << "], is not existed " << std::endl ;
		return 0 ;
	}

	return Conv( argv[1] ) ;
}


void ShowUsage( char const * name )
{
	std::cout << "Usage: " << name << " target-filename " << std::endl ;
}


bool const IsExisted( char const * target )
{
	namespace fs = std::filesystem ;

	fs::path p ;
	p = target ;

	return fs::exists( p ) ;
}


bool const Conv( char const * target )
{
	using s = std::ios_base ;

	std::ifstream ifs ;
	ifs.open( target , s::in | s::binary ) ;

	

	ifs.close() ;

	return true ;
}
