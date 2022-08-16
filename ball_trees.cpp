//#pragma once
#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;

const char* input_data = "new_vector_data.dat";
const char* output_results = "brute_force_output.txt";
const char* input_queries_file = "queries.txt";
const int N = 10000000;
const int M = 100;

int cur_dim = 0;


typedef struct dim100 d100;

struct dim100{
        float coord[100];

};
struct myclass {
  bool operator() (d100& i,d100& j) { return (i.coord[cur_dim]<j.coord[cur_dim]);}
} myobject;
vector<d100> v(N);
vector<d100> queries;

typedef struct max_heap max_heap;

class heap_cmp
{
public:
  bool operator() (const pair<float,int>& lhs,const pair<float,int> &rhs) const
  {
    return (lhs.first<rhs.first);
  }
};

struct max_heap{
        priority_queue<pair<float,int>,vector<pair<float,int>>,heap_cmp> pq;
        int get_top_point()
        {
            return pq.top().second;
        }
} init_heap;


struct node
{
    d100 pivot;
    float radius;
    int l,r;
    bool is_leaf;
    struct node *left,*right;
    node()
    :left(0),right(0),is_leaf(false)
    {}
};

typedef struct node node;
node *root = NULL;
float calc_euclidean_distance(d100 &p1,d100 &p2)
{
    float ans=0.0f,tmp;
    for(int i=0;i<100;i++)
    {
        tmp = (p1.coord[i] - p2.coord[i]);
        ans += tmp*tmp;
    }
    return (ans);
}

void copy(d100& a,d100 &b)
{
    for(int i=0;i<100;i++) a.coord[i] = b.coord[i];
}

node* construct_leaf(int l,int r)
{
    //since it's uniform distribution any dimension has a uniform spread
    sort(v.begin()+l,v.begin()+r+1,myobject);
    cur_dim = (cur_dim+1)%100;
    int median = (l+r+1)>>1;
    node *leaf = new node();
    if(leaf==NULL) {cout<<"Memory full!";return NULL;}
    copy(leaf->pivot,v[median]);
    float temp_r = 0.0f;
    for(int i=l;i<=r;i++)
    {
        float distance = calc_euclidean_distance(v[median],v[i]);
        temp_r = max(1.0f*distance,temp_r);
    }
    leaf->radius = temp_r;
    leaf->is_leaf=true;
    leaf->l = l;leaf->r = r;
    leaf->left = leaf->right = NULL;
    return leaf;
}
node* construct_ball_tree(int l,int r)
{
    if(r-l<=1000)
    {
        return construct_leaf(l,r);
    }
    sort(v.begin()+l,v.begin()+r+1,myobject);
    cur_dim = (cur_dim+1)%100;
    int median = (l+r+1)>>1;
    node *internal_node = new node();
    if(internal_node==NULL) {cout<<"Memory full!";return NULL;}
    copy(internal_node->pivot,v[median]);
    float temp_r = 0.0f;
    for(int i=l;i<=r;i++)
    {
        float distance = calc_euclidean_distance(v[median],v[i]);
        temp_r = max(1.0f*distance,temp_r);
    }
    internal_node->radius = temp_r;
    internal_node->left = construct_ball_tree(l,median-1);
    internal_node->right = construct_ball_tree(median+1,r);
    return internal_node;
}

void knn_search(d100 &q,node *ball)
{
    auto tope = init_heap.get_top_point();
    float d1=calc_euclidean_distance(q,ball->pivot);
    float d2=calc_euclidean_distance(q,v[tope]);
    if(d1-ball->radius>=d2)return;
    else if(ball->is_leaf)
    {
        int l_lim = ball->l,r_lim = ball->r;
        for(int i=l_lim;i<=r_lim;i++)
        {
            tope = init_heap.get_top_point();
            d1 = calc_euclidean_distance(q,v[i]);
            d2=calc_euclidean_distance(q,v[tope]);
            if(d1<d2)
            {
                init_heap.pq.pop();
                init_heap.pq.push({d1,i});
            }
        }
    }
    else
    {
        float a1,a2;
        auto lft= ball->left,rght = ball->right;
        a1 = calc_euclidean_distance(lft->pivot,q);
        a2 = calc_euclidean_distance(rght->pivot,q);
        if(a1<a2-rght->radius)
        {
            knn_search(q,lft);

        }
        else if(a2<a1-lft->radius)
        {
            knn_search(q,rght);
        }
        else
        {
            knn_search(q,lft);
            knn_search(q,rght);
        }
    }

}

void load_all_points()
{
    {
        FILE *file  = fopen(input_data,"rb");
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<M;j++)
                {
                    float f;
                    fread(&f,sizeof(float),1,file);
                    v[i].coord[j] = f;
                }
            }
        fclose(file);
    }
    cout<<"All points loaded!\n";
    //sort(v.begin(),v.end(),myobject);
}
void load_queries()
{
    {
        freopen(input_queries_file,"r",stdin);
        int n;
        cin>>n;
        //cout<<n<<"\n";
        queries.resize(n);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<M;j++)
                cin>>queries[i].coord[j];
        }
        //fclose(stdin);
    }
        cout<<"All queries loaded!\n";
}

void initialize_heap_for_a_query(d100& q)
{
    while(!init_heap.pq.empty()) init_heap.pq.pop();
    for(int i=0;i<10;i++)
    {
        float distance = calc_euclidean_distance(q,v[i]);
        init_heap.pq.push({distance,i});
    }
    assert(init_heap.pq.size()==10);
}

void calculate_by_ball_trees(vector<vector<int>> &results2)
{
    vector<long long int> time;
    int qno=0;
    for(auto& i:queries)
    {
        auto start = high_resolution_clock::now();
        initialize_heap_for_a_query(i);
        knn_search(i,root);
        vector<pair<float,int>> tempv;
        while(!init_heap.pq.empty())
        {tempv.push_back(init_heap.pq.top());init_heap.pq.pop();}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        time.push_back(1ll*duration.count());
        for(int i=9;i>=0;--i)
        {
            results2[qno].push_back(tempv[i].second);
            // for(int j=0;j<100;j++)
            // {
            //     cout<<tempv[i].second.coord[j]<<" ";
            // }
            // cout<<"\n";
        }
        qno++;

    }
    sort(time.begin(),time.end());
    float avg = ((time[49]+time[50])*1.0f)/2.0f;
    cout<<"\nMedian time taken(ball tree & heap) :"<<avg/1000<<" ms\n";
    cout<<"\nMin time taken(ball tree & heap) :"<<time.front()/1000<<" ms\n";
    cout<<"\nMax time taken(ball tree & heap) :"<<time.back()/1000<<" ms\n";
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
float calc_average(int index)
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
    load_all_points();
    load_queries();

    root = construct_ball_tree(0,N-1);
    vector<vector<int>> results2(M);
    calculate_by_ball_trees(results2);

    vector<vector<d100>> query_output(100),results1(100,vector<d100>(10));
    int l=0;
    for(auto &i:results2)
    {
        for(auto &j:i)
        {
            d100 temp;
            copy(temp,v[j]);
            query_output[l].push_back(temp);
        }
        ++l;
    }

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
