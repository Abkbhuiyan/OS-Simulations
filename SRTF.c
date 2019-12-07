

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
///defining functions



void FCFS();
void RoundRobin();

///defining process structure
struct process {
    int processName,arrivalTime,burstTime,sjfWaitingTime,sjfRemainingTime,sjfTurnAroundTime;
    int sjfCompleted;
} p[100];

int n;
int i,j,time=0,sum_burstTime=0,tq,fcfsTime=0,sjfTime=0;
float sjfAvgWaitingTime=0,sjfAvgTurnAroundTime=0;


/// main function
void main() {

    printf("Enter no of processes:");
    scanf("%d",&n);

    ///taking input process details
    for(i=0; i<n; i++ ){

        printf("\nEnter the arrival time and burst time of process P%d: ",i+1);
        scanf("%d%d",&p[i].arrivalTime,&p[i].burstTime);
        p[i].processName = i+1;
        p[i].sjfRemainingTime=p[i].burstTime;
        p[i].sjfCompleted = 0;
        p[i].sjfTurnAroundTime = p[i].burstTime;
        sum_burstTime+=p[i].burstTime;
    }
    sortByArrivalTime();
    ///performing simulation
    SJF();

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

int iscomplite() {
    int i;
    for(i=0; i<n; i++)
        if( p[i].sjfCompleted==0)
            return 0;
    return 1;
}
int minProcess() {
    int imin,min=9999,i;
    for(i=0; i<n; i++) {
        if( p[i].arrivalTime <= sjfTime && p[i].sjfCompleted==0)
            if( min > p[i].sjfRemainingTime ) {
                min= p[i].sjfRemainingTime;
                imin=i;
            }
    }
    return imin;
}
///calculating gantt chart for SJF
void gantChartSJF(int q[],int x) {
    int i,a[100],s=0;
    float avgtt=0,avgwt=0;
    printf("\n Gantt Chart for SRTF::\n 0");
    for(i=0; i<x-1; i++) {

        while(i<x-1&&q[i]==q[i+1]) {
            s++;
            i++;
        }
        s++;
        ///generating gantt chart
        printf("-->P%d--<%d",p[q[i]].processName,s);


        p[q[i]].sjfWaitingTime =s-p[q[i]].arrivalTime-p[q[i]].sjfTurnAroundTime;
    }
    printf("\n\nDetails\n");
    printf("\n\nProcess \t\tA.Time \t\tB.Time \t\tW.Time \t\tT.Time");
    for(i=0; i<n; i++) {
        p[i].sjfTurnAroundTime+=p[i].sjfWaitingTime;
        sjfAvgWaitingTime+=p[i].sjfWaitingTime;
        sjfAvgTurnAroundTime += p[i].sjfTurnAroundTime;
         printf("\nP%d \t\t\t%d \t\t%d \t\t%d \t\t%d",p[i].processName,p[i].arrivalTime, p[i].burstTime, p[i].sjfWaitingTime, p[i].sjfTurnAroundTime );

    }
    printf("\n\n Average Waiting Time: %.2f",sjfAvgWaitingTime/n);
    printf("\n\n Average Turnaround Time: %.2f",sjfAvgTurnAroundTime/n);
}
}
///function that implement SJF
void SJF() {
    int a,count=0;
    int q[100];
    while(1) {
        if(iscomplite())
            break;
        a=minProcess();
        q[count] =a;
        p[a].sjfRemainingTime -=1;
        if( p[a].sjfRemainingTime==0)
            p[a].sjfCompleted=1;
        sjfTime++;
        count++;
    }
    gantChartSJF(q,count);
}
