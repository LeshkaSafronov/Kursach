#include <iostream>
#include <fstream>
#include <malloc.h>
using namespace std;
int IP[64] = {57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7,56,48,40,32,24,16,8,0,58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6};
int E[48] = {31,0,1,2,3,4,3,4,5,6,7,8,7,8,9,10,11,12,11,12,13,14,15,16,15,16,17,18,19,20,19,20,21,22,23,24,23,24,25,26,27,28,27,28,29,30,31,0};
int G[56] = {56,48,40,32,24,16,8,0,57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,60,52,44,36,28,20,12,4,27,19,11,3};
int H[48] = {13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,3,25,7,15,6,26,19,12,1,40,51,30,36,46,54,29,39,50,44,32,47,43,48,38,55,33,52,45,41,49,35,28,31};
int shift_left[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int shift_right[16] = {0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int S[8][4][16] ={
        {
            {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
            {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
            {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
            {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
        },
        {
            {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
            {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
            {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
            {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
        },
        {
            {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
            {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
            {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
            {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
        },
        {
            {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
            {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
            {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
            {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
        },
        {
            {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
            {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
            {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
            {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
        },
        {
            {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
            {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
            {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
            {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
        },
        {
            {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
            {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
            {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
            {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
        },
        {
            {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
            {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
            {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
            {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
        }
    };
int P[32]= {15,6,19,20,28,11,27,16,0,14,22,25,4,17,30,9,1,7,23,13,31,26,2,8,18,12,29,5,21,10,3,24};
int _IP[64] = {39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25,32,0,40,8,48,16,56,24};
unsigned long long to_bit(char * data)
{
    unsigned long long res = 0;
    for (int i=0; i<8; i++)
        for (int j=7; j>=0; j--) res = (res << 1) ^ ((data[i] >> j) & 1);
    return res;
}
unsigned long long to_bit_key(char * data)
{
    unsigned long long res = 0;
    for (int i=0; i<7; i++)
        for (int j=7; j>=0; j--) res = (res << 1) ^ ((data[i] >> j) & 1);
    return res;
}
unsigned long long to_IP(unsigned long long value)
{
    unsigned long long res = 0;
    for (int i=0; i<64; i++) res = res ^ (((value >> IP[i]) & 1) << i);
    return res;
}
unsigned long long to_G(unsigned long long value)
{
    unsigned long long res = 0;
    for (int i=0; i<56; i++) res = res ^ (((value >> G[i]) & 1) << i);
    return res;
}
unsigned long long to_H(unsigned long long value)
{
    unsigned long long res = 0;
    for (int i=0; i<48; i++) res = res ^ (((value >> H[i]) & 1) << i);
    return res;
}
unsigned long long to_E(unsigned long long value)
{
    unsigned long long res = 0;
    for (int i=0; i<48; i++) res = res ^ (((value >> E[i]) & 1) << i);
    return res;
}
unsigned long long to_P(unsigned long long value)
{
    unsigned long long res = 0;
    for (int i=0; i<32; i++) res = res ^ (((value >> P[i]) & 1) << i);
    return res;
}
unsigned long long to__IP(unsigned long long value)
{
    unsigned long long res = 0;
    for (int i=0; i<64; i++) res = res ^ (((value >> _IP[i]) & 1) << i);
    return res;
}
unsigned long long f(unsigned long long R, unsigned long long key)
{
    unsigned long long b[8]={0}, new_R = 0;
    int cnt = 0;
    R = to_E(R);
    R^=key;
    while (R!=0) {
        b[cnt++]=R & ((1 << 6)-1);
        R >>= 6;
    }
    for (int i=7; i>=0; i--) {
        unsigned long long cur_block=S[7-i][((b[i] >> 5) << 1)^(b[i] & 1)][(b[i] >> 1) & ((1 << 4)-1)];
        new_R=(new_R << 4) ^ cur_block;
    }
    return to_P(new_R);
}
unsigned long long encode(unsigned long long value, unsigned long long key)
{
    value = to_IP(value);
    unsigned long long L = value >> 32, R = value & (((unsigned long long)1 << 32) -1);
    key = to_G(key);
    unsigned long long C = key >> 28, D = key & (((unsigned long long)1 << 28) -1);
    for (int i=0; i<16; i++) {
        C <<= shift_left[i];
        D <<= shift_left[i];
        key = to_H((C << 32)^D);
        unsigned long long new_L = R;
        unsigned long long new_R = L ^ f(R,key);
        L = new_L;
        R = new_R;
    }
    return to__IP((L << 32)^R);
}
unsigned long long decode(unsigned long long value, unsigned long long key)
{
    value = to_IP(value);
    unsigned long long L = value >> 32, R = value & (((unsigned long long)1 << 32) -1);
    key = to_G(key);
    unsigned long long C = key >> 28, D = key & (((unsigned long long)1 << 28) -1);
    for (int i=0; i<16; i++) {
        C <<= shift_left[i];
        D <<= shift_left[i];
    }
    for (int i=0; i<16; i++) {
        C >>= shift_right[i];
        D >>= shift_right[i];
        key = to_H((C << 32)^D);
        unsigned long long new_L = R ^ f(L,key);
        unsigned long long new_R = L;
        L = new_L;
        R = new_R;
    }
    return to__IP((L << 32)^R);
}

unsigned long long control_key(unsigned long long k)
{
    unsigned long long res = 0;
    int sum = 0, cnt = 0, cur_bit = 0;
    for (int i=0; i<56; i++) {
        cnt++;
        sum+=(k >> i) & 1;
        res = (((k >> i) & 1) << cur_bit) ^ res;
        cur_bit++;
        if (cnt % 7 == 0) {
            res = ((unsigned long long)((sum % 2 == 0 ? 1 : 0) & 1) << cur_bit) ^ res;
            cur_bit++;
            sum = 0;
        }
    }
    return res;
}
int main(int argc, char *argv[])
{
    string op = argv[1];
    if (argc != 7) {
        printf("Wrong count of argument\n");
        return -2;
    }
    if (op != "/E" && op!="/e" && op!="/D" && op!= "/d") {
        printf("Wrong argument\n");
        return -2;
    }
    unsigned long long key1 = control_key(to_bit_key(argv[4]));
    unsigned long long key2 = control_key(to_bit_key(argv[5]));
    unsigned long long key3 = control_key(to_bit_key(argv[6]));
    ifstream input (argv[2], std::ifstream::binary);
    if (!input.is_open()) {
        printf("Error opening file\n");
        return -2;
    }
    input.seekg(0,input.end);
    int input_length=input.tellg();
    if (input_length%8!=0) input_length=(input_length/8)*8+8;
    input.seekg(0,input.beg);

    ofstream output (argv[3], std::ofstream::binary);
    int cnt_of_byte=0;
    while (!input.eof()) {
        char * data = (char *) calloc(8,sizeof(char));
        if (data == NULL) {
            printf("Error\n");
            return -1;
        }
        input.read(data,8);
        unsigned long long out;
        if (op == "/E" || op == "/e") out = encode(encode(encode(to_bit(data), key1),key2),key3);
        if (op == "/D" || op == "/d") out = decode(decode(decode(to_bit(data), key3),key2),key1);
        for (int i=7; i>=0; i--) {
            char * buf = new char;
            * buf = (out >> (i*8)) & ((1 << 8)-1);
            output.write(buf,1);
        }
        cnt_of_byte+=8;
        printf("%d bytes complete (%1.f%% complete)\r",cnt_of_byte,cnt_of_byte/(float)input_length*100);
        if (input.eof()) break;
     }
}
