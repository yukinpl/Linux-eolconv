#include <iostream>
#include <filesystem>
#include <fstream>


enum class TYPE : uint8_t 
{
	DOS     = 0 ,
	UNIX    = 1 ,
	UNKNOWN = UINT8_MAX , 
} ;

void ShowUsage( char const * name ) ;
bool const IsExisted( char const * target ) ;
bool const Conv( char const * source , char const * target ) ;
TYPE const FindType( std::ifstream & ifs ) ;

int main( int argc , char * argv[] )
{
	if( 3 != argc )
	{
		ShowUsage( argv[ 0 ] ) ;
		return 0 ;
	}

	if( false == IsExisted( argv[ 1 ] ) )
	{
		std::cout << "The file [" << argv[ 1 ] << "], is not existed " << std::endl ;
		return 0 ;
	}

	if( true  == IsExisted( argv[ 2 ] ) )
	{
		std::cout << "The file [" << argv[ 2 ] << "], is existed " << std::endl ; 
		return 0 ;
	}

	return Conv( argv[ 1 ] , argv[ 2 ] ) ;
}


void ShowUsage( char const * name )
{
	std::cout << "Usage: " << name << " source-filename target-filename" << std::endl ;
}


bool const IsExisted( char const * target )
{
	namespace fs = std::filesystem ;

	fs::path p ;
	p = target ;

	return fs::exists( p ) ;
}


bool const Conv( char const * source , char const * target )
{
	using s = std::ios ;

	std::ifstream ifs ;
	ifs.open( source , s::in | s::binary ) ;

	std::ofstream ofs ;
	ofs.open( target , s::out | s::binary ) ;

	if( false == ifs.is_open() )
	{
		std::cerr << "Fail to open the file [" << source << "]." << std::endl ;
		return false ;
	}

	if( false == ofs.is_open() )
	{
		std::cerr << "Fail to open the file [" << target << "]." << std::endl ;
		return false ;
	}

	TYPE type = FindType( ifs ) ;
	if( TYPE::UNKNOWN == type )
	{
		std::cout << "needless to conversion" << std::endl ;
		return false ;
	}
	else if( TYPE::DOS == type )
	{
		std::cout << "conversion from DOS to UNIX: " << target << std::endl ;
	}
	else if( TYPE::UNIX == type )
	{
		std::cout << "conversion from UNIX to DOS: " << target << std::endl ;
	}
	
	ifs.seekg( std::ios::beg ) ;
	
	char const linefeed[ 2 ] = { '\r' , '\n' } ;
	char buf[ 2048 + 2 ] ;
	while( true )
	{
		if( ifs.eof() )
		{
			break ;
		}

		ifs.read( buf , 1 ) ;

		if( linefeed[ 0 ] == buf[ 0 ] )
		{
			continue ;
		}
		else if( TYPE::DOS == type && linefeed[ 1 ] == buf[ 0 ] )
		{
			ofs.write( &( linefeed[ 1 ] ) , 1 ) ;
		}
		else if( TYPE::UNIX == type && linefeed[ 1 ] == buf[ 0 ] )
		{
			ofs.write( linefeed , 2 ) ;
		}
		else
		{
			ofs.write( buf , 1 ) ;
		}
	}

	ofs.close() ;
	ifs.close() ;

	return true ;
}


TYPE const FindType( std::ifstream & ifs )
{
	char prev , curr ;

	TYPE ret = TYPE::UNKNOWN ;

	while( ifs.read( & curr , 1 ) )
	{
		/**/ if( '\r' == prev && '\n' == curr )
		{
			ret = TYPE::DOS ;
			break ;
		}
		else if( '\r' != prev && '\n' == curr )
		{
			ret = TYPE::UNIX ;
			break ;
		}

		if( prev != curr )
		{
			prev = curr ;
		}
	}

	ifs.seekg( std::ios::beg ) ;

	return ret ;
}
