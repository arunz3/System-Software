#include<stdio.h>
#include<conio.h>


void findWaitingTime(int n, int bt[], int wt[])
{
	int i;
	wt[0] = 0;
	for (i=1 ; i < n; i++)
		wt[i] = bt[i-1]+wt[i-1];
}

void findTurnAroundTime(int n, int bt[], int wt[], int tat[])
{
	int i;
	for(i = 0; i < n; i++)
		tat[i] = wt[i] + bt[i];
}
void FCFSAlgorithm(int n, int bt[],int wt[], int tat[])
{
	int i;
	findWaitingTime(n,bt,wt);
	findTurnAroundTime(n,bt,wt,tat);
	printf("P BT WT TAT\n");
	for (i=0; i<n ; i++)
	{
		printf("%d",i+1);
		printf(" %d",bt[i]);
		printf("  %d",wt[i]);
		printf("   %d",tat[i]);
		printf("\n");
	}
}
void SJF(int n,int bt[],int wt[],int tat[])
{
		int i,j,temp;
		for(i = 0;i < n; i++){
			int pos = i;
			for(j = i+1; j < n; j++){
				if(bt[j] < bt[pos]){
					pos = j;
				}
				temp = bt[i];
				bt[i] = bt[pos];
				bt[pos] = temp;
			}
		}
		FCFSAlgorithm(n,bt,wt,tat);
}
void Priority(int n,int bt[],int wt[], int tat[], int pr[],int p[]){
	int i,j,temp, pos,total;
	for(i=0;i<n;i++)
	 {

			 pos=i;
			 for(j=i+1;j<n;j++)
			 {
					 if(pr[j]<pr[pos])
							 pos=j;
			 }

			 temp=pr[i];
			 pr[i]=pr[pos];
			 pr[pos]=temp;

			 temp=bt[i];
			 bt[i]=bt[pos];
			 bt[pos]=temp;

			 temp=p[i];
			 p[i]=p[pos];
			 p[pos]=temp;
	 }
	 wt[0]=0;	//waiting time for first process is zero

	 //calculate waiting time
	 for(i=1;i<n;i++)
	 {
			 wt[i]=0;
			 for(j=0;j<i;j++)
					 wt[i]+=bt[j];

		     total+=wt[i];
	 }

	 printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
	 for(i=0;i<n;i++)
	 {
			 tat[i]=bt[i]+wt[i];     //calculate turnaround time
			 total+=tat[i];
			 printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
	 }

}
void RoundRobin()
{
	     int count,j,n,time,remain,flag=0,time_quantum;
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10];
  printf("Enter Total Process:\t ");
  scanf("%d",&n);
  remain=n;
  for(count=0;count<n;count++)
  {
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1);
    scanf("%d",&at[count]);
    scanf("%d",&bt[count]);
    rt[count]=bt[count];
  }
  printf("Enter Time Quantum:\t");
  scanf("%d",&time_quantum);
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
  for(time=0,count=0;remain!=0;)
  {
    if(rt[count]<=time_quantum && rt[count]>0)
    {
      time+=rt[count];
      rt[count]=0;
      flag=1;
    }
    else if(rt[count]>0)
    {
      rt[count]-=time_quantum;
      time+=time_quantum;
    }
    if(rt[count]==0 && flag==1)
    {
      remain--;
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
      wait_time+=time-at[count]-bt[count];
      turnaround_time+=time-at[count];
      flag=0;
    }
    if(count==n-1)
      count=0;
    else if(at[count+1]<=time)
      count++;
    else
      count=0;
  }
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n);
}
void main()
{

	int ch,n,i, tat[20],wt[20],bt[20],p[20],pr[20];
	//clrscr();
	printf("Enter number of process:");
	scanf("%d",&n);
	printf("\n Enter process Burst time & Priority:\n");
	for(i=0 ; i<n; i++)
	{
		printf("P[%d]:",i+1);
		printf("Burst Time:");
			 scanf("%d",&bt[i]);
			 printf("Priority:");
			 scanf("%d",&pr[i]);
			 p[i]=i+1; //process number
	}
	printf("Stimulate:\n 1.FCFSAlgorithm\n 2.SFF\n 3.Priority\n 4.Round Robin\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
					FCFSAlgorithm(n,bt,wt,tat);
					break;
		case 2:
					SJF(n,bt,wt,tat);
					break;
		case 3:
					Priority(n,bt,wt,tat,pr,p);
					break;
	       	case 4:
					RoundRobin();
					break;
		default:
					printf("Wrong input\n");
	}
	getch();
}
