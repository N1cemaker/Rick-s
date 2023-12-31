#include <stdio.h>

 //Define the round constant table
static const unsigned char RoundCon[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36 };




//Substitution Tables
static const unsigned char sbox[256] = {
	0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,
	0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
	0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,
	0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
	0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,
	0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
	0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,
	0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
	0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,
	0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
	0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,
	0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
	0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,
	0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
	0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,
	0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
	0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,
	0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
	0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,
	0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
	0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,
	0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
	0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,
	0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
	0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,
	0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
	0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,
	0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
	0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,
	0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
	0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,
	0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16,
};
//inverse Substitution Tables
static const unsigned char contrary_sbox[256] = {
	0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,
	0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
	0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,
	0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
	0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,
	0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
	0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,
	0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
	0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,
	0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
	0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,
	0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
	0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,
	0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
	0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,
	0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
	0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,
	0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
	0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,
	0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
	0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,
	0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
	0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,
	0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
	0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,
	0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
	0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,
	0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
	0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,
	0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
	0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,
	0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d,
};





//x2time
static unsigned char x2time(unsigned char x)
{
	if (x & 0x80)
	{
		return (((x << 1) ^ 0x1B) & 0xFF);
	}
	return x << 1;
}
//x3time
static unsigned char x3time(unsigned char x)
{
	return (x2time(x) ^ x);
}
//x4time
static unsigned char x4time(unsigned char x)
{
	return (x2time(x2time(x)));
}
//x5time
static unsigned char x5time(unsigned char x)
{
	return (x4time(x) ^ x);
}
//x6time
static unsigned char x6time(unsigned char x)
{
	return (x5time(x) ^ x);
}
//x7time
static unsigned char x7time(unsigned char x)
{
	return (x6time(x) ^ x);
}
//x8time
static unsigned char x8time(unsigned char x)
{
	return (x2time(x2time(x2time(x))));
}
//x9time
static unsigned char x9time(unsigned char x)
{
	return (x8time(x) ^ x);
}
//x10time
static unsigned char x10time(unsigned char x)
{
	return (x9time(x) ^ x);
}
//x11time
static unsigned char x11time(unsigned char x)
{
	return (x8time(x) ^ x2time(x) ^ x);
}
//x12time
static unsigned char x12time(unsigned char x)
{
	return (x11time(x) ^ x);
}
//x13time
static unsigned char x13time(unsigned char x)
{
	return (x8time(x) ^ x4time(x) ^ x);
}
//x14time 
static unsigned char x14time(unsigned char x)
{
	return (x8time(x) ^ x4time(x) ^ x2time(x));
}
//x15time
static unsigned char x15time(unsigned char x)
{
	return (x14time(x) ^ x);
}






//Byte substitution
static void SubBytes(unsigned char* C)
{
	int x;
	for (x = 0; x < 16; x++)
	{
		C[x] = sbox[C[x]];
	}
}
//inverse Byte substitution
static void Contrary_SubBytes(unsigned char* C)
{
	int x;
	for (x = 0; x < 16; x++)
	{
		C[x] = contrary_sbox[C[x]];
	}
}





//MixColumns
static void MixColumns(unsigned char* C)
{
	unsigned char tmp[4], xt[4];
	int i;
	for (i = 0; i < 4; i++, C += 4)
	{ 
		tmp[0] = x2time(C[0]) ^ x3time(C[1]) ^ C[2] ^ C[3];	
		tmp[1] = C[0] ^ x2time(C[1]) ^ x3time(C[2]) ^ C[3];	
		tmp[2] = C[0] ^ C[1] ^ x2time(C[2]) ^ x3time(C[3]);	
		tmp[3] = x3time(C[0]) ^ C[1] ^ C[2] ^ x2time(C[3]);	
		C[0] = tmp[0];
		C[1] = tmp[1];
		C[2] = tmp[2];
		C[3] = tmp[3];
	}
}
//inverse MixColumns
static void Contrary_MixColumns(unsigned char* C)
{
	unsigned char tmp[4];
	unsigned char xt2[4];
	unsigned char xt4[4];
	unsigned char xt8[4];
	int x;
	for (x = 0; x < 4; x++, C += 4)
	{
		tmp[0] = x14time(C[0]) ^ x11time(C[1]) ^ x13time(C[2]) ^ x9time(C[3]);
		tmp[1] = x9time(C[0]) ^ x14time(C[1]) ^ x11time(C[2]) ^ x13time(C[3]);
		tmp[2] = x13time(C[0]) ^ x9time(C[1]) ^ x14time(C[2]) ^ x11time(C[3]);
		tmp[3] = x11time(C[0]) ^ x13time(C[1]) ^ x9time(C[2]) ^ x14time(C[3]);
		C[0] = tmp[0];
		C[1] = tmp[1];
		C[2] = tmp[2];
		C[3] = tmp[3];
	}
}



//ShiftRows
static void ShiftRows(unsigned char* C)
{//Forward row shift
	unsigned char t;
	//Shift one bit to the left
	t = C[1]; C[1] = C[5]; C[5] = C[9]; C[9] = C[13]; C[13] = t;
	//Shift two bit to the left
	t = C[2]; C[2] = C[10]; C[10] = t;
	t = C[6]; C[6] = C[14]; C[14] = t;
	//Shift three bit to the left which is same as Shift one bit to the right
	t = C[15]; C[15] = C[11]; C[11] = C[7]; C[7] = C[3]; C[3] = t;
}
//Reverse row shift
static void Contrary_ShiftRows(unsigned char* C)
{
	unsigned char t;
	t = C[13]; C[13] = C[9]; C[9] = C[5]; C[5] = C[1]; C[1] = t;
	t = C[2]; C[2] = C[10]; C[10] = t;
	t = C[6]; C[6] = C[14]; C[14] = t;
	t = C[3]; C[3] = C[7]; C[7] = C[11]; C[11] = C[15]; C[15] = t;
}





//Key schedule
void ScheduleKey(unsigned char* inputkey, unsigned char* outputkey, int Col, int Round)
{
	unsigned char temp[4], t;
	int x, i;
	for (i = 0; i < (4 * Col); i++)
	{
		outputkey[i] = inputkey[i];
	}
	i = Col;
	while (i < (4 * (Round + 1))) 
	{
		for (x = 0; x < 4; x++)
			temp[x] = outputkey[(4 * (i - 1)) + x];
		if (i % Col == 0)
		{
			t = temp[0]; temp[0] = temp[1]; temp[1] = temp[2]; temp[2] = temp[3]; temp[3] = t;
			for (x = 0; x < 4; x++)
			{
				temp[x] = sbox[temp[x]];
			}
			temp[0] ^= RoundCon[(i / Col) - 1];
		}
		for (x = 0; x < 4; x++)
		{
			outputkey[(4 * i) + x] = outputkey[(4 * (i - Col)) + x] ^ temp[x];
		}
		++i;
	}
}



//Addroundkey
static void AddRoundKey(unsigned char* C, unsigned char* ex_key, int round)
{
	
	int x;
	for (x = 0; x < 16; x++)
	{	
		C[x] ^= ex_key[(round << 4) + x];
	}
}



//AES encrypt
void AesEncrypt(unsigned char* text, unsigned char* ex_key, int Round)
{	int round;

	AddRoundKey(text, ex_key, 0);
	//round1-9
	for (round = 1; round <= (Round - 1); round++)
	{
		SubBytes(text);		
		ShiftRows(text);		
		MixColumns(text);	
		AddRoundKey(text, ex_key, round);
	}
	//round10
	SubBytes(text);
	ShiftRows(text);
	AddRoundKey(text, ex_key, Round);
}
//AES decrypt
void Contrary_AesEncrypt(unsigned char* text, unsigned char* ex_key, int Round)
{
	int x;
	AddRoundKey(text, ex_key, Round);
	Contrary_ShiftRows(text);
	Contrary_SubBytes(text);
	for (x = (Round - 1); x >= 1; x--)
	{
		AddRoundKey(text, ex_key, x);
		Contrary_MixColumns(text);
		Contrary_ShiftRows(text);
		Contrary_SubBytes(text);
	}
	AddRoundKey(text, ex_key, 0);
}



int main(void) {
	unsigned char plaintext[17], key[17];
	unsigned char ex_key[15 * 16];
	int i;
	int j;
	printf("Welcome to use the AES machine\n");
	printf("Please enter plaintext (length = 16):\n");
	scanf("%s", plaintext);
	printf("please input key��\n");
	scanf("%s", key);

	//Encrypt
	ScheduleKey(key, ex_key, 4, 10);
	AesEncrypt(plaintext, ex_key, 10);//encrypt
	printf("The ciphertext is: ");	
	for (i = 0; i < 16; i++)
	{
		printf("%02x ", plaintext[i]);
	}
	printf("\n");
	printf("\n");
	//Decrypt
	Contrary_AesEncrypt(plaintext, ex_key, 10);//decrypt
	printf("The decrypted plaintext is: ");
	for (i = 0; i < 16; i++)
	{
		printf("%c ", plaintext[i]);
	}
	printf("\n");
	printf("\n");
	while (1);
	return 0;
}
