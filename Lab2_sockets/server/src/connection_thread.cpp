#include <connection_thread.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void * connectionHandle(void *arg)
{
   printf("Solicitação recebida: %d\n",(int) pthread_self() );

   char buf[BUF_SIZE];  /* buffer for outgoing file */
   strcpy(buf," ");
   long int status=0;
   
   connection_data * conn = ((connection_data *)arg);
   read(conn->sa, buf, BUF_SIZE); /* read file name from socket */
   char resp[BUF_SIZE],respHeader[BUF_SIZE];
   tratarSolic(buf,status,respHeader,resp);//,conn->h_addr);
   strcpy(buf,respHeader);
   strcat(buf,resp);
   write(conn->sa,buf,BUF_SIZE);
   printf("Resposta enviada: %d. Status: %ld\n",(int) pthread_self(), status);
   
   close(conn->sa); /* close connection */  
   free(conn);
   pthread_exit(0);
         
}
