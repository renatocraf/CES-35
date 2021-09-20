#ifndef __CONNECTION_THREAD__
#define __CONNECTION_THREAD__



#include <request.h>

using namespace std;

typedef struct
{
    int sa;
    char * h_addr;
} connection_data;

void * connectionHandle(void *arg);

#endif // __CONNECTION_THREAD__
