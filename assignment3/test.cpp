#include <bits/stdc++.h>
using namespace std ;

bool is_ffile_empty(std::fstream& pFile)
{
    return pFile.peek() == std::fstream::traits_type::eof();
}

int main(){
	fstream ofs ;
	while(true){
	ofs.open("Channel.txt") ; 
	if(is_ffile_empty(ofs))
		{
			cout<<"Channel idle\n";
			freopen("Channel.txt","w",stdout);
			cout<<"hello";

			break ;
		}
		else
		{
			cout<<"channel busy ;__; \n";
		}
	
	ofs.close() ; 
	}
}