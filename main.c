#include "headers.h"

int main(int argc, char *argv[])
{
	struct Stack *stack = NULL;
	struct Data data;
	createSignalObject(&data);
	while (1)
	{
		switch (_getch())
		{
			case '+':
			createNewThread(&data, &stack);
			break;
			case '-':
			if (size(stack) != 0)
				closeLastThread(&stack, &data);
			break;
			case 'q':
			closeAllThreads(&stack, &data);
			closeSignalObject(&data);
			return 0;
			break;
		}
	}
	return 0;
}