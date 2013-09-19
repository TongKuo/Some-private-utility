#include <iostream>
#include <string>
#include <algorithm>

int main( int _Argc, char* *_Argv )
    {
    int _ciStringCompare( const std::string&, const std::string& );
        
    std::string _StrOne( "tong g." );
    std::string _StrTwo( "Tong G." );
    
    if ( _ciStringCompare( _StrOne, _StrTwo ) == -1 )
        std::cout << _StrOne << " less than " << _StrTwo << std::endl;
    else if ( !_ciStringCompare( _StrOne, _StrTwo ) )
        std::cout << _StrOne << " equal to " << _StrTwo << std::endl;
    else
        std::cout << _StrOne << " more than " << _StrTwo << std::endl;
#
    return 0;
    }

int _ciCharCompare( char _CharOne, char _CharTwo )
    {
    int _lcOne = std::tolower( static_cast< unsigned char >( _CharOne ) );
    int _lcTwo = std::tolower( static_cast< unsigned char >( _CharTwo ) );

    if ( _lcOne < _lcTwo ) return -1;
    if ( _lcOne > _lcTwo ) return 1;

    return 0;
    }
    
int _ciStringCompareImpl( const std::string& _StrOne,
                          const std::string& _StrTwo )
    {
    typedef std::pair< std::string::const_iterator,
                       std::string::const_iterator > _PSCI;

    _PSCI _Pos = std::mismatch( _StrOne.begin()
                              , _StrOne.end()
                              , _StrTwo.begin()
                              , std::not2( std::ptr_fun( _ciCharCompare ) )
                              );

    if ( _Pos.first == _StrOne.end() )
        {
        if ( _Pos.second == _StrTwo.end() )
            return 0;
        else
            return -1;
        }

    return _ciCharCompare( *_Pos.first, *_Pos.second );
    }
    
int _ciStringCompare( const std::string& _StrOne,
                      const std::string& _StrTwo )
    {
    return ( _StrOne.size() <= _StrTwo.size() ) 
                    ? _ciStringCompareImpl( _StrOne, _StrTwo )
                    : _ciStringCompareImpl( _StrTwo, _StrOne 
           );
    }
