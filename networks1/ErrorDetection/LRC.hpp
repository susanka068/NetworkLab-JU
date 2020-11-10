#include "bits/stdc++.h"
using namespace std;
class LRC
{
public:
	string dataword  ;
	string  codeword ; 
public:
	 LRC(string s){
	 	dataword = s ; 
	 }
	 LRC(string s , string t){
	 	dataword = s ; 
	 	codeword = t ; 
	 }
public:
	 string codeword_generator(string s,int length){
	 	vector<string> vstring ;
	 	string lstring = "" ; 
	 	
	 	for(int i = 0 ; i < s.size() ; i+=length)
	 		{
	 			string sub = s.substr(i,length);
	 			vstring.push_back(sub);
	 		}
	 	for(int i = 0 ; i < length ; i++)
	 		{
	 			int count1 = 0 ; 
	 			for(int j = 0 ; j < vstring.size() ; j++)
	 				if(vstring[j][i] == '1')
	 					count1++;
	 			lstring += (count1&1)?'1':'0';

	 		}
	 		cout<<"codeword "<<(s+lstring)<<endl;
	 		return (lstring + s) ; 
	 }
	bool detect_error(string code,int length){
		string data = code.substr(length);
	 	vector<string> vstring ;
	 	string lstring = "" ; 
	 	
	 	for(int i = 0 ; i < data.size() ; i+=length)
	 		{
	 			string sub = data.substr(i,length);
	 			vstring.push_back(sub);
	 		}
	 	for(int i = 0 ; i < length ; i++)
	 		{
	 			int count1 = 0 ; 
	 			for(int j = 0 ; j < vstring.size() ; j++)
	 				if(vstring[j][i] == '1')
	 					count1++;
	 			lstring += (count1&1)?'1':'0';

	 		}
	 	if(lstring == code.substr(0,length)){
	 		cout<<"No error detected \n";
	 	}
	 	else
	 		cout<<"Error detected";
	 	return (lstring == code.substr(0,length) ); 
	}
};