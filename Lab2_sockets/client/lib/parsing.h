#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define BUFSIZE 4096  /* block transfer size */

using namespace std;

void separarURL(string url,char *host, long int &port, char *file,char *nomeArq);
void cabecalho(char *getReq, char file[],char host[]);
long int separarResp(string buf,char *respHeader,char *resp, int &sizeHeader, int &sizeResp);