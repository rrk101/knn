#include<bits/stdc++.h>
using namespace std;

const char *output_file_name = "new_vector_data.txt";

const int N = 10000000;

const float range_from  = -100.0f;
const float range_to    = 100.0f;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<float>  distr(range_from, range_to);



int main()
{

    {
        FILE *file  = fopen(output_file_name,"wb");
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
