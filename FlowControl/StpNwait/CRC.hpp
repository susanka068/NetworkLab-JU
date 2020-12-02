#include "bits/stdc++.h"
using namespace std;
class CRC
{
public:
	string dataword  ;
	string  codeword ; 
public:
	 CRC(string s){
	 	dataword = s ; 
	 }
	 CRC(string s , string t){
	 	dataword = s ; 
	 	codeword = t ; 
	 }
	 CRC(){
	 	dataword="";
	 	codeword="";
	 }
public:
		char exor(char a,char b)                                      // perform exor operation
			{
			if(a==b)
			return '0';
			else
			return '1';
			}
		string codeword_generator(string data, string key = "10001001") // CRC-7 -> x^7 + x^3 + 1 ; 
			{
			int datalen = data.size();
			int keylen = key.size();

			for(int i=0;i<keylen-1;i++)                //appending n-1 zeroes to data
				data += '0';

			int codelen = datalen+keylen-1;                //lenght of appended data word

			string temp(200 ,'0'),rem(keylen-1 , '0');

			for(int i=0;i<keylen;i++)
				rem[i]=data[i];                    //considering n bits of data for each step of binary division/EXOR 

			for(int j=keylen;j<=codelen;j++)
			{
			    for(int i=0;i<keylen;i++)
			    temp[i]=rem[i];                // remainder of previous step is divident of current step

			    if(rem[0]=='0')                //if 1's bit of remainder is 0 then shift the rem by 1 bit
			    {
			        for(int i=0;i<keylen-1;i++)
			            rem[i]=temp[i+1];
			    }
			    else                    //else exor the divident with generator key
			    {    
			        for(int i=0;i<keylen-1;i++)
			            rem[i]=exor(temp[i+1],key[i+1]);
			            
			    }
			    if(j!=codelen)
			        rem[keylen-1]=data[j];        //appending next bit of data to remainder obtain by division
			    else
			        rem[keylen-1]='\0';
			}
			    
			for(int i=0;i<keylen-1;i++)
			data[datalen+i]=rem[i];                //replace n-1 zeros with n-1 bit CRC
			data[codelen]='\0';
			//cout<<"CRC="<<rem<<"\ncodeword="<<data<<endl;
				return data ; 
			}

	bool detect_error(string code, string key = "10001001" ){
		int keylen = key.size() ; 
		int codelen = code.size() ; 
		string data = code.substr(0 , codelen - keylen + 1 ) ; 
		string crc = code.substr(codelen - keylen + 1 , keylen-1) ;
		if(code!=codeword_generator(data,key))
		{
			cout<<"error_detected\n";
		}
		else
		{
			cout<<"No error detected\n";
			//cout<<"dataword = "<<data<<endl ;
		}
		return (code!=codeword_generator(data,key));
	}
};