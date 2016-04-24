#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#define PLATFORM_WIN 1 
#define PLATFORM_UNIX 2 

#if defined(_WIN32) || defined(_WIN64) 
	#include <windows.h>
	#include <process.h>
	#include <conio.h> 
	#define PLATFORM PLATFORM_WIN 
#else 
	#include <pthread.h>
	#include <unistd.h>
	#include <termios.h>
	#define PLATFORM PLATFORM_UNIX 

char _getch();
#endif 

struct Data 
{
	#if PLATFORM == PLATFORM_WIN
	CRITICAL_SECTION CriticalSection;
	HANDLE ThreadId;
	#else
	pthread_t thread;	
	pthread_mutex_t mutex;
	#endif
	int count;
};

#include "stack.h"

void createNewThread(struct Data *, struct Stack **);
void closeLastThread(struct Stack **, struct Data *);
void closeAllThreads(struct Stack **, struct Data *);

void createSignalObject(struct Data *);
void closeSignalObject(struct Data *data);

#if PLATFORM == PLATFORM_WIN
unsigned  __stdcall printThreads(PVOID);
#else
void* printThreads(void*);
#endif
