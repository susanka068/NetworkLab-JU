#include "bits/stdc++.h"
using namespace std ; 

class ErrorInjection
{
public:
	string single_bit_inject(string& data,int position){
		data[position] = '1' + '0' - data[position] ;
		return data;
	}
	string burst_inject(string data,int start,int end)
	{
		string res = data ; 
		for(int position = start ; position <= end ; position++)
			res[position] = '1' + '0' - data[position] ;
		return res;
	}
	string random_inject(string& data){
		int tot_number = rand() ;
		for(int i = 0 ; i < tot_number ; i++ ){
			int ind = rand()%(data.size() ) ;
			data[ind] = '1' + '0' - data[ind];
		} 
		return data;
	}
};