#include<bits/stdc++.h>
using namespace std;

void bin_2_mips(string a);			//converts into mips instruction
void r_format(string a);			//converts r-format
void i_format(string a);			//converts i-format
void j_format(string a);			//converts j-format
int bin_2_deci(string a, string b, string c);			//converts binary to decimal numbers with required number of bits
string labeltable_label[100];		//table storing labels
int labeltable_address[100];		//table storing corresponding addresses

int bin_2_deci(string a, string b, string c)	
{
	stringstream ss(b);
	char bit;						//reads character
	int num = 0;					
	int j;
	if(a == "j" || a == "jal")
		j = 25;						//26 bit address value
	else if(a == "shamt")
		j = 4;						//5 bit shift amount
	else if(a == "immediate")
		j = 15;						//16 bit immediate value
	for(int i=j; i>=0; i--)
	{
		ss >> bit;
		if(bit == '1' && (i == j && j != 4) && c == "signed")		
		{
			num = num - pow(2, i);
		}
		else if(bit == '1')
			num = num + pow(2, i);
	}
	return num;
}

string register_number(string b)		//gives particular string type according to number
{
	if(b == "00000")
		return "$zero";
	else if(b == "00010")
		return "$v0";
	else if(b == "00011")
		return "$v1";
	else if(b == "00100")
		return "$a0";
	else if(b == "00101")
		return "$a1";
	else if(b == "00110")
		return "$a2";
	else if(b == "00111")
		return "$a3";
	else if(b == "01000")
		return "$t0";
	else if(b == "01001")
		return "$t1";
	else if(b == "01010")
		return "$t2";
	else if(b == "01011")
		return "$t3";
	else if(b == "01100")
		return "$t4";
	else if(b == "01101")
		return "$t5";
	else if(b == "01110")
		return "$t6";
	else if(b == "01111")
		return "$t7";
	else if(b == "10000")
		return "$s0";
	else if(b == "10001")
		return "$s1";
	else if(b == "10010")
		return "$s2";
	else if(b == "10011")
		return "$s3";
	else if(b == "10100")
		return "$s4";
	else if(b == "10101")
		return "$s5";
	else if(b == "10110")
		return "$s6";
	else if(b == "10111")
		return "$s7";
	else if(b == "11000")
		return "$t8";
	else if(b == "11001")
		return "$t9";
	else if(b == "11100")
		return "$gp";
	else if(b == "11101")
		return "$sp";
	else if(b == "11110")
		return "$fp";
	else if(b == "11111")
		return "$ra";
}

void bin_2_mips(string a)			//converts binary to mips language
{
	string opcode;		
	char bit;
	stringstream ss(a);

	//reads opcode to determine which format it belongs
	for(int i=0; i<6; i++)		
	{
		ss >> bit;
		opcode.push_back(bit);
	}
	if(opcode == "000000")
		r_format(a);
	else if(opcode == "000010" || opcode == "000011")
		j_format(a);
	else
		i_format(a);
}

void r_format(string a)		//converts r_format to mips language
{
	string mips_instruction;
	string opcode;
	string operation;
	string rs;
	string rt;
	string rd;
	string shamt;
	string funct;
	char bit;

	stringstream ss(a);

	for(int i=0; i<32; i++)
	{
		ss >> bit;
		if(i < 6)							//reads opcode bit by bit
		{
			opcode.push_back(bit);
		}
		else if(i>5 && i<11)				//reads source register
		{
			rs.push_back(bit);
		}
		else if(i>10 && i<16)				//reads source register
		{
			rt.push_back(bit);
		}
		else if(i>15 && i<21)				//reads destination register
		{
			rd.push_back(bit);
		}
		else if(i>20 && i<26)				//reads shift amount
		{
			shamt.push_back(bit);
		}
		else if(i>25 && i<32)				//reads function type
		{
			funct.push_back(bit);
		}
	}
		rs = register_number(rs);
		rt = register_number(rt);
		rd = register_number(rd);

	if(funct == "100000")
	{
		operation = "add";
		mips_instruction = operation + " " + rd + ", " + rs + ", " + rt;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "100010")
	{
		operation = "sub";
		mips_instruction = operation + " " + rd + ", " + rs + ", " + rt;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "100100")
	{
		operation = "and";
		mips_instruction = operation + " " + rd + ", " + rs + ", " + rt;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "100111")
	{
		operation = "nor";
		mips_instruction = operation + " " + rd + ", " + rs + ", " + rt;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "000000")
	{
		operation = "sll";
		mips_instruction = operation + " " + rd + ", " + rt + ", ";
		cout<<mips_instruction<<bin_2_deci("shamt", shamt, "signed")<<endl;
	}
	else if(funct == "000010")
	{
		operation = "srl";
		mips_instruction = operation + " " + rd + ", " + rt + ", ";
		cout<<mips_instruction<<bin_2_deci("shamt", shamt, "signed")<<endl;
	}
	else if(funct == "001000")
	{
		operation = "jr";
		mips_instruction = operation + " " + rs;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "011000")
	{
		operation = "mult";
		mips_instruction = operation + " " + rs + ", " + rt;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "011010")
	{
		operation = "div";
		mips_instruction = operation + " " + rs + ", " + rt;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "010010")
	{
		operation = "mflo";
		mips_instruction = operation + " " + rd;
		cout<<mips_instruction<<endl;
	}
	else if(funct == "010000")
	{
		operation = "mfhi";
		mips_instruction = operation + " " + rd;
		cout<<mips_instruction<<endl;
	}
}

void i_format(string a)
{
	string opcode;
	string operation;
	string rs;
	string rt;
	string addr;
	string sign = "signed";
	int address;
	string label;
	char bit;
	string mips_instruction;
	stringstream ss(a);
	for(int i=0; i<32; i++)
	{
		ss >> bit;
		if(i < 6)
			opcode.push_back(bit);
		else if(i > 5 && i < 11)
			rs.push_back(bit);
		else if(i > 10 && i < 16)
			rt.push_back(bit);
		else
			addr.push_back(bit);
	}

	if(opcode == "000100" || opcode == "000101")
	{
		if(opcode == "000100")
			operation = "beq";
		else
			operation = "bne";

		rs = register_number(rs);
		rt = register_number(rt);
		address = bin_2_deci("immediate", addr, " ");	// in this case it is offset value
		
		mips_instruction = operation + " " + rs + ", " + rt + ", ";
		cout<<mips_instruction<<address<<endl;
	}
	else
	{
		if(opcode == "001000")
			operation = "addi";
		else if(opcode == "001001")
		{
			operation = "addiu";
			sign = "unsigned";
		}
		else if(opcode == "001100")
			operation = "andi";
		else if(opcode == "001101")
			operation = "ori";
		else if(opcode == "001010")
			operation = "slti";
		else if(opcode == "001001")
		{
			operation = "sltiu";
			sign = "unsigned";
		}
		else if(opcode == "100011")
			operation = "lw";
		else if(opcode == "101011")
			operation = "sw";

		if(operation == "lw" || operation == "sw")
		{
			rs = register_number(rs);
			rt = register_number(rt);
			address = bin_2_deci("immediate", addr, "signed");
			cout<<operation<<" "<<rt<<", "<<address<<"("<<rs<<")"<<endl;
		}
		else
		{
			rs = register_number(rs);
			rt = register_number(rt);
			address = bin_2_deci("immediate", addr, sign);
			mips_instruction = operation + " " + rt + ", " + rs;
			cout<<mips_instruction<<", "<<address<<endl;
		}
	}
}

void j_format(string a)
{
	string opcode;
	string addr;
	int address;
	string label;
	string operation;
	string mips_instruction;
	char bit;

	stringstream ss(a);
	for(int i=0; i<32; i++)
	{
		ss >> bit;

		if(i < 6)
			opcode.push_back(bit);
		else
			addr.push_back(bit);
	}
	if(opcode == "000010")
	{
		operation = "j";
	}
	else
	{
		operation = "jal";
	}
	address = bin_2_deci(operation, addr, "") * 4;
	for(int i=0; i<100; i++)
	{
		if(labeltable_address[i] == address)
		{
			label = labeltable_label[i];
			break;
		}
	}
	mips_instruction = operation + " " + label;
	cout<<mips_instruction<<endl;
}

int main()
{
	char file[10];
	char outfile[13];
	char bit;
	string line;
	
	labeltable_label[0] = "loop";
	labeltable_address[0] = 10000;
	labeltable_label[1] = "exit";
	labeltable_address[1] = 10004;
	labeltable_label[2] = "procedure";
	labeltable_address[2] = 10008;
	labeltable_label[3] = "l1";
	labeltable_address[3] = 10012;
	labeltable_label[4] = "fibo";
	labeltable_address[4] = 10016;
	labeltable_label[5] = "fact";
	labeltable_address[5] = 10020;
	labeltable_label[6] = "combi";
	labeltable_address[6] = 10024;

	
	cout<<"enter file name"<<endl;
	cin >> file;
	freopen(file, "r", stdin);
	outfile[0] = 'b';
	outfile[1] = 'i';
	outfile[2] = 'n';
	outfile[3] = '2';
	
	for(int i=4; i<9; i++)
	{
		outfile[i] = file[i-4];
	}
	outfile[9] = '.';
	outfile[10] = 'a';
	outfile[11] = 's';
	outfile[12] = 'm';
	freopen(outfile, "w", stdout);

	while(getline(cin, line))
	{
		string instruction;
		stringstream ss(line);
		
		int i = 0;
		for(i=0; i<32; i++)
		{
			ss >> bit;
			instruction.push_back(bit);
		}
		bin_2_mips(instruction);
	}
	return 0;
}