#include<iostream>
#include<cstring>
using namespace std;
class base{
protected:
    char *acc_num;
public:
    double bal;
    base(char *acc,double bal)
    {
      acc_num= new char[100];
      strcpy(acc_num,acc);
      this->bal=bal;
    }
     bool validate()
     {
      if(strlen(acc_num)==10)
        return true;
      else
        return false;
    }
    void display(){
      cout<<"Account number is "<<acc_num<<endl;
      cout<<"Initial balance in account is "<<bal<<endl;
    }
    virtual bool transfer()=0;
};
class IMPS:public base{
protected:
    double totalAmount;
    double serviceTax;
    double netAmount;
public:
    IMPS(double amt,char* account,double balance):base(account,balance){
      totalAmount=amt;
      serviceTax=((0.02)*totalAmount);
      netAmount=totalAmount+serviceTax;
    }
    bool transfer(){
        if(netAmount<=bal){
        bal=bal-netAmount;
        return true;
      }
      else
        return false;
    }
    void disp(){
        cout<<"After applying service charge "<<serviceTax<<" balance amount is "<<bal<<endl;
    }
};
class NEFT:public base{
protected:
    double totalAmount;
    int flag=0;
    int hr,mi,sec;
public:
    NEFT(double amt,char* account,double balance,int hr,int mi,int se):base(account,balance){
      totalAmount=amt;
      this->hr=hr;
      this->mi=mi;
      this->sec=sec;
    }
    void check()
    {
      if(hr>=9&&hr<=18)
        {
            if(hr==9||hr==18)
            {
                if(mi==0||sec==0)
                {
                    flag=1;
                }
            }
            else
            {
                flag=1;
            }
        }
        else
        {
            flag=0;
        }
    }
    bool transfer(){
        check();
        if(flag==1)
        {
            if(bal>=totalAmount)
            {
                bal=bal-totalAmount;
                return true;
            }
            else
                return false;
        }
        else if(flag==0)
        {
           cout<<"Transaction not possible in entered time"<<endl;
           return false;
        }
    }
    void disp(){
      cout<<"After transferring amount "<<totalAmount<<" balance is "<<bal<<endl;
          }
};
class RTGS:public base{
protected:
    double totalAmount;
public:
    RTGS(double amt,char* account,double balance):base(account,balance){
      totalAmount=amt;
    }
    bool transfer(){
      if(totalAmount>=10000){
        bal=bal-totalAmount;
        return true;
      }
      else
        return false;
    }
    void disp(){
      cout<<"After transferring amount "<<totalAmount<<" balance is "<<bal<<endl;
    }
};
int main(){
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"**************************************************WELCOME TO OUR BANK*************************************************"<<endl;
        cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl<<endl<<endl;
    cout<<"There are three different ways i.e. RTGS, NEFT and IMPS through which we can transfer funds from one bank account to another"<<endl;
    cout<<"Note: A valid account number consists of ten digits"<<endl;
    cout<<"Necessary Condition for RTGS: RTGS is used for the transfer amount of more than 10000"<<endl;
    cout<<"Necessary Condition for IMPS: IMPS applies 2% service charge on transfer amount and then make transaction if possible"<<endl;
    cout<<"Necessary Condition for NEFT: NEFT transfer is applicable between 9:00am to 6:00pm"<<endl;
    char accountNumber[100];
    double bal;
    double amt;
    cout<<"Enter account number"<<endl;
    cin>>accountNumber;
    if(strlen(accountNumber)!=10)
        cout<<"Invalid Account Number";
    else
    {
    cout<<"Enter balance"<<endl;
    cin>>bal;
    cout<<"Enter transfer amount"<<endl;
    cin>>amt;
    cout<<"Enter 1 for NEFT, 2 for IMPS, 3 for RTGS"<<endl;
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:
        {
           cout<<"Enter time in 24 hr format"<<endl;
           int hrs,mins,sec;
           cout<<"h/m/s = "<<endl;
           cin>>hrs>>mins>>sec;
           NEFT ne(amt,accountNumber,bal,hrs,mins,sec);
           ne.display();
           if(ne.validate()){
               if(ne.transfer()){
                 cout<<"Transfer occurred successfully"<<endl;
                 ne.disp();
               }
               else{
                 cout<<"Transfer unsuccessful"<<endl;
               }
            break;
           }
           else{
            cout<<"Invalid Account Number"<<endl;
           }
        }
    case 2:
        {
            IMPS i(amt,accountNumber,bal);
            i.display();
            if(i.validate()){
             if(i.transfer()){
               cout<<"Transfer occurred successfully"<<endl;
               i.disp();
              }
            }
            else{
                cout<<"Invalid Account Number"<<endl;
            }
            break;
        }
    case 3:
        {
            RTGS r(amt,accountNumber,bal);
            r.display();
            if(r.validate()){
             if(r.transfer()){
               cout<<"Transfer occurred successfully"<<endl;
               r.disp();
              }
              else{
                cout<<"Transfer unsuccessfull"<<endl;
              }
            }
            else{
                cout<<"Invalid Account Number"<<endl;
            }
            break;
        }
    default:
        cout<<"Invalid Choice";
    }
    }
    return 0;
}
