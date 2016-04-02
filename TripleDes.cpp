#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
using namespace std;
int cur, cnt;
char data[8], _key1[8], _key2[8], _key3[8];
ifstream input;
ofstream output;
int IP[4][16] = {
            {57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3},
            {61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7},
            {56,48,40,32,24,16,8,0,58,50,42,34,26,18,10,2},
            {60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6}
        };
int E[8][6] = {
            {31,0,1,2,3,4},
            {3,4,5,6,7,8},
            {7,8,9,10,11,12},
            {11,12,13,14,15,16},
            {15,16,17,18,19,20},
            {19,20,21,22,23,24},
            {23,24,25,26,27,28},
            {27,28,29,30,31,0}
        };
int G[4][14] = {
            {56,48,40,32,24,16,8,0,57,49,41,33,25,17},
            {9,1,58,50,42,34,26,18,10,2,59,51,43,35},
            {62,54,46,38,30,22,14,6,61,53,45,37,29,21},
            {13,5,60,52,44,36,28,20,12,4,27,19,11,3}
        };
int SHIFT_LEFT[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int SHIFT_RIGHT[16] = {0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int H[3][16] = {
            {13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,3},
            {25,7,15,6,26,19,12,1,40,51,30,36,46,54,29,39},
            {50,44,32,47,43,48,38,55,33,52,45,41,49,35,28,31}
    };
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
int P[8][4]= {
        {15,6,19,20},
        {28,11,27,16},
        {0,14,22,25},
        {4,17,30,9},
        {1,7,23,13},
        {31,26,2,8},
        {18,12,29,5},
        {21,10,3,24}
    };
int _IP[4][16] = {
        {39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30},
        {37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28},
        {35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26},
        {33,1,41,9,49,17,57,25,32,0,40,8,48,16,56,24}
    };
unsigned long long get_bits(char data[])
{
    unsigned long long res=0;
    for (int i=0; i<8; i++) {
        for (int j=7; j>=0; j--) res=(res << 1) ^ ((data[i] >> j) & 1);
        data[i]=0;
    }
    return res;
}
void get_chars(unsigned long long out)
{
    char output_data[8]={0};
    int cnt=0;
    for (int i=56; i>=0; i-=8) output_data[cnt++]=(out >> i) & ((1 << 8)-1);
    for (int i=0; i<8; i++) output.write(&output_data[i],1);
}

bool check_IP(unsigned long long x, unsigned long long _x)
{
    for (int i=0; i<4; i++)
        for (int j=0; j<16; j++) {
            int id2=i*16+j;
            if (((x >> IP[i][j]) & 1) != ((_x >> id2) & 1)) return false;
        }
    return true;
}
void transform_IP(unsigned long long &x)
{
    unsigned long long _x=0;
    for (int i=0; i<4; i++)
        for (int j=0; j<16; j++) {
            int id1=IP[i][j], id2=i*16+j, w=(x >> id1) & 1;
            _x=((((_x >> (id2+1)) << 1)^w) << id2) ^ (_x & (((unsigned long long)1 << id2)-1));
        }
    x=_x;
}
void transform_E(unsigned long long &x)
{
    unsigned long long _x=0;
    for (int i=0; i<8; i++)
        for (int j=0; j<6; j++) {
            int id1=E[i][j], id2=i*6+j, w=(x >> id1) & 1;
            _x=((((_x >> (id2+1)) << 1)^w) << id2) ^ (_x & (((unsigned long long)1 << id2)-1));
        }
    x=_x;
}
void transform_G(unsigned long long &x)
{
    unsigned long long _x=0;
    for (int i=0; i<4; i++)
        for (int j=0; j<14; j++) {
            int id1=G[i][j], id2=i*14+j, w=(x >> id1) & 1;
            _x=((((_x >> (id2+1)) << 1)^w) << id2) ^ (_x & (((unsigned long long)1 << id2)-1));
        }
    x=_x;
}
void transform_H(unsigned long long &x)
{
    unsigned long long _x=0;
    for (int i=0; i<3; i++)
        for (int j=0; j<16; j++) {
            int id1=H[i][j], id2=i*16+j, w=(x >> id1) & 1;
            _x=((((_x >> (id2+1)) << 1)^w) << id2) ^ (_x & (((unsigned long long)1 << id2)-1));
        }
    x=_x;
}
void transform_P(unsigned long long &x)
{
    unsigned long long _x=0;
    for (int i=0; i<8; i++)
        for (int j=0; j<4; j++) {
            int id1=P[i][j], id2=i*4+j, w=(x >> id1) & 1;
            _x=((((_x >> (id2+1)) << 1)^w) << id2) ^ (_x & (((unsigned long long)1 << id2)-1));
        }
    x=_x;
}
void transform__IP(unsigned long long &x)
{
    unsigned long long _x=0;
    for (int i=0; i<4; i++)
        for (int j=0; j<16; j++) {
            int id1=_IP[i][j], id2=i*16+j, w=(x >> id1) & 1;
            _x=((((_x >> (id2+1)) << 1)^w) << id2) ^ (_x & (((unsigned long long)1 << id2)-1));
        }
    x=_x;
}
void print_bin(unsigned long long x)
{
    for (int i=63; i>=0; i--) printf("%d",(x >> i) & 1);
    printf("\n");
}

unsigned long long f(unsigned long long R, unsigned long long key)
{
    unsigned long long b[8]={0}, new_R=0;
    transform_E(R);
    int cnt=0;
    R^=key;
    while (R!=0) {
        b[cnt++]=R & ((1 << 6)-1);
        R >>= 6;
    }
    for (int i=7; i>=0; i--) {
        unsigned long long cur_block=S[7-i][((b[i] >> 5) << 1)^(b[i] & 1)][(b[i] >> 1) & ((1 << 4)-1)];
        new_R=(new_R << 4) ^ cur_block;
    }
    transform_P(new_R);
}
unsigned long long get_next_key(unsigned long long &C, unsigned long long &D, int it)
{
    C <<= SHIFT_LEFT[it];
    D <<= SHIFT_LEFT[it];
    unsigned long long K=(C << 32)^D;
    transform_H(K);
    return K;
}
unsigned long long get_previous_key(unsigned long long &C, unsigned long long &D, int it)
{
    C >>= SHIFT_RIGHT[it];
    D >>= SHIFT_RIGHT[it];
    unsigned long long K=(C << 32)^D;
    transform_H(K);
    return K;
}
void prepare_key(unsigned long long key, unsigned long long &C, unsigned long long &D)
{
    C=key >> 28;
    D=key & ((1 << 28)-1);
}
unsigned long long encryption_des(unsigned long long x, unsigned long long key)
{
    unsigned long long C,D;
    transform_IP(x);
    transform_G(key);
    prepare_key(key,C,D);
    unsigned long long L=x >> 32, R=x & (((unsigned long long)1 << 32)-1), res=0;
    for (int i=0; i<16; i++) {
        key=get_next_key(C,D,i);
        unsigned long long cur_L=R;
        unsigned long long cur_R=L^f(R,key);
        L=cur_L;
        R=cur_R;
    }
    res=(L << 32)^R;
    transform__IP(res);
    return res;
}
unsigned long long decryption_des(unsigned long long x, unsigned long long key)
{
    unsigned long long C , D;
    transform_IP(x);
    transform_G(key);
    prepare_key(key,C,D);
    for (int i=0; i<16; i++) key=get_next_key(C,D,i);
    unsigned long long L=x >> 32, R=x & (((unsigned long long)1 << 32)-1), res=0;
    for (int i=0; i<16; i++) {
        key=get_previous_key(C,D,i);
        unsigned long long cur_L=R^f(L,key);
        unsigned long long cur_R=L;
        L=cur_L;
        R=cur_R;
    }
    res=(L << 32)^R;
    transform__IP(res);
    return res;
}
void control_key(unsigned long long &key)
{
    unsigned long long blocks[8]={0}, cntr_key=0, cnt=0;
    while (key!=0) {
        blocks[cnt]=key & ((1 << 7)-1);
        cnt++;
        key >>= 7;
    }
    for (int i=7; i>=0; i--) {
        int tmp=blocks[i], cnt=0;
        while (tmp!=0) {
            cnt+=tmp & 1;
            tmp >>= 1;
        }
        if (cnt%2==0) blocks[i]=(1 << 7)^blocks[i];
        cntr_key = (cntr_key << 8) ^ blocks[i];
    }
    key=cntr_key;
}
int main(int argc, char *argv[])
{
    string op=argv[1];
    input.open(argv[2],ifstream::binary);
    output.open(argv[3],ofstream::binary);
    input.seekg(0,input.end);
    int input_length=input.tellg();
    if (input_length%8!=0) input_length=(input_length/8)*8+8;
    input.seekg(0,input.beg);
    printf("Insert keys\n");
    scanf("%s",_key1);
    scanf("%s",_key2);
    scanf("%s",_key3);
    unsigned long long key1=get_bits(_key1);
    unsigned long long key2=get_bits(_key2);
    unsigned long long key3=get_bits(_key3);
    control_key(key1);
    control_key(key2);
    control_key(key3);
    long long cnt_of_byte=0;
    while (!input.eof()) {
        char *buffer = new char;
        input.read(buffer,1);
        if (input.eof()) break;
        if (cur==8) {
            if (op=="/E" || op=="/e") get_chars(encryption_des(encryption_des(encryption_des(get_bits(data),key1),key2),key3));
            else get_chars(decryption_des(decryption_des(decryption_des(get_bits(data),key3),key2),key1));
            cnt_of_byte+=8;
            printf("%I64d bytes complete (%1.f%c complete)\r",cnt_of_byte,cnt_of_byte/float(input_length)*100,'%');
            cur=0;
        }
        data[cur++]=*buffer;
    }
    if (cur!=0) {
        if (op=="/E" || op=="/e") get_chars(encryption_des(encryption_des(encryption_des(get_bits(data),key1),key2),key3));
        else get_chars(decryption_des(decryption_des(decryption_des(get_bits(data),key3),key2),key1));
        cnt_of_byte+=8;
        printf("%I64d bytes complete (%1.f%c complete)\r",cnt_of_byte,cnt_of_byte/float(input_length)*100,'%');
    }
    printf("\n");
    if (op=="/E" || op=="/e") printf("Encryption complete\n");
    else printf("Decryption complete\n");
    input.close();
    output.close();
}
