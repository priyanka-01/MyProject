#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "convert.cpp"
#include "tables.cpp"

using namespace std;

/*--------------------pass1--------------------------*/

ifstream fin;
ofstream fout,err;

bool err_flag=0;
int line_num,count;
string pc,end;

bool is_space(char c)
{
	if(c==' ') return true;
	if(c== '\t') return true;
	return false;
}

void getword(string a , string word[] )
{
	int i;
	//cout<<"getword called"<<endl;
	for(i=0;i<5;++i)
	{
		word[i]="";
	}
	count = 0;
	i=0;
	while(is_space(a[i]) && i<a.length()) {++i;}
	if(i==a.length()|| a[i]=='.') return;
	for(;i<a.length();)
	{
		while(is_space(a[i]) && i<a.length()){++i;continue;}
		if(i==a.length()) break;
		for(;!is_space(a[i]) && i<a.length() ;++i) word[count]+=a[i];
			++count;
	}
}

void generate(string word[])
{
	cout<<"word[0]: "<<word[0]<<"\tpc: "<<pc<<endl;
	if(OPTAB[word[0]].exist=='y')
	{
		cout<<"0 is opcode!"<<endl;
		fout<<""<<endl;
		fout<<word[0]<<endl;
		fout<<word[1]<<endl;
		fout<<pc<<endl;
		pc=tohex(todec(pc)+3);
		fout<<pc<<endl;
		return;
	}

	else if(OPTAB[word[0]].exist=='n')
	{
		if(SYMTAB[word[0]].exist=='y')
		{
			err<<"line "<<line_num<<": Duplicate Symbol"<<endl;
			cout<<"line "<<line_num<<": Duplicate Symbol"<<endl;
			err_flag=1;
		}
		else
		{
			SYMTAB[word[0]].address=pc;
			SYMTAB[word[0]].exist='y';
			fout<<word[0]<<endl;
			fout<<word[1]<<endl;
			fout<<word[2]<<endl;
			fout<<pc<<endl;
			if(OPTAB[word[1]].exist=='y')
				pc=tohex(todec(pc)+3);
			else if(word[1]=="WORD")
				pc=tohex(todec(pc)+3);
			else if(word[1]=="RESW")
			{
				pc=tohex(todec(pc)+(atoi(word[2].c_str())*3));
			}
			else if(word[1]=="RESB")
			{
				pc=tohex(todec(pc)+(atoi(word[2].c_str())));
			}
			else if (word[1]=="BYTE")
			{
				int l=word[1].length()-3;
				if(word[1][0]=='X') l/=2;
				pc=tohex(todec(pc)+l);
			}
			fout<<pc<<endl;
		}
	}
	else
	{
		err<<"Line "<<line_num<<" : Opcode not found"<<endl;
		cout<<"Line "<<line_num<<" : Opcode not found"<<endl;
		err_flag=1;
	}
}

void pass1()
{
	make();
	char ch;
	string s;
	string word[5];
	fin.open("input_fibonacci.txt");
	if(fin==NULL)
		exit(1);
	fout.open("intermediate.txt");
	err.open("error.txt");
	getline(fin,s);
	//cout<<s<<count;
	getword(s,word);
	//for(int k=0;k<5;++k) cout<<word[k]<<endl;
	line_num=5;
	if(count==0) //comment or subroutine called
	{
		fout<<line_num<<endl;
		fout<<"$";
		fout<<s<<endl;
		fout<<""<<endl;
		line_num+=5;
		cout<<"s: "<<s<<endl;
    }
    pc="0";
    if(word[0]=="START")
    {
    	fout<<line_num<<endl;
    	pc=word[1];
    	fout<<"START"<<endl;
    	fout<<word[2]<<endl;
    	fout<<pc<<endl;
    	fout<<pc<<endl;
    	cout<<pc<<" is start!"<<endl;
    }
    else if(word[1]=="START")
    {
    	fout<<line_num<<endl;
    	pc=word[2];
    	fout<<word[0]<<endl;
    	fout<<"START"<<endl;
    	fout<<word[2]<<endl;
    	fout<<pc<<endl;
    	fout<<pc<<endl;
    	cout<<pc<<" is start!"<<endl;
    }
    else
    generate(word);
    while(true)
    {
    	getline(fin,s);
    	getword(s,word);
    	line_num+=5;
    	//cout<<"s: "<<s<<endl;
    	fout<<line_num<<endl;
    	if(count==0)
    	{
    		//cout<<"Comment detected"<<endl;
    		fout<<"$"<<endl;
    		fout<<s<<endl;
    		fout<<""<<endl;
    		fout<<""<<endl;
    		fout<<""<<endl;
    		continue;
    	}
    	if(word[0]=="END")
    	{
    		fout<<word[0]<<endl;
    		fout<<word[1]<<endl;
    		fout<<pc<<endl;
    		fout<<""<<endl;
    		end=pc;
    		break;
    	}
    	generate(word);
    }
}

/*int main()
{
	pass1();
	return 0;
}*/

