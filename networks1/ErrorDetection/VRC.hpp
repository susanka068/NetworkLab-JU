#include "bits/stdc++.h"
#include <fstream>
using namespace std;
class VRC
{
public:
	string dataword  ;
	string codeword ; 
public:
	 VRC(string s){
	 	dataword = s ; 
	 }
	 VRC(string s , string t){
	 	dataword = s  ; 
	 	codeword = t ; 
	 }
public:
	 string codeword_generator(string s){
	 	int count1 = 0 ; 
	 	for(int i = 0 ; i < s.size() ; ++i)
	 		if(s[i]=='1')
	 			count1++ ; 
	 	string res = s ; 
	 	res += (count1&1)?'1':'0';
	 	cout<<"generate codeword : "<<res<<endl ;
	 	return res ; 
	 }
	bool detect_error(string s){
		int count1 = 0 ; 
	 	for(int i = 0 ; i < s.size() ; ++i)
	 		if(s[i]=='1')
	 			count1++ ; 
	 	if(count1&1)
	 		cout<<"Error detected\n";
	 	else
	 	{
	 		cout<<"no error detected \ndataword = " ;

	 		for(int i = 0 ; i < s.size() -1 ; ++i)
	 			cout<<s[i];
	 		cout<<endl;
	 	}
	 	return (count1&1) ; 
	}
};