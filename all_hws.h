#include <iostream> 
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>

#define MAX_INT 2147483647
#define E 2.71828
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

using namespace std;

class Product_List{
    private:
        vector<int> products;
    public:
        Product_List();
        Product_List(int array[],int product_size);
        Product_List(vector<int> vector);
        void add_product(int value);
        void print_products();
        vector<int> get_vector();
};

class Orders{
    private:
        vector<Product_List> order_list;
    public:
        Orders();
        Orders(vector<Product_List> vector);
        void add_order(Product_List order);
        void print_orders();
        vector<int> return_sum_value();
        bool is_lower(vector<int> vect,int& difference);
        vector<Product_List> get_vector();
};

class Cases{
    private:
        vector<Product_List> case_list;
        vector<int> case_nums;
    public:
        Cases();
        Cases(vector<Product_List> vector);
        void add_case(Product_List the_case);
        void print_cases();
        vector<int> return_sum_value(vector<int> indexes);
        int get_case_list_size();
        vector<Product_List> get_vector();
        vector<int> get_vector_case_nums();
        void sort_by_order_sum(vector<int> order_sum);
        void sort_by_order_sum_absolute(vector<int> order_sum);
        void sort_by_bound(vector<int> order_sum);
        int find_difference_sum(int index,vector<int> order_sum);
        int find_difference_sum_absolute(int index,vector<int> order_sum);
};

class Algorithm{
    protected:
        vector<Cases> case_set_list;
        vector<Orders> order_set_list;
        vector<int> case_num;
        int test_index;
    public:
        Algorithm();
        Algorithm(int test_index);
        void set_test_index(int index);
        int get_test_index();
        void read_and_setup(string filename);
        double rng_zero_between_one();
};

class brute_force : public Algorithm{
    private:
        vector<int> min_indexes;
        int min_diff;
        void combination_process(int set_index,int array[], int data[], int start, int end, int index, int r);
        void wrapper_combination(int set_index,int size, int combination);
    public:
        brute_force();
        brute_force(int test_index);
        void brute_force_algorithm(int test_num);
};

class greedies_and_bb : public Algorithm{
    public:
        greedies_and_bb();
        vector<int> greedy_algorithm(int test_index,bool does_print);
        void greedy_algorithm2(int test_index);
        void branch_and_bound(int test_index);
};

class VNS : public Algorithm{
    /*private:
        vector< vector<int> > permutations;*/
    public:
        VNS();
        VNS(int test_index);
        vector<int> insert_neigborhood(vector<int> permutation,int feasible_solution_limit);
        vector <int> exchange_neigborhood(vector<int> permutation,int feasible_solution_limit);
        vector<int> insert_path_neigborhood(vector<int> permutation,int feasible_solution_limit);
        vector<int> exchange_path_neigborhood(vector<int> permutation,int feasible_solution_limit);
        vector<int> shake(int neighborhood,vector<int> initial_solution,int& feasible_solution_limit);
        vector<int> local_search(int neighborhood,vector<int> initial_solution,int& feasible_solution_limit);
        void VNS_algorithm();
   
};

class SA : public Algorithm{
    /*private:
        vector< vector<int> > permutations;*/
    public:
        SA();
        SA(int test_index);
        vector <int> exchange_neigborhood(vector<int> permutation,int feasible_solution_limit);
        vector<int> neighborhood_search(vector<int> initial_solution,int& feasible_solution_limit);
        void SA_algorithm();
};

class TS : public Algorithm{
    /*private:
        vector< vector<int> > permutations;*/
    public:
        TS();
        TS(int test_index);
        vector<vector<int> > create_candidate_list(vector<int> solution,int candidate_size,vector<vector<int> >& changed_index_list);
        int find_feasible_limit(vector<int> solution,int& difference);
        vector<int> create_random_initial_solution(int size);
        vector <int> exchange_neigborhood(vector<int> permutation,vector<int>& changed_index);
        void decrease_tabu_list(vector<int>& tabu_list);
        void TS_algorithm();
   
};

class GA : public Algorithm{
    /*private:
        vector< vector<int> > permutations;*/
    public:
        GA();
        GA(int test_index);
        bool is_there_value(int value,vector<int> vector);
        int find_feasible_limit(vector<int> solution,int& difference);
        int roulette_selection(vector<float> fitness_array);
        vector< vector<int> > random_population_generate(int population_size,int chromosome_size);
        vector< vector<int> > create_mating_pool(vector< vector<int> > population);
        vector<int> O1_process(vector<int> parent1,vector<int> parent2,bool is_child_1);
        void O1_crossover(vector<vector<int> >& population);
        void mutation(vector<vector<int> >& population);
        vector<int> find_best_solution(vector <vector<int> > population,int& result_feasible_limit,int& result_min_dif);
        vector <int> exchange_neigborhood(vector<int> permutation);
        void GA_algorithm();
   
};

class ACO : public Algorithm{
    private:
        int alpha;
        int beta;
        int t_max;
        vector<vector<float> > pheromone_matrix;
    public:
        ACO();
        ACO(int test_index,int alpha,int beta,int t_max);
        void initializepheromones(float initial_value,vector<int> initial_solution);
        float calculateNij(int case_num1,int case_num2,bool& is_feasible);
        vector<float> remaining_city_probs(int choosen_city,vector<int>remaining_cities);
        int roulette_selection(vector<float> fitness_array);
        int find_feasible_limit(vector<int> solution,int& difference);
        void ACO_algorithm();

};