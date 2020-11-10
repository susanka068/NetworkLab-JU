#include <bits/stdc++.h>
#include "./ErrorInjection.hpp"
using namespace std ; 
int main(){
	   
        fstream inject , output ; 
        inject.open("../transmission_input.txt");
        output.open("../output.txt");
        string s ; 
        cout<<"getting dataword ....\n";
        inject>>s ;
        cout<<"here's the codeword going through the transmission channel \n" ; 
        cout<<s<<endl;

        cout<<"1. random error \n 2.custom error\n";
        int ll ;
        cin>>ll ;
        if(ll==1){
            ErrorInjection e ;
            cout<<e.random_inject(s)<<endl ;
            output<<e.random_inject(s);
            output.close();
            inject.close();
        } 
        else{
        int k ;
        cout<<"enter 257 to exit \n";
        ErrorInjection e ;
        int n ; 
        cout<<"enter position to induce error : - " ; 
        string new_string = s ;
        while(cin>>n){

        	if(n==257)
        	       break ;
            cout<<"new codeword: \n";
            new_string = e.single_bit_inject(s,n) ;
        	cout<<new_string<<endl;
            
            cout<<"enter position to induce error : - " ; 
                
        }
        output<<new_string;
        output.close();
        inject.close();
    }
       
}

 