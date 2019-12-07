
#include<stdio.h>
///defining functions
void enqueue(int i);
int dequeue();
int isInQueue(int i);
void sortByArrivalTime();

///defining process structure
struct process
{
    char processName[10];
    int arrivalTime,burstTime,waitingTime,turnAroundTime,remainingTime;
    int completed;

} p[100];
/// defining global variables
int n;
int readyQueue[100];  //queue
int front=-1,rear=-1;

///function to inseremainingTime element into queue
void enqueue(int i)
{
    if(rear==100)
        printf("overflow");
    rear++;
    readyQueue[rear]=i;
    if(front==-1)
        front=0;

}
///function to remove element into queue
int dequeue()
{
    if(front==-1)
        printf("underflow");
    int temp=readyQueue[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
///function to check if element exist into queue
int isInQueue(int i)
{
    int k;
    for(k=front; k<=rear; k++)
    {
        if(readyQueue[k]==i)
            return 1;
    }
    return 0;

}
///function to soremainingTime the processes ascending to their arrival time
void sortByArrivalTime()
{
    struct process temp;
    int i,j;
    for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++)
        {
            if(p[i].arrivalTime>p[j].arrivalTime)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
}
///main function
void main()
{
    int i,j,time=0,sum_burstTime=0,tq;
    char c;
    float avgwaitingTime=0, avgturnAroundTime=0;
    printf("Enter no of processes:");
    scanf("%d",&n);

    printf("\nEnter the time slice:");
    scanf("%d",&tq);

    ///taking input process details
    for(i=0; i<n; i++,c++)
    {
        printf("\nEnter the processName of the process: ");
        scanf("%s",&p[i].processName);
        printf("\nEnter the arrival time and burst time of process %s: ",p[i].processName);
        scanf("%d%d",&p[i].arrivalTime,&p[i].burstTime);
        p[i].remainingTime=p[i].burstTime;
        p[i].completed=0;
        sum_burstTime+=p[i].burstTime;
    }
    ///soremainingTimeing the processes & inseremainingTimeing first process
    sortByArrivalTime();
    enqueue(0);          // enqueue the first process
    printf("Process execution order GanturnAroundTime CharemainingTime: \n\n 0");

    for(time=p[0].arrivalTime; time<sum_burstTime;)
    {
        i=dequeue();
        ///checking & processing if the remaining time is less or equal to the time slice
        if(p[i].remainingTime<=tq)
        {
            time+=p[i].remainingTime;
            p[i].remainingTime=0;
            p[i].completed=1;
            printf("-->%s<--%d",p[i].processName,time);
            p[i].waitingTime=time-p[i].arrivalTime-p[i].burstTime;
            p[i].turnAroundTime=time-p[i].arrivalTime;
            ///inseremainingTimeing the new processes into the ready queue which comes to the system
            for(j=0; j<n; j++)
            {
                if(p[j].arrivalTime<=time && p[j].completed!=1&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
        }
        ///checking & processing if the remaining time is more to the time slice
        else
        {
            time+=tq;
            p[i].remainingTime-=tq;
            printf("-->%s<--%d",p[i].processName,time);

            ///inseremainingTimeing the new processes into the ready queue which comes to the system
            for(j=0; j<n; j++)
            {
                if(p[j].arrivalTime<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
                {
                    enqueue(j);

                }
            }
            /// inseremainingTimeing the uncompleted process into the ready queue
            enqueue(i);
        }
    }
    ///displaying the processing details
    printf("\n\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time");
    for(i=0; i<n; i++)
    {
        avgwaitingTime+=p[i].waitingTime;
        avgturnAroundTime+=(p[i].waitingTime+p[i].burstTime);
        printf("\n%s\t\t%d\t\t%d\t\t%d\t\t%d",p[i].processName,p[i].arrivalTime,p[i].burstTime,p[i].waitingTime,p[i].turnAroundTime);
    }
    printf("\n\nAverage waiting time:%.2f\n",avgwaitingTime/n);
    printf("\nAverage Turnaround Time time:%.2f\n",avgturnAroundTime/n);
}
