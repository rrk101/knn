# knn
k-nearest neighbours


Programming language : c++
compiler : gcc version 8.1.0 (x86_64-win32-seh-rev0, Built by MinGW-W64 project)

Commands to execute :
1. g++ -std=c++11 generate_data_points.cpp -o generate_data_points.exe
Generates "new_vector_data.dat", default parameters are : N=10**7 and dim = 100, 
uniform real distribution(-100,100)

2. g++ -std=c++11 generate_query_points.cpp -o generate_query_points.exe
Generates "queries.txt", default parameters are : N = 100 and dim = 100,
uniform real distribution(-100,100)

3. g++ -std=c++11 brute_force_output_generation.cpp -o brute_force_output_generation.exe
Generates "brute_force_output.txt",contains 10 nearest neigbours for each query.

For Linear time solution:
With Integer approximation:
> g++ -std=c++11 -O3 brute_force_dist_opt_integer_approximated.cpp -o brute_force_dist_opt_integer_approximated.exe

Without Integer approximation:
>  g++ -std=c++11 -O3 brute_force_dist_opt.cpp -o brute_force_dist_opt.exe

For ball tree solution:
With Integer approximation:
> g++ -std=c++11 -O3 ball_tree_integer_approximated.cpp -o ball_tree_integer_approximated.exe

Without Integer approximation:
> g++ -std=c++11 -O3 ball_tree.cpp -o ball_tree.exe

| program | tf-xla | tf-standard | tf-mlir |
| ---     | ------ | ------------ | -------|
| 1,1    | 1,2 | 1,3 | 1,4 |






