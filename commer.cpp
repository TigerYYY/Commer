//
//  commer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//  https://stepik.org/lesson/221924/step/4?unit=194864
//
//  Решение задачи коммивояжёра полным перебора

#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

// Кол-во городов
int  n = 0;
// Длинны дорог
vector< vector<int> >   a;
// Текущая перестановка
vector<int>   p;
// 
vector<bool>  used;
// INT_MAX
const int  INF = std::numeric_limits<int>::max();
// 
int  ans = INF;

int  count()
{
    int  sum = 0;

    int  beg = 0;
    //const int  end = 0;

    for( const auto d : p )
    {
        sum += a[ beg ][ d ];
        beg = d;
    }

    cout << "   " << sum;
    cout << "\n";

    return  sum;
}

void  out()
{
    for( int  i = 0; i < n; i++ )
    { 
        if( i )  cout << " ";
        cout << p[i];
    }
    //cout << "\n";
}

void  rec( int  idx )
{
    if( idx == n - 1 )
    {
        out();
        ans = min( ans, count() );
        return;
    }
    for( int  i = 1 ; i <= n - 1 ; i++ )
    {
        if( used[ i ] )
        {
            continue;
        }
        p[ idx ] = i;
        used[ i ] = true;
        rec( idx + 1 );
        used[ i ] = false;
    }
}

//   Удалить ' ' и '\t' в начале и в конце строки
//
std::string  trim( const std::string&  s )
{
    size_t startPos = s.find_first_not_of(" \t");
    if ( startPos == std::string::npos )  return "";
    size_t  endPos = s.find_last_not_of(" \t");
    return  s.substr( startPos, endPos - startPos + 1 );
}

//  Прочитать из файла в  a (длинны дорог)
//  Return: 0 - Ok
//
int  read_file( const char*  name )
{
    ifstream  file( name );
    if( file.bad() )
    {
        return  1;
    }
    string  str;
    // 
    if( !getline( file, str ) )
    {
        return  2;
    }
    if( str.empty() )
    {
        return  3;
    }
    // Удалить ' ' и '\t' в начале и в конце строки
    istringstream  iss( trim( str ) );
    vector<int>  numline;
    while( !iss.eof() )
    {
        int  val = 0;
        iss >> val;
        numline.push_back( val );
    }
    if( numline.size() == 0 )
    {
        return  4;
    }
    n = (int)numline.size();
    a.resize( n );
    a[ 0 ] = numline;
    int  nline = 1;
    while( getline( file, str ) )
    {
        if( str.empty() )
        {
            return  3;
        }
        // Удалить ' ' и '\t' в начале и в конце строки
        istringstream  iss( trim( str ) );
        numline.clear();
        while( !iss.eof() )
        {
            int  val = 0;
            iss >> val;
            numline.push_back( val );
        }
        if( numline.size() != n )
        {
            return  7;
        }
        if( ++nline > n )
        {
            return  5;
        }
        a[ nline - 1 ] = numline;
    }
    if( nline < n )
    {
        return  6;
    }
    return  0; //Ok
}

int  main( int  argc, char*  argv[] )
{
    setlocale( LC_ALL, "rus" );

    if( argc == 1 )
    {
        cout << "Ошибка: имя файла с матрицей расстояний не задано";
        return 1;
    }
    if( !filesystem::exists( argv[ 1 ] ) )
    {
        cout << "Ошибка: файла  " << argv[ 1 ] << "  с матрицей расстояний не существует";
        return 2;
    }

    if( read_file( argv[ 1 ] ) != 0 )
    {
        cout << "Ошибка: чтенмя файла";
        return 3;
    }

    cout << "Кол-во городов: " << n << "\n";

    p = vector<int>( n );
    used = vector<bool>( n, false );
    rec(0);

    cout << ans;

    return 0;
}
