#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <stdio.h>
typedef struct 
          {
          	int readingpipes[2];
          	int writingpipes[2];
          }array_of_pipes;
int main(void)
{
	pid_t pid;
	int no__of_processes, no_of_messages,i,j;
	int buffersize[1024];
	int readpipe[2];
	int writepipe[2];
	int lasttofirstwritepipe[2];
	int firsttolastreadpipe[2];
	int a,b,c,d,e;
	char buf[]
    
	printf("\n enter number of processes to create: " );
	scanf("%d",&no__of_processes);
	fflush (stdin);

	array_of_pipes pipedesciptors[no__of_processes];

	printf("\n enter number of messages to send: ");
	scanf("%d",&no_of_messages);
	fflush (stdin);
	printf("process are: %d \tmessages are %d\n",no__of_processes,no_of_messages );
	char read_msg_c[no_of_messages][1024];
	char read_msg_p[1024];
	char exitmsg[1024]="terminate all processes have message";

	for(i=0;i<no_of_messages;i++)
	{
		printf("\nenter message %d\n: ",i);
		scanf("%s",read_msg_c[i]);
		
	}
	
	for(i=0 ; i < no__of_processes ; i++)
	{
		pipe(pipedesciptors[i].readingpipes);
	    pipe(pipedesciptors[i].writingpipes);	
	       
	}
	

    for(i=0;i<no__of_processes;i++)
    {
    	pid=fork();
    	
    	if(pid<0)
	    {
			printf("processes could be created\n");
			exit(1);
	    }
	    else if(pid == 0)
	    {   
	    	sleep(1);
	    	close(pipedesciptors[i].readingpipes[1]);
	    	
	    	printf("\nprocess id is %d\n",getpid());
	    	
	    	
	    	read(pipedesciptors[i].readingpipes[0],read_msg_p,sizeof(read_msg_p));
	    	printf("\n%s\n",read_msg_p);
	    	close(pipedesciptors[i].readingpipes[0]);
	    	write(pipedesciptors[i].readingpipes[1],"all processes have the message",strlen(read_msg_p));
	       
	    	    	
	    }

	    else if(pid>0)
	    {    
	    	close(pipedesciptors[i].readingpipes[1]);
	    	if(read(pipedesciptors[i].readingpipes[0],buf,sizeof(buf)) < 0)
                        {
                            printf("\nNo message to read!\n");
                            break;
                        }
            else
	    	for(i=0;i<no__of_processes;i++)
	    	{
	    	close(pipedesciptors[i].readingpipes[0]);
	    	for(j=0;j<no_of_messages;j++)
	    	{

	    		write(pipedesciptors[i].readingpipes[1], 
	    		read_msg_c[j], strlen(read_msg_c[j]));
	    		// close(pipedesciptors[i].writingpipes[0]);
	    
	    	}

	    	}
	    	
	    	

	    }
    }
    return(0);
}
