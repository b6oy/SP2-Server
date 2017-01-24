#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <assert.h>

using namespace std;

//void Assertion(const char * assertion, const char * file, const uint32 line);
#define ASSERT(assertion) { if( !(assertion) ) { /*Assertion(#assertion, __FILE__, __LINE__);*/ assert( assertion &&0); } }
//void Error(const string str, const char * file, const uint32 line);
#define ERR(str)	{ /*Error(str, __FILE__, __LINE__)*/; }

#define NULL 0

typedef unsigned long long uint64;
typedef signed long long int64;
typedef unsigned long uint32;
typedef signed long int32;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned char uint8;
typedef signed char int8;

#include <list>
#define LinkedList std::list
#ifdef __MINGW32__
#include <tr1\unordered_map>
#define HashMap std::tr1::unordered_map
#else
#include <unordered_map>
#define HashMap std::unordered_map
#endif
#include <map>
#define Map std::map
#include <vector>
#define Vector std::vector
#define AutoPtr std::auto_ptr

//-------------------------------------------MACROS----------------------------------------------------------
#define foreach(x,y)		for(decltype(( y ).begin()) x = ( y ).begin(); x != ( y ).end(); ++x)
#define foreach_a(x,y)	for(decltype(&( y )[0]) x = &( y )[0]; x < &( y )[0] + (sizeof( y )/sizeof(( y )[0])); x++)

#endif // TYPEDEFS_H
