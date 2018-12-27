#include "syscall.h"


int main() {

	char* message;
	int* result = 0;

	int buffer = Wait_Message("J",message,-1);
	Send_Answer(result,"Answer: Hello from K",buffer);
    Exit(0); 
}