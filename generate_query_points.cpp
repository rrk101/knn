#include<bits/stdc++.h>
using namespace std;


const int N = 100;
const float range_from  = -100.0f;
const float range_to    = 100.0f;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<float>  distr(range_from, range_to);

int main()
{
    freopen("queries.txt","w",stdout);

    vector<vector<float>> v(N,vector<float>(100));

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<100;j++)
        {
            if(i==0) v[i][j]=0.0f;
            else v[i][j] = distr(rng);
        }
    }
    cout<<N<<"\n";
    for(auto &i:v)
    {
        for(auto &j:i) cout<<j<<" ";
        cout<<"\n";
    }



    return 0;
}
