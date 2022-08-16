#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const char* input_data = "new_vector_data.dat";
const char* output_results = "brute_force_output.txt";
const char* input_queries_file = "queries.txt";
const float N = 10000000,M = 100;
const int range_from  = -100.0f;
const int range_to    = 100.0f;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_real_distribution<int>  distr(range_from, range_to);

typedef struct dim100 d100;

struct dim100{
        float coord[100];

};

inline void copy(d100 &a,vector<float> &v)
{
    for(int i=0;i<100;i++)
    {
        a.coord[i] = v[i];
    }
}
inline void copy(d100 &a,d100 &b)
{
    for(int i=0;i<100;i++)
    {
        a.coord[i] = b.coord[i];
    }
}



class cmp
{
public:
  inline bool operator() (const pair<int,float>& lhs,const pair<int,float> &rhs) const
  {
    return (lhs.second<rhs.second);
  }
};

/*void int_random_table(vector<vector<int>> &v,int n,int m)
{
    for(int i=0;i<n;i++)
    {
        for(float j=0;j<m;j++)
            v[i][j] = distr(rng);
    }
}*/

inline int calc_euclidean_distance(vector<float> &p1,vector<float> &p2)
{
    //cout<<p1.size()<<" "<<p2.size()<<"\n";
    assert(p1.size()==p2.size());
    int n = p1.size();
    int ans=0.0f,tmp;
    for(int i=0;i<n;i++)
    {
        tmp = (p1[i] - p2[i]);
        ans += tmp*tmp;
    }
    return (ans);
}

inline bool cmp1(pair<int,float> a,pair<int,float> b)
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
        vector<pair<int,int>> tempv;
        for(int j=0;j<N;j++)
        {
            int distance = calc_euclidean_distance(v[j],i);
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
        priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> pq;
        for(int j=0;j<N;j++)
        {
            int distance = calc_euclidean_distance(v[j],i);
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
        vector<pair<int,int>> tempv;
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
    float avg = ((time[49]+time[50])*1.0f)/2.0f;
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
vector<vector<float>> l1_norm_differences(100,vector<float>(10));
bool is_equal(vector<vector<d100>> &a,vector<vector<d100>> &b,float &difference)
{
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<10;j++)
        {
            int cur_diff=0.0f;
            for(int k=0;k<100;k++)
            {
                if(a[i][j].coord[k]!=b[i][j].coord[k])
                {
                    cur_diff+=abs(a[i][j].coord[k]-b[i][j].coord[k]);
                }
            }
            l1_norm_differences[i][j]=cur_diff;
            difference += cur_diff;
        }
    }
    if(difference>0.0f) return false;
    return true;
}
void print_row(int index)
{
    cout<<"\nL1 norm diff for row "<<index<<" : \n";
    for(int i=0;i<10;i++)
        cout<<l1_norm_differences[index][i]<<" ";
    cout<<"\n";
}
int calc_average(int index)
{
    float sum=0.0f;
    for(int i=0;i<10;i++)
        sum+=l1_norm_differences[index][i];
    return sum/10.0;
}
void analyse_l1_norm()
{
    float total_average=0.0f;
    for(int i=0;i<100;i++)
    {
        cout<<"\nFor Query "<<i+1<<" : ";
        print_row(i);
        cout<<"\nMAX diff : "<<*max_element(l1_norm_differences[i].begin(),l1_norm_differences[i].end())<<"\n";
        cout<<"MIN diff : "<<*min_element(l1_norm_differences[i].begin(),l1_norm_differences[i].end())<<"\n";
        cout<<"Average diff :"<<calc_average(i)<<"\n";
        total_average += calc_average(i);
    }
    cout<<"Average of all queries : "<<total_average/100.0<<"\n";
}
int main()
{

    //priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> pq;
    /*{
        vector<vector<int>> v(N,vector<int>(M)),queries(100,vector<int>(M));
        int_random_table(v,N,M);
        int_random_table(queries,100,M);
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
    vector<vector<int>> results2;
    //results1 = calculate_by_sort(points,queries);
    //cout<<"here\n";
    results2 = calculate_by_heap(points,queries);
    vector<vector<d100>> query_output(100),results1(100,vector<d100>(10));
    int l=0;
    for(auto &i:results2)
    {
        for(auto &j:i)
        {
            d100 temp;
            copy(temp,points[j]);
            query_output[l].push_back(temp);
        }
        ++l;
    }
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
            freopen(output_results,"r",stdin);
                for(auto &i:results1)
                {
                    for(auto &j:i)
                    {
                        d100 temp;
                        for(int k=0;k<100;k++) cin>>temp.coord[k];
                        copy(j,temp);
                    }
                }
                    // cout<<"\n";

        }
        float difference=0.0f;
        if(is_equal(query_output,results1,difference))
        //if(query_output==results1)
        {
            cout<<"The results are same!\n";
        }
        else
        {
            cout<<"The results are different!\n";
            cout<<"difference : "<<difference;
            analyse_l1_norm();
        }


    return 0;
}
