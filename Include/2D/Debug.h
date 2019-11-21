#ifndef ____DEBUG____
#define ____DEBUG____

//if windows
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

//if linux
// #include <stdlib.h> ( jle met comme ça car on peut pas mettre stlib avant le if car l'ordre est important )
// #define DBG_NEW new
#endif