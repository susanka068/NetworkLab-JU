#include <bits/stdc++.h>
using namespace std ;

void clear_channel_buffer(){
	fstream ofs ;
	ofs.open("Channel.txt" , ios::out | ios::trunc ) ; 
	ofs.close();
}

int main(){
	clear_channel_buffer();
	return 0 ; 
}