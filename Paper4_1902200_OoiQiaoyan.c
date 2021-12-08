#include<stdio.h>
int main()
{
      int i, limit, total = 0, x, current =0, tq =0,maxBurst=0, minBurst=0;
      //arrival_time[20], burst_time[20], rbt[20],wt[20];
      float tat, twt;
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);

      int arrival_time[limit], burst_time[limit], rbt[limit],wt[limit];
      x = limit;
      for(i = 0; i < limit; i++)
      {
            printf("\nEnter Details of Process[%d]\n", i + 1);
 
            printf("Arrival Time:\t");
 
            scanf("%d", &arrival_time[i]);
 
            printf("Burst Time:\t");
 
            scanf("%d", &burst_time[i]);
 
            rbt[i] = burst_time[i];
      }
      printf("An Efficient Dyanmic Round Robin CPU Scheduling Algorithm\n");
      printf("Developed by Ooi Qiaoyan (1902200)\n");
      printf("\nProcess ID \t Arrival Time \t Burst Time \t  Waiting Time \t Turnaround Time\n");

      i =0;
      while(i < limit)
      {

	x =0;
	current =0;
	maxBurst =0;
	minBurst=0;
	while(x < limit)
	{
		if(arrival_time[x] <= total && rbt[x] >0)
		{

			if(rbt[x] > maxBurst)
			{
				maxBurst = rbt[x];
			}
			if(minBurst == 0)
                  	{
                      		minBurst = rbt[x];
                  	}
                  	// if is lower than current min_burst, update min_burst
                  	else if(rbt[x]< minBurst)
                  	{
                      		minBurst = rbt[x];
                  	}
                	current++;
              	}
              x++;


	}
// if more than 1 process in queue, assign 80% of max_burst as quantum
          if(current > 1)
          {
              // calculate 80% of max_burst and typecast to int
              tq = 0.8 * maxBurst;
              // [OPTIONAL] round up the quotient
              tq++;

              // if no processes in the ready queue has a remaining_burst_time less than the set quantum,
              // set quantum to max_burst
              if(minBurst > tq)
              {
                  tq = maxBurst;
              }
          }
          // else, assign max_burst as quantum
          else
          {
              tq = maxBurst;
          }

          // if process hasnt arrived in queue, go to next process
          if(arrival_time[i]> total)
          {
              i++;
          }
          // if process already completed, go to next process
          else if(rbt[i] == 0)
          {
              i++;
          }
          // process is determined to be in ready queue waiting to be processed
          else
          {
              // if valid to be processed (remaining_burst_time is not zero and can finish in one cycle)
              if(rbt[i]<= tq && rbt[i]>0)
              {
                  // calculate the wait_time of the process
                  wt[i] = total - arrival_time[i];

                  // increment the total_time_elapsed accordingly
                  total += rbt[i];

                  // set this process as finished executing
                  rbt[i] = 0;

                  // print out the details of the process
                  printf("Process[%d]\t %d \t\t %d\t\t  %d\t\t %d\n", i + 1,arrival_time[i], burst_time[i], wt[i] , wt[i] + burst_time[i]);

                  // update the total times
                  tat = tat + burst_time[i] + wt[i];
                  twt += wt[i];
                  // iterate through the process list again
                  i=0;
              }
              // if not valid to be processed, go to next process
              else
              {
                  i++;
              }
		//printf("tq = %d \n rbt = %d \n", tq, rbt[i]);

          }
    }
    printf("Average Waiting Time\t%.1f",twt/limit);
    printf("\nAverage Turnaround Time\t%.1f\n",tat/limit);

}
