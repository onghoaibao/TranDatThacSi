#include <iostream>
#include <string.h>
#include <locale>
using namespace std;

string getMajor(string str);
string getMinor(string str);
long convertHEXtoDEC(string s);
string getValueByPos(int pos, string sData);
int main () {
    //0CAD0025BB
    // string s = "OK+DISISOK+DISC:4C000215:2G234454CF6D5A0FADF2F4911BA9FFA7:0CAD0025BB:0CF3EE041CBB:-052OK+DISC:00000000:00000000000000000000000000000000:0C9D0015BB:B9782E08068C:-071OK+DISCE";

    // int i1 = s.find("0CF3EE041CBB");
    // string a1 = s.substr(i1 - 11, 10);

    // int i2 = s.find("B9782E08068C");
    // string a2 = s.substr(i2 - 11, 10);

    // string pos11 = getValueByPos(1, a1);
    // string pos12 = getValueByPos(2, a1);
    // string pos13 = getValueByPos(3, a1);

    // string pos21 = getValueByPos(1, a2);
    // string pos22 = getValueByPos(2, a2);
    // string pos23 = getValueByPos(3, a2);

    // cout << "pos11: " << pos11 <<endl;
    // cout << "pos12: " << pos12 <<endl;
    // cout << "pos13: " << pos13 <<endl;

    // cout << "pos21: " << pos21 <<endl;
    // cout << "pos22: " << pos22 <<endl;
    // cout << "pos23: " << pos23 <<endl;
    char a = 43;
    cout << a << endl;
   return 0;

}

string getMajor(string str){
    string rs = "";
    rs = str.substr(0, 4);
    return rs;
}

string getMinor(string str){
    string rs = "";
    rs = str.substr(4, 4);
    return rs;
}

long convertHEXtoDEC(string s) {
    char * p;
    long n = strtol( s.c_str(), & p, 16 );
    if ( * p != 0 ) { //my bad edit was here
        cout << "not a number" << endl;
    }
    return n;
}

string getValueByPos(int pos, string sData){
    int rs = 0;
    string hma = getMajor(sData);
    string hmi = getMinor(sData);

    switch(pos){
        case 1:
            rs = convertHEXtoDEC(hma)%100;
            break;
        case 2:
            rs = convertHEXtoDEC(hma)/100;
            break;
        case 3:
            rs = convertHEXtoDEC(hmi)%100;
            break;
    }

    return to_string(rs);
}