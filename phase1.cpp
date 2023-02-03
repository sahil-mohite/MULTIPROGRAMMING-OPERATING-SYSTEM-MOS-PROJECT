#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

//all function declaration
void MOS(int);
void READ();                       
void WRITE();
void TERMINATE();
void LOAD();
void STARTEXECUTION();
void EXECUTEUSERPROGRAM();
void printM(char [100][4]);

#define ROW 100
#define COL 4

char M[100][4];     //Memory
char IR[4];         //Instruction Register (4 bytes)
char R[4];          //General Purpose Register (4 bytes)
int IC;             //Instruction Counter Register (2 bytes)
int SI;             //Interrupt
bool C;             //Toggle (1 byte)

char buffer[40];
int buffer_size = 39;
fstream infile;
fstream outfile;

void INIT()
{
    for(int i = 0; i<ROW; i++){
        for(int j = 0; j<COL; j++ ){
            M[i][j]=' ';
        }
    }
    IR[0] = {' '};
    R[0] = {' '};
    C = false;
}

void MOS(int SI)
{

    switch(SI)
    {
        case 1 : READ();
                break;

        case 2 : WRITE();
                break;

        case 3 : TERMINATE();
                break;

    }
}

void READ()
{
    for(int i=0;i<=buffer_size;i++)
        buffer[i]='\0';

    infile.getline(buffer,44);

    int k = 0;
    int i = IR[2]-48;
    i = i*10;

    for( int l=0 ; l<10 ;  ++l){
        for(int j = 0 ; j<4; ++j){
            if(k == 40 || buffer[k] == '\0'){
            break;
            }
            M[i][j] = buffer[k];
            k++;
        }
        if(k == 40){
            break;
        }
        i++;
    }


}

void WRITE()
{
    for(int i=0;i<=buffer_size;i++)
        buffer[i]='\0';

    int k = 0;
    int i = IR[2]-48;
    i = i*10;


    for( int l=0 ; l<10 ;  ++l){
        for(int j = 0 ; j<4; ++j){
            if(k == 40 || M[i][j] == '\0'){
                break;
            }
            buffer[k]=M[i][j];
            //writing requested data to output file(charcter by charater)
            outfile<<buffer[k];
            k++;
        }
        if(k == 40){
            break;
        }
        i++;
    }
    outfile<<"\n";
}


void TERMINATE()
{
    string message = "----------program executed sucessfully----------\n";
    
    outfile<<message; 
    outfile<<"\n";
    outfile<<"\n";
}


void STARTEXECUTION()
{
    IC = 0;
    EXECUTEUSERPROGRAM();
}

void EXECUTEUSERPROGRAM()
{
    while(true)
    {
        for(int i = 0; i<4; i++){           //Load in register
            IR[i] = M[IC][i];
        }
        IC++;

        if(IR[0] == 'G' && IR[1] == 'D'){           //GD
            SI = 1;
            MOS(SI);
        }
        else if(IR[0] == 'P' && IR[1] == 'D'){       //PD
            SI = 2;
            MOS(SI);
        }
        else if(IR [0] == 'H'){                     //H
            SI = 3;
            MOS(SI);
            break;
        }

        else if(IR[0] == 'L' && IR[1] == 'R'){       //LR
            int i = IR[2]-48;
            i = i*10 + (IR[3]-48);

            for(int j=0;j<=3;j++)
                R[j]=M[i][j];
        }
        else if(IR[0] == 'S' && IR[1] == 'R'){       //SR
            int i = IR[2]-48;
            i = i*10 +( IR[3]-48) ;

            for(int j=0;j<=3;j++)
                M[i][j]=R[j];

        }
        else if(IR[0] == 'C' && IR[1] == 'R'){       //CR
        
            int i = IR[2]-48;
            i = i*10 + (IR[3] - 48);
            //cout<<i;
            int count=0;

            for(int j=0;j<=3;j++)
                if(M[i][j] == R[j])
                    count++;

            if(count==4)
                C=true;

            //cout<<C;
        }
        else if(IR[0] == 'B' && IR[1] == 'T'){       //BT
            if(C == true)
            {
                int i = IR[2]-48;
                i = i*10 + (IR[3] - 48);

                //make instruction pointer to i
                IC = i;
            }
        }
    }
}

void LOAD()
{   
    cout<<"\n*******Reading Data from memory**********\n"<<endl;
    int x=0;
    do
    {
        for(int i=0;i<=buffer_size;i++)      
           buffer[i]='\0';

        infile.getline(buffer,41);
        for(int k=0;k<=39;k++)
           cout<<buffer[k];

        cout<<"\n";

        if(buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J'){
            INIT();
        }
        else if(buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A'){
            STARTEXECUTION();
        }
        else if(buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D'){
            x=0;
            printM(M);
            continue;
        }
        else{
            int k = 0;
            if(x!=0)
            {
                x++;
            }
            for(; x <100; ++x)
            {
                
                for(int j = 0 ; j<4; ++j)
                {
                    M[x][j] = buffer[k];
                    k++;
                }

                if(k == 40 || buffer[k] == ' ' || buffer[k] == '\n')
                {
                    break;
                }

            }

        }

    } while(!infile.eof());         //continues to take input till end of the file


}

void printM(char M[100][4]){

    int count = 0;
    int block = 0;
    for(int i=0; i<ROW; i++)
    {   
        if(count==10 || count == 0)
        {
            cout<<"\nBlock "<< block <<endl;
            block++;
            count=0;
        }
        for(int j=0; j<COL; j++)
        {
            cout<<M[i][j]<<"  ";
        }
        count++;
        cout<<endl;
    }
}


int main()
{
    infile.open("input_phase1.txt");
    outfile.open("output_phase1.txt");

    LOAD();


    return 0;
}
