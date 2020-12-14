#include <bits/stdc++.h>
using namespace std ;

bool is_ffile_empty(std::fstream& pFile)
{
    return pFile.peek() == std::fstream::traits_type::eof();
}


void send(fstream& ofs){
	string data = "1010101011110101010" ; 
	ofs<<data;
}



void listen_to_channel(){
	fstream ofs ;
	while(true){
		
		ofs.open("Channel.txt" , fstream::in | fstream::out ) ; 
		if(is_ffile_empty(ofs))
		{
			cout<<"Channel idle\n";
			ofs<<"jkdfjk";
			break ;
		}
		else
		{
			cout<<"channel busy ;__; \n";
		}
		ofs.close();
	}
}



int main(){
	
	listen_to_channel() ;

	return 0 ; 
}
