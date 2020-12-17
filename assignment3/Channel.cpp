#include <bits/stdc++.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


using namespace std ;

string data_string ; 




void clear_channel_buffer(){
	/*

	clears up the chnnel bufffer on receiveing an acknowledgement from the receiver

	*/
	fstream ofs ;
	ofs.open("Channel.txt" , ios::out | ios::trunc) ;
	ofs.close();
}

void listening_to_sender(){
	FILE *fp ; 
	fp = freopen("Channel.txt" , "r" , stdin) ; 
	cin>>data_string  ; 
	fclose(fp);
}

void transmitting_to_receiver(){
	FILE *fp ; 
	freopen("Receiver.txt" , "w" , stdout) ; 
	cout<<data_string;
	fclose(fp);
}

bool detect_collision(){
	FILE *fp ; 
	fp = freopen("Channel.txt" , "r" , stdin ) ; 
	string check_flag ; 
	cin>>check_flag ; 
	if(check_flag.size() > 48)
	{

		cout<<"collision deteted\n" ;
		clear_channel_buffer();
		return true ;  
	}

	fclose(fp) ; 
	cout<<"no collision deteted\n" ; 
	transmitting_to_receiver() ;
	sleep(2) ; 
	clear_channel_buffer() ;
	return false ;
}

int main(){
	while(true){
	// creating a non blocking thread 
	listening_to_sender() ;
	transmitting_to_receiver() ;
	clear_channel_buffer();

	//detect_collision();

	
	
	}
	return 0 ; 
}
