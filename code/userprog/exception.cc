// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
#include "thread.h"
#include  <map>
#include <string>
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	is in machine.h.
//----------------------------------------------------------------------

map <int,Thread* > threadMap;

char* retrieveChars(int);

//message - passsing func declarations //

void SendMessage(char*,char*,ThreadMessageBuffer*);

//////////////////////////////////////////////////

void Exit_POS(int id){


}

void ForkTest1(int id)
{
	
}
///////////////////////////////////////////

void ForkTest2(int id)
{
	
}

////////////////////////////////////////
void ForkTest3(int id)
{
	
}
///////////////////////////////////////

void
ExceptionHandler(ExceptionType which)
{
    int type = kernel->machine->ReadRegister(2);

    DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

    switch (which) {
    case SyscallException:
      switch(type) {
      case SC_Halt:
	DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

	SysHalt();

	ASSERTNOTREACHED();
	break;

	  case SC_Fork_POS: {
	  	
	  	return;

	  }


	  break;

	  case SC_Wait_POS:{

	  	return;
	  }

	  break;

	  case SC_Write: {

	  	//kernel->machine->ReadMem

	  	return;
	  	
	  }

	  
	  break;

	  case SC_Send_Message:{

	  	cout<<"------------------------------------------------------"<<endl;
	  	cout<<"Entered in Send Message Call Thread: "<<kernel->currentThread->getName()<<endl;
	  	cout<<"------------------------------------------------------"<<endl;

	  	kernel->currentThread->msgCounter++;

	  	if(kernel->currentThread->msgCounter <= kernel->messageLimit){

		  	int startIndex_progname = kernel->machine->ReadRegister(4);
		  	char *receiverID = retrieveChars(startIndex_progname);
		  	string reciever_name = receiverID;

		  	//cout<<"Reciever ID Parameter : "<<receiverID<<endl;


		  	int startIndex_message = kernel->machine->ReadRegister(5);
		  	char *message = retrieveChars(startIndex_message);

		  	int dummy_buffer_id = kernel->machine->ReadRegister(6);

		  	// find available buffer

		  	ThreadMessageBuffer *availableBuffer = NULL;

		  	//check if buffer already have the sender and reciever id
		  	for(int i = 0; i < 10 ; i++){
		  		if(kernel->bufferPool[i]->getUsed()){

		  			string send_name_id = kernel->bufferPool[i]->getSenderID();
		  			string currentThreadName = kernel->currentThread->getName();
		  			string recieve_name_id = kernel->bufferPool[i]->getReceiverID();

		  			if((send_name_id == currentThreadName && recieve_name_id == reciever_name) 
		  				|| (send_name_id == reciever_name && recieve_name_id == currentThreadName)){

		  					availableBuffer = kernel->bufferPool[i];

		  				//cout<<"Enter in the if"<<endl;
		  				break;
		  			}
		  		}
		  	}
		  	//cout<<"Reach here"<<endl;

		  	if(availableBuffer == NULL){

		  		for(int i=0;i<10;i++){

		  		if(kernel->bufferPool[i] == NULL){

		  			//cout<<"buffer "<<i<<" is null"<<endl;
		  		}

		  		else{

		  			if(kernel->bufferPool[i]->getUsed() == FALSE){

		  			// Get the unused buffer & mark it to send the message to the receiver
		  			availableBuffer = kernel->bufferPool[i];
		  			break;
		  			}

		  		}

		  		
		  	}

		  	}

		  			  	

		  	if(availableBuffer != NULL){

		  		//cout<<"available buffer ID: "<<availableBuffer->getBufferID()<<endl;
		  		//cout<<"receiver name: "<<reciever_name<<endl;
		  		kernel->currentThread->thread_to_buffer_map[reciever_name] = availableBuffer;
		  		SendMessage(receiverID,message,availableBuffer); // send message to the receiver throught the buffer
		  		cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
		  		cout<<"Message Sent From Sender "<<kernel->currentThread->getName()<<" as: '"<<message<<"' to the receiver: "<<reciever_name<<" through Buffer ID: "<<availableBuffer->getBufferID()<<endl;
		  		cout<<"------------------------------------------------------------------------------------------------------------"<<endl;

		  		kernel->machine->WriteRegister(2,availableBuffer->getBufferID());

		  	}
		  	else{

		  		// No Buffers availble from kernel's buffer pool to send the message
		  		cout<<"-------------------------------------------------"<<endl;
		  		cout<<"No available buffers to send message from sender: "<<kernel->currentThread->getName()<<" to receiver: "<<reciever_name<<endl;
		  		cout<<"--------------------------------------------------"<<endl;
		  	}
		}
		else{
			cout<<"-------------------------------------------------"<<endl;
			cout<<"Send Message Limit Exceeded.Cannot Send Message"<<endl;
			cout<<"-------------------------------------------------"<<endl;
		}

	 

	  	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  	//cout<<"PC Reg: "<<PCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;

	  	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	  	//cout<<"Next PC Reg: "<<NextPCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;
	  
	  	/* set next programm counter for brach execution */
	  	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);

	  	return;


	  }
	  break;

	  case SC_Wait_Message:{

	  	cout<<"------------------------------------------------------"<<endl;
	  	cout<<"Entered in Wait Message Call Thread: "<<kernel->currentThread->getName()<<endl;
	  	cout<<"------------------------------------------------------"<<endl;

	  	int startIndex_progname = kernel->machine->ReadRegister(4);
	  	char *senderID = retrieveChars(startIndex_progname);
	  	string sender_name = senderID;

	  	int message_address = kernel->machine->ReadRegister(5);

	  	int dummy_buffer_id = kernel->machine->ReadRegister(6);

	  	//Identify the corresponding buffers from it's thread buffer pool using sender's name

	  	if(kernel->thread_tableMap[sender_name] != NULL || kernel->currentThread->threadBufferPool->NumInList() > 0 ){

	  		// if sender still exists & is not yet destroyed

		  	bool foundID = FALSE;

		  	ListIterator<ThreadMessageBuffer*> *iterator =new ListIterator<ThreadMessageBuffer*>(kernel->currentThread->threadBufferPool);

		  	while(!iterator->IsDone()) {
					//iterate to find the sender's buffers to extract the message
		  			string name = iterator->Item()->getSenderID();
			  		if( name == sender_name){
			  			foundID = TRUE;
			  		}
					iterator->Next();		
				}


			if(!foundID){

				kernel->currentThread->isWaitingForMessage = 1; // mark this thread as still waiting for sender's buffer
		  		kernel->currentThread->thread_waiting_message = sender_name;
		  		cout<<"-----------------------------------------------------------------------------------------------------------"<<endl;
		  		cout<<"SLEEPING Thread: "<<kernel->currentThread->getName()<<" REASON: Sender-"<<sender_name<<" 's Buffer Not yet Available to Read"<<endl;
		  		cout<<"------------------------------------------------------------------------------------------------------"<<endl;
		  		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		  		kernel->currentThread->Sleep(FALSE);
		  		(void) kernel->interrupt->SetLevel(oldLevel);
			}

			cout<<"********************************************************"<<endl;
			cout<<"RUNNING: Wait Message call of thread: "<<kernel->currentThread->getName()<<endl;
			cout<<"********************************************************"<<endl;

			ThreadMessageBuffer *buffer = NULL;

			ListIterator<ThreadMessageBuffer*> *iterator1 =new ListIterator<ThreadMessageBuffer*>(kernel->currentThread->threadBufferPool);

			int i = kernel->currentThread->threadBufferPool->NumInList();

		  	while(!iterator1->IsDone() && i > 0) {
					
		  			// recheck for sender's buffer again after waking up
		  			string name = iterator1->Item()->getSenderID();
			  		if( name == sender_name){
			  			buffer = iterator1->Item();
			  			kernel->currentThread->threadBufferPool->Remove(buffer);
			  			kernel->currentThread->thread_to_buffer_map[sender_name] = buffer;
			  		}
					iterator1->Next();
					i--;
							
				}

				
		  	// definitely buffer would be availble since this thread is woken up by the sender who wants to send message
			
			kernel->currentThread->thread_waiting_message = "";
			kernel->currentThread->isWaitingForMessage = 0;

			if(buffer != NULL){

				cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
		  		cout<<"Message Received by Reciever "<<kernel->currentThread->getName()<< " as: '"<<buffer->getMessage() <<"' from sender : "<<sender_name<<" read from Sender's Buffer ID: "<<buffer->getBufferID()<<endl;
		  		cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;

		  		char* dummy = buffer->getMessage();
		  		message_address = (int)dummy;

		  		kernel->machine->WriteRegister(2,buffer->getBufferID());
			}
		}
		else{
			cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
			cout<<"Sender: "<<sender_name<<" not available to send message to this thread: "<<kernel->currentThread->getName()<<endl;
			cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;

			if(kernel->currentThread->kernel_message != NULL){
				// kernel sends a message
				char* dummy = kernel->currentThread->kernel_message;
		  		message_address = (int)dummy;

			}
		}
 
	  	

	  	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  	//cout<<"PC Reg: "<<PCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;

	  	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	  	//cout<<"Next PC Reg: "<<NextPCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;
	  
	  	/* set next programm counter for brach execution */
	  	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	  

	  	return;


	  }
	  break;

	  case SC_Send_Answer:{

	  	cout<<"------------------------------------------------------"<<endl;
	  	cout<<"Enter in Send Answer Call Thread: "<<kernel->currentThread->getName()<<endl;
	  	cout<<"------------------------------------------------------"<<endl;

	  	int result = kernel->machine->ReadRegister(4);
	  	/*char *receiverID = retrieveChars(startIndex_progname);
	  	string reciever_name = receiverID;*/
	  	char* receiverID;
	  	string reciever_name = "";

	  	//cout<<"Reciever ID Parameter : "<<receiverID<<endl;

	  	int startIndex_answer = kernel->machine->ReadRegister(5);
	  	char *answer = retrieveChars(startIndex_answer);

	  	int program_buffer_id = kernel->machine->ReadRegister(6);

	  	ThreadMessageBuffer *buffer = NULL;

	  	for(int i = 0; i < 10 ; i++){
	  		int id = kernel->bufferPool[i]->getBufferID();
	  		if( id == program_buffer_id){
			  			buffer = kernel->bufferPool[i];
			  			reciever_name = buffer->getSenderID();
			  			receiverID = buffer->getSenderID();
			  	}
	  	}

	  	/*ListIterator<ThreadMessageBuffer*> *iterator2 =new ListIterator<ThreadMessageBuffer*>(kernel->bufferPool);

		  	while(!iterator2->IsDone()) {
					// find the buffer of the sender
		  			int id = iterator2->Item()->getBufferID();
			  		if( id == program_buffer_id){
			  			buffer = iterator2->Item();
			  			reciever_name = buffer->getSenderID();
			  			receiverID = buffer->getSenderID();
			  		}
					iterator2->Next();		
				}*/

	  	if(kernel->currentThread->thread_to_buffer_map[reciever_name] != NULL){
	  		//cout<<"in"<<endl;

	  		// identifying the buffer that was used to send message to receiver. Re-using the same buffer to send answer to the receiver
	  		//buffer = kernel->currentThread->thread_to_buffer_map[reciever_name];
	  		buffer->setAnswer(answer);
	  		buffer->setSenderID(kernel->currentThread->getName());
	  		buffer->setReceiverID(receiverID);
	  		buffer->setUsed(TRUE);
	  	} 

	  	if( kernel->thread_tableMap[reciever_name] != NULL){

	  		// found receiver and use the buffer above to send answer to the receiver

	  		Thread* recieverThread = kernel->thread_tableMap[reciever_name];
	  		recieverThread->answerBufferPool->Append(buffer);
	  		cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
	  		cout<<"Answer Sent From Sender "<<kernel->currentThread->getName()<<" as: '"<<answer<<"' to the receiver: "<<reciever_name<<" from the reused buffer with Buffer ID: "<<buffer->getBufferID()<<endl;
	  		cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;

	  		kernel->currentThread->thread_to_buffer_map.erase(reciever_name);
	  		// store the result value in that is got by the thread
	  		int actual_result = 1;
	  		result = (int)&actual_result;


	  		if(recieverThread->isWaitingForAnswer == 1){
	  			string senderName = kernel->currentThread->getName();
	  			if(recieverThread->thread_waiting_answer == senderName){

	  				// sender has sent the answer now, to the receiver
	  			recieverThread->isWaitingForAnswer = 0; // mark waiting for answer as false in the receiver since sender has sent the answer already
	  			recieverThread->thread_waiting_answer = "";
	  			IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
				kernel->scheduler->ReadyToRun(recieverThread); // put the receiver in ready to run list
				(void) kernel->interrupt->SetLevel(oldLevel);

	  			}

	  		}

	  	}
	  	else{

	  		// receiver Not available
	  		int actual_result = 0;
	  		result = (int)&actual_result;  // send answer failed - sending 0
	  		cout<<"--------------------------------------"<<endl;
	  		cout<<" Receiver: "<<reciever_name<<" not available to send answer"<<endl;
	  		cout<<"--------------------------------------"<<endl;
	  		//cout<<"else"<<endl;
	  	}

	  	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  	//cout<<"PC Reg: "<<PCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;

	  	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	  	//cout<<"Next PC Reg: "<<NextPCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;
	  
	  	/* set next programm counter for brach execution */
	  	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	  	 	

	  	return;


	  }
	  break;

	   case SC_Wait_Answer:{

	   	cout<<"---------------------------------------------------------------------------------------"<<endl;
	  	cout<<"Entered in Wait Answer Call Thread: "<<kernel->currentThread->getName()<<endl;
	  	cout<<"---------------------------------------------------------------------------------------"<<endl;

	  	/*int startIndex_progname = kernel->machine->ReadRegister(4);
	  	char *senderID = retrieveChars(startIndex_progname);
	  	string sender_name = senderID;*/

	  	char *senderID ="";
	  	string sender_name = "";

	  	int result = kernel->machine->ReadRegister(4);
	  	int ans = kernel->machine->ReadRegister(5);
	  	int program_buffer_id = kernel->machine->ReadRegister(6);

	  	//cout<<"program_buffer_id "<<program_buffer_id<<endl;

	  	for(int i = 0; i < 10 ; i++){
	  		int id = kernel->bufferPool[i]->getBufferID();
	  		if( id == program_buffer_id){
			  			//buffer = kernel->bufferPool[i];
	  			//cout<<"id  "<<id<<endl;
			  			sender_name = kernel->bufferPool[i]->getReceiverID();
			  			senderID = kernel->bufferPool[i]->getReceiverID();
			  			//cout<<"Buffer pool : "<<kernel->bufferPool[i]->getSenderID()<<" "<<kernel->bufferPool[i]->getReceiverID()<<endl;
			  	}
	  	}



	  	// check if sender is avilable in thread map

	  	if(kernel->thread_tableMap[sender_name] != NULL || kernel->currentThread->answerBufferPool->NumInList() > 0){

		  	bool foundID = FALSE;

		  	ListIterator<ThreadMessageBuffer*> *iterator =new ListIterator<ThreadMessageBuffer*>(kernel->currentThread->answerBufferPool);

		  	while(!iterator->IsDone()) {
					// find the buffer of the sender
		  			string name = iterator->Item()->getReceiverID();
		  			//cout<<"name  "<<name<<endl;
		  			//cout<<"Buffer Answer pool : "<<iterator->Item()->getSenderID()<<" "<<iterator->Item()->getReceiverID()<<endl;
			  		if( name == sender_name){
			  			foundID = TRUE;
			  		}
					iterator->Next();		
				}


			if(!foundID){

				// sender's buffer not yet found to read answer from
				kernel->currentThread->isWaitingForAnswer = 1; // mark as waiting
		  		kernel->currentThread->thread_waiting_answer = sender_name;
		  		//cout<<"SLEEPING due to corr buffer not found: "<<kernel->currentThread->getName()<<endl;
		  		cout<<"-----------------------------------------------------------------------------------------------------------"<<endl;
		  		cout<<"SLEEPING Thread: "<<kernel->currentThread->getName()<<" REASON: Sender-"<<sender_name<<" 's Buffer Not yet Available to Read"<<endl;
		  		cout<<"------------------------------------------------------------------------------------------------------"<<endl;
		  		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		  		kernel->currentThread->Sleep(FALSE);
		  		(void) kernel->interrupt->SetLevel(oldLevel);
			}

			cout<<"********************************************************"<<endl;
			cout<<"RUNNING: Wait Answer Call of thread: "<<kernel->currentThread->getName()<<endl;
			cout<<"********************************************************"<<endl;


			ThreadMessageBuffer *buffer = NULL;

			iterator =new ListIterator<ThreadMessageBuffer*>(kernel->currentThread->answerBufferPool);

			int i = kernel->currentThread->answerBufferPool->NumInList();

		  	while(!iterator->IsDone() && i > 0) {
					// find the corresponding sender's buffer
		  			string name;
		  			if(!foundID)
		  				name = iterator->Item()->getSenderID();
		  			else
		  				name = iterator->Item()->getReceiverID();
			  		if( name == sender_name){
			  			buffer = iterator->Item();
			  			kernel->currentThread->answerBufferPool->Remove(buffer);
			  			kernel->currentThread->thread_to_buffer_map.erase(sender_name);
			  			//buffer->setUsed(FALSE);
			  		}
					iterator->Next();	
					i--;	
				}

		  	// definitely sender's buffer will be avilable right now
			kernel->currentThread->thread_waiting_message = "";
			kernel->currentThread->isWaitingForMessage = 0;
	 		
	 		if(buffer != NULL){

	 		cout<<"----------------------------------------------------------------------------------------"<<endl;
		  	cout<<"Answer Received by Reciever "<<kernel->currentThread->getName()<< " as: '"<<buffer->getAnswer() <<"' from sender : "<<sender_name<<" from the reused sender's buffer ID:"<<buffer->getBufferID()<<endl;
		  	cout<<"----------------------------------------------------------------------------------------"<<endl;
		  	// overwrite result(from user - program) with the answer received
		  	char* dummy_ans = buffer->getAnswer();
		  	ans = (int)dummy_ans;  
		}
		else{

			// dummy answer received from kernel
			if(kernel->currentThread->kernel_message != NULL){

				char* dummy_ans = kernel->currentThread->kernel_message;
		  		ans = (int)dummy_ans; 
		  		int kernel_result = -1;
		  		result = (int)&kernel_result;

			}
		}


 		}	  	


	  	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  	//cout<<"PC Reg: "<<PCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;

	  	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	  	//cout<<"Next PC Reg: "<<NextPCReg<<endl;
	  	//cout<<"RR PCReg+4:"<<kernel->machine->ReadRegister(PCReg)+4<<endl;
	  
	  	/* set next programm counter for brach execution */
	  	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);

	  	return;


	  }
	  break;




      case SC_Add:
	DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
	
	/* Process SysAdd Systemcall*/
	int result;
	result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
			/* int op2 */(int)kernel->machine->ReadRegister(5));

	DEBUG(dbgSys, "Add returning with " << result << "\n");
	/* Prepare Result */
	kernel->machine->WriteRegister(2, (int)result);
	
	/* Modify return point */
	{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}

	return;
	
	ASSERTNOTREACHED();

	break;

		case SC_Exit:{

			cout<<"***************************************************"<<endl;
	  		cout<<"Calling EXIT On: "<<kernel->currentThread->getName()<<endl;
	  		//cout<<"***************************************************"<<endl;

			string currentThread_name = kernel->currentThread->getName();

			kernel->thread_tableMap.erase(currentThread_name);


			for(std::map<string,Thread*> :: iterator itr = kernel->thread_tableMap.begin(); itr != kernel->thread_tableMap.end() ; itr++){

				if(itr->second != NULL){
	  			
	  			if((itr->second->thread_waiting_message == currentThread_name && itr->second->isWaitingForMessage == 1) 
	  				|| (itr->second->thread_waiting_answer == currentThread_name && itr->second->isWaitingForAnswer == 1)  ){

	  				cout<<"Thread: "<<itr->second->getName()<<" is Dependent On This Thread: "<<kernel->currentThread->getName()<<" For answer/message"<<endl;
	  				//cout<<"Dependent thread: "<<itr->second->getName()<<endl;
	  				ThreadMessageBuffer* buffer = itr->second->thread_to_buffer_map[currentThread_name];

	  				if(!(itr->second->threadBufferPool->IsInList(buffer) || itr->second->answerBufferPool->IsInList(buffer))){

	  					cout<<"++++ KERNEL SENDING DUMMY RESPONSE TO WAITING THREAD: "<<itr->second->getName()<<" ++++++"<<endl;
	  					cout<<"Putting dependent thread: "<< itr->second->getName() << " Back into Ready List "<<endl;
	  					int msg_ans = kernel->machine->ReadRegister(5);
	  					char* dummy_msg = "Kernel's Message";
	  					msg_ans = (int)dummy_msg;
	  					itr->second->kernel_message = dummy_msg;
	  					itr->second->answer_result = -1;
						IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
						kernel->scheduler->ReadyToRun(itr->second);
						(void) kernel->interrupt->SetLevel(oldLevel);

	  				}

	  			}
	  			else{

	  				// no other thread is waiting for this thread
	  				//cout<<"No Other Threads Are Waiting For This Thread: "<<kernel->currentThread->getName()<<" For answer/message"<<endl;
	  			}
	  		}

	  		}

	  		//cout<<"***************************************************"<<endl;
	  		cout<<"Thread: "<<kernel->currentThread->getName()<<" EXITED"<<endl;
	  		cout<<"***************************************************"<<endl;
			kernel->currentThread->Finish();
			return;


		}
			
		break;

      default:
	cerr << "Unexpected system call " << type << "\n";
	break;
      }
      break;
    default:
      cerr << "Unexpected user mode exception" << (int)which << "\n";
      break;
    }
    ASSERTNOTREACHED();
}


char* retrieveChars(int startIndex){

	//cout<<"inside retrieve chars func"<<endl;

	char *buff = new char[1];
	  	//buff[0] = '@';

	char *ch = new char[50];

	int size=0;

	int i=0;

	 do{

	  	kernel->machine->ReadMem(startIndex,1,(int*)&buff[0]);
	  	ch[i] = buff[0];
	  	//cout<<ch[i];
	  	size++;
	  	i++;
	  	startIndex++;

	  	}while(buff[0] != '\0');

	return ch;


}


void SendMessage(char* receiverID,char* message,ThreadMessageBuffer* buffer){


	//init buffer details to send to receiver

	string receiver_name = receiverID;

	buffer->setUsed(TRUE);
	buffer->setReceiverID(receiverID);
	buffer->setSenderID(kernel->currentThread->getName());
	buffer->setMessage(message);


	if(kernel->thread_tableMap[receiver_name] != NULL){

		
		Thread* recieverThread = kernel->thread_tableMap[receiver_name];
		//cout<<"Reach recieverThread-"<<endl;
		if(!recieverThread->threadBufferPool->IsInList(buffer))
			recieverThread->threadBufferPool->Append(buffer);
		//cout<<"After Reach"<<endl;

		/*cout<<"Reach recieverThread-"<<endl;
		if(recieverThread->threadBufferPool->IsInList(buffer)){
			recieverThread->threadBufferPool->Remove(buffer);
			recieverThread->threadBufferPool->Append(buffer);
		}
		cout<<"After Reach"<<endl;*/

		//cout<<" Appending in ThreadBufferPool of "<<recieverThread->getName()<<" Buffer Id "<<buffer->getBufferID()<<endl;

		if(recieverThread->isWaitingForMessage == 1){

			//cout<<"Reciever Thread is already waiting for message "<<endl;
			//receiver thread waiting for message
			string senderName = kernel->currentThread->getName();
			if(recieverThread->thread_waiting_message == senderName){

				recieverThread->isWaitingForMessage = 0; // set to not waiting
				recieverThread->thread_waiting_message = "";
				IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
				kernel->scheduler->ReadyToRun(recieverThread); // put the receiver in ready to run list
				(void) kernel->interrupt->SetLevel(oldLevel);

			}

		}

	}
	else{

		cout<<"-----------------------------------------"<<endl;
		cout<<"Receiver thread:"<<receiver_name<<" not available to send message"<<endl;
		cout<<"-----------------------------------------"<<endl;
	}

}