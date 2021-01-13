#include<bits/stdc++.h>
using namespace std;

/* function prototypes */

void make_32bit_instr(string b);	//converts into 32 bit binary instruction
void r_format(string b);			//converts instruction into r-format binary instruction
void i_format(string b);			//converts instruction into i-format binary instruction
void j_format(string b);			//converts instruction into j-format binary instruction
string register_number(string b);	//gives register number in binary form
string deci_2_bin(string a, string c);		//converts number in string format to 16 bit binary number in string format
string bin_2_hex(string c);			//converts number in string format to hexadecimal number in string format
char hex_rule(int n);				//rule book for hexadecimal conversion
string labeltable_label[100];		//stores label
int labeltable_address[100];		//stores random address corresponding to label
string dec_2_bin(string a, int n);	//converts number into required number of bits of binary format

string dec_2_bin(string a, int n)
{
	int num = n;
	string bin;						//where the binary number will be stored
	int i;
	if(a == "j" || a == "jal")		//if in this format then convert it into 26 bits
		i = 25;
	else 
		i = 15;						//other types 16 bits

	while(num != 0)
	{
		if(num%2 == 1)
			bin.push_back('1');
		else
			bin.push_back('0');

		num = num/2;
		i--;
	}
	for(int j=i; j>=0; j--)			//placing 0s in remaining bits at back
	{
		bin.push_back('0');
	}
	reverse(bin.begin(), bin.end());	//reverse the string 
	return bin;
}

char hex_rule(int n)		//rule book for hexadecimal conversion
{
	if(n == 0)
		return '0';
	else if(n == 1)
		return '1';
	else if(n == 2)
		return '2';
	else if(n == 3)
		return '3';
	else if(n == 4)
		return '4';
	else if(n == 5)
		return '5';
	else if(n == 6)
		return '6';
	else if(n == 7)
		return '7';
	else if(n == 8)
		return '8';
	else if(n == 9)
		return '9';
	else if(n == 10)
		return 'a';
	else if(n == 11)
		return 'b';
	else if(n == 12)
		return 'c';
	else if(n == 13)
		return 'd';
	else if(n == 14)
		return 'e';
	else if(n == 15)
		return 'f';
}

string bin_2_hex(string c)
{
	//cout<<"yes12"<<endl;
	int d = 0;
	string hex;

	for(auto it=c.begin(); it < c.end(); it=it+4)		//take 4 bits pairs and convert it into one hexadecimal digit
	{
		d = 0;
		if(*it == '1')
			d = d + 8;
		if(*(it+1) == '1')
			d = d + 4;
		if(*(it+2) == '1')
			d = d + 2;
		if(*(it+3) == '1')
			d = d + 1;
		hex.push_back(hex_rule(d));
	}
	return hex;											//return hexadecimal string
}
string deci_2_bin(string a, string c)
{
	int num = stoi(c);			//converts string into number
	string bin;					//where binary number will be stored in the form of string	
	int i;
	if(a == "shamt")
		i = 4;
	else
		i = 15;					//16 bits binary number
	if(num >= 0)				//if number is positive so signed and unsigned will be same
	{
		while(num != 0)
		{
			if(num%2 == 1)
				bin.push_back('1');
			else
				bin.push_back('0');

			num = num/2;
			i--;
		}
		for(int j=i; j>=0; j--)
		{
			bin.push_back('0');
		}
		reverse(bin.begin(), bin.end());
	}
	else						//if number is negative
	{
		num = abs(num);					//absolute number
		bin = dec_2_bin("a", num);		//convert to binary
		for(auto it=bin.begin(); it<bin.end(); it++)		//complement of binary number
		{
			if(*it == '1')
				*it = '0';
			else
				*it = '1';
		}
		for(auto it=bin.rbegin(); it<bin.rend(); it++)		//adding 1 in this binary number
		{
			if(*it == '1')
				*it = '0';
			else
			{
				*it = '1';
				break;
			}
		}
	}
	return bin;					//return the binary number
}

string register_number(string b)
{
	if(b == "$zero")
		return "00000";
	else if(b == "$v0")
		return "00010";
	else if(b == "$v1")
		return "00011";
	else if(b == "$a0")
		return "00100";
	else if(b == "$a1")
		return "00101";
	else if(b == "$a2")
		return "00110";
	else if(b == "$a3")
		return "00111";
	else if(b == "$t0")
		return "01000";
	else if(b == "$t1")
		return "01001";
	else if(b == "$t2")
		return "01010";
	else if(b == "$t3")
		return "01011";
	else if(b == "$t4")
		return "01100";
	else if(b == "$t5")
		return "01101";
	else if(b == "$t6")
		return "01110";
	else if(b == "$t7")
		return "01111";
	else if(b == "$s0")
		return "10000";
	else if(b == "$s1")
		return "10001";
	else if(b == "$s2")
		return "10010";
	else if(b == "$s3")
		return "10011";
	else if(b == "$s4")
		return "10100";
	else if(b == "$s5")
		return "10101";
	else if(b == "$s6")
		return "10110";
	else if(b == "$s7")
		return "10111";
	else if(b == "$t8")
		return "11000";
	else if(b == "$t9")
		return "11001";
	else if(b == "$gp")
		return "11100";
	else if(b == "$sp")
		return "11101";
	else if(b == "$fp")
		return "11110";
	else if(b == "$ra")
		return "11111";

}
void make_32bit_instr(string b)
{
	stringstream ss(b);
	string w;
	while(ss >> w)		//read operation type
	{
		if(w == "add" || w == "sub" || w == "addu" || w == "and" || w == "or" || w == "nor" || w == "slt" || w == "sll" || w == "srl" || w == "jr" || w == "mult" || w == "div" || w == "mflo" || w == "mfhi")	//these operations follow r-format
			r_format(b);
		else if(w == "addi" || w == "lw" || w == "sw" || w == "beq" || w == "bne" || w == "andi" || w == "ori" || w == "slti")
			i_format(b);
		else if(w == "j" || w == "jal")
			j_format(b);
	}
}
void r_format(string b)
{
	stringstream ss(b);
	string w;		//reads word
	string funt;	//reads fuunction
	string opcode;	//reads opcode
	string op;		//reads type of operation
	string rs;		//reads register source 1
	string rt;		//reads register source 2
	string rd;		//reads register destination
	string shamt;	//reads shift amount

	ss >> w;
	op = w;		//reads operation
	
	if(op == "add" || op == "sub" || op == "and" || op == "or" || op =="nor" || op == "slt")
	{
		ss >> w;							//reads destination register
		w.erase(3);							//removes comma character
		rd = register_number(w);			

		ss >> w;							//reads source register 1
		if(w == "$zero,")					//if it is zero register
			w.erase(5);
		else								//if it is another register
			w.erase(3);	
		rs = register_number(w);		

		ss >> w;							//reads source register 2
		if(w == "$zero,")
			w.erase(5);
		else
			w.erase(3);	
		rt = register_number(w);		

		opcode = "000000";			//r-format have same opcodes
		shamt = "00000";			//no shift 

		/* each operation have particcular function value */
		if(op == "add")
			funt = "100000";
		else if(op == "sub")
			funt = "100010";
		else if(op == "and")
			funt = "100100";
		else if(op == "or")
			funt = "100101";
		else if(op == "nor")
			funt = "100111";
		else if(op == "slt")
			funt = "101010";
	}
	else if(op == "sll" || op == "srl")
	{
		opcode = "000000";

		ss >> w;		//reads destination register
		w.erase(3);		//removes comma character
		rd = register_number(w);			

		ss >> w;		//reads source register 2
		w.erase(3);
		rt = register_number(w);		

		rs = "00000";		//no second register

		ss >> w;
		shamt = deci_2_bin("shamt", w);		//shift amount in binary digits
		if(op == "sll")
			funt = "000000";
		else if(op == "srl")
			funt = "000010";
	}
	else if(op == "jr")
	{
		opcode = "000000";
		ss >> w;
		rs = register_number(w);
		rd = "00000";
		rt = "00000";
		shamt = "00000";
		funt = "001000";
	}
	else if(op == "mult" || op == "div")
	{
		opcode = "000000";
		if(op == "mult")
			funt = "011000";
		else
			funt = "011010";
		ss >> w;
		w.erase(3);
		rs = register_number(w);

		ss >> w;
		rt = register_number(w);

		rd = "00000";
		shamt = "00000";
	}
	else if(op == "mflo" || op == "mfhi")	//for multiplication and division cases: move lo and hi to given register
	{
		opcode = "000000";
		if(op == "mflo")
			funt = "010010";
		else 
			funt = "010000";
		ss >> w;
		rd = register_number(w);
		rs = "00000";
		rt = "00000";
		shamt = "00000";
	}

	w = opcode + rs + rt + rd + shamt + funt;					//specified format of machine code
	cout<<w<<" 	"<<"("<<bin_2_hex(w)<<", "<<b<<")"<<endl;		//sepcified format 
}

void i_format(string b)
{
	stringstream ss(b);
	string op;			//store operation
	string opcode;		//store opcode
	string immediate;	//store immediate value
	string rs;			//store source register
	string rt;			//store register destination
	string w;			//read word

	ss >> w;			//reads type of operation
	op = w;		
	if(op == "beq" || op == "bne")
	{
		if(op == "beq")
			opcode = "000100";
		else if(op == "bne")
			opcode = "000101";

		ss >> w;							//reads source register
		if(w == "$zero,")
			w.erase(5);						//removes comma character
		else
			w.erase(3);						//removes comma character
		rs = register_number(w);			

		ss >> w;							//reads source register 2
		if(w == "$zero,")
			w.erase(5);
		else
			w.erase(3);
		rt = register_number(w);		

		ss >> w;					 //reads offset value
		immediate = deci_2_bin("immediate", w);	//converts into binary number
				
	}
	else if(op == "addi" || op == "addiu" || op == "andi" || op == "ori" || op == "slti")
	{
		if(op == "addi")
			opcode = "001000";
		else if(op == "addiu")
			opcode = "001001";
		else if(op == "andi")
			opcode = "001100";
		else if(op == "ori")
			opcode = "001101";
		else if(op == "slti")
			opcode = "001010";

		ss >> w;						//reads destination register
		if(w == "$zero,")
			w.erase(5);
		else
			w.erase(3);
		rt = register_number(w);		

		ss >> w;					//reads source register
		if(w == "$zero,")
			w.erase(5);
		else
			w.erase(3);
		rs = register_number(w);

		ss >> w;						//reads constant value
		immediate = deci_2_bin("immediate", w);		
	}
	else if(op == "lw" || op == "sw")
	{
		
		if(op == "lw")
			opcode = "100011";
		else if(op == "sw")
			opcode = "101011";

		ss >> w;
		if(w == "$zero,")
			w.erase(5);
		else
			w.erase(3);
		rt = register_number(w);		//reads destination / source register

		ss >> w;						//reads immediate value 
		immediate = deci_2_bin("immediate", w);

		ss >> w;						//reads base register
			w.erase(0,1);
			w.erase(3);

		rs = register_number(w);		
	}
	
	w = opcode + rs + rt + immediate;
	cout<<w<<" 	"<<"("<<bin_2_hex(w)<<", "<<b<<")"<<endl;	
}

void j_format(string b)		//this function converts j-format instructon to binary code
{
	string op;		//reads operation type
	string opcode;		//reads opcode for a operation
	string address;		//reads address of a procedure/instruction
	string w;		//reads word

	stringstream ss(b);

	ss >> w;
	op = w;		//reads operation type

	if(op == "j")
		opcode = "000010";
	else if(op == "jal")
		opcode = "000011";

	ss >> w;		//reads address
	for(int i=0; i<100; i++)
	{
		if(labeltable_label[i] == w)		//found label name in symbol table
		{
			address = dec_2_bin(op, labeltable_address[i]/4);		//maps address corresponding to label name and divided by furdue to byte addressing
			break;
		}
	}
	w = opcode + address;
	cout<<w<<" 	"<<"("<<bin_2_hex(w)<<", "<<b<<")"<<endl;
}


int main()
{
	/* labels and their corresponding random addresses */
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

	char  file[10];		//stores input file name
	char outfile[12];	//stores output file name
	string line;
	string word;
	cout<<"enter file name"<<endl;
	cin>>file;
	for(int i=0; i<5; i++)
	{
		outfile[i] = file[i];
	}
	outfile[5] = 'b';
	outfile[6] = 'i';
	outfile[7] = 'n';
	outfile[8] = '.';
	outfile[9] = 't';
	outfile[10] = 'x';
	outfile[11] = 't';

	freopen(file , "r", stdin);
	freopen(outfile, "w", stdout);

	while(getline(cin, line))		//reads the line from the file
	{
		string t;
		stringstream ss(line);
		while(ss >> word)
		{

			if(word == "#")		//if we detect comment indicator type then stop reading the words afterwards
				{
					break;
				}

				t = t + word + " ";
		}
		
		//cout<<t<<endl;
		make_32bit_instr(t);
	}
	return 0;
}