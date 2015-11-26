#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

/*----------------------------convert----------------------*/

//typedef string hexa;

char tohexdigit(int c)
{
	if(c==0) return '0';
	if(c==1) return '1';
	if(c==2) return '2';
	if(c==3) return '3';
	if(c==4) return '4';
	if(c==5) return '5';
	if(c==6) return '6';
	if(c==7) return '7';
	if(c==8) return '8';
	if(c==9) return '9';
	if(c==10) return 'A';
	if(c==11) return 'B';
	if(c==12) return 'C';
	if(c==13) return 'D';
	if(c==14) return 'E';
	if(c==15) return 'F';
}

string tohex(int c)
{
	string sum="";
	while(c>0)
	{
		sum=tohexdigit(c%16) + sum;
		c/=16;
	}
	return sum;
}

int todecdigit(char c)
{
	if(c=='0') return 0;
	if(c=='1') return 1;
	if(c=='2') return 2;
	if(c=='3') return 3;
	if(c=='4') return 4;
	if(c=='5') return 5;
	if(c=='6') return 6;
	if(c=='7') return 7;
	if(c=='8') return 8;
	if(c=='9') return 9;
	if(c=='A') return 10;
	if(c=='B') return 11;
	if(c=='C') return 12;
	if(c=='D') return 13;
	if(c=='E') return 14;
	if(c=='F') return 15;
}

int todec(string str)
{
	int l=str.length()-1,t=1,sum=0;
	while(l>=0)
	{
		sum+=(todecdigit(str[l])*t);
		t*=16;
		--l;
	}
	return sum;
}

string extend(int n,string str)
{
	string t="";
	int i;
	for(i=0;i<n-str.length();++i)
		t+="0";
	return t+str;
}

string tobinary(char c)
{
	if(c=='0') return "0000";
	if(c=='1') return "0001";
	if(c=='2') return "0010";
	if(c=='3') return "0011";
	if(c=='4') return "0100";
	if(c=='5') return "0101";
	if(c=='6') return "0110";
	if(c=='7') return "0111";
	if(c=='8') return "1000";
	if(c=='9') return "1001";
	if(c=='A') return "1010";
	if(c=='B') return "1011";
	if(c=='C') return "1100";
	if(c=='D') return "1101";
	if(c=='E') return "1110";
	if(c=='F') return "1111";
}

char tohexnum(string c)
{
	if(c=="0000") return '0';
	if(c=="0001") return '1';
	if(c=="0010") return '2';
	if(c=="0011") return '3';
	if(c=="0100") return '4';
	if(c=="0101") return '5';
	if(c=="0110") return '6';
	if(c=="0111") return '7';
	if(c=="1000") return '8';
	if(c=="1001") return '9';
	if(c=="1010") return 'A';
	if(c=="1011") return 'B';
	if(c=="1100") return 'C';
	if(c=="1101") return 'D';
	if(c=="1110") return 'E';
	if(c=="1111") return 'F';
}

/*int main()
{
	return 0;
}*/