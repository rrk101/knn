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

Measurements(baseline) --num_iters = 1

| file | tf-xla | tf-standard | mlir(without pass) |
| ---  | ---    | ---         | ---  |
| conv2d.py | 0.10638 | 0.01459 | 0.2936 |
| cast_conv.py | 0.09484 | 0.0190808 | 0.23932 |
| conv_transpose.py | 0.1523 | 0.02032 | 0.3551 |
| cast_transpose_conv.py | 0.10161 | 0.0226 | 0.3819 |
| conv_cast.py | 0.0929 | 0.0192 | 0.2534 |
| transpose_conv.py | 0.1178 | 0.0163 | 0.2728 |

Measurements(baseline) --num_iters = 100

| file | tf-xla | tf-standard | mlir(without pass) |
| ---  | ---    | ---         | ---  |
| conv2d.py | 0.8470 | 0.2555 | 24.3245 |
| cast_conv.py | 0.75833 | 0.60676 | 27.4252 |
| conv_transpose.py | 0.8580 | 0.21777 | 28.7019 |
| cast_transpose_conv.py | 0.699764 | 0.56004 | 27.334 |
| conv_cast.py | 0.7824 | 0.6150 | 28.277 |
| transpose_conv.py | 0.0929 | 0.0192 | 25.34 |





