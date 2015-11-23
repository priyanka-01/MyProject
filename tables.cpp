#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

/*-----------------------Tables----------------------------*/

struct op_info{
	char exist;
	string opcode;
	op_info(){
		exist='n';
	}
};

struct sym_info{
	string address;
	string value;
	char exist;
	sym_info(){
		exist='n';
	}
};

typedef map<string,op_info> map1;
typedef map<string,sym_info> map2;

map1 OPTAB;
map2 SYMTAB;

void make()
{
	OPTAB["ADD"].opcode ="18";
	OPTAB["ADD"].exist ='y';
	
	OPTAB["ADDR"].opcode ="90";
	OPTAB["ADDR"].exist ='y';
	
	OPTAB["ADDF"].opcode ="58";
	OPTAB["ADDF"].exist ='y';	

	OPTAB["AND"].opcode ="AND";
	OPTAB["AND"].exist ='y';

	OPTAB["CLEAR"].opcode ="B4";
	OPTAB["CLEAR"].exist ='y';
	
	OPTAB["COMP"].opcode ="28";
	OPTAB["COMP"].exist ='y';

	OPTAB["COMPF"].opcode ="88";
	OPTAB["COMPF"].exist ='y';

	OPTAB["COMPR"].opcode ="A0";
	OPTAB["COMPR"].exist ='y';
	
	OPTAB["DIV"].opcode ="24";
	OPTAB["DIV"].exist ='y';

	OPTAB["DIVF"].opcode ="64";
	OPTAB["DIVF"].exist ='y';

	OPTAB["DIVR"].opcode ="9C";
	OPTAB["DIVR"].exist ='y';
	
	OPTAB["J"].opcode ="3C";
	OPTAB["J"].exist ='y';

	OPTAB["JEQ"].opcode ="30";
	OPTAB["JEQ"].exist ='y';

	OPTAB["JGT"].opcode ="34";
	OPTAB["JGT"].exist ='y';

	OPTAB["JLT"].opcode ="38";
	OPTAB["JLT"].exist ='y';

	OPTAB["JSUB"].opcode ="48";
	OPTAB["JSUB"].exist ='y';

	OPTAB["LDA"].opcode ="00";
	OPTAB["LDA"].exist ='y';

	OPTAB["LDB"].opcode ="68";
	OPTAB["LDB"].exist ='y';

	OPTAB["LDCH"].opcode ="50";
	OPTAB["LDCH"].exist ='y';

	OPTAB["LDF"].opcode ="70";
	OPTAB["LDF"].exist ='y';

	OPTAB["LDL"].opcode ="08";
	OPTAB["LDL"].exist ='y';

	OPTAB["LDS"].opcode ="6C";
	OPTAB["LDS"].exist ='y';

	OPTAB["LDT"].opcode ="74";
	OPTAB["LDT"].exist ='y';

	OPTAB["LDX"].opcode ="04";
	OPTAB["LDX"].exist ='y';

	OPTAB["LPS"].opcode ="D0";
	OPTAB["LPS"].exist ='y';

	OPTAB["MUL"].opcode ="20";
	OPTAB["MUL"].exist ='y';

	OPTAB["MULF"].opcode ="60";
	OPTAB["MULF"].exist ='y';

	OPTAB["OR"].opcode ="44";
	OPTAB["OR"].exist ='y';

	OPTAB["RD"].opcode ="D8";
	OPTAB["RD"].exist ='y';

	OPTAB["RSUB"].opcode ="4C";
	OPTAB["RSUB"].exist ='y';
	
	OPTAB["STA"].opcode ="0C";
	OPTAB["STA"].exist ='y';

	OPTAB["SSK"].opcode ="EC";
	OPTAB["SSK"].exist ='y';

	OPTAB["STB"].opcode ="78";
	OPTAB["STB"].exist ='y';

	OPTAB["STCH"].opcode ="54";
	OPTAB["STCH"].exist ='y';

	OPTAB["STF"].opcode ="80";
	OPTAB["STF"].exist ='y';

	OPTAB["STI"].opcode ="D4";
	OPTAB["STI"].exist ='y';

	OPTAB["STL"].opcode ="14";
	OPTAB["STL"].exist ='y';

	OPTAB["STS"].opcode ="7C";
	OPTAB["STS"].exist ='y';

	OPTAB["STSW"].opcode ="E8";
	OPTAB["STSW"].exist ='y';

	OPTAB["STT"].opcode ="84";
	OPTAB["STT"].exist ='y';

	OPTAB["STX"].opcode ="10";
	OPTAB["STX"].exist ='y';

	OPTAB["SUB"].opcode ="1C";
	OPTAB["SUB"].exist ='y';

	OPTAB["SUBF"].opcode ="5C";
	OPTAB["SUBF"].exist ='y';

	OPTAB["TD"].opcode ="E0";
	OPTAB["TD"].exist ='y';

	OPTAB["TIX"].opcode ="2C";
	OPTAB["TIX"].exist ='y';

	OPTAB["WD"].opcode ="DC";
	OPTAB["WD"].exist ='y';
}

/*int main()
{
	make();
	return 0;
}*/
