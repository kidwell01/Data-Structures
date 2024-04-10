#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float calculate(char p, float a, float b){
    cout<<"Enter the first double: "<<endl;
    cin>>a;
    cout<< "Enter operand: "<<endl;
    cin>>p;
    cout<<"Enter the second double: "<<endl;
    cin>>b;


    if(p=='+'){
    cout<<a + b;
    return a + b;
    }
    else if(p=='-'){
        cout<<a - b;
        return (a-b);
    }
    else if(p=='/'){
        if((b==0)){
        cout<<"sorry you can not divide by 0"<<endl;
        return 0;
        }
        else{
        cout<<a / b;
        return (a/b);
        }
    }
    else if(p=='*'){
        cout<<a * b;
        return (a*b);
    }
    else{
        cout<<"Invalid operator"<<endl;
        return 0;
    }
}

int main(){
    char operat;
    float x, y;

    calculate(operat, x, y);
    return 0;
}