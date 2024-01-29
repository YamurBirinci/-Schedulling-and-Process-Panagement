#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Process {
    int PID;            //Process ID
    int duration;       //Process Duration time, all except the first three initial processes will be randomly assigned.
    bool usedBefore;    //Checks whether the process has been used before.
    int R1, R2, R3;     //Process resource unit is always randomly determined.
};



//Compare according to their durations.
bool comparingDurations(const Process& process1, const Process& process2) {
    return process1.duration < process2.duration;
}

//Print the Priority Queue.
void printVector(const vector<Process>& processes, const int resources[3]) {
    cout << "Priority Queue: F( ";

    for (const Process& process : processes) {
        cout << "P" << process.PID << ":" << process.duration;
        //If it is not the last process, print a comma.
        if (process.PID != processes.back().PID) {
            cout << ", ";
        }
    }

    cout << " )R" << endl;

    cout << "Resources Available: " << resources[0] << " " << resources[1] << " " << resources[2] << endl;
}

//Print the Initial Processes.
void printInitial(const vector<Process>& processes, const int resources[3]) {
    cout << endl; cout << "Initial Processes are: " << endl;

    for (const Process& p : processes) {
        cout << "(P" << p.PID << ", " << p.duration << " ," << p.R1 << ", " << p.R2 << ", " << p.R3 << ")" << endl;
    }

    cout << endl; cout << endl;
}


int main() {
    srand((unsigned int)time(0));
    int numberP = 1; //The number of Processes to determine the PID numbers

    //Create Priorty Queue and Resources.
    vector<Process> processVector;
    int resources[3] = { 10, 10, 10 };

    //Create Initial 3 Process.
    for (int counter = 0; counter < 3; counter++) {
        Process process;
        process.PID = numberP;  numberP++;
        process.usedBefore = false;
        process.R1 = rand() % 7 + 1; process.R2 = rand() % 7 + 1; process.R3 = rand() % 7 + 1;
        cout << "Enter duration for P" << process.PID << ": ";
        cin >> process.duration;
        processVector.push_back(process);
    }

    //Print the Initial Processes.
    printInitial(processVector, resources);
    sort(processVector.begin(), processVector.end(), comparingDurations);

    //Print 'Time Unit: 1'.
    cout << "Time Unit: 1" << endl;
    printVector(processVector, resources); cout << endl;

    int i = 0; //Initialize to navigate through the three processes.
    int deadlock = 0; //Initialize deadlock counter.

    //Repeat 30 times.
    for (int timeUnit = 2; timeUnit <= 30; timeUnit++) {
        cout << "Time Unit: " << timeUnit << endl;

        //If usedBefore is false (it has never been started before) and its resources are not sufficient, it moves through the queue until it finds a sufficient resource.
        while (processVector[i % 3].usedBefore == false &&
            !(resources[0] > processVector[i % 3].R1 && resources[1] > processVector[i % 3].R2 && resources[2] > processVector[i % 3].R3) ||
            (resources[0] == processVector[i % 3].R1 && resources[1] == processVector[i % 3].R2 && resources[2] == processVector[i % 3].R3)) {

            cout << "P" << processVector[i % 3].PID << " cannot start lack of resources!" << endl;
            i++;    deadlock++; //Increase 'i' to move in the queue, and increase the deadlock since an uninitiated insufficient resource was found.

            if (deadlock >= 3) { //If deadlock reaches 3, it indicates none of the resources are enough; stop while loop.
                break;
            }
        }

        if (deadlock >= 3) {// Deadlock happend, so stop the process.
            cout << "DEADLOCK HAPPENED; Processes cannot be executed." << endl;
            break;
        }
        else { //It indicates there are enough resources, reset the deadlock.
            deadlock = 0;
        }

        if (processVector[i % 3].usedBefore == false) { //If the Process's usedBefore is false (it has never been started before)...
            //execute it. Preserve the Process's resources and set the Process's usedBefore to true (since it is now used), and decrease the duration time.

            cout << "Last Executed Process: P" << processVector[i % 3].PID << endl;

            resources[0] -= processVector[i % 3].R1;    resources[1] -= processVector[i % 3].R2;    resources[2] -= processVector[i % 3].R3;
            processVector[i % 3].usedBefore = true;      processVector[i % 3].duration--;
        }
        else {
            //If it is a previously started Process, execute it directly and reduce the duration time.
            cout << "Last Executed Process: P" << processVector[i % 3].PID << endl;
            processVector[i % 3].duration--;
        }


        //If there is a finished process...
        if (processVector[i % 3].duration == 0) {
            //Print it to show it is finished.
            cout << "Last Finished Process: P" << processVector[i % 3].PID << endl;

            //Release the resources of the process.
            resources[0] += processVector[i % 3].R1;    resources[1] += processVector[i % 3].R2;    resources[2] += processVector[i % 3].R3;

            //Add the process ID next to the deleted process to nextPID.
            int nextPID = processVector[(i + 1) % 3].PID;

            //Print priorty queue and delete the finished process.
            printVector(processVector, resources);
            processVector.erase(processVector.begin() + i % 3);

            //Increase the time by one to print the recently generated process on the screen in a new time unit
            timeUnit++;

            //If the time is still less than 30, continue the process.
            if (timeUnit <= 30) {
                //Create a new process
                Process newProcess;
                newProcess.PID = numberP;   numberP++;
                newProcess.usedBefore = false;
                newProcess.duration = rand() % 7 + 1;
                newProcess.R1 = rand() % 7 + 1;     newProcess.R2 = rand() % 7 + 1;     newProcess.R3 = rand() % 7 + 1;

                cout << endl;

                //Print the created process to the screen.
                cout << "Time Unit: " << timeUnit << endl;
                cout << "New Process is generated: " << "(P" << newProcess.PID << ", " << newProcess.duration << " ,"
                    << newProcess.R1 << ", " << newProcess.R2 << ", " << newProcess.R3 << ")" << endl;

                //Add the new process to the end of the vector, sort the vector, then print it to the screen.
                processVector.push_back(newProcess);
                sort(processVector.begin(), processVector.end(), comparingDurations);
                printVector(processVector, resources);

                //Check each process in the vector. If the PID of the process is equal to nextPID, add one less than the search value to 'i' to start from there in the next loop. 
                //(One less because there is 'i++' at the end).
                int search = 0;
                for (const Process& process : processVector) {
                    if (process.PID == nextPID) {
                        i = search - 1;
                        break;
                    }
                    search++;
                }
            }

        }
        else {
            printVector(processVector, resources);
        }

        // Increase i at each iteration of the for loop to follow the process 
        i++; cout << endl;
    }
}
