#include <iostream>

using namespace std;

int main(){
    int N, X;
    int M;
    cout<<"Enter the number trials: "<<endl;
    cin>>N;
    cout<<"Enter the max of the range: "<<endl;
    cin>>M;
    int count=1;
    int number=rand()%M + 1;
    while(!(count>N)){
            cout<<"Enter your guess: "<<endl;
            cin>>X;
        if((X>=1)&&(X<=M)){
            if(X<number){
            cout<<"Guess is too low"<<endl;
            count++;
            }
            else if(X>number){
            cout<<"Guess is too high"<<endl;
            count++;
            }
            else{
            cout<<" Guess is correct"<<endl;
            break;
            }
        }
        else{
            cout<<"Out of range"<<endl;
        }
        //break;
    }
return 0;
}