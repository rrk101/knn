# knn
k-nearest neighbours

This is a O(nlogk) solution. The idea is to maintain a max-heap 'M', of size 'k', for each element 'vi' in the vector if distance(M.top(),q1)>distance(vi,q1),then  
M.pop() and M.insert(vi) else continue traversing.

Test :
1. g++ -std=c++11 generate_data_points.cpp
Generates "new_vector_data.dat", default parameters are : N=10**7 and dim = 100, 
uniform real distribution(-100,100)

2. g++ -std=c++11 generate_query_points.cpp
Generates "queries.txt", default parameters are : N = 100 and dim = 100,
uniform real distribution(-100,100)

3. g++ -std=c++11 brute_force_output_generation.cpp
Generates "brute_force_output.txt",contains 10 nearest neigbours for each query.





