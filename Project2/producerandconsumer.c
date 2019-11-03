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

    //these tell the operation to either wait or proceed with the task
    int wait(int);
	int signal(int);

    printf("\n1.Producer\n2.Consumer\n3.Exit");
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
 
int wait(int s)
{
	return (--s);
}
 
int signal(int s)
{
	return(++s);
}

    void producer(){
	mutex = wait(mutex);
	maximun = signal(maximun);
	minimum = wait(minimum);
	A++;
	printf("\nProducer produces the item %d",A);
	mutex = signal(mutex);
}

    void consumer(){
	mutex = wait(mutex);
	maximun = wait(maximun);
	minimum = signal(minimum);
	printf("\nConsumer consumes item %d",A);
	A--;
	mutex = signal(mutex);
}
