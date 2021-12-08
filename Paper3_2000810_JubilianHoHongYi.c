#include <stdio.h>
#define MAX_PROC 16

struct process
{
	int processNo;
	int arrivalTime;
	int burstTime;
	int waitingTime;
	int turnaroundTime;
	int currentTime;
	int responseTime;
};


//Global variables
int n;
struct process p[100];

void input()
{
	printf("Enter the number of processes : ");
	scanf("%d", &n);
	
	for(int i=0;i<n;i++)
	{
		printf("Enter Process Number/ID, Arrival Time and Burst Time in order, separating them with a space: ");
		scanf("%d %d %d",&p[i].processNo,&p[i].arrivalTime,&p[i].burstTime);
		p[i].responseTime = p[i].burstTime;
		p[i].waitingTime = 0;
		p[i].currentTime = p[i].arrivalTime;
	}
}

void irr()
{
	
	//Local variables
	int i,j,flag;
	struct process q[100],r[100];
	int readyBeginning = 0;
	int readyEnd = 0;
	float l,h;
	l=h=0;
	int count = 0;
	int timeVariable = 0;
	int timeQuantum = 25;
	int time_exec ;
	float averageWaitingTime = 0,averageTurnaroundTime = 0;
	
	//Additional IRR local variables
	struct process temp;//Used for swapping
	float median;//Used for storing median value 
	int mid;
	int oqt;
	int n_temp = 0;//Keeps track of number of distinct processes
	int exec_temp = 0;//Keeps track of number of processes executed
	
	//Copying to another array
	for(i=0;i<n;i++)
	{
		q[i] = p[i];
	}
	
	flag = 1;
	while(count!=n)
	{		
			//Appends the processes to the ready queue-->In the beginning
			if(flag == 1)
			{
				for(i=0;i<n;i++)
				{
					if(q[i].arrivalTime>=l && q[i].arrivalTime<=h)
					{
						r[readyEnd] = q[i];
						readyEnd++;
						n_temp++;
					}
				}
				if(readyEnd!=0)
				{
					flag --;
				}
				else
				{
					l=h;
					h++;
					continue;
				}
			}
		
		//Sort the processes in the ready queue based on burstTime
		for(i=readyBeginning;i<readyEnd;i++)
		{
			for(j=readyBeginning;j<readyEnd-1;j++)
			{
				if(r[j].burstTime>r[j+1].burstTime)
				{
					temp = r[j];
					r[j] = r[j+1];
					r[j+1] = temp;
				}
			}
		}
			
		if(exec_temp == 0)
		{
				//Find the median
				if((readyEnd-readyBeginning)%2 == 0)
				{
					mid = (readyEnd+readyBeginning)/2;
					median = 0.5*(r[mid].burstTime+r[mid-1].burstTime);
				}
				else
				{
				mid = (readyEnd+readyBeginning)/2;
				median = r[mid].burstTime;
				}
			
				//Find the optimal time quantum		
				timeQuantum = (median + r[readyEnd -1].burstTime)/2;	
		}	
		
		//Execute the process present arrivalTime readyBeginning
		printf("[%d] --- <%d> --- ",timeVariable,r[readyBeginning].processNo); 

		exec_temp = (exec_temp+1)%(n_temp);
		
		//Calculating parameters
		time_exec = (r[readyBeginning].responseTime>timeQuantum)?timeQuantum:r[readyBeginning].responseTime;
		r[readyBeginning].responseTime -=time_exec;
		r[readyBeginning].waitingTime += timeVariable - r[readyBeginning].currentTime;
		timeVariable +=time_exec;
		r[readyBeginning].currentTime = timeVariable;	

		//Update l and h
		l = h+0.001;
		h = h + time_exec; 
		
		//Append again
		for(i=0;i<n;i++)
		{
			if(q[i].arrivalTime>=l && q[i].arrivalTime<=h)
			{
				r[readyEnd] = q[i];
				readyEnd++;
			}
		}
		
		if(r[readyBeginning].responseTime == 0)
		{
			count++;
			averageWaitingTime += r[readyBeginning].waitingTime;
			r[readyBeginning].turnaroundTime = r[readyBeginning].currentTime - r[readyBeginning].arrivalTime;
			averageTurnaroundTime += r[readyBeginning].turnaroundTime;
			readyBeginning++;
			continue;
		}
		else
		{
			r[readyEnd] = r[readyBeginning];
			readyEnd++;
			readyBeginning++;
		}
	}

	printf("[%d]", timeVariable); //Ending Time
	
	printf("\n");
	printf("Average Turinaround Time: %.2f\n", averageTurnaroundTime/n);
	printf("Average Waiting Time: %.2f\n", averageWaitingTime/n);
}
int main()
{
    printf("Improved Round Robin Scheduling Algorithm With Varying Time Quantum\n");
    printf("Developed by Jubilian Ho (2000810)\n");
    printf("\n");
	//Accept input 
	input();
	
	printf("Timeline:\n");
	irr();
	return 0;
}
