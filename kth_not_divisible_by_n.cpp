#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k,i;
        cin>>n>>k;
        int a=n-1;
        int b=ceil(k/a);
        if(k%a!=0)
        i=b*a-k;
        else
        i=b*a-k+1;
        int ans=(b)*n-i;
        cout<<ans<<endl;
    }
}