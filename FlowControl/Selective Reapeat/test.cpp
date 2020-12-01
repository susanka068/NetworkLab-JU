#include "bits/stdc++.h"
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <thread>
#include "./CRC.hpp"

using namespace std ; 

const int readEnd = 0 ;  
const int writeEnd = 1 ;  
const int packet_size = 16 ;  
const int window_size = 4 ; 


int SenderPipe[2] ;    // sender(writes) => receiver(reads) 
int ReceiverPipe[2] ;  // receiver(writes) => sender(reads)



/* This function (SenderInitialise) pings the receiver with a initial data frame to check whether the receivee is ready to receiive data or not  */

void SenderInitialise(){
	printf("Sender process created\n");
	int data_array[25] ={1} ;
	int response_array[25] ; 
	if( write(SenderPipe[writeEnd] , data_array , 25*sizeof(int)) ==-1){ printf("failed to send\n"); }
	else{
			cout<<"Initial data packet sent to establish connection"<<endl;
		}
	if(read(ReceiverPipe[readEnd] , response_array , 25*sizeof(int))==-1){  printf("failed to read from Receiver pipe\n"); }
	else{
		if(response_array[5]==1)
		{
			printf("connection established with ack\n");
		}
		else{
			printf("failed to establish connection got N-ack\n");
		}
	}
}





void ReceiverInitialise(){
	printf("Receiver process created\n");
	int data_array[25] = {0} ;
	int response_array[25] = {0} ; 
	if(read(SenderPipe[readEnd] , data_array , 25*sizeof(int))==-1){  printf("failed to rea from sender pipe\n"); }
	else{
		if(data_array[5]==1)
		{
			response_array[5] = 1 ; 
			if(write(ReceiverPipe[writeEnd],response_array , 25*sizeof(int) )==-1){
				printf("failed to send acknowledgement\n");
			}
			else{
				printf("sent acknowledgement\n");
			}
		}
		else{
			if(write(ReceiverPipe[writeEnd],response_array , 25*sizeof(int) )==-1){
				printf("failed to send N-ack\n");
			}
			else{
				printf("sent N-acknowledgement\n");
			}
		}
	}

}

void  SenderProcess(){

		close(SenderPipe[readEnd]);
		close(ReceiverPipe[writeEnd]) ;


		
		string data_string ;  

		CRC ins ; 


		int data_array[25] ={0} ; 
		int response_array[25] = {0} ; 


        

		if(freopen("data.txt","r",stdin))
		{
			printf("extracting data from the textfile....\n");
			cin>>data_string;
		}
		else{
			printf("extraction failed \n");
		}


		cout<<"extracted data is "<<data_string <<endl ;
		cout<<"framing is underway..... \n";


		int start = 0 ;  
		int sz = data_string.size() ; 
		int sqno = 0 ; 
		int window_of_data[25][window_size] ;

		while(start < sz){



		string frame_string = data_string.substr(start,packet_size);
		string code_string = ins.codeword_generator(frame_string , "10011"); // CRC-4 ITU


		{

			/* creating the frame according the IEEE 802.3 format ......... */

			data_array[0] = getpid() ; 
			data_array[1] = getppid() ; 
			data_array[2] = 0 ; 
			data_array[3] = sqno ; 
			data_array[4] = packet_size ; 
			for(int  i= 0 ; i < code_string.size() ; i++ )
				data_array[ i + 5 ] = code_string[i] - '0' ; 

		}

		
			if( write(SenderPipe[writeEnd] , data_array , 25*sizeof(int)) ==-1){ printf("failed to send\n"); }
			else{
			cout<<"sent data packet "<<endl;
			cout<<data_array[0]<<" | "<<data_array[1]<<" | "<<data_array[2]<<" | "<<data_array[3]<<" | "<<data_array[4]<<" | ";
			for(int i = 5 ; i < 21 ; i++ )
				cout<<data_array[i];
			cout<<" | ";
			for(int i = 21 ; i < 25 ; i++ )
				cout<<data_array[i];
			cout<<" | ";

			cout<<endl;
			}


			if(read(ReceiverPipe[readEnd] , response_array , 25*sizeof(int))==-1){  printf("failed to read from Receiver pipe\n"); }
			else
			{
				if(response_array[5]==1 )
				{
					printf("ack received\n");
						start += packet_size ; 
						sqno = (sqno + 1 )%window_size ;  
				}
				else
				{
					printf("failed to establish connection got N-ack\n");
				}
			}

			//start += packet_size ; 
			//cout<<"start : "<<start<<endl;

	}


	int termination_array[25] = {127} ; 

	if( write(SenderPipe[writeEnd] , termination_array , 25*sizeof(int)) ==-1){ printf("failed to send\n"); }
			else{
			cout<<"sent termination_array packet "<<endl;
			}
		


		close(SenderPipe[writeEnd]);
		close(ReceiverPipe[readEnd]); 


}


void ReceiverProcess(){

		close(SenderPipe[writeEnd]);
		close(ReceiverPipe[readEnd]) ; 

		int i = 0 ; 

		int data_array[25] = { 0 } ; 
		int response_array[25] = {0} ;
		int sqno = 0 ; 


		CRC det ; 
		

		while( data_array[0] != 127){	
			string data_string = "" ; 
			if(read(SenderPipe[readEnd] , data_array , 25*sizeof(int) ) == -1){ printf("reading from Sender pipe failed\n"); }
			else
			{

				cout<<"received data packet "<<endl;			
				cout<<data_array[0]<<" | "<<data_array[1]<<" | "<<data_array[2]<<" | "<<data_array[3]<<" | "<<data_array[4]<<" | ";
				for(int i = 5 ; i < 21 ; i++ )
				{
					data_string += data_array[i] + '0' ; 
					cout<<data_array[i];
				}
				cout<<" | ";
				for(int i = 21 ; i < 25 ; i++ )
				{
					data_string += data_array[i] +'0';
					cout<<data_array[i];
				}
				cout<<" | "<<endl;


				{

					int prob = rand()%2 + 1;
					//cout<<"prob : "<<prob<<" | ";
					if(prob==1)
						data_string[0] = '0' + '1' - data_string[0] ;  
				}
				//cout<<data_string<<endl;

				if(!det.detect_error(data_string,"10011") || data_array[3] != sqno )
				{
					response_array[5] = 1 ; 
					if(write(ReceiverPipe[writeEnd],response_array , 25*sizeof(int) )==-1){
						printf("failed to send acknowledgement\n");
					}
					else{
						printf("sent acknowledgement\n");
					}
				}
				else{
					if(write(ReceiverPipe[writeEnd],response_array , 25*sizeof(int) )==-1){
						printf("failed to send N-ack\n");
					}
					else{
						printf("sent N-acknowledgement\n");
						sqno = ( sqno + 1 )%window_size ; 
					}
				}
			}
		
			i++ ; 
		}
		
		close(SenderPipe[readEnd]);
		close(ReceiverPipe[writeEnd]);
}


int main(int argc ,char* argv[]){
	
	if(pipe(SenderPipe)==-1 || pipe(ReceiverPipe) ){
		printf("failed to create a pipe\n"); 
		return 1 ; 
	}

	int pid = fork() ; // forked to create a child process . 
	if(pid ==-1)
	{
		printf("failed to create a child process\n");
		return 2 ; 

	} 
	

	if(pid == 0 ){
		/* We are in child (Sender) process */ 
		SenderInitialise();
		SenderProcess();
	
	}
	else{
	/* we are in parent (Receiver) process */
		ReceiverInitialise();
		ReceiverProcess();

	
		kill(pid, SIGKILL);
		wait(NULL);
		}
	}
