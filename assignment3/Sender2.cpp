#include <bits/stdc++.h>
#include "./Acesscontrol/csma.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <chrono>

using namespace std ;
using namespace std::chrono ; 


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

string framing(string payload){
	// frame the data according to IEEE 802.3 frame format 
	string frame = "" ; 

	// preamble ( 7 byte )

	string preamble = "1011011" ;
	frame += preamble ; 

	// of frame delimiter (SFD) ( 1 byte )

	string sfd = "+" ; 
	frame += sfd ; 

	// Destination Address ( 11 byte  )


	string destination_adress = "13.45.79.54" ; 
	frame += destination_adress ; 

	// source adress ( 11 byte  )


	string source_adress = "13.56.79.90" ; 
	frame += source_adress ;

	// payload length ( 2 byte )

	string length = "16" ; 
	frame += length ; 

	//  payload ( 16 byte )

	frame += payload ; 

	return frame ; 
}

void send(){

	string data = "1010101011110101" ; 
	string frame_packet = framing(data) ; 
	FILE *fp ; 
	fp = freopen("Channel.txt","a",stdout);
	cout<<frame_packet ; 
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
	// auto start = high_resolution_clock::now(); 
	one_persistent() ; 
	detect_collision() ; 
	// auto stop = high_resolution_clock::now(); 
	//  auto duration = duration_cast<microseconds>(stop - start); 
 //    cout << "Time taken by function: " << duration.count() << " microseconds" << endl; 
 //    cout<<"\nTime Elapsed: " << 1.0*clock() / CLOCKS_PER_SEC << " sec\n";
	return 0 ; 
}
