#include<iostream>
#include<vector>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ans=0;
        vector<int> vec(n);
        for(int i=0;i<n;i++){
            cin>>vec[i];
        }
        for(int i=0;i<n;i++){
            if(vec[i]==0){
                ans++;
            }else{
                ans+=vec[i];
            }
        }
        cout<<ans<<endl;

    }
}