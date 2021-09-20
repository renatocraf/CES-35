#include <request.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <netdb.h>
#include <fcntl.h>
//para usar o inet_ntoa, include arpa/inet
#include <arpa/inet.h>

void criarResp(long int status,int fd, string filename, char *respHeader, char *resp)
{
   char aux[BUF_SIZE];
   time_t rawtime;
   time(&rawtime);
   char statusStr[20];
   int contentLen;
   

   if(status == 200)
   {
      strcpy(statusStr,"200 OK");      
      read(fd, aux, BUF_SIZE);
      contentLen = sprintf(resp,"%s",aux);
      close(fd);
   }
   else if(status == 404)
   {
      strcpy(statusStr,"404 Not Found");      
      contentLen = sprintf(resp,"<!DOCTYPE HTML PUBLIC>\n<html><head>\n<title>404 Not Found</title>\n</head><body>\n<h1>Not Found</h1>\n<p>The requested URL %s was not found on this server.</p>\n</body></html>\n",filename.c_str());

   }
   else
   {
      strcpy(statusStr,"400 Bad Request");      
      contentLen = sprintf(resp,"<!DOCTYPE HTML PUBLIC >\n<html><head>\n<title>400 Bad Request</title>\n</head><body>\n<h1>Bad Request</h1>\n<p>Your browser sent a request that this server could not understand.<br /></p>\n</body></html>\n");
   }   
   sprintf(respHeader,"HTTP/1.1 %s\r\nDate: %sServer: web-server\r\nContent-Length: %d\r\nContent-Type: text/html; charset=iso-8859-1\r\n\r\n",statusStr,ctime(&rawtime),contentLen);

}


void tratarSolic(string buf,long int &status, char *respHeader, char *resp)//,  char *h_addr)
{   
   //printf("BUFF: %s\n",buf.c_str() );
   status=200;
   int inicio,fim,fim2,fd;
   string filename;
  
   


   //observando se é GET
   string aux = buf.substr(0,3);
    
   if(strcmp(aux.c_str(),GET)!=0) status = 400;   
   //observando o host 
      //host do server
   char host[] = "localhost";
   struct hostent *h;
   h = gethostbyname(host);
   char addressHost[20];
   strcpy(addressHost,inet_ntoa(*(struct in_addr*)h->h_addr));
   //printf("Host by addr %s\n",addressHost);
   
      //host do cliente
   inicio = buf.find("Host: ")+6;
   fim = buf.find("\r\n",inicio);
   fim2 = buf.find(":",inicio);
   if(fim2> 0 && fim2<fim)
      fim = fim2;
   aux = buf.substr(inicio,fim-inicio);

   
   struct hostent *hClient;

   hClient = gethostbyname(aux.c_str());

   char addressHostClient[20];
   strcpy(addressHostClient,inet_ntoa(*(struct in_addr*)hClient->h_addr));
   //printf("Host do Cliente: %s\n",addressHostClient);

   if(strcmp(addressHostClient,addressHost)!=0) status = 400;
   //if(strcmp(aux.c_str(),h_name)!=0) status = 400;

   if(status==200)
   {
      //pegando filename
      inicio = 5;
      fim = buf.find(" ",inicio);      
      filename = buf.substr(inicio,fim-inicio);
      //tentando abrir filename
      fd = open(filename.c_str(), O_RDONLY);
      if (fd < 0)
      {
         printf("Arquivo %s invalido:open failed!\n",filename.c_str());
         status = 404;
      } 
   }
   
   criarResp(status,fd,filename, respHeader,resp);
   
   return;
}
