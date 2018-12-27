#include "kernel.h"
#include "main.h"
#include "thread.h"
//#include "thread_message_buffer.h"

using namespace std;


void check(){
	

	ThreadMessageBuffer *buff = new ThreadMessageBuffer();
	buff->setMessage("salim");
	char *ch = buff->getMessage();
	char *t;
	for(t = ch; *t != '\0';t++){

		cout<<*t;
	}

	cout<<endl;

	buff->setSenderID("AB");

	cout<<"sender ID:"<<buff->getSenderID()<<endl;

	buff->setReceiverID("B");

	cout<<"receiever ID:"<<buff->getReceiverID()<<endl;

	buff->setAnswer("answer");
	char *ch1 = buff->getAnswer();
	char *t1;
	for(t1 = ch1; *t1 != '\0';t1++){

		cout<<*t1;
	}

	cout<<endl;

	buff->setUsed(true);
	cout<<"bool: "<<buff->getUsed()<<endl;
	

}

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %d looped %d times\n", which, num);
        kernel->currentThread->Yield();
    }
}

void
ThreadTest()
{
    Thread *t = new Thread("forked thread");
    //t->Fork((VoidFunctionPtr) SimpleThread, (void *) 1);
    
    //SimpleThread(0);
    check();
}
