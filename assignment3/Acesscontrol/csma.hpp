#include <bits/stdc++.h>
using namespace std ; 
class csma
{
public:

	bool is_ffile_empty(std::fstream& pFile)
{
    return pFile.peek() == std::fstream::traits_type::eof();
}


void send(){

	string data = "1010101011110101010" ; 
	FILE *fp ; 
	fp = freopen("../Channel.txt","a",stdout);
	cout<<data ; 
	fclose(fp) ; 

}


	void non_persistent(){

	}
	void one_persistent(){
		fstream ofs ;
		while(true){
			
			ofs.open("../Channel.txt" , fstream::in | fstream::out) ; 
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
	void p_persistent(){
		
	}
};