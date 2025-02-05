#include<stdio.h>
int main()
{
	int windowsize,sent=0,ack=0,totalframes,i;
	printf("enter the total no.of frames to be sent:");
	scanf("%d",&totalframes);
	printf("enter window size:");
	scanf("%d",&windowsize);
	while(sent<=totalframes)
	{
		for(i=0;i<windowsize&&sent<totalframes;i++)
		{
			printf("frames %d has been transmitted\n",sent++);
		}
		printf("please enter the last acknowledgment recieved frame:");
		scanf("%d",&ack);
		if(ack==totalframes)
		{
			printf("all frames successfully acknowledged\n");
			break;
		}
		else if(ack<sent)
		{
			printf("ack recieved from frame %d retransmitted from frame %d\n",ack,ack+1);
			sent=ack;
		}
		else if(ack>sent)
		{
			printf("invalid input");
		}
	}
	return 0;
}
