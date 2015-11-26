#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "run.cpp"
using namespace std;

/*-----------------pass 2---------------------*/

string txt_s="",txt_e="",start,locctr;
int txtlen=0,base= INT_MAX;

ifstream intm;
ofstream obj,mod,lst;
string set(string);
void input(string []);
void assembler(string []);
string get_code(string []);

string set(string s)
{
	string x=tobinary(s[0]);
	x=x.substr(1,3);
	x="1"+x;
	char c;
	c=tohexnum(x);
	string st="";
	for(int i=0;i<s.length();++i)
	{
	if(i!=0) st+=s[i];
	else st+=c;	
	}	
	return st;
}

void input(string x[])
{
	int i;
	for(i=0;i<6;++i)
		getline(intm,x[i]);
		//cout<<"Input successfully called"<<endl;
		cout<<"Input for line: "<<x[0]<<endl;
		for(i=1;i<6;++i)
			cout<<x[i]<<endl;
}

void assembler(string x[])
{
	string objcode;
	if(x[2]=="RESB"||x[2]=="RESW")
	{
		lst<<x[0]<<"\t"<<extend(4,x[4])<<"\t\t"<<x[1]<<"\t"<<x[2]<<endl;
		if(txtlen>0)
			obj<<txt_s<<"^"<<extend(2,tohex(txtlen/2))<<txt_e<<endl;
		txt_s="";
		txt_e="";
		txtlen=0;
		return ;
	}
	else
	{
		objcode=get_code(x);
		cout<<"x[2]: "<<x[2]<<"\t\t"<<objcode<<endl;

		lst<<x[0]<<"\t"<<extend(4,x[4])<<"\t\t"<<x[1]<<"\t"<<x[2]<<"\t"<<x[3]<<"\t\t"<<objcode<<endl;
	}
	if(txt_s=="")
	{
		locctr=tohex(todec(x[4]));
		txt_s="T^"+extend(6,locctr);
		txt_e="^"+objcode;
		txtlen=objcode.length();
	}
	else if ((txtlen+(objcode.length()))>60)
	{
		obj<<txt_s<<extend(2,tohex(txtlen/2))<<txt_e<<endl;
		locctr=tohex(todec(x[4]));
		txt_s="T^"+extend(6,locctr);
		txt_e="^"+objcode;
		txtlen=objcode.length();
	}
	else
	{
		txt_e+="^"+objcode;
		txtlen+=objcode.length();
	}
	if(x[2]=="LDB")
		base=todec(SYMTAB[x[3]].address);
}

string get_code(string x[])
{
	string ob1,ob2,p_ctr,op_add;
	if(x[2]=="BYTE")
	{
		int i;
		ob1="";
		if(x[3][0]=='X')
		{
			for(i=2;i<x[3].length()-1;++i) 
				ob1+=x[3][i];
		}
		else
		{
			for(i=2;i<x[3].length()-1;++i)
				ob1+=tohex((int)x[3][i]);
		}
		ob1=extend(6,ob1);
		return ob1;
	}

	else if(x[2]=="WORD")
	{
		ob1=tohex(atoi(x[3].c_str()));
		ob1=extend(6,ob1);
		return ob1;
	}

	else if(x[2]=="RSUB")
	{
		return "4F0000";
	}

	else
	{
		cout<<x[2]<<endl;
		ob1=OPTAB[x[2]].opcode;
		//ob1=tohex(todec(ob1)+3);
		ob2="0";
		p_ctr=tohex(todec(x[5]));
		op_add=tohex(todec(SYMTAB[x[3]].address));
		cout<<"Program Counter: "<<p_ctr<<"Operand address: "<<op_add<<endl;
		int f=0;
		if(x[3][x[3].length()-2]==',') 
		{
			string p;
			p=x[3].substr(0,6);
			op_add=tohex(todec(SYMTAB[p].address));
			f=1;
		}
		ob2=op_add;
		if(op_add.length()<4) ob2=extend(4,op_add);
		if(f==1)
		{
		ob2=set(ob2);
		} 
		return (ob1+ob2);	
	}
}

void load()
{
	string m[6];
 	if(err_flag)
 	{
 		cout<<"Errors found!\nRefer the error file to debug errors"<<endl;
 		exit(1);
 	}
 	intm.open("intermediate.txt");
 	obj.open("object.txt");
 	lst.open("list.txt");
 	lst<<"LINE\tLOC\t\tSOURCE STATEMENT\t\tObject Code"<<endl;
 	lst<<"----------------------------------------------------------------"<<endl<<endl;
 	input(m);
 	while(m[1]=="$")
 	{
 		lst<<m[0]<<"\t\t"<<m[2]<<endl;
 		input(m);
 	}

 	if(m[2]=="START")
 	{
 		lst<<m[0]<<"\t"<<extend(4,m[4])<<"\t\t"<<m[1]<<"\t"<<m[2]<<"\t"<<m[3]<<endl;
 		obj<<"H^";
 		int i;
 		for(i=0;i<m[1].length();++i) obj<<m[1][i];
 		for(;i<6;++i) obj<<" ";
 		//hexa len=m[2];
 	    obj<<"^"<<extend(6,m[3]);
 		obj<<"^"<<extend(6,end)<<endl;
 	    start=m[3];
 	}
 	else
 	{
 		err_flag=1;
 		err<<"Intermediate file has no start!"<<endl;
 	}
 	while(1)
 	{
 		input(m);
 		if(m[1]=="$")
 		{
 			lst<<m[0]<<"\t\t"<<endl;
 			continue;
 		}
 		if(m[1]=="END")
 		{
 			lst<<m[0]<<"\t\t\t"<<m[1]<<"\t\t"<<m[2]<<endl;
 			if(txtlen>0)
 			{
 				obj<<txt_s<<"^"<<extend(2,tohex(txtlen/2))<<txt_e<<endl;
 				cout<<"!!"<<endl;
 			}
 			obj<<"E^"<<extend(6,start);
 			break;	
 		}
 		assembler(m);
 		cout<<"opcode: "<<m[2]<<":::";
 	}
 		if(err_flag)
    {
        cout<<"Errors encountered! Listing file not prepared!"<<endl;
        cout<<"Have a look at the error file to know more!"<<endl;
    }
    else
    {
        cout<<"INPUT FILE ASSEMBLED SUCCESSFULY!!"<<endl;
    }
}



int main()
{
 	pass1();
 	load();
    return 0;
}
