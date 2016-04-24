struct Stack {
	#if PLATFORM == PLATFORM_WIN
		HANDLE ThreadId;
	#else
		pthread_t thread;
	#endif
		struct Stack *next;
};

int size(const struct  Stack *);
void push(struct Stack **, struct Data);
void pop(struct Stack **);