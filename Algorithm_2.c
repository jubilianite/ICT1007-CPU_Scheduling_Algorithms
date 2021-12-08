#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	//initalize variables
	int k_factor=2,cpu_runtime,choice,i,j,n,total=0,pos,temp,current,length,
	temp_arr[50],arr_bt[50],bt[50],p[50],wt[50],tat[50];
	float avg_wt,avg_tat;

	/*Without user input (random generator)*/
	// srand(time(0)); //random number every time

	printf("Enter the number of process:");
	scanf("%d",&n);
	//0 for k_factor=2, 1 for alternative K_FACTOR increment
	printf("Enter 0 for not alternate; 1 for alternate: ");
	scanf("%d",&choice);
	
	/*user input*/
	printf("Enter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;           
    }
	printf("A K_FACTOR-Factor CPU Scheduling Algorithm\n");
	printf("Developed by Lee Yen Ning (2001775)\n");

	// random burst time
	// printf("\nEnter Burst Time:\n");
	
	// for (i=0;i<n;i++)
	// {
	// 	bt[i]=rand() % 100+1; //generate range 1 to 100
	// 	p[i]=i+1;
	// 	printf(" %d \n", bt[i]);
	// }

	//sorting
	for(i=0;i<n;i++)
	{
		pos=i;
		for(j=i+1;j<n;j++)
		{
			if(bt[j]<bt[pos])
				pos=j;
		}

		temp=bt[i]; //selection sort; switch places
		bt[i]=bt[pos];
		bt[pos]=temp;
		
		temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;

	}
	length = n; //length of array
	cpu_runtime = bt[0]; //time cpu run
	temp_arr[0] = p[0];//allocate p1 first
    arr_bt[0] = bt[0];
	

	//delete from ready queue
    for(i=0; i<length-1; i++)
    {
        p[i] = p[i + 1];
		bt[i] = bt[i + 1];
    }

	/* Decrement array size by 1 */
	length--;

	i=1; //index start from 1

	while(length!=0)
	{
		if(i%2==0 && choice==1) //check_factor if even; even means increment
		{
			k_factor=k_factor+1;
		}
		if (length==1) //if odd number and last element
        {
            temp_arr[i] = p[0];
            arr_bt[i] = bt[0];
        
        }
		else if((k_factor * bt[0]) > (cpu_runtime+bt[1]))
		{
			temp_arr[i] = p[1];
			arr_bt[i] = bt[1];
				
			current = bt[1];

			//delete from ready queue
			for(j=1; j<length-1; j++)
			{
				p[j] = p[j + 1];
				bt[j] = bt[j + 1];
			}
			
		}
		else
		{
	        temp_arr[i] = p[0];
			arr_bt[i] = bt[0];
				
			current = bt[0];

			for(j=0; j<length-1; j++)
			{
				p[j] = p[j + 1];
				bt[j] = bt[j + 1];
			}
		}
		cpu_runtime+=current;
		i=i+1;
		/* Decrement array size by 1 */
		length--;
	}

	wt[0]=0; //temp_arr[0] waiting time is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=arr_bt[j];
 
        total+=wt[i];
    }
    //average waiting time
	avg_wt=(float)total/n; 
    total=0;
 
    //calculate turnaround time
    printf("\nProcess Id\t    Burst Time    \tWaiting Time\tTurnaround Time\n");
    for(i=0;i<n;i++)
    {
        tat[i]=arr_bt[i]+wt[i];
        total+=tat[i];
        printf("\nProcess[%d]\t\t %d\t\t    %d\t\t\t%d",temp_arr[i],arr_bt[i],wt[i],tat[i]);
    }
 
    avg_tat=(float)total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%0.2f",avg_wt);
    printf("\nAverage Turnaround Time=%0.2f\n",avg_tat);
	
	return 0;
}