#include "syscall.h"


int main() {

	char* message;
	int* result = 0;

	int buffer = Wait_Message("G",message,-1);
	Send_Answer(result,"Answer: Hello from H To G",buffer);
    Exit(0); 
}