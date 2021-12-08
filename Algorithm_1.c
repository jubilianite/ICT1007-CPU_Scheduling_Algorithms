#include <stdio.h>
#include <stdbool.h>

int n, i, j, time_q = 0, count, p_time = 0, sum = 0, max = 0, length = 0;
int exe_time[100], execopy[100], arr_time[100],queue[100], wait_t[100], tat[100];
bool cont = true, stop = false;
float avg_wt, avg_tat;

void shortestfirst() //function for SRTF

{
    if (p_time >= max) {
        cont = false;
    }

    for (i = 0; i < n; i++)
    {
        if (arr_time[i] <= p_time && exe_time[i] > 0)
        {
            queue[length] = i + 1;
            length = length + 1;

        }

    }
    for (i = 0; i < length; i++)
    {
        for (j = i + 1; j < length; j++)
        {
            int indexi, indexj;
            indexi = queue[i] - 1;
            indexj = queue[j] - 1;
            if (exe_time[indexi] > exe_time[indexj]) // if one is greater than the other, then swap.
            {
                int temp = queue[j];
                queue[j] = queue[i];
                queue[i] = temp;
            }
        }
    }
    int p_index = queue[0] - 1;

    if (exe_time[p_index] > time_q)
    {
        p_time = p_time + time_q;

        exe_time[p_index] -= time_q;

    }
    else
    {
        p_time = p_time + exe_time[p_index];

        exe_time[p_index] = 0;
        tat[p_index] = p_time - arr_time[p_index];
    }

    for (i = 0; i < length; i++)
    {
        printf("%d ", queue[i]);
    }
    length = 0;
    printf("\n");
}

void roundrobin() // function for RR
{
    if (stop == false) {
        for (i = 0; i < length; i++)
        {

            printf("%d ", queue[i]);
        }
    }
    if (length == 1) {
        stop = true;
    }
    printf("\n");
    int p_index = queue[0] - 1;
    if (exe_time[p_index] > time_q)
    {
        p_time += time_q;
        exe_time[p_index] -= time_q;
        int temp = queue[0];
        for (i = 1; i < length; i++)
        {
            queue[i - 1] = queue[i];
        }
        queue[length - 1] = temp;
    }
    else
    {
        p_time += exe_time[p_index];
        exe_time[p_index] = 0;
        tat[p_index] = p_time - arr_time[p_index];
        int temp = queue[0];//3
        for (i = 1; i < length; i++)
        {
            queue[i - 1] = queue[i];
        }
        queue[length - 1] = 0;
        length = length - 1;
    }
}
int main()
{
    printf("Efficient Process Scheduling Algorithm using RR and SRTF\n");

    printf("Enter number of processes:"); // input number of processes
    scanf("%d", &n);

    for (count = 0; count < n; count++)
    {
        printf("Enter Arrival Time and Execution Time for Process Number %d :", count + 1);
        scanf("%d %d", &arr_time[count], &exe_time[count]); //input for arrival and execution time
    }
    printf("Enter time quantum:"); // user input time quantum
    scanf("%d", &time_q);

    printf("Arrangement of processes in ready queue:\n");

    for (i = 0; i < n; i++)
    {
        if (max < arr_time[i]) // to get max arrival time
        {
            max = arr_time[i];
        }
        sum = sum + exe_time[i]; // calculate sum of execution time
        execopy[i] = exe_time[i];
    }

    while (cont == true) { //run until cont is false
        shortestfirst();
    }

    for (i = 0; i < n; i++)
    {
        if (exe_time[i] > 0) // find process with exe time more than 0
        {
            queue[length] = i + 1;
            length += 1;
        }
    }
    for (i = 0; i < length; i++) // sort queue based on execution time
    {
        for (j = i + 1; j < length; j++)
        {
            int indexi, indexj;
            indexi = queue[i] - 1;
            indexj = queue[j] - 1;
            if (exe_time[indexi] > exe_time[indexj]) // if one is greater than the other, then swap.
            {
                int temp = queue[j];
                queue[j] = queue[i];
                queue[i] = temp;
            }
            else
            {
                continue;
            }
        }
    }

    while (sum != p_time) { //if total execution time not equal to process time, continue
        roundrobin();
    }

    for (i = 0; i < n; i++)
    {
        wait_t[i] = tat[i] - execopy[i]; // calculation for waiting time
        avg_wt += wait_t[i]; // sum of waiting time of all processes
        avg_tat += tat[i]; // sum of turnaround time of all processes
    }
    avg_wt = avg_wt / n; // find average wt
    avg_tat = avg_tat / n; // find average tat
    printf("Average waiting time: %0.2f \n", avg_wt);
    printf("Average turn around time %0.2f \n", avg_tat);

}
