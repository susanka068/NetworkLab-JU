#include <bits/stdc++.h>
#include "../ErrorDetection/VRC.hpp"
#include "../ErrorDetection/LRC.hpp"
#include "../ErrorDetection/CRC.hpp"
#include "../ErrorDetection/CheckSum.hpp"

using namespace std ; 
int main(){

	cout<<"enter dataword :- \n" ; 
	string s ;
	cin>>s; 
	VRC data(s);
	LRC data1(s);
	CRC data2(s);
	checksum data3 ; 
	ofstream output ; 
	output.open("../transmission_input.txt");
	cout<<"\n choose \n 1. VRC \n 2. LRC \n 3. CRC \n 4. checksum \n 5. exit \n";
	int k ; 
	while(cin>>k){
		if(k==5)
			break ; 
		else if(k==1)
			output<<data.codeword_generator(s) ;
		else if(k==2)
		{
			int len ; 
			cout<<"enter frame lenght: " ;
			cin>>len ; 
			output<<data1.codeword_generator(s,len) ; 

		}
		else if(k==3)
		{
			output<<data2.codeword_generator(s) ; 
		}
		else if(k==4)
		{
			int len ; 
			cout<<"enter frame lenght: " ;
			cin>>len ; 
			data3.codeword_generator(s,len) ; 
		}
		cout<<"\n choose \n 1. VRC \n 2. LRC \n 3. CRC \n 4. checksum \n 5. exit  \n";
	}
	output.close();
	return 0; 
	//cout<<data2.codeword_generator(s,"1101"); 
}

