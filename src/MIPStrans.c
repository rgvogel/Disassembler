/*
 * MIPStrans.c
 *Precondition takes in a string of 32 binary digits
 *Post-Condition: returns a mips command based on the string of binary digits
 *  Created on: May 16, 2016
 *      Author: Roderick Vogel
 *     This converts a string of binary digits first to decimal using the binTodec function.
 *     Following this based on the opcode it either goes to the R method, I method or j method.
 *     Each of these methods will translate the code to decimals based on method and then convert it to MIPs code.
 */

#include "disassembler.h"

void MIPStrans(char string[])
{

	int opCode;
	opCode = binToDec( string,0,5);
	/**
	 *check opCode
	 */
	if(opCode == 0)
	{
		rFormat(string);
	}
	else if (opCode == 2 || opCode == 3  )
	{
		jFormat(string);
	}

	else
	{
		iFormat(string);
	}
}
/**
 * check code for r format includes add addu,sub, subu,
 * and, or, nor, sll, slr, slt, sltu, jr
 * seperated  by opcode 6 bit, then second
 * register  5bit, last register 5 bit, last register 5 bit,
 * empty 5 bit, last
 */
 void rFormat(char string[])
 {

	 	int fun; // number for function
	 	/**
	 	 * list of function types
	 	 */
	 static char * func[] =  {
			 "sll","","slr","","","","","","jr","",
			 "","","","","","","","","","",
			 "","","","","","","","","","",
			 "","","add","addu","sub","subu","and","or","","nor",
			 "","","slt","sltu","","","","","",""
	 };

	 /*
	  * number for function and 3 register
	  */

	 fun = binToDec(string,26,31);
	 printf("%d \n",fun);
	char*rs = getRegName(binToDec(string,6,10));
	char*rt = getRegName(binToDec(string,11,15));
	char*rd = getRegName(binToDec(string,16,20));
	//printf("%s, %s,%s \n",rs, rt, rd);
	if(func[fun]== "" || func[fun]== NULL)
	{
		printf("\t Error no function called\n");

	}
	else if( func[fun]== "jr")
	{
		printf("%s \t %s \n", func[fun], rs);

	}
	else
	{
		//print out address of the
		printf("%s \t %s, \t%s, \t%s \n", func[fun], rd, rs,rt);
	}
 }
 /**
  * check code for i format includes addi addiu,andi,ori,lw,lui
  * ,beq,bne,slti,sltiu
  * seperated  by opcode 6 bit and function, then first
  * register  5bit, last register 5 bit, last register 5 bit,
  * last 16 bits immedaite int
  */
 void iFormat(char string[])
 {
	 char*rs; //first register written
	 char*rt;
	 int im;
	 int fun; // number for function

	 static char * funci[] =  {
			 "","","","","beq","bne","","","addi","addiu",
			 "slti","sltiu","andi","ori","","lui","","","","",
			 "","","","","","","","","","",
			 "","","","","","lw","","","","",
			 "","","","sw","","","","","",""
	 };
	fun = binToDec(string,0,5);
	rs = getRegName(binToDec(string,6,10));
	rt = getRegName(binToDec(string,11,15));
	im = binToDec(string, 16,31);
	printf("hello %d \t %s \n", binToDec(string,0,5),funci[fun]);
	if(funci[fun]== "" || funci[fun]== NULL)
	{
		printf("\t Error no function called\n");

	}
	else if( funci[fun] == "lw" || funci[fun]== "sw")
	{
		printf("%s \t%s, \t%d \n", funci[fun],rt, im);
	}
	else
	{
		printf("%s,  \t%s, \t%s, \t%d \n", funci[fun],rt, rs, im);
	}
 }
 /**
  * check code for j format includes j,
  * seperated  by opcode 6 bit and function, then last 26 bits is address
  */
 void jFormat(char string[])
 {
	 int fun; // number for function
	 int address; // address
	 static char * funcj[] =  {
				 "","","j","jal","","","","","","",
		 };
	 fun = binToDec(string,0,5);

	 address = binToDec(string,6,31);
		if(funcj[fun]== "" || funcj[fun]== NULL)
		{
			printf("\t Error no function called\n");

		}
		else
		{
			printf("%s, \t %d \n", funcj[fun], address);
		}
 }
