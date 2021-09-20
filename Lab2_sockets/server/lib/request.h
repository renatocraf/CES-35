#ifndef __REQUEST__
#define __REQUEST__

#include <string>

#define BUF_SIZE 4096  /* block transfer size */
#define GET "GET"

using namespace std;

void criarResp(long int status,int fd, string filename, char *respHeader, char *resp);
void tratarSolic(string buf,long int &status, char *respHeader, char *resp);

#endif // __REQUEST__
