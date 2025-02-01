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
//                 input        input         output         input
void Decompress(char comp[], int compSize, string &Decomp, cnode *code) {
    string Bits_String = ""; 
    char currentBit;
    int ct=0;
    cnode *ptrav;
    for (int i = 0; i < compSize; i++) {
        for (int bit = 7; bit >= 0; bit--) { 
            // '0' 3lshan t5leha string
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
void Display_Decompressed(string Decomp){
    for(int i=0;i<Decomp.length();i++){
        cout<<Decomp[i];
    }
}
int main() {
    clist L;
    cnode *pnn;
    cTnode *ptop = NULL; 
    ifstream data("/COMP_FILE.jpeg",ifstream::binary);
    ifstream CODE_TXT("/CODE.txt",ifstream::binary);
    ofstream OUTPUT("/OUTPUT.jpeg",ifstream::binary);
    string line;
    data.seekg(0,data.end);
    // h1 is the length of the file
    int h1 = data.tellg();
    data.seekg(0,data.beg);
    string dataString;
    char *data_hex = new char[h1];
    char ch;
    for(int i=0;i<h1;i++){
        data.read(&ch,1);
        data_hex[i] = ch;
    }
    clist Encoded;
    while(getline(CODE_TXT,line)){
        // if(line != " "){
            pnn = new cnode;
            pnn->letter = (char)line[0];
            for(int i=1;i<line.length();i++){
                pnn->binary += line[i];
            }
            Encoded.attach(pnn);
        // }
    }

    string Decompressed="";

    Decompress(data_hex,h1,Decompressed,Encoded.phead);
     for(int i=0;i<h1;i++){
        OUTPUT.write(&Decompressed[i],1);
    }
}