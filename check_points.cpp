#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

//count no. of points in file
// should be 10**7 * 100
const int N = 10000000;
int main()
{
    int n=0;
    vector<float> v;
    auto start = high_resolution_clock::now();
    {
        FILE *file  = fopen("new_vector_data.dat","rb");
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<100;j++)
                {
                    float f;
                    fread(&f,sizeof(float),1,file);
                    v.push_back(f);
                }
            }
        fclose(file);
    }
    auto stop = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() / 1000<< " milliseconds\n";

    cout<<v.size()<<"\n";
    n = v.size();
    int k = 0;
    while(n)
    {
        ++k;
        n/=10;
    }
    cout<<"no. of digits: "<<k<<"\n";


    return 0;
}
