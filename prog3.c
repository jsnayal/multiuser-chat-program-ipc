#include<stdio.h>
#include<string.h>
#include<sys/shm.h>
#include<stdlib.h>
#include"common.h"


int main()
{
	struct com *shared;
	int shmid;
	int i,j,temp,k;
	shmid=shmget((key_t)1234,sizeof(struct com),0666 | IPC_CREAT);
	
	if(shmid==-1)
	{
		printf("Shared memory not created\n");
		exit(0);
	}
	
	shared=shmat(shmid,(void *)0,0);
	
	while(1)
	{
		if(shared->flag==3)
		{
				system("clear");
				printf("Recieved Matrix 1 is \n");
			for(i=0;i<shared->row;i++)
			{
				for(j=0;j<shared->col;j++)
				{
					printf("%d ",(shared->array1[i][j]));
				}
				printf("\n");
			}		
				printf("\nRecieved Matrix 2 is \n");
			for(i=0;i<shared->row;i++)
			{
				for(j=0;j<shared->col;j++)
				{
					printf("%d ",(shared->array2[i][j]));
				}
				printf("\n");
			}
				for(i=0;i<shared->row;i++) //Addition of two matrix
				{
					for(j=0;j<shared->col;j++)
					{	
						shared->add[i][j]=shared->array1[i][j]+shared->array2[i][j];
					}
				}

				
				for(i=0;i<shared->col;i++) //multi of two matrix
				{
					for(j=0;j<shared->row;j++)
					{	
						temp=0;
						for(k=0;k<shared->row;k++)
							{
							   temp+=shared->array1[k][i]*shared->array2[j][k];	
							}
						shared->multi[i][j]=temp;
			
					}
				}
			shared->flag=2;
			break;

		}
	}
  return 0;
}
