#include <bits/stdc++.h>
#include "./Acesscontrol/csma.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
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

	string data = "1010101011110101010" ; 
	FILE *fp ; 
	fp = freopen("Channel.txt","a",stdout);
	cout<<data ; 
	fclose(fp) ; 

}

void one_persistent(){
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

void non_persistent(){
	fstream ofs ;
	while(true){


			

		int period = rand()%600000 + 1 ;  // generatinng the random interval of waiting time period 


		cout<<"waiting period : "<<period<<"microseconds\n" ;  

				
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
		usleep(period);
	}
}


void p_persistent(){
		fstream ofs ;
	while(true){

				
		ofs.open("Channel.txt" , fstream::in | fstream::out) ; 
		if(is_ffile_empty(ofs))
		{
			cout<<"Channel idle\n";
			const int  p  = 3 ; 
			int prob = rand()%p ; 
			if(prob==1)
			{
				cout<<"sending with p-persistent method "; // here p = 1/3 ; 
				send() ; 
			}
			else{
				sleep(2) ; 
				continue ; 
			}
			break ;
		}
		else
		{
			cout<<"channel busy ;__; \n";
			continue ; 
		}
		
		ofs.close() ;
	}
	}

bool detect_collision(){
	FILE *fp ; 
	fp = freopen("Channel.txt" , "r" , stdin ) ; 
	string check_flag ; 
	cin>>check_flag ; 
	if(check_flag.size() > 16)
	{
		fclose(fp);
		cout<<"string is"<<check_flag;
		cout<<"collision deteted\n" ;
		return true ;  
	}

	fclose(fp) ; 
	cout<<"no collision deteted\n" ; 
	return false ;
}


int main(){

	p_persistent() ; 
	detect_collision() ; 
	return 0 ; 
}
