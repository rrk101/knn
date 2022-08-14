#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const char* input_data = "new_vector_data.dat";
const char* output_results = "brute_force_output.txt";
const char* input_queries_file = "queries.txt";
const int N = 10000000,M = 100;
const float range_from  = -100.0f;
const float range_to    = 100.0f;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<float>  distr(range_from, range_to);


class cmp
{
public:
  bool operator() (const pair<int,float>& lhs,const pair<int,float> &rhs) const
  {
    return (lhs.second<rhs.second);
  }
};

/*void float_random_table(vector<vector<float>> &v,int n,int m)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            v[i][j] = distr(rng);
    }
}*/

float calc_euclidean_distance(vector<float> &p1,vector<float> &p2)
{
    //cout<<p1.size()<<" "<<p2.size()<<"\n";
    assert(p1.size()==p2.size());
    int n = p1.size();
    float ans=0.0f,tmp;
    for(int i=0;i<n;i++)
    {
        tmp = p1[i] - p2[i];
        ans += tmp*tmp;
    }
    return sqrt(ans);
}

bool cmp1(pair<int,float> a,pair<int,float> b)
{
    return a.second<b.second;
}

vector<vector<int>> calculate_by_sort(vector<vector<float>> &v,vector<vector<float>> &q)
{
    vector<vector<int>> ans;
    vector<long long int> time;
    for(auto &i:q)
    {
        auto start = high_resolution_clock::now();
        vector<pair<int,float>> tempv;
        for(int j=0;j<N;j++)
        {
            float distance = calc_euclidean_distance(v[j],i);
            tempv.push_back({j,distance});
        }
        sort(tempv.begin(),tempv.end(),cmp1);
        //for(auto &kl:tempv) cout<<kl.first<<" "<<kl.second<<"\n";
        //cout<<"\n\n";
        vector<int> tans;
        for(int op=0;op<10;op++) tans.push_back(tempv[op].first);

        ans.push_back(tans);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        time.push_back(1ll*duration.count());
    }
    sort(time.begin(),time.end());
    float avg = ((time[49]+time[50])*1.0f)/2.0f;
    cout<<"\nMedian time taken(sort brute force) :"<<avg/1000<<" ms\n";
    cout<<"\nMin time taken(sort brute force) :"<<time.front()/1000<<" ms\n";
    cout<<"\nMax time taken(sort brute force) :"<<time.back()/1000<<" ms\n";
    return ans;
}

vector<vector<int>> calculate_by_heap(vector<vector<float>> &v,vector<vector<float>> &q)
{
    vector<vector<int>> ans;
    vector<long long int> time;
    for(auto &i:q)
    {
        auto start = high_resolution_clock::now();
        priority_queue<pair<int,float>,vector<pair<int,float>>,cmp> pq;
        for(int j=0;j<N;j++)
        {
            float distance = calc_euclidean_distance(v[j],i);
            if(pq.size()<10)
                    pq.push({j,distance});
            else
            {
                auto a = pq.top();
                if(a.second>distance)
                {
                    pq.pop();
                    pq.push({j,distance});
                    assert(pq.size()==10);
                }
            }
        }
        vector<pair<int,float>> tempv;
        while(!pq.empty()) {tempv.push_back(pq.top());pq.pop();}
        sort(tempv.begin(),tempv.end(),cmp1);
        // for(auto &kl:tempv) cout<<kl.first<<" "<<kl.second<<"\n";
        // cout<<"\n\n\n";
        vector<int> tans;
        for(int op=0;op<10;op++) tans.push_back(tempv[op].first);
        ans.push_back(tans);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        time.push_back(1ll*duration.count());
    }
    sort(time.begin(),time.end());
    float avg = (time[49]+time[50])*1.0f/2.0f;
    cout<<"\nMedian time taken(heap brute force) :"<<avg/1000<<" ms\n";
    cout<<"\nMin time taken(heap brute force) :"<<time.front()/1000<<" ms\n";
    cout<<"\nMax time taken(heap brute force) :"<<time.back()/1000<<" ms\n";
    return ans;
}

void load_all_points(vector<vector<float>> &data)
{
    {
        FILE *file  = fopen(input_data,"rb");
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<M;j++)
                {
                    float f;
                    fread(&f,sizeof(float),1,file);
                    data[i][j] = f;
                }
            }
        fclose(file);
    }
    cout<<"All points loaded!\n";
}

void load_queries(vector<vector<float>> &queries)
{
    {
        freopen(input_queries_file,"r",stdin);
        int n;
        cin>>n;
        //cout<<n<<"\n";
        queries.resize(n);
        for(int i=0;i<n;i++)
        {
            queries[i].resize(M);
            for(int j=0;j<M;j++)
                cin>>queries[i][j];
        }
        //fclose(stdin);
    }
        cout<<"All queries loaded!\n";
}

int main()
{

    //priority_queue<pair<int,float>,vector<pair<int,float>>,cmp> pq;
    /*{
        vector<vector<float>> v(N,vector<float>(M)),queries(100,vector<float>(M));
        float_random_table(v,N,M);
        float_random_table(queries,100,M);
        vector<vector<int>> results1,results2;
        results1 = calculate_by_sort(v,queries);
        cout<<"here\n";
        results2 = calculate_by_heap(v,queries);
        if(results1==results2)
        {
            cout<<"The results are same!\n";
        }
        else
        {
            cout<<"The results are different!\n";
        }
    }*/
    vector<vector<float>> points(N,vector<float>(M)),
                        queries;
    load_all_points(points);
    load_queries(queries);
    //cout<<queries.size()<<" "<<queries.back().size()<<"\n";
    vector<vector<int>> results1,results2;
    //results1 = calculate_by_sort(points,queries);
    //cout<<"here\n";
    results2 = calculate_by_heap(points,queries);
    // if(results1==results2)
    // {
    //     cout<<"The results are same!\n";
    // }
    // else
    // {
    //     cout<<"The results are different!\n";
    // }
    //cout<<"HERE"<<results.size()<<" "<<results.back().size()<<"\n";
        {
            freopen(output_results,"w",stdout);
                for(auto &i:results2)
                {
                    for(auto &j:i) cout<<j<<" ";
                    cout<<"\n";
                }
        }


    return 0;
}
