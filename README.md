## Advanced XV6 - Operating Systems & Networks

        initial ticket count         -     10
        PBS priority                 -     lower the value higher the priority
```c 
struct proc* ans;       // process to switch to in all schedulings below
```

### **Code used for testing etc.,:**
- ```int do_rand(unsigned long *ctx)``` & ```int rand(void)``` from grind.c --> FreeBSD.
- ```waitx sys call``` & ```time.c``` - complete implementation from tutorial code
- ```schedulertest.c``` - from google for testing scheduling algo's


### **Compilation Format:**
```sh
$ make clean
$ make qemu SCHEDULER=FCFS/LBS/PBS/MLFQ    (or)    make qemu
```

## **Scheduling Analysis:**
 
### **1.FCFS(First Come First Serve) :**
For FCFS we have stored the startTime of each process as  follows:
```c
int startTime;
proc->startTime;
```
then we find the process with the minimum startTime and switch to that process 


### **2.LBS(Lottery Based Scheduler) :**
For LBS we have stored - tickets - number of tickets per process in struct proc
```c
int settickets(int number);
```
settickets syscall --  can be used to the change ticket count of the calling process
```c
int lottery;
int parr[NPROC]={0};  // prefix array sum for tickets
parr[0]=0;
```
parr               --  pref sum array is build based on ticket values of all process in proc[]
then we get a random number(lottery) from [0,total_No_of_tickets]
- for ith process ```parr[i]-parr[i-1]``` is its ticket count so if  lottery is in that range we pick that process as ```ans```;
- that is its probability in total tickets


### **3.PBS(Priority Based Scheduler) :**
For PBS we have stored the following:
```c
uint32 stime;                 // total sleep time in that schedule
uint32 runtime;               // How long the process ran for in that schedule
int sp;                       // static priority
int nice;                     // niceness
int runcnt;                   // number of times the process is scheduled
void    update_time();        // updates runtime,stime for RUNNING,SLEEPING procs 
void    clockintr();          // we run update_time() in it to update runtime,stime

```

we calculate niceness and then ```dynamic priority (dp)``` then find the proc with least dp value as ```ans```

```c
int setpriority(int new_priority,int pid);  // updates priority of a process to new_priority
```


### **Performance Comparison:**
<pre>    AVERAGE:            runtime                 waittime                
    RR                  112                     16                  
    FCFS                37                      31           
    LBS                 106                     15-16                   
    PBS                 106                     15          
    MLFQ                                                    </pre>              


- We observe that MLFQ is the best  
- then PBS is the best with less waittime after MLFQ
- then PBS performs well for batch systems and has less waittime than RR
- FCFS is the worst scheduling 
<!-- 
- but here we don't change the priorities for the process in LBS,PBS using setttickets/setpriority
- thus the waittime may be decreased by using settickets/setpriority in LBS/PBS -->


## **MLFQ(Multi Level Feedback Queue) :**
For MLFQ we have stored the startTime of each process as  follows:

```c
// queue implementation
struct queue{};                 
struct procarr{};
int pushq();
int popq();
int rmq();
int empty();            // check if empty
// queue implementation


```
- we take 5 priority queues with different timer ticks
- 





# advanced_xv6
# advanced_xv6
