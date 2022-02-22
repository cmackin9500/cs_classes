// Extra credit lab
// COSC130
// This lab is a disassembler. It takes a binary machine code language and converts it intp RISCV format. The user will specify input file, output file (stdout or file), and whether they want it printed in abi or x format.
// Casey Mackinnon
// March 15th 2019
// Recieved help from TA Leroy, TA Chris, TA Daniel, TA Adnan, and TA Jacob
// I was not able to get the abi part of the lab. So when the user specifies abi format, it will still spit out in x format.

#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

// There were 5 types that I found. Each intruction will go through and see which type it is.
string R_type(int);
string I_type(int);
string S_type(int);
string U_type(int);
string J_type(int);
string abi(int);

int main(int argc, char *argv[])
{
// If the user types in too little or too much command line arguments the program will tell the correct format and return -1.
	if (!(argc == 3 || argc == 4)) {
		printf("Usage: %s <intput file> <output file> <instruction (optional)>\n", argv[0]);
		return -1;
	}

// opens the input file. If it does not exist, tell the user and return -1.
	FILE *in = fopen(argv[1], "rb");
	if (in == nullptr) {
			perror(argv[1]);
			return -1;
		}

// This finds the size of the input file. It will determine how many intructions to decode.
	fseek(in, 0, SEEK_END);
	int count = ftell(in)/4;
	fseek(in, 0, SEEK_SET);
	int *decode = (int*) malloc(sizeof(int)*count); // creates a dynamically allocated array
	
// transfters each instruction into an dynamic array
	for(int i = 0; i < count; ++i) 
	{
		int data;
		fread(&data, 1, 4, in);
		decode[i] = data;
	}

// once all done, closes the input file
	fclose(in);

// depending on what the user specifies, it will determine if it will be printed out in stdout or output file
	string ofile = argv[2];
	FILE *out;

	if(ofile == "-") {
		out = stdout;
	}
	else {
		out = fopen(argv[2], "wb");
		if(out == nullptr) {
			perror(argv[2]);
			return -1;
		}
	}

	int mask = 0x7f;

// this swtich statement will determine which type each interuction is.
	string op;
	for(int i = 0; i < count; ++i)
	{
		int type = decode[i] & mask;
		switch(type)
		{
			case 0x37:
				op = U_type(decode[i]);
				break;
			
			case 0x6f:
				op = J_type(decode[i]);
				break;

			case 0x3:
			case 0x13:
			case 0x67:
			case 0x1b:
				op = I_type(decode[i]);
				break;

			case 0x23:
				op = S_type(decode[i]);
				break;

			case 0x33:
				op = R_type(decode[i]);
				break;
			default:
		// if it does not match any instruction, it will tell the user it is invalid
				char err[25];
				char orr[100];
				sprintf(err, "     %-6s%s", "inv", "invalid");
				sprintf(orr, "%-30s// 0x%08x\n", err, decode[i]);
				op = "";
				fprintf(out, "%s", orr);
				break;
		}
		// prints out all the decoded instructions
		fprintf(out, "%s", op.c_str());
	}

// closes the output file and frees the dynamically allocated array of instructions
	fclose(out);
	free(decode);

	return 0;
}

// This function was for the abi file but I could not get this to work
string abi(int x) 
{

	string abi[] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "t3", "t4", "t5", "t6"};

	return abi[x];
}

// All the instructions needed in each type functions are coming from the table in RISCV. I take the binary instruction, shift it and and it to find the specific instrctions. 

string U_type(int decode)
{
// finds the neccessary instructions 
	int rd = (decode >> 7) & 0x1f;
	int imm = decode & 0xfffff000;
	char s[6];
	char out[25];
	char ret[100];

// stores all decoded instruction, stores it into a string and returns it
	sprintf(s,"%-5s", " ");
	sprintf(out, "%slui   x%d, %d", s, rd, imm);
	sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	return ret;
}

string J_type(int decode)
{
// finds all the neccessary instrcution
	int rd = (decode >> 7) & 0x1f;
	int first = (decode & 0x80000000) >> 11;			// 20
	int second = (decode & 0xff000);					// 19:12
	int third = (decode & 0x7fe00000) >> 20;			// 10:1
	int fourth = (decode & 0x100000) >> 9;				// 11
	int num = first^second^third^fourth;
	if(first == 1) {
		num |= 0xffe00000;
	}
	
// stores all decoded instruction, stores it into a string and returns itchar ret[100];
	char ret[100];
	char out[25];
	char s[6];
	sprintf(s, "%-5s", " ");
	sprintf(out, "%sjal   x%d, %d", s, rd, num);
	sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	return ret;
}	


string I_type(int decode)
{
// finds all the neccessary instrction. Since there are many under here, there are a lot of instructions
	bool i = false;
	bool a = false;
	int rd = (decode >> 7) & 0b11111;
    int rs1 = (decode >> 15) & 0b11111;
	int funct3 = (decode >> 12) & 0b111;
	int imm = (decode >> 20);
	int opcode = decode & 0b1111111;
	int shamt = (decode >> 20) & 0x1f;
	string command;
	char out[25];
	char ret[100];
	char s[6];

	sprintf(s, "%-5s", " ");

// determines which instruction that is needed to decode by lokking through the funct 3 and funct 7
	if(funct3 == 0x0) {
		if(opcode == 0x67) {
			command = "jalr";
			i = true;
		}
		else if(opcode == 0x3) {
			command = "lb";
		}
		else if(opcode == 0x13) {
			command = "addi";
			i = true;
		}
		else if(opcode == 0x1b) {
			command = "addiw";
			i = true;
		}
	}
// there are multiple ones which same funct so must make sure it gets to everything
	else if(funct3 == 0x1) {
		if(opcode == 0b11) {
			command = "lh";
		}
		else if(opcode == 0b10011) {
			command = "slli";
			i = true;
			a = true;
		}
	}
	else if(funct3 == 0x2) {
		command = "lw";
	}
	else if(funct3 == 0x3) {
		command = "ld";
	}
	else if(funct3 == 0x4) {
		command = "xori";
		i = true;
	}
	// i means immediate
	else if(funct3 == 0b101) {
		command = "srai";
		i = true;
		a = true;
	}
	else if(funct3 == 0x6) {
		if(opcode == 0x13) {
			command = "ori";
			i = true;
		}
		else if(opcode == 0x33) {
			command = "lwu";
			i = true;
		}
	}

	else if(funct3 == 0x7) {
		command = "andi";
		i = true;
	}
// if it matches none of them, it will tell the user it is invalid and returns -1
	else {
		sprintf(out, "%s%-6s%s", s, "inv", "invalid");
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
		return ret;
	}
	
// prinst the encoded instruction into a string depending on which one it is
	if(i == true && a == true) {
		sprintf(out, "%s%-6sx%d, x%d, %d", s, command.c_str(), rd, rs1, shamt);
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	}
	else if(i == true) {
		sprintf(out, "%s%-6sx%d, x%d, %d", s, command.c_str(), rd, rs1, imm);
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	}
	else {
		sprintf(out, "%s%-6sx%d, %d(x%d)", s, command.c_str(), rd, imm, rs1);
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	}	
	return ret;
}

string S_type(int decode)
{
// finds all the neccessary instrctions.
	string command;
	char out[25];
	char ret[100];
	char s[6];
	int rs1 = (decode >> 15) & 0x1f;
    int rs2 = (decode >> 20) & 0x1f;
    int funct3 = (decode >> 12) & 0x3;
	int first = (decode >> 7) & 0x1f;
	int second = (decode >> 22) & 0xfe0;
	int imm = first^second;		// the immediate here is more complex so it finds the two parts and merges them.
	
	sprintf(s, "%-5s", " ");

// finds out which instruction to decode
	if((decode >> 31) == 1) {
		imm |= 0xfffff000;
	}
// there are only storing instrctions in here.
	else if(funct3 == 0x0) {
		command = "sb";
	}
	else if(funct3 == 0x1) {
		command = "sh";
	}
	else if(funct3 == 0x2) {
		command = "sw";
	}
	else if(funct3 == 0x3) {
		command = "sd";
	}
// if it matches none, it will tell the user it is invalid
	else {
		sprintf(out, "%s%-6s%s", s, "inv", "invalid");
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
		return ret;
	}

// prints out the decoded instruction into a string
	sprintf(out, "%s%-6sx%d, %d(x%d)", s, command.c_str(), rs2, imm, rs1);
	sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	return ret;
}

string R_type(int decode)
{
// Gets all the needed instructions. This was a type with the most instructions so it needed many parts to find.
	string command;
	char out[25];
	char ret[100];
	char s[6];
	char what;	// this finds out which form of printf is going to be used
	int opcode = decode & 0x7f;
	int rd = (decode >> 7) & 0x1f;
	int rs1 = (decode >> 15) & 0x1f;
	int rs2 = (decode >> 20) & 0x1f;
	int funct3 = (decode >> 12) & 0b111;
	int funct7 = (decode >> 25) & 0x7f;
	int shamt1 = (decode >> 20) & 0x3f;
	int shamt2 = (decode >> 20) & 0x1f;
	int left = (decode >> 26) & 0x3f;

	sprintf(s, "%-5s", " ");

// looks through all the funct3 and funct7 to determine the one
	if(opcode == 0x33) {
		if(funct3 == 0x0) {
			if(funct7 == 0x0) {
				command = "add";
			}
			else if(funct7 == 0x20) {
				command = "sub";
			}
		}

		else if(funct3 == 0x1) {
			command = "sll";
		}

		else if(funct3 == 0x4) {
			command = "xor";
		}
		else if(funct3 == 0x5) {
			if(funct7 == 0x0) {
				command = "srl";
			}
			else if(funct7 == 0x20) {
				command = "sra";
			}
		}
		else if(funct3 == 0x6) {
			command = "or";
		}
		else if(funct3 == 0x7) {
			command = "and";
		}
		what = 'n';
	}
	// no means there is nothing special

	else if(opcode == 0x13) {
		if(funct3 == 0x1) {
			command = "slli";
		}
		else if(funct3 == 0x5) {
			if(left == 0x0) {
				command = "srli";
			}
			else if(left == 0x10) {
				command = "srai";
			}
		}
		what = 's';
	}
	// s means the decode will be in a form s...

	else if(opcode == 0x1b) {
		if(funct3 == 0x1) {
			command = "slliw";
		}
		else if(funct3 == 0x5) {
			if(left == 0x0) {
				command = "srliw";
			}
			else if(left == 0x10) {
				command = "sraiw";
			}
		}
		what = 'w';
	}
	// w means it will have w at the end

	else if(opcode == 0x3b) {
		if(funct3 == 0x0) {
			if(left == 0x0) {
				command = "addw";
			}
			else if(left == 0x10) {
				command = "subw";
			}
		}
		else if(funct3 == 0x1) {
			command = "sllw";
		}
		else if(funct3 == 0x5) {
			if(left == 0x0) {
				command = "srlw";
			}
			else if(left == 0x10) {
				command = "sraw";
			}
		}
		what = 'n';
	}
// if none matches, tells the user invalid
	else {
		sprintf(out, "%s%-6s%s", s, "inv", "invalid");
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
		return ret;
	}
// prints into string in correct format
	if(what == 'n') {
		sprintf(out, "%s%-6sx%d, x%d, x%d", s, command.c_str(), rd, rs1, rs2);
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	}

	else if(what == 's') {
		sprintf(out, "%s%-6sx%d, x%d, %d", s, command.c_str(), rd, rs1, shamt1);
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	}

	else if(what == 'w') {
		sprintf(out, "%s%-6sx%d, x%d, %d", s, command.c_str(), rd, rs1, shamt2);
		sprintf(ret, "%-30s// 0x%08x\n", out, decode);
	}
	return ret;
} 

