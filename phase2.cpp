#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<fstream>
#include <string>
using namespace std;
#define ROW 300
#define COL 4

vector<vector<string>> Memory(ROW, vector<string>(COL,""));
vector<string> R(4);
char value=' ';

vector<string> IR(4);
int IC {00};
bool C {false};
int count=0;
int SI=3;
int TI=0;
int PI=0;
int PTE,PTR,PID;
int RA;
int TTC=0,LLC=0,TTL=0,TLL=0;
int program_card_counter;
int programEnded=0;

vector<string> words {};
string line;
vector<string> PCB(12);
vector<int> randomno;
int IC1{00};
int frame_no;
int IC_cnt;


void READ();
void WRITE();
void LOAD();
void TERMINATE(int);
void STARTEXECUTION();
void MOS();
int ALLOCATE();
int ADDRESS_MAP(int);
void PRINT_MEMORY();
int GET_VALID_PAGE_NO(int);
void PCB_Initilization();
void get_RA();
void WRITE_TERMINATE(int);
void PROGRAM_PAGE_NO();
void INIT();
void PRINT();


void PRINT(){


 IC_cnt=IC1+1;
 if(TTC>TTL){
    IC_cnt--;
 }
  ofstream fout("output_phase2.txt",ios::app);
    // while (fout) {
         fout<<endl;
         fout<<"Job ID :"<<PID<<endl;
         fout << "IC  :  "<<IC_cnt<<endl;
         fout << "IR  :  ";
         for(int i=0;i<4;i++){
            fout<<IR[i];
         }
         fout<<endl;
         fout << "TTC  :  "<<TTC<<endl;
         fout << "LLC  :  "<<LLC<<endl;
     fout.close();
}
void INIT(){

    R.clear();
    IR.clear();

    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            Memory[i][j]="";
        }
    }
    char value=' ';
    for(int i=0;i<4;i++){
        IR[i]={""};
    }
    IR={""};
    R={" "};
    IC=0;
    C = false;
    SI=3;
    TI=0;
    PI=0;
    PTE=0,PTR=0;
    RA;
    TTC=0,LLC=0,TTL=0,TLL=0;
    program_card_counter=0;
    programEnded=0;

    words.clear();
    line="";
    PCB.clear();
    randomno.clear();
    IC1 =0;
    IC_cnt=0;
    fill(R.begin(),R.end(),value);

}


void PROGRAM_PAGE_NO(){    
    int flag=0;
     do{
        frame_no=ALLOCATE();
        flag=0;
        for(int i=0;i<randomno.size();i++){
            if(frame_no==randomno[i])
            {
                 flag=1;
                 break;
            }
        }
    
     }while(flag==1);
         randomno.push_back(frame_no);
         int num=frame_no;
         if(num>9){
            int n1 = num%10;
            num=num/10;
            string s = to_string(n1);
          Memory[PTR+program_card_counter][3]=s;
            n1=num%10;
            s = to_string(n1);
        Memory[PTR+program_card_counter][2]=s;
        }
        else{
        Memory[PTR+program_card_counter][2]=to_string(0);
        Memory[PTR+program_card_counter][3]=to_string(num);
        }
        frame_no=frame_no*10;
}

void WRITE_TERMINATE(int n){
     ofstream fout("output_phase2.txt",ios::app);
     string buffer;
     int l;
    switch(n){
        case 0: 
                buffer="No error";
                l=0;
                while (fout && l<buffer.size()) {
                      fout << buffer[l++];
                    
                 }
                fout.close();
                PRINT();
                PRINT_MEMORY();
                break;
        case 1:
                buffer="Out of Data";
                l=0;
                while (fout && l<buffer.size()) {
                      fout << buffer[l++];
                    
                 }
                fout.close();
                PRINT();

                break;
        case 2:
                buffer="Line Limit Exceeded";
                l=0;
                while (fout && l<buffer.size()) {
                      fout << buffer[l++];   
                 }
            
                fout.close();
                PRINT();
                break;
        case 3:
                l=0;
                buffer="Time Limit Exceeded";
                while (fout && l<buffer.size()) {
                      fout << buffer[l++];   
                 }
                fout.close();
                PRINT();

                break;
        case 4:
                buffer="Operation Code Error";
                l=0;
                while (fout && l<buffer.size()) {
                      fout << buffer[l++];   
                 }
            
                fout.close();
                PRINT();
                break; 
        case 5:
                buffer="Operand Error";
                l=0;
                while (fout && l<buffer.size()) {
                      fout << buffer[l++];   
                 }
    
                fout.close();
                PRINT();
                break;
        case 6:
                 l=0;
                 buffer="Invalid Page Fault";
                while (fout && l<buffer.size()) {
                      fout << buffer[l++];   
                 }
        
                fout.close();
                PRINT();
                break;
            


        
    }
    programEnded=1;
    return;

}

void PCB_Initilization(){
     string temp,temp2,temp3;
           for(int i=8;i<12;i++){
              temp=temp+line[i];
              temp2=temp2+line[i+4];
              temp3=temp3+line[i-4];

           }
            TTL=stoi(temp);
            TLL=stoi(temp2);
            PID=stoi(temp3);
}
void get_RA(){
    string s = IR[2];
    string s1 = IR[3];
    s=s+s1;
    if ( !isdigit(s[0]) || !isdigit(s[1]))
    {
        PI=2;
        TI=0;
        MOS();
    }
    int n = stoi(s);
    RA=ADDRESS_MAP(n);
}

int GET_VALID_PAGE_NO(int VA){
      
    int flag=0;
     int FN;
     do{
        FN =ALLOCATE();
        flag=0;
        for(int i=0;i<randomno.size();i++){
            if(FN==randomno[i])
            {
                 flag=1;
                 break;
            }
        }
    
     }while(flag==1);
  
    // string s=Memory[PTE][2];
    // s =s+ Memory[PTE][3];
    //  if ( !isdigit(s[0]) && !isdigit(s[0]))
    // {
    //     PI=2;
    //     MOS();
    // }
        int num=FN;
        if(FN>9){
            int n1 = FN%10;
            FN=FN/10;
            string s = to_string(n1);
            Memory[PTE][3]=s;
            n1=FN%10;
            s = to_string(n1);
            Memory[PTE][2]=s;
        }
        else{
            Memory[PTE][2]=to_string(0);
            Memory[PTE][3]=to_string(FN);
        }
        randomno.push_back(num);
        return num;
       
    
}

int ALLOCATE(){
    
    int random = rand() % 30;
    return random;
}

int ADDRESS_MAP(int VA){
    if(VA<0 && VA>99){
        PI=2;
        TERMINATE(5);
    }

    int num=0;
    PTE=PTR+(VA/10);
    string s=Memory[PTE][2];
    s =s+ Memory[PTE][3];
    if(s=="**"){
         num=GET_VALID_PAGE_NO(VA);
         RA=num*10+(VA%10);
         return RA;
    }
    if ( !isdigit(s[0]) && !isdigit(s[0]))
    {
        PI=2;
        MOS();
    }
    int n=stoi(s);
    RA=n*10+(VA%10);

    return RA;
}

void MOS(){

   if(TTC>TTL)
   {
            TI=2;
            SI=1;
   } 
      
      if(programEnded==1)
        return;

   if(TI==0){
         
        if(SI==1)
            READ();
        else if(SI==2)
            WRITE();
        else if(SI==3)
            TERMINATE(0);
    }
    if(TI==2) {
        if(SI==1)
            TERMINATE(3);
        else if(SI==2){
            WRITE();
            TERMINATE(3);
        }
        else if(SI==3)
            TERMINATE(0);
    }

      if(TI==2){
         if(PI==1){
            TERMINATE(4);
        }
        else if(PI==2){
            TERMINATE(5);
        }
        else if(PI==3)
            TERMINATE(3);
    }
    
     if(TI==0){
         if(PI==1)
            TERMINATE(4);
        else if(PI==2)
            TERMINATE(5);
        else if(PI==3)
            TERMINATE(6);
    }
       
   
      if(programEnded==1)
        return;

}


void TERMINATE(int n){
   
  
   switch(n){
    case 0: cout<<"No Error";
            WRITE_TERMINATE(0);
            break;
    case 1: cout<<"Out of Data"<<endl;
            WRITE_TERMINATE(1);
            break;
    case 2: cout<<"Line limit Exceeded"<<endl;
            WRITE_TERMINATE(2);
            break;
    case 3: cout<<"Time Limit Exceeded"<<endl;
            WRITE_TERMINATE(3);
            break;
    case 4: cout<<"Operation Code Error"<<endl;
            WRITE_TERMINATE(4);
            break;
    case 5: cout<<"Operand Error"<<endl;
            WRITE_TERMINATE(5);
            break;
    case 6: cout<<"Invalid Page Fault"<<endl;
            WRITE_TERMINATE(6);
            break;
   }
return;
}


void READ(){
            
            int wordLen = line.length();
            if( line[0]=='$' && line[1]=='E' ){
                TERMINATE(1);
            }
            int c=0;
            bool flag = false;
            
            for(int j=RA;j<RA+10;j++){
                for(int k=0;k<COL;k++){
                     if(c < wordLen)
                     {
                        Memory[j][k]=line[c++];
                        
                     }
                    else
                     {
                        flag = true;
                        break;
                     }  
                }
              if(flag==true)
              {
                break;
              }
            }
    return;
}



void WRITE(){
            
        if(LLC>=TLL)
            TERMINATE(2);
        else{
                int c=0;
                bool flag = false;
                string word="";
                vector <string> buffer;

                for(int j=RA;j<RA+10;j++){
                    for(int k=0;k<COL;k++){
                        word+=Memory.at(j).at(k);
                    }
                
                }
                buffer.push_back(word);
            

                ofstream fout("output_phase2.txt",ios::app);
                string line1;
                
                int i=0;
                
                while (fout && i<buffer.size()) {
                    fout << buffer[i]<< endl;
                
                    i++;
                }
                fout.close();
                LLC++;
    
        }
          


return;
}





void STARTEXECUTION(){

int cnt=0;
while(IC1!=IC){
            
            if(TTC>TTL && programEnded==0)
            {
                TI=2;
                SI=1;
                // ++IC1;
                MOS();
            } 
            if(programEnded==1){
                return;
            }

           
             RA = ADDRESS_MAP(IC1);
             for(int i=0;i<4;i++){
                IR[i]=Memory[RA][i];
             }
             

            if(IR[0]=="G" && IR[1]=="D"){
                get_RA();
                SI=1;
                cnt++;
                 if(cnt>1){
                    return;
                }
            //  TTC=TTC+2;
            TTC++;
            MOS();
            
            }
            else if(IR[0]=="P" && IR[1]=="D"){
                SI=2;
                get_RA();
                TTC++;
                MOS();

            }   
            else if(IR[0]=="H"){
                 TTC++;
                 SI=3;
                 MOS();
            }
            else if(IR[0]=="L" && IR[1]=="R")
            {  
                get_RA();
                if(Memory[RA][0]=="" && Memory[RA][1]=="" && Memory[RA][2]=="" && Memory[RA][3]==""){
                    PI=3;
                    TERMINATE(6);
                }
                for(int j=0;j<4;j++){
                     R[j]=Memory[RA][j];
              }
              TTC++;
            //   cout<<endl;
            }
            else if (IR[0]=="S" && IR[1]=="R")
            {
                SI=1;
                get_RA();
                if(R[0]==" " && R[1]==" " && R[2]==" " && R[3]==" "){
                    PI=3;
                    TERMINATE(6);
                }
                else{
                    for(int j=0;j<4;j++){
                     Memory[RA][j]=R[j];
               }
                // TTC=TTC+2;
                TTC++;
                }
               
            }

             else if(IR[0]=="C" && IR[1]=="R")
            {
              
              get_RA();
              for(int j=0;j<4;j++){
                if(R[j]==Memory[RA][j])
                    C=true;
                else{
                    C=false;
                    break;
                }
            }
             TTC++;
            
           
        }  
        else if(IR[0]=="B" && IR[1]=="T"){
                string s = Memory[RA][2];
                string s1 = Memory[RA][3];
                s=s+s1;
                int n = stoi(s);
                if(C==true){
                     IC1=n;
                 }
        }
         else{
            PI=1;
            SI=0;
            TTC++;
            MOS();
   
            
        }
      
      if(C==true && IR[0]=="B")
        continue;
      else
        ++IC1;
   
    
 }   
 return;
 

 
}


void LOAD(){
    ifstream fin;
    fin.open("input_phase2.txt");

    int temp=0;
    string s;
    bool flag = false;
    int count;


     while(fin){
         getline(fin, line);
        int c=0;
         if(line[0]=='$'&& line[1]=='A'){
           int j=0;
           string temp,temp2;
            PCB_Initilization();
            PTE=ALLOCATE();
             randomno.push_back(PTE);
            PTR = PTE*10;
            for(int j=PTR;j<PTR+10;j++){
                for(int k=0;k<COL;k++){
                    Memory[j][k]='*';
                }
            }    
            count++;

         }
         else if(line[0]=='$' && line[1]=='E'){
            
            // if(IR[0]=="" || IR[0]=="G" && IR[1]=="D" && frame_no==0){
            //     TERMINATE(1);
            // }
            
            if(IR[0]=="" || IR[0]=="G" && IR[1]=="D" && programEnded==0){
                TERMINATE(1);
            }
            cout<<"Program Ended"<<endl;

            ofstream fout("output_phase2.txt",ios::app);
            while (fout) {
                      fout <<endl;
                      fout <<endl;
                      break;
                 }
            fout.close();
            INIT();
            count=0;    
        }
         else if(line[0]=='$' && line[1]=='D'){
            count++;
         }
         else if(count==2){
            STARTEXECUTION();
         }
         else if(count==1){
         int wordLen = line.length();
         c=0;
         flag=false;
        PROGRAM_PAGE_NO();
        

            for(int j=frame_no;j<ROW;j++){
                for(int k=0;k<COL;k++){
                

                    if(c < wordLen){
                         Memory[j][k]=line[c++];
                    }
                    else
                    {
                    flag = true;
                    break;
                    }  
                }
                IC++;
             if(flag==true)
             {
               
                break;
             }
          }
          program_card_counter++;
         }
         
     }
     fin.close();
    
}   

void PRINT_MEMORY(){
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
        cout<<i<<" =>  ";
        for(int j=0; j<COL; j++)
        {
            cout<<Memory.at(i).at(j)<<"  ";
        }
        count++;
        
        cout<<endl;
    }
    
}

int main(){
    fill(R.begin(),R.end(),value);
    ofstream fout;   
    fout.open("output_phase2.txt");
    fout<<"";
    fout.close();
    LOAD();
}

