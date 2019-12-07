

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
///defining functions



void FCFS();
void RoundRobin();

///defining process structure
struct process {
    int processName,arrivalTime,burstTime,fcfsWaitingTime,fcfsTurnAroundTime,fcfsCompletionTime;
} p[100];

int n;
int i,j,time=0,sum_burstTime=0,tq,fcfsTime=0,sjfTime=0;
float fcfsAvgWaitingTime=0,fcfsAvgTurnAroundTime=0;

char fcfsGanttChart[500]="0";

/// main function
void main() {

    printf("Enter no of processes:");
    scanf("%d",&n);

    ///taking input process details
    for(i=0; i<n; i++ ){

        printf("\nEnter the arrival time and burst time of process P%d: ",i+1);
        scanf("%d%d",&p[i].arrivalTime,&p[i].burstTime);
        p[i].processName = i+1;

    }
    sortByArrivalTime();
    ///performing simulation
    FCFS();

}
void sortByArrivalTime() {
    struct process temp;
    int i,j;
    for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++) {
            if(p[i].arrivalTime>p[j].arrivalTime) {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
}
/// implementing the FCFS algorithm
void FCFS() {
    sortByArrivalTime();
    printf("\nGantt Chart for FCFS:: \n 0");
    for(i=0; i<n; i++) {
        if(i==0) {
            p[i].fcfsWaitingTime = 0;
            p[i].fcfsCompletionTime = p[i].burstTime;
        } else {
            p[i].fcfsWaitingTime = p[i-1].fcfsCompletionTime - p[i].arrivalTime;
            p[i].fcfsCompletionTime = p[i-1].fcfsCompletionTime + p[i].burstTime;
        }
        p[i].fcfsTurnAroundTime = p[i].burstTime + p[i].fcfsWaitingTime;
        ///generating the gantt chart
        printf("-->P%d<--%d",p[i].processName,p[i].fcfsCompletionTime);

    }
    /// calculating waiting and turnaround time for FCFS
    printf("\n\nProcess \t\tA.Time \t\tB.Time \t\tW.Time \t\tT.Time");
     for(i=0; i<n; i++) {
            printf("\nP%d \t\t\t%d \t\t%d \t\t%d \t\t%d",p[i].processName,p[i].arrivalTime, p[i].burstTime, p[i].fcfsWaitingTime, p[i].fcfsTurnAroundTime );
        fcfsAvgWaitingTime+=p[i].fcfsWaitingTime;
        fcfsAvgTurnAroundTime+=(p[i].fcfsWaitingTime+p[i].burstTime);
    }
    printf("\n\n Average Waiting Time: %.2f",fcfsAvgWaitingTime/n);
    printf("\n\n Average Turnaround Time: %.2f",fcfsAvgTurnAroundTime/n);
}

