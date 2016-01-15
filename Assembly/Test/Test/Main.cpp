#include <iostream>

typedef union
{
	struct
	{
		short v;
		short d;
		short s;
	} t1;

	struct
	{
		int a[2];
		char *p;
	} t2;
} u_type;

void get(u_type *up, char *dest)
{
	*dest = *up->t2.p;
}

int main()
{
	__asm	// MOV
	{
		MOV		EAX,	0xAAAAAAAA
		MOV		AX,		0xBBBB
		MOV		AH,		0xDD
		MOV		AL,		0xEE
		MOV		ECX,	EAX
		MOV		CH,		AL
		MOV		DX,		AX
		MOV		CX,		1
	}

	__asm	// ADD
	{
		ADD		ECX,	0x0000ABCD
		ADD		EAX,	ECX
		ADD		AX,		0x000F
		ADD		CX,		AX
		ADD		AH,		AL
		ADD		DL,		0x23
		ADD		BH,		2
	}

	__asm	// SUB
	{
		SUB		EDX,	0x000000DE
		SUB		EBX,	EAX
		SUB		AX,		0x00D0
		SUB		CX,		BX
		SUB		BH,		0xFF
		SUB		CL,		AH
		SUB		EDX,	3
	}

	__asm	// AND
	{
		AND		EBX,	0xABCDEF01
		AND		ECX,	EBX
		AND		DX,		0xBBBB
		AND		AX,		3
		AND		AH,		0x22
		AND		BL,		DH
	}

	__asm	// OR
	{
		OR		EBX,	ECX
		OR		EDX,	0x12345678
		OR		AX,		DX
		OR		CX,		0x3210
		OR		AH,		AL
		OR		AL,		0x11
		OR		BH,		2
	}

	__asm	// XOR
	{
		XOR		ECX,	EBX
		XOR		EDX,	0x11112222
		XOR		BX,		0x5678
		XOR		CX,		DX
		XOR		BH,		3
		XOR		AL,		0x88
	}

	__asm	// NOT
	{
		NOT		EDX
		NOT		CX
		NOT		AH
	}


	int a = 10;
	short b = 16;
	short c = 17;
	short d = 250;
	short e = 10;
	short f = 10;
	short g = 10;
	short h = a;

	__asm
	{
		MOV		a,	1000
		ADD		b,	1000
		SUB		c,	1000
		AND		d,	1000
		OR		e,	1000
		XOR		f,	1000
		NOT		g
	}

	std::cout << "MOV a:" << a << std::endl;
	std::cout << "ADD b:" << b << std::endl;
	std::cout << "SUB c:" << c << std::endl;
	std::cout << "AND d:" << d << std::endl;
	std::cout << "OR  e:" << e << std::endl;
	std::cout << "XOR f:" << f << std::endl;
	std::cout << "NOT g:" << g << std::endl;

	return 0;
}
