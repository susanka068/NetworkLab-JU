#include <bits/stdc++.h>
using namespace std ;

bool is_ffile_empty(std::fstream& pFile)
{
    return pFile.peek() == std::fstream::traits_type::eof();
}

bool check_channel_status(fstream& ofs){
	string flag ; 
	ofs>>flag ;
	cout<<"string is "<<flag<<endl;
	return flag=="" ; 
}

void send(){

	string data = "101010101111110110" ; 
	FILE *fp ; 
	fp = freopen("Channel.txt","a",stdout);
	cout<<data ; 
	fclose(fp) ; 

}

void listen_to_channel(){
	fstream ofs ;
	while(true){
		
		ofs.open("Channel.txt" , fstream::in | fstream::out) ; 
		if(is_ffile_empty(ofs))
		{
			cout<<"Channel idle\n";
			send() ; 
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
