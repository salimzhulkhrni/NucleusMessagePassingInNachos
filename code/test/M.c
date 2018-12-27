#include "syscall.h"


int main() {

	char* message;

	int buffer = Wait_Message("L",message,-1);
	Wait_Message("L",message,-1);
	Wait_Message("L",message,-1);
	Wait_Message("L",message,-1);
    Exit(0); 
}