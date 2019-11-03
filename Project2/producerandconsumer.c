#include<stdio.h>
#include<stdlib.h>
// The maximun and the minimum acts as the buffer sizes. A is the initial value and the Mutex allows
// one tread or option to go through
int mutex=1;
int maximun=0;
int minimum=3;
int A=0;

int main (){
    //this n int is going to be the user input of what he wants to do
    int n;
    void producer();
    void consumer();

    //these tell the operation to either wait or proceed with the task. Also they are they act like
    //the semaphores wait and signal
    int sem_wait(int);
	int sem_signal(int);

    printf("\n1.Produce a item\n2.Consume a item\n3.Exit");
	while(1)
	{
		printf("\n Pick one:");
		scanf("%d",&n);
		switch(n)
		{
			case 1:	if((mutex==1)&&(minimum!=0))
						producer();
					else
						printf("Buffer is at max capacity!!");
					break;
			case 2:	if((mutex==1)&&(maximun!=0))
						consumer();
					else
						printf("Buffer is at the lowest!!");
					break;
			case 3:
					exit(0);
					break;
		}
	}
	
	return 0;
}
 
int sem_wait(int s)
{
	return (--s);
}
 
int sem_signal(int s)
{
	return(++s);
}
// This is the producer function where creates a item and increments it so it can keep tabs on how many it has created.
    void producer(){
	mutex = sem_wait(mutex);
	maximun = sem_signal(maximun);
	minimum = sem_wait(minimum);
	A++;
	printf("\nitem is produced %d",A);
	mutex = sem_signal(mutex);
}
// This is the consumer function where it consumes the items and decrements the total amount of inside the buffer size
    void consumer(){
	mutex = sem_wait(mutex);
	maximun = sem_wait(maximun);
	minimum = sem_signal(minimum);
	printf("\nitem is consumed %d",A);
	A--;
	mutex = sem_signal(mutex);
}
