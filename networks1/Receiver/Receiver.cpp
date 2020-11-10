#include <bits/stdc++.h>
#include "../ErrorDetection/VRC.hpp"
#include "../ErrorDetection/LRC.hpp"
#include "../ErrorDetection/CRC.hpp"
//#include "../ErrorDetection/CheckSum.hpp"

using namespace std ; 
int main(){
	 cout<<"Loading Codeword..... \n" ; 
	string s ;
	fstream input ; 
	input.open("../output.txt");
	input>>s;
	
	VRC data(s);
	LRC data1(s);
	CRC data2(s);
	cout<<"\n choose \n 1. VRC \n 2. LRC \n 3. CRC \n 4. checksum \n 5. exit \n";
	int k ; 
	while(cin>>k){
		if(k==5)
			break ; 
		else if(k==1)
			data.detect_error(s) ;
		else if(k==2)
		{
			int len ; 
			cout<<"enter frame lenght: -" ;
			cin>>len ; 
			data1.detect_error(s,len) ; 

		}
		else if(k==3)
		{
			data2.detect_error(s) ; 
		}
		else if(k==4)
		{
			int len ; 
			cout<<"enter frame lenght: -" ;
			cin>>len ; 
			data2.detect_error(s) ; 
		}
		cout<<"\n choose \n 1. VRC \n 2. LRC \n 3. CRC \n 4. checksum \n 5. exit  \n";
	}
	input.close();
	return 0; 
	//cout<<data2.codeword_generator(s,"1101"); 
	
}

