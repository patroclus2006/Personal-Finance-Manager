#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

class Transaction{
public:
    string type;
    double amount;

    Transaction(){
        type="x";
        amount=0;
    }

    Transaction(string t,double a){
        type=t;
        amount=a;
    }

    void show(){
        cout<<type<<" "<<amount<<endl;
    }
};


class Account{
public:
    double income;
    vector<Transaction> exp;
    double goal;

    Account(){
        income=0;
        goal=0;
    }

    Account(double i){
        income=i;
    }

    void add(string t,double a){

        Transaction temp(t,a);
        exp.push_back(temp);

        ofstream f("data.txt",ios::app);

        if(f){
            f<<t<<","<<a<<"\n";
        }
    }

    void load(){

        ifstream f("data.txt");

        string t;
        double a;

        exp.clear();

        while(getline(f,t,',')){
            f>>a;
            f.ignore();

            Transaction x(t,a);
            exp.push_back(x);
        }
    }

    double total(){
        double s=0;
        for(int i=0;i<exp.size();i++){
            s=s+exp[i].amount;
        }
        return s;
    }

    double net(){
        return income-total();
    }

    void print(){
        for(int i=0;i<exp.size();i++){
            exp[i].show();
        }
    }
};


void debug(Account a){
    cout<<"income "<<a.income<<endl;
    cout<<"total "<<a.total()<<endl;
}


class Report{
public:
    virtual void run(Account a)=0;
};


class R1:public Report{
public:
    void run(Account a){
        cout<<"SUMMARY\n";
        cout<<a.income<<"\n";
        cout<<a.net()<<"\n";
    }
};

class R2:public Report{
public:
    void run(Account a){
        cout<<"DETAIL\n";
        cout<<a.income<<"\n";
        a.print();
        cout<<a.net()<<"\n";
    }
};



void analysis(Account a){

    cout<<"ANALYSIS\n";

    double inc=a.income;
    double ex=a.total();

    cout<<inc<<" inc\n";
    cout<<ex<<" exp\n";

    if(inc!=0){
        cout<<(ex/inc)*100<<" %\n";
    }

    debug(a);

    if(inc-ex<0){
        cout<<"BAD BAD BAD\n";
    }else{
        cout<<"ok\n";
    }
}



int main(){

    int code;

    cout<<"code? ";
    cin>>code;

    if(code!=2585){
        cout<<"wrong";
        return 0;
    }

    double income;
    char m;

    cout<<"income: ";
    cin>>income;

    cout<<"D W M ? ";
    cin>>m;

    double res=income;

    if(m=='D'){
        res=income*30;
    }
    if(m=='W'){
        res=income*4;
    }

    cout<<"res "<<res<<endl;

    Account a(res);
    a.load();


    while(1){

        cout<<"\n1 add\n2 show\n3 net\n4 analysis\n5 report\n0 exit\n";

        int c;
        cin>>c;

        if(c==0){
            break;
        }

        if(c==1){
            string t;
            double am;

            cout<<"t? ";
            cin>>t;

            cout<<"am? ";
            cin>>am;

            a.add(t,am);
        }

        if(c==2){
            a.print();
        }

        if(c==3){
            cout<<a.net()<<endl;
        }

        if(c==4){
            analysis(a);
        }

        if(c==5){

            int x;
            cout<<"1 or 2 ";
            cin>>x;

            Report* r;

            if(x==1){
                r=new R1();
            }
            if(x==2){
                r=new R2();
            }

            r->run(a);
        }

        if(c==999){
            debug(a);
        }
    }

    return 0;
}
