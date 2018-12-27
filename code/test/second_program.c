#include "syscall.h"


int main() {

	char* message;
	int* result = 0;
	char* answer;

	int buffer = Wait_Message("first_program",message,-1);
	Send_Answer(result,"Answer Hello from second program",buffer);
	Send_Message("first_program","Hello again From Second Program",-1);
	Wait_Answer(result,answer,buffer);
    Exit(0); 
}