#include "headers.h"

char _getch()
{
	struct termios old, new;
	char ch;
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &new);
	ch = getchar();

	tcsetattr(0, TCSANOW, &old);
	return ch;
}

void* printThreads(void* data_temp)
{
	struct Data data;
	data = *((struct Data*)data_temp);
	free(data_temp);
	while(1) {
		pthread_mutex_lock(&(data.mutex));
		usleep(200000);
		printf("thread number: %d\n", data.count);
		pthread_mutex_unlock(&(data.mutex));
	}
}

void createNewThread(struct Data *data, struct Stack **stack)
{	
	data->count++;
	struct Data* data_temp = (struct Data*)malloc (sizeof(struct Data));
	*data_temp = *data;
	if (pthread_create(&(data->thread), NULL, &printThreads, (void*)data_temp)){
		perror("pthread_create error");
		exit(1);
	}
	else
		push(&*stack, *data);
}

void closeLastThread(struct Stack **stack, struct Data *data)
{
	pthread_mutex_lock(&(data->mutex));
	pthread_cancel((*stack)->thread);
	pop(&*stack);
	data->count--;
	pthread_mutex_unlock(&(data->mutex)); 
}

void closeAllThreads(struct Stack **stack, struct Data *data)
{	
	pthread_mutex_lock(&(data->mutex));
	while(size(*stack) != 0)
	{
		pthread_cancel((*stack)->thread);
		pop(stack);
		data->count--;
	}
	pthread_mutex_unlock(&(data->mutex));;
}

void createSignalObject(struct Data *data)
{
	data->count = 0;
	pthread_mutex_init(&(data->mutex), NULL);
	pthread_mutex_unlock(&(data->mutex));
}
