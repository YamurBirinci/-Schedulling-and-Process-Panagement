Round Robin ensures that all processes have fair access to the processor by allocating equal and limited processor time to each process. The priority queue sorts the processes according to their completion time. This allows shorter processes to be completed faster.

With this information, a simple operating system simulation was prepared in which processes with resources determined as 10 each and random durations except the first three initial processes are managed by a CPU and processed using the Round robin algorithm combined with the priority queue. In this project, instead of using priority queues, vectors that can behave like it were used.


![1](https://github.com/YamurBirinci/Schedulling-and-Process-Management/assets/99952328/afbcfa0f-9b61-4b55-bfed-3a73ef98a1aa)

## Notes

1. The duration times of the first three processes are determined by the user. Each duration must be between 0 and 8.

2. Each process has the following properties: (PID, duration, R1, R2, R3). PID is the id of the process; duration is the CPU time required by the process to be finished.

3. There is a vector in the system that provides a priority order that organizes the processes for storage. The CPU first completes the shortest process in one unit of time before moving on to the second, third, and so on.

4. This queue stores all processes that are in the ''ready'' state, which means they can be processed by the CPU if their required resources are available.

5. Once a process runs on the CPU and exits the system, the resources it consumed are released and added back to the pool of accessible resources.
