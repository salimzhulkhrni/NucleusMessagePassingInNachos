#include "syscall.h"


int main() {
	int buffer = Send_Message("M","First Message- Hello From L",-1);
	Send_Message("M","Second Message- Hello From L",-1);
	Send_Message("M","Third Message- Hello From L",-1);
	Send_Message("M","Fourth Message- Hello From L",-1);
    Exit(0); 
}