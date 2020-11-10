#include "bits/stdc++.h"
using namespace std;
class checksum
{public:
    bitset<8> getsum(bitset<8> a,bitset<8> b){
        bitset<8> sum = a^b ; 
        bitset<8> carry = (a&b)<<1 ; 
        if(carry.none())
            return sum ; 
        return getsum(sum , carry) ; 
    }
     void codeword_generator(string s, int length) {
      vector<string> vstring ;
      vector<bitset<8> > bitvector ; 
      bitset<8> sum , carry ; 
        
        for(int i = 0 ; i < s.size() ; i+=length)
            {
                string sub = s.substr(i,length);
                vstring.push_back(sub);
                bitset<8> bit(sub);
                cout<<bit<<endl;
                sum = getsum(sum , bit) ; 
            }
            sum.flip();

            cout<<"checksum = "<<sum<<endl ;
            cout<<"codeword generated = "<<s + sum.to_string()<<endl;
    }

    //  void insert(bool* data, uint16_t cksum) {
    //     *(uint16_t *)data = cksum; 
    // }

    //  bool isOk(bool data[], int len) {
    //     if (calc(data, len) == 0) {
    //         return true;
    //     }

    //     return false;
    // }
};