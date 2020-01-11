#ifndef ____DEBUG____
#define ____DEBUG____

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
 #include <stdlib.h>
 #define DBG_NEW new
#endif

#endif