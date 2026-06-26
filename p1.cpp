#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class traconesh{
public:
    string type;
    double amount;

    traconesh(){
        type="x";
        amount=0;
    }

    traconesh(string t,double a){
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
    vector<traconesh> expense;
 

    Account(){
        income=0;
       
    }

    Account(double i){
        income=i;
    }

    void add(string t,double a){

        traconesh temp(t,a);
        expense.push_back(temp);

        ofstream f("data.txt",ios::app);

        if(f){
            f<<t<<","<<a<<"\n";
        }
    }

    void load(){

        ifstream f("data.txt");

        string t;
        double a;

        expense.clear();

        while(getline(f,t,',')){
            f>>a;
            f.ignore();

            traconesh x(t,a);
            expense.push_back(x);
        }
    }

    double total(){
        double s=0;
        for(int i=0;i<expense.size();i++){
            s=s+expense[i].amount;
        }
        return s;
    }

    double net(){
    	double x = total();
    	double y = income-x;
    	
        return y;
    }

    void print(){
        for(int i=0;i<expense.size();i++){
            expense[i].show();
        }
    }
};





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

    cout<<inc<<" income\n";
    cout<<ex<<" expeense\n";

    if(inc!=0){
        cout<<(ex/inc)*100<<" %\n";
    }

    

    if(inc-ex<0){
           cout<<"BAD BAD BAD\n";
    }else{
        cout<<"good\n";
    }
}



int main(){
 		int code;

  cout<<"enter your registery code please"<<endl;
   cin>>code;

	 if(code!=2585){
        cout<<"wrong code sorry you cant log in ;)";
        return 0;
    }

  	  double income;
    char income_type;

  	  cout<<"would you please enter your income: ";
   		 cout<<"it can be monthly weekly and daily ";
    cin>>income;

      cout<<"(please if your income is monthly enter 'M',if its weekly enter 'W' and if its daily enter 'D'and then press 'ENTER') ";
    cin>>income_type;

    double result=income;

    if(income_type=='D' || income_type=='d'){
    result = income * 30;
			}
	else if(income_type=='W' || income_type=='w'){
    result = income * 4;
		}
	else if(income_type=='M' || income_type=='m'){
    result = income;
	}
	else{
    cout << "nvalid TYPE" << endl;
	}

     cout<<"your monthly income is  "<<result<<endl;

   	 Account a(result);
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

             cout<<"expense type? ";//type
            cin>>t;

              cout<<"how much did you spend on it? ";//amount
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
            cout<<"report v1[press 1] or report v2[press 2] ";
            cin>>x;

            Report* r;

            if(x==1){
                r=new R1();
            }
            if(x==2){
                r=new R2();
            }

            r->run(a);
            delete r;
        }

    
    }

    return 0;
}
