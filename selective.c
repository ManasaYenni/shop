#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define maxframes 7
#define windowsize 4
void selective_repeat(int frames)
{
	int ack[frames];
	int i=0,k;
	for(k=0;k<frames;k++)
	{
		ack[k]=0;
	}
	while(i<frames)
	{
		int window=0,j;
		for(j=i;j<i+windowsize&&j<frames;j++)
		{
			if(ack[j]==0)
			{
				printf("sender: sending frame %d\n",j+1);
			}
		}
		sleep(1);
		for(j=i;j<i+windowsize&&j<frames;j++)
		{
			if(ack[j]==0)
			{
				int success=rand()%2;
				if(success==1)
				{
					printf("receiver: received ack of frame %d\n",j+1);
					ack[j]=1;
				}
				else
				{
					printf("receiver: no ack received for frame %d\n",j+1);
				}
			}
		}
		while(i<frames&&ack[i]==1)
		{
			i++;
		}
		printf("\n");
	}
	printf("all frames sent successfully");
}
int main()
{
	int frames;
	printf("enter no.of frames:");
	scanf("%d",&frames);
	selective_repeat(frames);
	return 0;
}
