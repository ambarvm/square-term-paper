#include<vector>
#include<iostream>
#include<bits/stdc++.h>
#include<cstdlib>

#define rounds 4
#define ROOT 0x1f5U /* Generator of GF(2^8), maintains GF(2^8) */

using namespace std;

// Word lengths:
// sizeof(char) = 8 bits
// sizeof(short) = 16 bits
// sizeof(int) = 32 bits
// sizeof(long) = 64 bits

typedef unsigned char bit8;     // 8 bit word
typedef unsigned short bit16;   // 16 bit word
typedef unsigned int bit32;     // 32 bit word

// sbox for block cipher square
vector<bit16> sbox =
{0xb1, 0xce ,0xc3 ,0x95 ,0x5a ,0xad ,0xe7 ,0x02 ,0x4d ,0x44 ,0xfb ,0x91 ,0x0c ,0x87 ,0xa1 ,0x50,
 0xcb, 0x67 ,0x54 ,0xdd ,0x46 ,0x8f ,0xe1 ,0x4e ,0xf0 ,0xfd ,0xfc ,0xeb ,0xf9 ,0xc4 ,0x1a ,0x6e,
 0x5e, 0xf5 ,0xcc ,0x8d ,0x1c ,0x56 ,0x43 ,0xfe ,0x07 ,0x61 ,0xf8 ,0x75 ,0x59 ,0xff ,0x03 ,0x22,
 0x8a, 0xd1 ,0x13 ,0xee ,0x88 ,0x00 ,0x0e ,0x34 ,0x15 ,0x80 ,0x94 ,0xe3 ,0xed ,0xb5 ,0x53 ,0x23,
 0x4b, 0x47 ,0x17 ,0xa7 ,0x90 ,0x35 ,0xab ,0xd8 ,0xb8 ,0xdf ,0x4f ,0x57 ,0x9a ,0x92 ,0xdb ,0x1b,
 0x3c, 0xc8 ,0x99 ,0x04 ,0x8e ,0xe0 ,0xd7 ,0x7d ,0x85 ,0xbb ,0x40 ,0x2c ,0x3a ,0x45 ,0xf1 ,0x42,
 0x65, 0x20 ,0x41 ,0x18 ,0x72 ,0x25 ,0x93 ,0x70 ,0x36 ,0x05 ,0xf2 ,0x0b ,0xa3 ,0x79 ,0xec ,0x08,
 0x27, 0x31 ,0x32 ,0xb6 ,0x7c ,0xb0 ,0x0a ,0x73 ,0x5b ,0x7b ,0xb7 ,0x81 ,0xd2 ,0x0d ,0x6a ,0x26,
 0x9e, 0x58 ,0x9c ,0x83 ,0x74 ,0xb3 ,0xac ,0x30 ,0x7a ,0x69 ,0x77 ,0x0f ,0xae ,0x21 ,0xde ,0xd0,
 0x2e, 0x97 ,0x10 ,0xa4 ,0x98 ,0xa8 ,0xd4 ,0x68 ,0x2d ,0x62 ,0x29 ,0x6d ,0x16 ,0x49 ,0x76 ,0xc7,
 0xe8, 0xc1 ,0x96 ,0x37 ,0xe5 ,0xca ,0xf4 ,0xe9 ,0x63 ,0x12 ,0xc2 ,0xa6 ,0x14 ,0xbc ,0xd3 ,0x28,
 0xaf, 0x2f ,0xe6 ,0x24 ,0x52 ,0xc6 ,0xa0 ,0x09 ,0xbd ,0x8c ,0xcf ,0x5d ,0x11 ,0x5f ,0x01 ,0xc5,
 0x9f, 0x3d ,0xa2 ,0x9b ,0xc9 ,0x3b ,0xbe ,0x51 ,0x19 ,0x1f ,0x3f ,0x5c ,0xb2 ,0xef ,0x4a ,0xcd,
 0xbf, 0xba ,0x6f ,0x64 ,0xd9 ,0xf3 ,0x3e ,0xb4 ,0xaa ,0xdc ,0xd5 ,0x06 ,0xc0 ,0x7e ,0xf6 ,0x66,
 0x6c, 0x84 ,0x71 ,0x38 ,0xb9 ,0x1d ,0x7f ,0x9d ,0x48 ,0x8b ,0x2a ,0xda ,0xa5 ,0x33 ,0x82 ,0x39,
 0xd6, 0x78 ,0x86 ,0xfa ,0xe4 ,0x2b ,0xa9 ,0x1e ,0x89 ,0x60 ,0x6b ,0xea ,0x55 ,0x4c ,0xf7 ,0xe2};

vector<bit16> sbox_inverse = 
{
 53, 190,   7,  46,  83, 105, 219,  40, 111, 183, 118, 107,  12, 125,  54, 139, 
146, 188, 169,  50, 172,  56, 156,  66,  99, 200,  30,  79,  36, 229, 247, 201, 
 97, 141,  47,  63, 179, 101, 127, 112, 175, 154, 234, 245,  91, 152, 144, 177, 
135, 113, 114, 237,  55,  69, 104, 163, 227, 239,  92, 197,  80, 193, 214, 202, 
 90,  98,  95,  38,   9,  93,  20,  65, 232, 157, 206,  64, 253,   8,  23,  74, 
 15, 199, 180,  62,  18, 252,  37,  75, 129,  44,   4, 120, 203, 187,  32, 189, 
249,  41, 153, 168, 211,  96, 223,  17, 151, 137, 126, 250, 224, 155,  31, 210, 
103, 226, 100, 119, 132,  43, 158, 138, 241, 109, 136, 121, 116,  87, 221, 230, 
 57, 123, 238, 131, 225,  88, 242,  13,  52, 248,  48, 233, 185,  35,  84,  21, 
 68,  11,  77, 102,  58,   3, 162, 145, 148,  82,  76, 195, 130, 231, 128, 192, 
182,  14, 194, 108, 147, 236, 171,  67, 149, 246, 216,  70, 134,   5, 140, 176, 
117,   0, 204, 133, 215,  61, 115, 122,  72, 228, 209,  89, 173, 184, 198, 208, 
220, 161, 170,   2,  29, 191, 181, 159,  81, 196, 165,  16,  34, 207,   1, 186, 
143,  49, 124, 174, 150, 218, 240,  86,  71, 212, 235,  78, 217,  19, 142,  73, 
 85,  22, 255,  59, 244, 164, 178,   6, 160, 167, 251,  27, 110,  60,  51, 205, 
 24,  94, 106, 213, 166,  33, 222, 254,  42,  28, 243,  10,  26,  25,  39,  45, 
};

void gamma(bit16 *matrix)
{
    // gamma function substitutes bytes using sbox
    int i;
    for(i = 0; i < 16; i++)
        matrix[i] = sbox[matrix[i]];
}


void gamma_inverse(bit16 *matrix)
{
    // gamma function substitutes bytes using sbox
    int i;
    for(i = 0; i < 16; i++)
        matrix[i] = sbox_inverse[matrix[i]];
}


void pi(bit16 *matrix)
{
    // pi function is simple transpose
    bit16 temp;
    temp = matrix[1]; matrix[1] = matrix[4]; matrix[4] = temp;
    temp = matrix[2]; matrix[2] = matrix[8]; matrix[8] = temp;
    temp = matrix[6]; matrix[6] = matrix[9]; matrix[9] = temp;
    temp = matrix[3]; matrix[3] = matrix[0xC]; matrix[0xC] = temp;
    temp = matrix[7]; matrix[7] = matrix[0xD]; matrix[0xD] = temp;
    temp = matrix[0xB]; matrix[0xB] = matrix[0xE]; matrix[0xE] = temp;
}


void sigma(bit16 *matrix, bit16 *round_key)
{
    // sigma xors key with a matrix
    int i;
    for(i = 0; i < 16; i++)
        matrix[i] ^= round_key[i] ;
}


bit16 times2(bit16 n)
{
    // Used for multiplication with 2 in Galois Field
    n = n << 1;
    if ((n&0x100) != 0)
        n ^= ROOT;
    return n;
}


void key_schedule(bit16 *round_key, bit16 *r)
{
    // 
    bit16 temp;
    temp = round_key[0xC];
    round_key[0] ^= *r;
    round_key[0] ^= round_key[0xD]; round_key[4] ^= round_key[0]; round_key[8] ^= round_key[4]; round_key[0xC] ^= round_key[8];
    round_key[1] ^= round_key[0xE]; round_key[5] ^= round_key[1]; round_key[9] ^= round_key[5]; round_key[0xD] ^= round_key[9];
    round_key[2] ^= round_key[0xF]; round_key[6] ^= round_key[2]; round_key[0xA] ^= round_key[6]; round_key[0xE] ^= round_key[0xA];
    round_key[3] ^= temp; round_key[7] ^= round_key[3]; round_key[0xB] ^= round_key[7]; round_key[0xF] ^= round_key[0xB];
    *r = times2(*r);
}


void theta(bit16 *matrix)
{
    // This is similar to mix columns in AES just done in rows
    // A simple multiplication with a matrix C.
    // C = {{2, 3, 1, 1},
    //      {1, 2, 3, 1},
    //      {1, 1, 2, 3},
    //      {3, 1, 1, 2}};
    int i, j;
    bit16 temp[16];
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            temp[4*i+j]  = times2(matrix[4*i+j]);
            temp[4*i+j] ^=        matrix[4*i+((j+1)%4)];
            temp[4*i+j] ^= times2(matrix[4*i+((j+1)%4)]);
            temp[4*i+j] ^=        matrix[4*i+((j+2)%4)];
            temp[4*i+j] ^=        matrix[4*i+((j+3)%4)];
        }
    }
    for(j = 0; j < 16; j++)
        matrix[j] = temp[j];
}


bool isBalanced(vector<bit16*> set, int j, int k)
{
	int i;
	int x = 0;
	for(i = 0; i < 256; i++)
		x ^= set[i][j*4+k];
	if(x == 0)
		return true;
	else
		return false;

}


bool isConstant(vector<bit16*> set, int j, int k)
{
	int i;
	for(i = 0; i < 256; i++)
		if(set[0][j*4+k] != set[i][j*4+k])
			return false;
	return true;
}


bool isAll(vector<bit16*> set, int j, int k)
{
	vector<int> lane{};
	int i;
	auto f = find(lane.begin(), lane.end(), set[0][0]);
	for(i = 0; i < 256; i++)
		lane.push_back(set[i][j*4+k]);

	for(i = 0; i < 256; i++)
	{
		f = find(lane.begin(), lane.end(), i);
		if(f != end(lane))
			lane.erase(f);
	}

	if(lane.size() == 0)
		return true;
	return false;
}


vector<vector<int>> get_all_indices(vector<bit16*> set)
{
	vector<int> lane{};
	int i, j, k;
	vector<vector<int>> indices;
	for(j = 0; j < 4; j++)
	{
		for(k = 0; k < 4; k++)
		{
			if(isAll(set, j, k))
				indices.push_back(vector<int>{j, k});
			lane.clear();
		}
	}
	return indices;
}


vector<vector<int>> get_constant_indices(vector<bit16*> set)
{
	int i, j, k;
	vector<vector<int>> indices;
	for(j = 0; j < 4; j++)
	{
		for(k = 0; k < 4; k++)
		{
			if(isConstant(set, j, k))
				indices.push_back(vector<int>{j, k});
		}
	}
	return indices;
}


vector<vector<int>> get_balanced_indices(vector<bit16*> set)
{
	int i, j, k;
	int x = 0;
	vector<vector<int>> indices;
	for(j = 0; j < 4; j++)
	{
		for(k = 0; k < 4; k++)
		{
			if(isBalanced(set, j, k))
				indices.push_back(vector<int>{j, k});
		}
	}
	return indices;
}


void print(vector<vector<char>> v)
{
	cout << "-----------------\n";
	cout << "| " << v[0][0] << " | " <<  v[0][1] << " | " << v[0][2] << " | " << v[0][3] << " |\n";
	cout << "-----------------\n";
	cout << "| " << v[1][0] << " | " <<  v[1][1] << " | " << v[1][2] << " | " << v[1][3] << " |\n";
	cout << "-----------------\n";
	cout << "| " << v[2][0] << " | " <<  v[2][1] << " | " << v[2][2] << " | " << v[2][3] << " |\n";
	cout << "-----------------\n";
	cout << "| " << v[3][0] << " | " <<  v[3][1] << " | " << v[3][2] << " | " << v[3][3] << " |\n";
	cout << "-----------------\n";
}


void check_all_and_balanced(vector<bit16*> p)
{
	int i;
	vector<vector<char>> v(4, vector<char>(4, 'U'));
	vector<vector<int>> all_indices = get_all_indices(p);
	for(i = 0; i < all_indices.size(); i++)
		v[all_indices[i][0]][all_indices[i][1]] = 'A';

	vector<vector<int>> constant_indices = get_constant_indices(p);
	for(i = 0; i < constant_indices.size(); i++)
		v[constant_indices[i][0]][constant_indices[i][1]] = 'C';
	cout << "\nAll and Constant property:\n";
	print(v);
	

	// cout << "Indices that follow \"Balanced\" property:\n";
	vector<vector<int>> balanced_indices = get_balanced_indices(p);
	for(i = 0; i < balanced_indices.size(); i++)
		v[balanced_indices[i][0]][balanced_indices[i][1]] = 'B';
	cout << "\nBalanced property:\n";
	print(v);

}


void visualise_and_attack(bit16 *key)
{
   bit16 i, j, a, b, k, r, round_key[16];
   a = 0;
   b = 0;
   vector<bit16*> p;
   vector<bit16*> q;
   for(i = 0; i < 256; i++)
      p.push_back((bit16*)malloc(16*sizeof(bit16)));
   for(i = 0; i < 256; i++)
      q.push_back((bit16*)malloc(16*sizeof(bit16)));
   srand(time(0));
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			r = rand();
			for(k = 0; k < 256; k++)
				p[k][i*4+j] = r % 256;
		}
	}

	for(i = 0; i < 256; i++)
		p[i][a*4+b] = i;

   r = 1;
   for(i = 0; i < 16; i++)
      round_key[i] = key[i];
   



   cout << "\n\n######################## Round 1 ########################\n";
   theta(round_key);   /*  sigma(theta(round_key of first round)) */
   for(i = 0; i < 256; i++)
      sigma(p[i],round_key);
   cout << "\n############ After Theta ############\n";
   check_all_and_balanced(p);


   for(i = 0; i < 16; i++)
      round_key[i] = key[i];


   for(i = 0; i < 256; i++)
      gamma(p[i]);
   cout << "\n############ After Gamma ############\n";
   check_all_and_balanced(p);


   for(i = 0; i < 256; i++)
      pi(p[i]);
   cout << "\n############ After Pi ############\n";
   check_all_and_balanced(p);


   key_schedule(round_key,&r); 
   

   for(i = 0; i < 256; i++)
      sigma(p[i],round_key);
   cout << "\n############ After Sigma ############\n";
   check_all_and_balanced(p);


   for(i = 2; i <= rounds; i++)
   {
      cout << "\n\n######################## Round " << i << " ########################\n";
      for(j = 0; j < 256; j++)
         theta(p[j]);
      cout << "\n############ After Theta ############\n";
      check_all_and_balanced(p);


      for(j = 0; j < 256; j++)
         gamma(p[j]);
      cout << "\n############ After Gamma ############\n";
      check_all_and_balanced(p);


      for(j = 0; j < 256; j++)
         pi(p[j]);
      cout << "\n############ After Pi ############\n";
      check_all_and_balanced(p);


      key_schedule(round_key, &r);


      for(j = 0; j < 256; j++)
         sigma(p[j], round_key);
      cout << "\n############ After Sigma ############\n";
      check_all_and_balanced(p);
   }
   cout << "\n############ Last round key for reference ############\n";
   for(i = 0; i < 16; i++)
      cout << round_key[i] << " ";
   cout << "\n";
   // cout << "\n################### Attacking row: " << row << " and column: " << col << " ###################\n";
   vector<vector<bit16>> attacked_key(4, vector<bit16>(4, 0));
   for(bit8 row = 0; row < 4; row++)
   {
      for(bit8 col = 0; col < 4; col++)
      {
         // bit8 row = 2;
         // bit8 col = 0;
         for(k = 0; k < 256; k++)
         {
            bit16 guess[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            guess[col*4+row] = k;
            // Copy p to q
            for(i = 0; i < 256; i++)
               for(j = 0; j < 16; j++)
                  q[i][j] = p[i][j];
            
            for(j = 0; j < 256; j++)
               sigma(q[j], guess);
            for(j = 0; j < 256; j++)
               pi(q[j]);
            for(j = 0; j < 256; j++)
               gamma_inverse(q[j]);
            if(isBalanced(q, row, col))
            {
               attacked_key[row][col] = k;
               break;
            }
         }
      }
   }
   cout << "\n############### Key found after attack ###############\n";
   for(i = 0; i < 4; i++)
   {
      for(j = 0; j < 4; j++)
         cout << attacked_key[i][j] << " ";
      cout << "\n";
   }
   // check_all_and_balanced(q);
}


int main()
{
   bit16 key[] = {1, 2, 3, 4,
               5, 6, 7, 8,
               9, 10, 11, 12,
               13, 14, 15, 16};
   visualise_and_attack(key);
}