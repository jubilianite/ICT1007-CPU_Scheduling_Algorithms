#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	setbuf(stdout, NULL);

	// Program name
	printf("Improved Round Robin\n");

	// initialize variables
	int number_of_process, arrival_time[10], burst_time[10],
			temp_burst_time[10], turn_around_time[10], Process_Waiting_Time[10],
			process_time_quantum[10], priority[10], completion_time[10];
	int Time_Quantum, no_process_completed = 0;
	float average_wait_time, average_turnaround_time, Waiting_Time = 0;
	int current_process = -1; // keep track of current process to check for context switch
	int context_switch = 0;

	// get user input
	printf("Enter the no of processes: ");
	scanf("%d", &number_of_process);

	for (int i = 0; i < number_of_process; i++) {
		printf("Enter Burst Time, Arrival time and Priority for process %d: ", i + 1);
		scanf("%d %d %d", &burst_time[i],&arrival_time[i],&priority[i]);
		temp_burst_time[i] = burst_time[i];
/*
		printf("Enter arrival time for process %d: ", i + 1);
		scanf("%d", &arrival_time[i]);

		printf("Enter priority level for process %d: ", i + 1);
		scanf("%d", &priority[i]);
		*/
	}

	printf("\nEnter Time Quantum:\t");
	scanf("%d", &Time_Quantum);

	// uncomment to test example 1
/*
	 Time_Quantum = 500;
	 number_of_process = 5;

	 burst_time[0] = 550;
	 burst_time[1] = 800;
	 burst_time[2] = 200;
	 burst_time[3] = 2600;
	 burst_time[4] = 1600;

	 temp_burst_time[0] = 550;
	 temp_burst_time[1] = 800;
	 temp_burst_time[2] = 200;
	 temp_burst_time[3] = 2600;
	 temp_burst_time[4] = 1600;

	 arrival_time[0] = 0;
	 arrival_time[1] = 200;
	 arrival_time[2] = 100;
	 arrival_time[3] = 400;
	 arrival_time[4] = 0;

	 priority[0] = 3;
	 priority[1] = 1;
	 priority[2] = 3;
	 priority[3] = 2;
	 priority[4] = 2;

*/
	// uncomment to test example 2
/*
	 Time_Quantum = 500;
	 number_of_process = 7;

	 burst_time[0] = 550;
	 burst_time[1] = 1250;
	 burst_time[2] = 1950;
	 burst_time[3] = 50;
	 burst_time[4] = 500;
	 burst_time[5] = 1200;
	 burst_time[6] = 100;

	 temp_burst_time[0] = 550;
	 temp_burst_time[1] = 1250;
	 temp_burst_time[2] = 1950;
	 temp_burst_time[3] = 50;
	 temp_burst_time[4] = 500;
	 temp_burst_time[5] = 1200;
	 temp_burst_time[6] = 100;

	 arrival_time[0] = 0;
	 arrival_time[1] = 0;
	 arrival_time[2] = 0;
	 arrival_time[3] = 0;
	 arrival_time[4] = 0;
	 arrival_time[5] = 0;
	 arrival_time[6] = 0;

	 priority[0] = 3;
	 priority[1] = 1;
	 priority[2] = 3;
	 priority[3] = 3;
	 priority[4] = 2;
	 priority[5] = 1;
	 priority[6] = 3;
*/

	// adjust TQ based on priority (step 5)
	int time_quantum_high = Time_Quantum * 12 / 10;
	printf("Time Quantum for High Priority Processes: %d\n", time_quantum_high);
	int time_quantum_medium = Time_Quantum;
	printf("Time Quantum for Medium Priority Processes: %d\n",
			time_quantum_medium);
	int time_quantum_low = Time_Quantum * 8 / 10;
	printf("Time Quantum for Low Priority Processes: %d\n", time_quantum_low);

	for (int i = 0; i < number_of_process; i++) {
		if (priority[i] == 1) {
			process_time_quantum[i] = time_quantum_low;
		} else if (priority[i] == 3) {
			process_time_quantum[i] = time_quantum_high;
		} else if (priority[i] == 2) {
			process_time_quantum[i] = time_quantum_medium;
		}
	}

	while (1) {

		// check if any existing arrived process that has BT <= 100 (step 6)
		for (int k = 0; k < number_of_process; k++) {
			if (arrival_time[k] <= Waiting_Time && burst_time[k] > 0
					&& burst_time[k] <= 100) {
				Waiting_Time = Waiting_Time + burst_time[k];
				completion_time[k] = Waiting_Time;
				burst_time[k] = 0; // This will set the burst time of the process to 0 as the left over burst time is less than the Quantum
				no_process_completed++;
				printf("%i(%f)\n", k + 1, Waiting_Time);
				if (current_process != k
						&& no_process_completed <= number_of_process) {
					context_switch++;
					current_process = k;
				}
			}
		}

		for (int i = 0; i < number_of_process; i++) {
			if (arrival_time[i] <= Waiting_Time) {
				if (burst_time[i] > 0) {
					// if satisfy conditions, complete process execution, update total_waiting_time and process_completion, CT (step 8, 9, 10)
					if (burst_time[i] <= process_time_quantum[i]
							|| (burst_time[i] > process_time_quantum[i]
									&& burst_time[i]
											<= 13 * process_time_quantum[i] / 10
									&& priority[i] == 3)
							|| (burst_time[i] > process_time_quantum[i]
									&& burst_time[i]
											<= 12 * process_time_quantum[i] / 10
									&& (priority[i] == 1 || priority[i] == 2))) {
						Waiting_Time = Waiting_Time + burst_time[i];
						completion_time[i] = Waiting_Time;
						burst_time[i] = 0;
						no_process_completed++;
						printf("%i(%f)\n", i + 1, Waiting_Time);
						if (current_process != i
								&& no_process_completed <= number_of_process) {
							context_switch++;
							current_process = i;
						}
					} else { // execute process within TQ and update process waiting_time and burst_time
						burst_time[i] = burst_time[i] - process_time_quantum[i];
						Waiting_Time = Waiting_Time + process_time_quantum[i];
						printf("%i(%f)\n", i + 1, Waiting_Time);
						if (current_process != i
								&& no_process_completed <= number_of_process) {
							context_switch++;
							current_process = i;
						}
					}
				}
			}

		}

		// check if all process has been completed
		if (no_process_completed == number_of_process) {
			break;
		}

	}

	// calculate TAT = CT - AT
	// calculate WT = TAT - BT
	// and ave TAT and ave WT respectively (step 12)
	for (int i = 0; i < number_of_process; i++) {
		turn_around_time[i] = completion_time[i] - arrival_time[i];
		Process_Waiting_Time[i] = turn_around_time[i] - temp_burst_time[i];
		average_turnaround_time += turn_around_time[i];
		average_wait_time += Process_Waiting_Time[i];
	}

	printf("Process ID \tBurst Time \tWaiting Time \tTurnaround Time\n");
	for (int i = 0; i < number_of_process; i++) {
		printf("%4d\t\t%6d\t\t%8d\t\t%7d\n", i + 1, temp_burst_time[i],
				Process_Waiting_Time[i], turn_around_time[i]);
	}

	printf("Number of context switches: %d\n", context_switch - 1);
	printf("The Average Waiting time is:\t %f \n",
			average_wait_time / number_of_process);
	printf("The Average Turnaround time is:\t %f\n",
			average_turnaround_time / number_of_process);

}
