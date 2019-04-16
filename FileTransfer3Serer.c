#include <stdlib.h>   /* Create a algo and add the intruder program into it */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 20000 
#define BACKLOG 5
#define LENGTH 512 

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main ()
{
	
	int sockfd; 
	int nsockfd; 
	int num;
	int sin_size; 
	struct sockaddr_in addr_local; 
	struct sockaddr_in addr_remote; 
	char revbuf[LENGTH]; 

	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
	    error("ERROR: Failed to obtain Socket Descriptor.\n");
	}
	else 
		printf("[Server] Obtaining socket descriptor successfully.\n");

	
	addr_local.sin_family = AF_INET; 
	addr_local.sin_port = htons(PORT); 
	addr_local.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(addr_local.sin_zero), 8); 

	
	if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
	{
	    error("ERROR: Failed to bind Port.\n");
	}
	else 
		printf("[Server] Binded tcp port %d in addr 127.0.0.1 sucessfully.\n",PORT);

	if(listen(sockfd,BACKLOG) == -1)
	{
	    error("ERROR: Failed to listen Port.\n");
	}
	else
		printf ("[Server] Listening the port %d successfully.\n", PORT);

	int success = 0;
	while(success == 0)
	{
	    sin_size = sizeof(struct sockaddr_in);

	    if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1) 
		{
	        error("ERROR: Obtaining new Socket Despcritor.\n");
		}
	    else 
			printf("[Server] Server has got connected from %s.\n", inet_ntoa(addr_remote.sin_addr));

		char* fr_name = "/home/rishabh/Desktop/ProjectMinor/Final/all_in_one_labeled.csv";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
			printf("File %s Cannot be opened file on server.\n", fr_name);
		else
		{
			bzero(revbuf, LENGTH); 
			int fr_block_sz = 0;
			
			    while(fr_block_sz = recv(nsockfd, revbuf, LENGTH, 0)) 
			    {
			        if(fr_block_sz < 0)
			        {
			            error("Error receiving file from client to server.\n");
			        }
			        int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
			        if(write_sz < fr_block_sz)
			        {
			            error("File write failed on server.\n");
			        }
					else if(fr_block_sz)
					{
						break;
					}
			        bzero(revbuf, LENGTH);
			    }
			    printf("Ok received from client!\n");
			    fclose(fr);
			
		}

		
		system("cd ; chmod +x script.sh ; ./script.sh");

		
	        char* fs_name = "/home/rishabh/Desktop/ProjectMinor/Final/malicious.csv";
	        char sdbuf[LENGTH]; 
	        printf("[Server] Sending %s to the Client...", fs_name);
	        FILE *fs = fopen(fs_name, "r");
	        if(fs == NULL)
	        {
	            printf("ERROR: File %s not found on server.\n", fs_name);
				exit(1);
	        }

	        bzero(sdbuf, LENGTH); 
	        int fs_block_sz; 
	        while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
	        {
	            if(send(nsockfd, sdbuf, fs_block_sz, 0) < 0)
	            {
	                printf("ERROR: Failed to send file %s.\n", fs_name);
	                exit(1);
	            }
	            bzero(sdbuf, LENGTH);
	        }
	        printf("Ok sent to client!\n");
	        success = 1;
	        pclose(nsockfd);
	        printf("[Server] Connection with Client closed. Server will wait now...\n");
	        while(waitpid(-1, NULL, WNOHANG) > 0);
	    //}
	}
}
