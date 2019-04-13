#include<stdio.h>
#include<windows.h>
#define apex 10000000

int main()
{
	int n,i,j,k,temp,temp2,total,total_time=0,count=0,avg_WT=0,avg_TAT=0;

	printf("------------------------------------------------------------------------------------------------------------\n");

	printf("Enter the number of processes: ");
	scanf("%d",&n);
	printf("=-----------------------------------------------------------------------------------------------------------\n");

	int p[n],at[n],bt[n];
	int wt[n+1];
	int tat[n+1];
	int r[n];

	printf("Enter arrival time:\n\n");
	for(i=0;i<n;i++)
	{
		printf("P%d \t",i+1);
		scanf("%d",&at[i]);
		p[i]=i+1;
	}

    printf("\n------------------------------------------------------------------------------------------------------------\n");

	printf("Enter burst time:\n\n");
    for(i=0;i<n;i++)
	{
		printf("P%d \t",i+1);
		scanf("%d",&bt[i]);
		p[i]=i+1;
	}

    // calculates total time taken by processor
	for(i=0;i<n;i++)
    {
        if(at[i]!=0)
        {
            total_time+=bt[i];
            total_time+=2;
        }

    }
    total_time-=2;

	printf("------------------------------------------------------------------------------------------------------------\n");
	// sorts processes w.r.t. arrival time
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(at[j]>at[j+1])
			{
				int c=at[j];
				at[j]=at[j+1];
				at[j+1]=c;

				c=bt[j];
				bt[j]=bt[j+1];
				bt[j+1]=c;

				c=p[j];
				p[j]=p[j+1];
				p[j+1]=c;
			}
		}
	}

    // shows discarded or executed message
	for(i=0;i<n;i++)
	{
		Sleep(1500);

		if(at[i]==0)
		{
			printf("P%d Discarded(because arrival time is 0)\n\n",p[i]);
		}

		else
		{
			printf("P%d will be executed\t\n",p[i]);
		}
	}

	printf("\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("PROCESS\tARRIVAL TIME\tBURST TIME\n\n");

    //displays all processes
	for(i=0;i<n;i++)
	{
		Sleep(1500);
		printf("P%d\t%d\t\t%d\n\n",p[i],at[i],bt[i]);
	}

    // sets waiting time (for processes with arrival time 0) to -1
	for(i=0;i<n;i++)
	{
		if(at[i]!=0)
		break;
		wt[p[i]]=-1;
		count++;
	}

	k=count;//number of processes with arrival time 0

    // calculates waiting time and turnaround time for each process
	for(total=1;n-count>0;)
	{
		for(i=k;i<n;i++)
		{
			if(at[i]>total)
			{
				total++;
				i=i-1;
				continue;
			}

			temp=apex;
			temp2=i;

			for(j=i;j<n && at[j]<=total;j++)
			{
				if(bt[j]<temp&&r[j]!=1)
				{
					temp=bt[j];
					temp2=j;
				}
			}

			wt[p[temp2]]=total-at[temp2];
			tat[p[temp2]]=wt[p[temp2]]+temp;
			total=total+bt[temp2]+2;
			r[temp2]=1;
			count++;
			break;
		}
	}

	printf("PROCESS\tWAITING TIME\t TURNAROUND TIME\n\n");
    for(i=1;i<=n;i++)
	{
	    Sleep(1500);

		if(wt[i]==-1)
		printf("P%d\tDISCARDED\tDISCARDED\n\n",i);

		else
		{
		    // calculates avg waiting time and avg turnaround time
			printf("P%d\t%d\t\t%d\n\n",i,wt[i],tat[i]);
			avg_WT+=wt[i];
			avg_TAT+=tat[i];
		}
    }

    printf("------------------------------------------------------------------------------------------------------------\n");
    Sleep(1500);

	printf("Average waiting time:");
	printf("%f\n",(avg_WT*1.0)/(n-k));
	printf("------------------------------------------------------------------------------------------------------------\n");

	printf("Average turnaround time:");
	printf("%f\n",(avg_TAT*1.0/(n-k)));
	printf("------------------------------------------------------------------------------------------------------------\n");

	printf("Total time taken by processor:");
	printf("%d\n",total_time);
	printf("------------------------------------------------------------------------------------------------------------\n");

	return(0);
}
