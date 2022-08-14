#include<bits/stdc++.h>
using namespace std;

const char *output_file_name = "vector_data.txt";
const char *input_file_name = "vector_data.txt";
const int N = 10000000;

const float range_from  = -100.0f;
const float range_to    = 100.0f;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<float>  distr(range_from, range_to);



int main()
{
    //freopen(output_file_name,"w",stdout);
    //freopen(input_file_name,"r",stdin);
    //int n;
    //cin>>n;
    //n = N;
    //n = 10;
    //float data[n][2];
    //vector<float> query(100,0.0f);
    // vector<vector<float>> data(n,vector<float>(100));
    // for(auto &i:data)
    // {
    //     for(auto &j:i) j = distr(rng);
    // }
    //
    // for(auto &i:data)
    // {
    //
    // }
    {
        FILE *file  = fopen("new_vector_data.dat","wb");
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<100;j++)
                {
                    float f = distr(rng);
                    fwrite(&f,sizeof(float),1,file);
                }
            }
        fclose(file);
    }

    return 0;
}
