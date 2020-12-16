#include <bits/stdc++.h>
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

int main(){
	listening_to_sender() ;
	transmitting_to_receiver() ;
	clear_channel_buffer();
	return 0 ; 
}
