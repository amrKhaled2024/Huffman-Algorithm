#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class cTnode{
    public:
        int info;
        string letter;
        cTnode *pRight;
        cTnode *pLeft;
        
        cTnode(){
            info = 0;
            letter = "";
            pRight = NULL;
            pLeft = NULL;
        }
};
class cnode {
    public:
        int info;
        string letter;
        cTnode *pdown;
        cnode *pnext;
        string binary;

        cnode(){
            info = 0;
            letter = "";
            pnext = NULL;
            pdown = NULL;
            binary = "";
        }
};
class clist{
    public: 
        cnode *phead;
        cnode *ptail;

        clist(){
            phead = NULL;
            ptail = NULL;
        }
        // ~clist(){
        //     cnode *ptrav = phead;
        //     cnode *ptemp;
        //     while (ptrav != NULL){
        //         ptemp = ptrav;
        //         ptrav = ptrav->pnext;
        //         delete ptemp;
        //     }
        // }

        void attach(cnode *pnn){
            pnn->pnext = NULL;
            if(phead == NULL){
                phead = pnn;
                ptail = pnn;
            }
            else{
                ptail->pnext = pnn;
                ptail = pnn;
            }
        }
        
        void sortAttach(cnode* pnn) {
            if (phead == NULL || pnn->info < phead->info) {
                pnn->pnext = phead;
                phead = pnn;
                if(ptail == NULL){
                    ptail = pnn;
                }
                return;
            }

            cnode* ptrav = phead;
            while(ptrav->pnext != NULL && ptrav->pnext->info <= pnn->info) {
                ptrav = ptrav->pnext;
            }

            pnn->pnext = ptrav->pnext;
            ptrav->pnext = pnn;

            if(pnn->pnext == NULL){
                ptail = pnn;
            }
        }

        void display(){
            cnode *ptrav = phead;
            while(ptrav != NULL){
                cout << ptrav->letter << " " << ptrav->binary<<endl;
                ptrav = ptrav->pnext;
            }
            cout << endl;
        }
};

void Frequency(char data[],int counts[],int size){
    int ct=0;
    for(int i=0;i<256;i++){
        for(int a=0;a < size;a++){
            if(data[a] == (i-128)){
              ct++;  
            }
        }
        counts[i]=ct;
        ct = 0; 
    }   
}
void Freq_Display(int counts[]){
    int let;
    for(int i=0;i<256;i++){
        let = i - 128;
        if(counts[i] != 0){
            cout<<let<<" => "<<counts[i]<<endl;
        }
    }
}
void Huffman_Tree(clist& L, cTnode*& ptop){
    while(L.phead != NULL && L.phead->pnext != NULL){
        cnode *first = L.phead;
        cnode *second = L.phead->pnext;

        L.phead = second->pnext;
        if(L.phead == NULL){
            L.ptail = NULL;
        }

        // cut the 2 nodes
        first->pnext = NULL;
        second->pnext = NULL;

        cnode *pnn = new cnode;
        cTnode *pnnTreeTop = new cTnode;

        pnn->info = first->info + second->info;
        pnn->pdown = pnnTreeTop;
        pnn->letter = first->letter + second->letter;

        pnnTreeTop->info = first->info + second->info;
        pnnTreeTop->letter = first->letter + second->letter;
        
        if(second->pdown != NULL){
            pnnTreeTop->pRight = second->pdown;
            delete second;
        }else{
            cTnode *ptRight = new cTnode;
            ptRight->info = second->info;
            ptRight->letter = second->letter;
            pnnTreeTop->pRight = ptRight;
        }

        if(first->pdown != NULL){
            pnnTreeTop->pLeft = first->pdown;
            delete first;
        }else{
            cTnode *ptLeft = new cTnode;
            ptLeft->info = first->info;
            ptLeft->letter = first->letter;
            pnnTreeTop->pLeft = ptLeft;
        }

        L.sortAttach(pnn);
        ptop = pnnTreeTop;
    }
}
void displayTree(cTnode *ptrav){
    if(ptrav == NULL){
        return;
    }
    displayTree(ptrav->pLeft);
    cout << ptrav->info << " " << ptrav->letter << endl;
    displayTree(ptrav->pRight);
}
void Huffman_Code(cTnode *ptrav, string dir, clist &enc,cTnode *ptop) {
    if (ptrav == NULL) {
        return;
    }
    // the leafs are the letters needed 
    if (ptrav->pLeft == NULL && ptrav->pRight == NULL) {
        cnode *pnn = new cnode;
        pnn->info = ptrav->info;
        pnn->letter = ptrav->letter;
        pnn->binary = dir;
        enc.attach(pnn);
        return;
    }
    Huffman_Code(ptrav->pLeft, dir + "0", enc,ptop);
    Huffman_Code(ptrav->pRight, dir + "1", enc,ptop);
}

void compress(char data[],int data_size, cnode *code, char comp[], int &size, char *&new_comp) {
    int c = 0, rem = 7;
    char letter;
    int code_length;
    cnode *ptrav;
    for(int i = 0;i < data_size;i++) {
        letter = data[i];
        ptrav = code;
        while (ptrav!=NULL && ptrav->letter[0] != letter) {
            ptrav = ptrav->pnext;
        }
        if (ptrav == NULL) continue; 

        code_length = ptrav->binary.length();

        for (int a = 0; a < code_length; a++) {
            comp[c] = comp[c] << 1;  
            if (ptrav->binary[a] == '1') {
                comp[c] = comp[c] | 1; 
            }
            rem --;
            if (rem < 0) {
                rem = 7;
                c++;
            }
        }
    }
    if (rem != 7) {
        int used_bits = 7 - rem ; 
        comp[c] = comp[c] << (rem+1); 
    }
    // exporting only the used bits (indexes)
    size = c + 1;

    new_comp = new char[size];
    for (int i = 0; i < size; i++) {
        new_comp[i] = comp[i];
    }
}
void display_compress_binary(char comp[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 7; j >= 0; j--) {
            cout << ((comp[i] >> j) & 1);
        }
    }
    cout << endl;
}
void display_compress_char(char comp[], int length) {
    for (int i = 0; i < length; i++) {
        cout << (int)comp[i]<<" ";
    }
    cout << endl;
}
//                 input        input         output         input
void Decompress(char comp[], int compSize, string &Decomp, cnode *code) {
    string Bits_String = ""; 
    char currentBit;
    int ct=0;
    cnode *ptrav;
    for (int i = 0; i < compSize; i++) {
        for (int bit = 7; bit >= 0; bit--) { 
            currentBit = ((comp[i] >> bit) & 1) + '0';
            Bits_String += currentBit; 
            ptrav = code;
            while (ptrav != NULL) {
                if (ptrav->binary == Bits_String) {
                    if(i == compSize - 1){
                        ct++;
                    }
                    if(ct < 2){
                        Decomp += ptrav->letter;
                        Bits_String = "";
                    }
                    break;
                }
                ptrav = ptrav->pnext;
            }
        }
    }
}
void exp_CODE(cnode *ptrav){
    ofstream CODE("/CODE.txt");
    while (ptrav != NULL){
        CODE<<ptrav->letter;
        CODE<<ptrav->binary.size();
        CODE<<ptrav->binary;
        CODE<<endl;
        ptrav = ptrav->pnext;
    }
}
void Display_Decompressed(string Decomp){
    for(int i=0;i<Decomp.length();i++){
        cout<<Decomp[i];
    }
}
int main() {
    clist L;
    clist Encoded;
    cnode *pnn;
    cTnode *ptop = NULL; 
    ifstream data("/INPUT.jpeg",ifstream::binary);
    ofstream f2("/COMP_FILE.jpeg",ofstream::binary);

    data.seekg(0,data.end);
    
    int h1 = data.tellg();
    data.seekg(0,data.beg);

    string dataString;

    int counts[256];
    char *data_hex = new char[h1];
    char ch;
    for(int i=0;i<h1;i++){
        data.read(&ch,1);
        data_hex[i] = ch;
    }
    Frequency(data_hex, counts,h1);
 
    for (int i = 0; i < 256; i++) { 
        if (counts[i] > 0) { 
            pnn = new cnode;
            pnn->info = counts[i];
            pnn->letter = i - 128;
            L.sortAttach(pnn);
        }
    }

    Huffman_Tree(L, ptop);
    cTnode *ptop_temp = ptop;
    Huffman_Code(ptop, "", Encoded,ptop_temp);
    cout<<endl;
    int size_temp = h1*2;
    int size_new;
    char comp_temp[size_temp];
    char *new_comp;
    string Decompressed;
    compress(data_hex,h1, Encoded.phead, comp_temp,size_new,new_comp);

    display_compress_char(new_comp, size_new);
    for(int i=0;i<size_new;i++){
        f2.write(&new_comp[i],1);
    }
    Decompress(new_comp,size_new,Decompressed,Encoded.phead);
    exp_CODE(Encoded.phead);

}
