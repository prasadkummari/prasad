#include<stdio.h> 
#include<pthread.h> 
#include<semaphore.h> 
#include<unistd.h> 

sem_t  sid;
pthread_t id1,id2;
int g=1;

void *f1(void *p)
{
	printf("F1...entering....\n");
	sem_wait(&sid);

	printf("Thread :g=%d\n",g);
	sleep(3);
	g+=10;
	printf("Thread1:g(+10):%d\n",g);

	printf("Just Exiting f1...\n");

	sem_post(&sid);
}

void *f2(void *p)
{
	printf("F2..entering....\n");
	sem_wait(&sid);

	printf("Thread2:g=%d\n",g);
	sleep(2);
	g+=100;
	printf("Thread:g(+100):%d\n",g);

	printf("Just Exiting f2...\n");

	sem_post(&sid);
}

int main()
{
	sem_init(&sid,0,1);

	pthread_create(&id1,NULL,f1,NULL);
	pthread_create(&id2,NULL,f2,NULL);
	
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	
	sem_destroy(&sid);

	return 0;
	
	
}
