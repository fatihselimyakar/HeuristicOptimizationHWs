#include "all_hws.h"

/* Global function that provides print vector */
void print_vector(vector<int> vect){
    for(int i=0;i<vect.size();++i){
        cout<<vect[i]<<" ";
    }
    cout<<endl;
}

/* Print solution appropriate format */
void print_solution(vector<int> vector,int feasible_limit){
    vector.resize(feasible_limit);
    sort(vector.begin(),vector.end());
    for(int i=0;i<vector.size();++i){
        cout<<vector[i]+1<<" ";
    }
    cout<<endl;
}

/* Class Product_List's methods */

/* Class Product_List's no parameter constructor */
Product_List::Product_List(){}

/* Class Product_List's array constructor */
Product_List::Product_List(int array[],int product_size){
    for(int i=0;i<product_size;++i){
        this->products.push_back(array[i]);
    }
}

/* Class Product_List's vector constructor */
Product_List::Product_List(vector<int> vector){
    this->products=vector;
}

/* Provides printing the products */
void Product_List::print_products(){
    for(int i=0;i<this->products.size();++i){
        cout<<"Product"<<i+1<<":"<<this->products[i]<<" ";
    }
    cout<<endl;
}

/* Adds product in the private product list vector */
void Product_List::add_product(int value){
    this->products.push_back(value);
}

/* Getter of the private product list vector */
vector<int> Product_List::get_vector(){
    return this->products;
}

/* Class Orders's methods */

/* Constructors of the Orders methods */
Orders::Orders(){}

Orders::Orders(vector<Product_List> vector){
    this->order_list=vector;
}

/* Affs new order in the order list */
void Orders::add_order(Product_List order){
    this->order_list.push_back(order);
}

/* Prints orders */
void Orders::print_orders(){
    for(int i=0;i<this->order_list.size();++i){
        cout<<"Order"<<i+1<<"-> ";
        this->order_list[i].print_products();
    }
}

/* Returns vector that includes the summation of the order list's product values */ 
vector<int> Orders::return_sum_value(){
    vector<int> ret_vec;
    for(int i=0;i<this->order_list.size();++i){
        for(int j=0;j<this->order_list[i].get_vector().size();++j){
            if(i==0){
                ret_vec.push_back(0);
            }
            ret_vec[j]+=this->order_list[i].get_vector()[j];
        }
    }
    return ret_vec;
}

/* Checks whether each element of the vector given as a parameter is greater than or equal to each element of the vector returned as the result of return_sum_value. If so it returns true, otherwise it returns false. */
bool Orders::is_lower(vector<int> vect,int& difference){
    vector<int> sum_of_order=this->return_sum_value();
    difference=0;
    bool ret_val=true;
    for(int i=0;i<vect.size();++i){
        if(sum_of_order[i]>vect[i]){
            ret_val = false;
        }
        difference+=(vect[i]-sum_of_order[i]);
    }
    
    return ret_val;
}

/* Gets the private vector of the orders */
vector<Product_List> Orders::get_vector(){
    return this->order_list;
}

/* Class Cases's methods */

/* Cases class's constructor methods */
Cases::Cases(){}

Cases::Cases(vector<Product_List> vector){
    this->case_list=vector;
}

/* Add case in the case_list */
void Cases::add_case(Product_List the_case){
    this->case_list.push_back(the_case);
    this->case_nums.push_back(case_nums.size()+1);
}

/* Prints the case_list's products */
void Cases::print_cases(){
    for(int i=0;i<this->case_list.size();++i){
        cout<<"Case"<<i+1<<"-> ";
        this->case_list[i].print_products();
    }
}

/* Returns vector that includes the summation of the case list's choosen product values */ 
vector<int> Cases::return_sum_value(vector<int> indexes){
    vector<int> ret_vec;

    for(int i=0;i<indexes.size();++i){
        for(int j=0;j<this->case_list[indexes[i]].get_vector().size();++j){
            if(i==0){
                ret_vec.push_back(0);
            }
            ret_vec[j]+=this->case_list[indexes[i]].get_vector()[j];
        }
    }

    return ret_vec;
}

/* Returs the case list size */
int Cases::get_case_list_size(){
    return case_list.size();
}

/* Returns the private case_list vector */
vector<Product_List> Cases::get_vector(){
    return this->case_list;
}

/* Returs the case_nums */
vector<int> Cases::get_vector_case_nums(){
    return this->case_nums;
}

/* Sorts the case_nums and case lists by looking sum */
void Cases::sort_by_order_sum(vector<int> order_sum){
    int i, j,n=this->case_list.size();  
    for (i = 0; i < n-1; i++){      
        for (j = 0; j < n-i-1; j++){
            if (this->find_difference_sum(j,order_sum) > this->find_difference_sum(j+1,order_sum)){
                Product_List temp=this->case_list[j];
                this->case_list[j]=this->case_list[j+1];
                this->case_list[j+1]=temp;

                int temp_num=this->case_nums[j];
                this->case_nums[j]=this->case_nums[j+1];
                this->case_nums[j+1]=temp_num;
            } 
        }   
    } 
}

/* Sorts the case_nums and case lists by looking sum's absolute */
void Cases::sort_by_order_sum_absolute(vector<int> order_sum){
    int i, j,n=this->case_list.size();  
    for (i = 0; i < n-1; i++){      
        for (j = 0; j < n-i-1; j++){
            if (this->find_difference_sum_absolute(j,order_sum) > this->find_difference_sum_absolute(j+1,order_sum)){
                Product_List temp=this->case_list[j];
                this->case_list[j]=this->case_list[j+1];
                this->case_list[j+1]=temp;

                int temp_num=this->case_nums[j];
                this->case_nums[j]=this->case_nums[j+1];
                this->case_nums[j+1]=temp_num;
                //cout<<"değişşş";
            } 
        }   
    } 
}

/* Sorts the case_nums and case lists by looking bound */
void Cases::sort_by_bound(vector<int> order_sum){
    int i, j,n=this->case_list.size(),bound,bound2;  
    for (i=0;i<n-1;i++){      
        for (j=0;j<n-i-1;j++){
            bound=this->find_difference_sum_absolute(j,order_sum);
            bound2=this->find_difference_sum_absolute(j+1,order_sum);
            if (bound > bound2){
                Product_List temp=this->case_list[j];
                this->case_list[j]=this->case_list[j+1];
                this->case_list[j+1]=temp;

                int temp_num=this->case_nums[j];
                this->case_nums[j]=this->case_nums[j+1];
                this->case_nums[j+1]=temp_num;
            } 
        }   
    } 
}

/* Finds difference of case sum and order sum's sum */
int Cases::find_difference_sum(int index,vector<int> order_sum){
    int sum=0;
    for(int i=0;i<this->case_list[index].get_vector().size();++i){
        sum+=this->case_list[index].get_vector()[i]-order_sum[i];
    }
    //cout<<sum<<endl;
    return sum;
}

/* Finds difference of case sum and order sum's absolute sum */
int Cases::find_difference_sum_absolute(int index,vector<int> order_sum){
    int sum=0;
    for(int i=0;i<this->case_list[index].get_vector().size();++i){
        sum+=abs(this->case_list[index].get_vector()[i]-order_sum[i]);
    }
    //cout<<sum<<endl;
    return sum;
}

/* Algorithm class's methods */

/* Constructors of the Algorithm class */
Algorithm::Algorithm(){ /* Intentionally empty */ }

Algorithm::Algorithm(int test_index){
    this->test_index=test_index;
}

/* It reads the test file. It adds the information it reads to the cases and orders vectors in the object. At the end of the function, there are cases and orders vectors with size as the number of tests. */
void Algorithm::read_and_setup(string filename){
    fstream file; 
    string str; 

    file.open(filename.c_str()); 
  
    int i=0;
    int line_counter=0;
    while (getline(file, str)) 
    { 
        if(str.compare("Cases:")==0){
            Cases cases;
            string case_string;
            while(getline(file,case_string)){
                if(case_string[0]!='['){
                    str=case_string;
                    break;
                }
                
                Product_List product_list;
                char c_str[999999];
                strcpy(c_str,case_string.c_str());
                char *token = strtok(c_str, "[ ,]"); 
                while (token != NULL) 
                { 
                    //printf("*%s\n", token); 
                    product_list.add_product(atoi(token));
                    token = strtok(NULL, "[ ,]"); 
                }
                cases.add_case(product_list);

                ++i;
            }
            case_set_list.push_back(cases);
            case_num.push_back(cases.get_case_list_size());
        }
        if(str.compare("Orders:")==0){
            Orders orders;
            string order_string;
            while(getline(file,order_string)){
                if(order_string[0]!='['){
                    str=order_string;
                    break;
                }

                Product_List product_list;
                char c_str[999999];
                strcpy(c_str,order_string.c_str());
                char *token = strtok(c_str, "[ ,]"); 
                while (token != NULL) 
                { 
                    //printf("*%s\n", token); 
                    product_list.add_product(atoi(token));
                    token = strtok(NULL, "[ ,]"); 
                }
                orders.add_order(product_list);

                ++i;
            }
            order_set_list.push_back(orders);
        }
        if(str.compare("---")==0){
            ++line_counter;
        }
        ++i;
    } 

    file.close();
}

/* Setter of the test index */
void Algorithm::set_test_index(int index){
    this->test_index=index;
}

/* Getter of the test index */
int Algorithm::get_test_index(){
    return this->test_index;
}

/* Returns the arbitrary number between 0-1 */
double Algorithm::rng_zero_between_one(){
    return ((double)(rand()%10000))/10000;
}

/*** HW1 ***/

/* Constructors of the Algorithm class */
brute_force::brute_force()
:Algorithm()
{
    min_diff=MAX_INT;
}

brute_force::brute_force(int test_index)
:Algorithm(test_index)
{
    min_diff=MAX_INT;
}

/* It constantly tries solutions with these combinations by finding all the combinations. When it subtracts the values of order products from all case products, it updates the minimums throughout the recursive calls. */
void brute_force::combination_process(int set_index,int array[], int data[], int left, int right, int index, int r){  
    vector<int> sum_indexes;
    if (index == r)  
    {  
        for (int j = 0; j < r; j++)  
            sum_indexes.push_back(data[j]);
        
        vector<int> cases_sum_vect=case_set_list[set_index].return_sum_value(sum_indexes);
        vector<int> order_sum_vect=order_set_list[set_index].return_sum_value();
        int sum_of_diff=0,dif;
        if(order_set_list[set_index].is_lower(cases_sum_vect,dif)){
            for(int i=0;i<cases_sum_vect.size();++i){
                sum_of_diff+=(cases_sum_vect[i]-order_sum_vect[i]);
            }
            if(sum_of_diff<min_diff){
                min_diff=sum_of_diff;
                min_indexes=sum_indexes;
            }
        }
        return;  
    }  
  
    for (int i=left;i<=right && right-i+1>=r-index; i++){  
        data[index] = array[i];  
        combination_process(set_index,array,data,i+1,right,index+1,r);  
    }  
}

/* The combination process function is the wrapper function. */
void brute_force::wrapper_combination(int set_index,int size, int combination){  
    int array[size];
    for(int i=0;i<size;++i){
        array[i]=i;
    }
    int data[combination];

    combination_process(set_index,array, data, 0, size-1, 0, combination);
}  

/* Brute force algorithm */
void brute_force::brute_force_algorithm(int test_num){
    for(int i=1;i<=case_num[test_num];++i){
        wrapper_combination(test_num,case_num[test_num],i);
    }
    
    for(int i=0;i<min_indexes.size();++i){
        ++min_indexes[i];
    }

    cout<<"The solution is:";
    print_vector(min_indexes);
}

/*** HW2 ***/
greedies_and_bb::greedies_and_bb():Algorithm(){}

/* Greedy Algorithm implementation 1 */
vector<int> greedies_and_bb::greedy_algorithm(int test_index,bool does_print){
    vector<int> order_sum = this->order_set_list[test_index].return_sum_value();
    this->case_set_list[test_index].sort_by_order_sum(order_sum);

    vector<int> sum;
    vector<int> choice;
    int dif;
    sum.resize(order_sum.size());
    for(int i=0;i<this->case_set_list[test_index].get_vector().size();++i){
        for(int j=0;j<order_sum.size();++j){
            sum[j]+=this->case_set_list[test_index].get_vector()[i].get_vector()[j];
        }
        choice.push_back(this->case_set_list[test_index].get_vector_case_nums()[i]);
        if(order_set_list[test_index].is_lower(sum,dif)){
            break;
        }
    }
    //Error calculating
    double total_error;
    for(int i=0;i<sum.size();++i){
        total_error+=(double)(sum[i]-order_sum[i])/(double)order_sum[i];
    }

    if(does_print){
        cout<<"(Test"<<test_index<<"-Greedy1)"<<"The solution is:";
        print_vector(choice);
        cout<<"Error:"<<total_error<<endl;
    }
    for(int i=0;i<choice.size();++i){
        choice[i]-=1;
    }
    return choice;

}

/* Greedy Algorithm implementation 2 */
void greedies_and_bb::greedy_algorithm2(int test_index){
    vector<int> order_sum = this->order_set_list[test_index].return_sum_value();
    this->case_set_list[test_index].sort_by_order_sum_absolute(order_sum);

    vector<int> sum;
    vector<int> choice;
    int dif;
    sum.resize(order_sum.size());
    for(int i=0;i<this->case_set_list[test_index].get_vector().size();++i){
        for(int j=0;j<order_sum.size();++j){
            sum[j]+=this->case_set_list[test_index].get_vector()[i].get_vector()[j];
        }
        choice.push_back(this->case_set_list[test_index].get_vector_case_nums()[i]);
        if(order_set_list[test_index].is_lower(sum,dif)){
            break;
        }
    }

    //Error calculating
    double total_error;
    for(int i=0;i<sum.size();++i){
        total_error+=(double)(sum[i]-order_sum[i])/(double)order_sum[i];
    }

    cout<<"(Test"<<test_index<<"-Greedy2)"<<"The solution is:";
    print_vector(choice);
    cout<<"Error:"<<total_error<<endl;

}

/* Branch and Bound implementation */
void greedies_and_bb::branch_and_bound(int test_index){
    vector<int> sum,choice,order_sum = this->order_set_list[test_index].return_sum_value();
    int dif;
    this->case_set_list[test_index].sort_by_bound(order_sum);
    sum.resize(order_sum.size());
    for(int i=0;i<this->case_set_list[test_index].get_vector().size();++i){
        for(int j=0;j<order_sum.size();++j){
            sum[j]+=this->case_set_list[test_index].get_vector()[i].get_vector()[j];
        }
        choice.push_back(this->case_set_list[test_index].get_vector_case_nums()[i]);
        if(order_set_list[test_index].is_lower(sum,dif)){
            cout<<"(Test"<<test_index<<"-BB)"<<"The solution is:";
            print_vector(choice);
            break;
        }
    }
}

/*** HW3 ***/

/* VNS Constructors */
VNS::VNS():Algorithm(){ }

VNS::VNS(int test_index):Algorithm(test_index){}

/* Sets an index from the indexes above and below the feasible_solution_limit. Inserts the upper index value into the lower index. */
vector<int> VNS::insert_neigborhood(vector<int> permutation,int feasible_solution_limit){
    /* Finds the lower and upper bound randomly */
    int lower_bound=rand()%feasible_solution_limit;
    int upper_bound;
    do{
        upper_bound=rand()%permutation.size();
    }
    while(upper_bound<feasible_solution_limit);

    /*  Insert */
    int value=permutation[upper_bound];
    permutation.erase(permutation.begin()+upper_bound);
    permutation.insert(permutation.begin()+lower_bound,value);

    return permutation;
}

/* Sets an index from the indexes above and below the feasible_solution_limit. Exchange the upper index value into the lower index value. */
vector <int> VNS::exchange_neigborhood(vector<int> permutation,int feasible_solution_limit){
    /* Finds the lower and upper bound randomly */
    int lower_bound=rand()%feasible_solution_limit;
    int upper_bound;
    do{
        upper_bound=rand()%permutation.size();
    }
    while(upper_bound<feasible_solution_limit);

    /* Exchange */
    int value=permutation[upper_bound];
    permutation[upper_bound]=permutation[lower_bound];
    permutation[lower_bound]=value;

    return permutation;
}

/* Sets an index from the indexes above and below the feasible_solution_limit. Insert the upper index value to end of the indexes path into the lower index. */
vector<int> VNS::insert_path_neigborhood(vector<int> permutation,int feasible_solution_limit){
    /* Finds the lower and upper bound randomly */
    int lower_bound=rand()%feasible_solution_limit;
    int upper_bound;
    do{
        upper_bound=rand()%permutation.size();
    }
    while(upper_bound<feasible_solution_limit);

    /* Creates the path */
    vector<int>insert_vector;
    for(int i=upper_bound;i<permutation.size();++i){
        insert_vector.push_back(permutation[i]);
    }
    /* Erases the path from permutation */
    int loop_number=permutation.size();
    for(int i=upper_bound;i<loop_number;++i){
        permutation.erase(permutation.begin()+upper_bound);
    }
    
    /* Inserts the path into permutation's lower bound */
    permutation.insert(permutation.begin()+lower_bound,insert_vector.begin(),insert_vector.end());

    return permutation;
}

/* Sets an index from the indexes above and below the feasible_solution_limit. Exchange the upper index value to end of the indexes path into the lower index. */
vector<int> VNS::exchange_path_neigborhood(vector<int> permutation,int feasible_solution_limit){
    /* Finds the lower and upper bound randomly */
    int lower_bound=rand()%feasible_solution_limit;
    int upper_bound;
    do{
        upper_bound=rand()%permutation.size();
    }
    while(upper_bound<feasible_solution_limit);

    /* Determines the exchange number and one by one changes starts from lower_bound and upper bound */
    int exchange_number=MIN(feasible_solution_limit-lower_bound,permutation.size()-upper_bound);
    for(int i=0;i<exchange_number;++i){
        int temp=permutation[lower_bound+i];
        permutation[lower_bound+i]=permutation[upper_bound+i];
        permutation[upper_bound+i]=temp;
    }

    return permutation;

}

/* It determines the feasible limit by creating a new permutation by applying the insert path or exchange path method according to the Neighborhood. */
vector<int> VNS::shake(int neighborhood,vector<int> initial_solution,int& feasible_solution_limit){
    vector<int> changed_solution;
    if(neighborhood==0){
        changed_solution=insert_path_neigborhood(initial_solution,feasible_solution_limit);
    }
    else if(neighborhood==1){
        changed_solution=exchange_path_neigborhood(initial_solution,feasible_solution_limit);
    }

    /* Finds the new feasible_solution_limit */
    vector<int> indexes;
    int new_feasible_solution_limit=0;
    int difference;
    for(int i=0;i<changed_solution.size();++i){
        indexes.push_back(i);
        ++new_feasible_solution_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            feasible_solution_limit=new_feasible_solution_limit;
            break;
        }
    }
    return changed_solution;
}

/* It determines the feasible limit by creating a new permutation by applying the insert or exchange method according to the Neighborhood. */
vector<int> VNS::local_search(int neighborhood,vector<int> initial_solution,int& feasible_solution_limit){
    vector<int> changed_solution;
    if(neighborhood==0){
        changed_solution=insert_neigborhood(initial_solution,feasible_solution_limit);
    }
    else if(neighborhood==1){
        changed_solution=exchange_neigborhood(initial_solution,feasible_solution_limit);
    }

    /* Finds the new feasible_solution_limit */
    vector<int> indexes;
    int new_feasible_solution_limit=0;
    int difference;
    for(int i=0;i<changed_solution.size();++i){
        indexes.push_back(changed_solution[i]);
        ++new_feasible_solution_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            feasible_solution_limit=new_feasible_solution_limit;
            break;
        }
    }
    return changed_solution;
}

/* Applies the Variable Neighborhood Search algorithm */
void VNS::VNS_algorithm(){
    int t_max=1000;
    int k,k_max=2;
    int feasible_limit=0;
    vector<int> initial_solution;
    vector<int> indexes;
    int difference;
    /* Creates an initial solution */
    for(int i=0;i<case_set_list[test_index].get_vector().size();++i){
        initial_solution.push_back(i);
    }
    for(int i=0;i<initial_solution.size();++i){
        indexes.push_back(initial_solution[i]);
        ++feasible_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            break;
        }
    }
    /* Repeat the following sequence until the stopping condition met. */
    for(int t=0;t<t_max;++t){
        /* Repeat the follwing steps until k = k_max */
        k=0;
        while(k<k_max){
            int changed_feasible_limit=feasible_limit;
            /* Shaking */
            vector<int>shake_res=shake(k,initial_solution,changed_feasible_limit);
            /* Local Search */
            vector<int>local_res=local_search(k,shake_res,changed_feasible_limit);

            /* Determines the new solution's and old solution's feasible solution indexes */
            vector<int> new_solution_indexes;
            for(int i=0;i<changed_feasible_limit;++i){
                new_solution_indexes.push_back(local_res[i]);
            }
            vector<int> old_solution_indexes;
            for(int i=0;i<feasible_limit;++i){
                old_solution_indexes.push_back(initial_solution[i]);
            }

            /* Finds the sum of product values by looking new and old dolutions */
            vector<int> sum_of_old_solution=case_set_list[test_index].return_sum_value(old_solution_indexes);
            vector<int> sum_of_new_solution=case_set_list[test_index].return_sum_value(new_solution_indexes);
            int old_difference=0;
            int new_difference=0;
            /* Compares and if feasible then changes the initial solution, else increases the k value */
            if(order_set_list[test_index].is_lower(sum_of_new_solution,new_difference)){
                if(order_set_list[test_index].is_lower(sum_of_old_solution,old_difference)){
                    // Move or not
                    if(new_difference<=old_difference){
                        initial_solution=local_res;
                        feasible_limit=changed_feasible_limit;
                        k=0;
                    }
                    else{
                        ++k;
                    }
                }
            }
            else{
                ++k;
            }           
        }
    }

    /* prints the solution that found */
    cout<<"(Test "<<test_index<<") The solution is:";
    print_solution(initial_solution,feasible_limit);

}

/** HW4 **/

/* SA Class constructors */
SA::SA():Algorithm(){ }

SA::SA(int test_index):Algorithm(test_index){}

/* Sets an index from the indexes above and below the feasible_solution_limit. Exchange the upper index value into the lower index value. */
vector <int> SA::exchange_neigborhood(vector<int> permutation,int feasible_solution_limit){
    /* Finds the lower and upper bound randomly */
    int lower_bound=rand()%feasible_solution_limit;
    int upper_bound;
    do{
        upper_bound=rand()%permutation.size();
    }
    while(upper_bound<feasible_solution_limit);

    /* Exchange */
    int value=permutation[upper_bound];
    permutation[upper_bound]=permutation[lower_bound];
    permutation[lower_bound]=value;

    return permutation;
}

/* It determines the feasible limit by creating a new permutation by applying the insert or exchange method according to the Neighborhood. */
vector<int> SA::neighborhood_search(vector<int> initial_solution,int& feasible_solution_limit){
    vector<int> changed_solution;
    changed_solution=exchange_neigborhood(initial_solution,feasible_solution_limit);

    /* Finds the new feasible_solution_limit */
    vector<int> indexes;
    int new_feasible_solution_limit=0;
    int difference;
    for(int i=0;i<changed_solution.size();++i){
        indexes.push_back(changed_solution[i]);
        ++new_feasible_solution_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            feasible_solution_limit=new_feasible_solution_limit;
            break;
        }
    }
    return changed_solution;
}

/* Applies the Simulated Annealing algorithm */
void SA::SA_algorithm(){
    int t_max=100;
    int k,k_max=50;
    int feasible_limit=0;
    int bests_feasible_limit=0;
    int bests_difference=99999999;
    vector<int> initial_solution;
    vector<int> best_solution;
    vector<int> indexes;
    vector<int> temperature_indexes;
    int difference;
    int total_difference;
    /* Creates an initial solution */
    for(int i=0;i<case_set_list[test_index].get_vector().size();++i){
        initial_solution.push_back(i);
    }
    for(int i=0;i<initial_solution.size();++i){
        indexes.push_back(initial_solution[i]);
        ++feasible_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            break;
        }
    }
    /* Finds the all of the cases summation's waste score and it determines the temperature value */
    for(int i=0;i<initial_solution.size();++i){
        temperature_indexes.push_back(initial_solution[i]);
    }
    order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(temperature_indexes),total_difference);
    /* Temperature value */
    double temperature=(double)total_difference;
    /* Repeat the following sequence until the stopping condition met. */
    for(int t=0;t<t_max;++t){
        /* Repeat the follwing steps until k = k_max */
        k=0;
        while(k<k_max){
            int changed_feasible_limit=feasible_limit;
            /* Neighborhood Search */
            vector<int>nbh_res=neighborhood_search(initial_solution,changed_feasible_limit);

            /* Determines the new solution's and old solution's feasible solution indexes */
            vector<int> new_solution_indexes;
            for(int i=0;i<changed_feasible_limit;++i){
                new_solution_indexes.push_back(nbh_res[i]);
            }
            vector<int> old_solution_indexes;
            for(int i=0;i<feasible_limit;++i){
                old_solution_indexes.push_back(initial_solution[i]);
            }

            /* Finds the sum of product values by looking new and old solutions */
            vector<int> sum_of_old_solution=case_set_list[test_index].return_sum_value(old_solution_indexes);
            vector<int> sum_of_new_solution=case_set_list[test_index].return_sum_value(new_solution_indexes);
            int old_difference=0;
            int new_difference=0;
            /* Finds the suitability and waste scores */
            bool is_suitable_new_solution=order_set_list[test_index].is_lower(sum_of_new_solution,new_difference);
            bool is_suitable_old_solution=order_set_list[test_index].is_lower(sum_of_old_solution,old_difference);
      
            /* If the new solution is the best then changed the best solution */
            if(new_difference<bests_difference){
                bests_difference=new_difference;
                bests_feasible_limit=changed_feasible_limit;
                best_solution=nbh_res;
            }
            /* if new solution is better than before then changes it */
            if(is_suitable_new_solution && is_suitable_old_solution && (new_difference<=old_difference)){
                initial_solution=nbh_res;
                feasible_limit=changed_feasible_limit;
            }
            /* Also randomly it can change still */
            else if(rng_zero_between_one()<pow(E,((double)(old_difference-new_difference))/temperature)){
                initial_solution=nbh_res;
                feasible_limit=changed_feasible_limit;
            }
            ++k;
        }
        temperature*=0.9;
    }

    /* prints the solution that found */
    cout<<"(Test "<<test_index<<") The solution is:";
    print_solution(best_solution,bests_feasible_limit);

}

/** HW5 **/

/* Tabu Search's consructor */
TS::TS():Algorithm(){ }

TS::TS(int test_index):Algorithm(test_index){}

/* Creates candidate list using the exchange neighbourhood */
vector<vector<int> > TS::create_candidate_list(vector<int> solution,int candidate_size,vector<vector<int> >& changed_value_list){
    vector<vector<int> > candidate_list;
    
    for(int i=0;i<candidate_size;++i){
        vector<int> changed_value;
        candidate_list.push_back(exchange_neigborhood(solution,changed_value));
        changed_value_list.push_back(changed_value);
    }

    return candidate_list;
}

/* Finds the exist solution's feasibility limit */
int TS::find_feasible_limit(vector<int> solution,int& difference){
    vector<int> indexes;
    int feasible_limit=0;
    for(int i=0;i<solution.size();++i){
        indexes.push_back(solution[i]);
        ++feasible_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            break;
        }
    }
    return feasible_limit;
}

/* Creates random initial solution */
vector<int> TS::create_random_initial_solution(int size){
    vector<int> solution;
    int i;
    for(i=0;i<size;++i){
        solution.push_back(i);
    }
    for(i=0;i<size;++i){
        int random_index=rand()%size;

        int temp=solution[i];
        solution[i]=solution[random_index];
        solution[random_index]=temp;
    }

    return solution;
}

/* Exchange the randomized upper index value into the lower index value. */
vector <int> TS::exchange_neigborhood(vector<int> permutation,vector<int>& changed_value){
    /* Finds the lower and upper bound randomly */
    int lower_bound=rand()%permutation.size();
    int upper_bound;
    do{
        upper_bound=rand()%permutation.size();
    }
    while(upper_bound==lower_bound);

    /* Exchange */
    int value=permutation[upper_bound];
    permutation[upper_bound]=permutation[lower_bound];
    permutation[lower_bound]=value;

    changed_value.push_back(permutation[upper_bound]);
    changed_value.push_back(permutation[lower_bound]);

    return permutation;
}

/* Decreases the count of tabu tenures */
void TS::decrease_tabu_list(vector<int>& tabu_list){
    for(int i=0;i<tabu_list.size();++i){
        if(tabu_list[i]!=0){
            --tabu_list[i];
        }
    }
}

/* Implies the Tabu Search Algorithm */
void TS::TS_algorithm(){
    /* Hyper parameters */
    int termination_condition=100;
    int candidate_size=50;
    int tabu_tenure=7;

    /* Creates initial solution and determines the feasible limit */
    vector<int> initial_solution=create_random_initial_solution(case_set_list[test_index].get_vector().size());
    int difference;
    int feasible_limit=find_feasible_limit(initial_solution,difference);

    /* Creates the tabu list and initializes the 0 */
    vector<int> tabu_list;
    for(int i=0;i<case_set_list[test_index].get_vector().size();++i){
        tabu_list.push_back(0);
    }

    /* Solution's variables */
    vector<int> best_solution;
    int bests_feasible_limit;
    int bests_min_solution_dif=MAX_INT;

    /* TS for loop */
    vector<vector<int> > candidate_list;
    vector<vector<int> > exchanged_list;
    for(int i=0;i<termination_condition;++i){

        candidate_list=create_candidate_list(initial_solution,candidate_size,exchanged_list);
        int local_difference=-1,local_feasible_limit=-1;
        int local_min_difference=MAX_INT,local_best_index=-1,local_best_feasible_limit=-1;

        int local_not_tabu_min_difference=MAX_INT,local_not_tabu_index=-1,local_not_tabu_min_feasible_limit=-1;

        /* Traverses the candidate list */
        for(int j=0;j<candidate_size;++j){
            local_feasible_limit=find_feasible_limit(candidate_list[j],local_difference);
            /* Find local best in candidate list */
            if(local_difference<local_min_difference){
                local_min_difference=local_difference;
                local_best_index=j;
                local_best_feasible_limit=local_feasible_limit;
            }
            /* If this is not tabu */
            if(tabu_list[exchanged_list[j][0]]==0 && tabu_list[exchanged_list[j][1]]==0){
                if(local_not_tabu_min_difference>local_difference){
                    local_not_tabu_min_difference=local_difference;
                    local_not_tabu_index=j;
                    local_not_tabu_min_feasible_limit=local_feasible_limit;
                }
            }
        }

        /* Decrease the tabu tenures */
        decrease_tabu_list(tabu_list);

        /* Aspiration criteria (If finds best) */
        if(local_min_difference<bests_min_solution_dif){
            best_solution=candidate_list[local_best_index];
            bests_feasible_limit=local_best_feasible_limit;
            bests_min_solution_dif=local_min_difference;
            
            initial_solution=best_solution;
            feasible_limit=bests_feasible_limit;
            difference=local_min_difference;

            tabu_list[exchanged_list[local_best_index][0]]=tabu_tenure;
            tabu_list[exchanged_list[local_best_index][1]]=tabu_tenure;
        }
        /* local best that have not tabu criteria in candidate list */
        else if(local_not_tabu_index!=-1){
            initial_solution=candidate_list[local_not_tabu_index];
            feasible_limit=local_not_tabu_min_feasible_limit;
            difference=local_not_tabu_min_difference;

            tabu_list[exchanged_list[local_not_tabu_index][0]]=tabu_tenure;
            tabu_list[exchanged_list[local_not_tabu_index][1]]=tabu_tenure;
        }
        /* Aspiration criteria (If all of candidate list are tabu)*/
        else{
            initial_solution=candidate_list[local_best_index];
            feasible_limit=local_feasible_limit;
            difference=local_min_difference;

            tabu_list[exchanged_list[local_best_index][0]]=tabu_tenure;
            tabu_list[exchanged_list[local_best_index][1]]=tabu_tenure;
        }
    }

    cout<<"(Test "<<test_index<<") The solution is:";
    print_solution(best_solution,bests_feasible_limit);

}
/*** HW6 **/

/* Genetic Algorithm constructors */
GA::GA():Algorithm(){ }

GA::GA(int test_index):Algorithm(test_index){}

/* find feasible limit and calculates the difference and returns these */
int GA::find_feasible_limit(vector<int> solution,int& difference){
    vector<int> indexes;
    int feasible_limit=0;
    for(int i=0;i<solution.size();++i){
        indexes.push_back(solution[i]);
        ++feasible_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            break;
        }
    }
    return feasible_limit;
}

/* Random population generates and returns it */
vector< vector<int> > GA::random_population_generate(int population_size,int chromosome_size){
    int i,j;
    vector< vector<int> > res_vector;
    for(i=0;i<population_size;++i){
        /* fills the temp vector 0..n */
        vector<int> temp_vector;
        for(j=0;j<chromosome_size;++j){
            temp_vector.push_back(j);
        }

        /* mix the temp vector by randomly changed */
        for(j=0;j<chromosome_size;++j){
            int random_index=rand()%chromosome_size;

            int temp=temp_vector[j];
            temp_vector[j]=temp_vector[random_index];
            temp_vector[random_index]=temp;
        }

        /* adds the temp vector in the main vector */
        res_vector.push_back(temp_vector);
    }

    return res_vector;
}

/* Performs the roulette wheel selection by looking the objective fuction */
int GA::roulette_selection(vector<float> fitness_array){
    float upper_bound=0,lower_bound=0,random=rng_zero_between_one(),total_fitness_value=0; 
    int i;
    for(i=0;i<fitness_array.size();++i){
        total_fitness_value+=fitness_array[i];
    }
    random*=total_fitness_value;

    for(i=0;i<fitness_array.size();++i){
        if(i==0){
            upper_bound=fitness_array[0];
            lower_bound=0;
        }
        else{
            lower_bound+=fitness_array[i-1];
            upper_bound+=fitness_array[i];
        }

        if(random>=lower_bound && random<=upper_bound){
            return i;
        }
        
    }
    return i;
}

/* Creates the mating pool by selecting in population using ruleth wheel selection */
vector< vector<int> > GA::create_mating_pool(vector< vector<int> > population){
    int i;
    vector<int> difference_list;
    vector<float> fitness_list;
    int total_dif=0;
    for(i=0;i<population.size();++i){
        int difference;
        find_feasible_limit(population[i],difference);
        difference_list.push_back(difference);
        total_dif+=difference_list[i];
    }

    for(i=0;i<difference_list.size();++i){
        fitness_list.push_back((float)total_dif/(float)difference_list[i]);
    }

    vector< vector<int> > ret_vec;
    for(i=0;i<population.size();++i){
        int index=roulette_selection(fitness_list);
        ret_vec.push_back(population[index]);
    }

    return ret_vec;

}

/* if the value is exist in vector then returns true, else return false */
bool GA::is_there_value(int value,vector<int> vector){
    for(int i=0;i<vector.size();++i){
        if(vector[i]==value){
            return true;
        }
    }
    return false;
}

/* Performs the order 1 process for parent1 and parent2 to create child */
vector<int> GA::O1_process(vector<int> parent1,vector<int> parent2,bool is_child_1){
    vector<int> child_vector;
    int random_index=rand()%parent1.size();
    int random_size=rand()%(parent1.size()-random_index);
    int finish_index;
    for(int i=0;i<parent1.size();++i){
        if(i<random_index){
            child_vector.push_back(-1);
        }
        else if(i==random_index){
            int j;
            for(j=random_index;j<=random_index+random_size;++j){
                /* Seperates the child1 or child2 creation */
                if(is_child_1){
                    child_vector.push_back(parent1[j]);
                }
                else{
                    child_vector.push_back(parent2[j]);
                }
            }
            i=j-1;
            finish_index=j;
        }
        else{
            child_vector.push_back(-1);
        }
        
    }

    finish_index%=parent2.size();
    vector<int> missing_values;
    for(int i=finish_index,counter=0;counter<parent2.size();++i,++counter){
        /* Seperates the child1 or child2 creation */
        if(is_child_1){
            if(is_there_value(parent2[i],child_vector)==false){
                missing_values.push_back(parent2[i]);
            }
        }
        else{
            if(is_there_value(parent1[i],child_vector)==false){
                missing_values.push_back(parent1[i]);
            }
        }        
        if(i==parent2.size()-1){
            i=-1;
        }
    }
    
    for(int i=finish_index,j=0,counter=0;counter<child_vector.size();++i,++counter){
        if(child_vector[i]==-1){
            child_vector[i]=missing_values[j];
            ++j;
        }
        if(i==child_vector.size()-1){
            i=-1;
        }
    }

    return child_vector;

}

/* Applies O1_crossover for all of chromosomes in the population */
void GA::O1_crossover(vector<vector<int> >& population){
    double random_number;
    for(int i=0;i<population.size();i+=2){
        random_number=rng_zero_between_one();
        if(random_number<=0.8){
            vector<int> child1=O1_process(population[i],population[i+1],true);
            vector<int> child2=O1_process(population[i],population[i+1],false);
            population[i]=child1;
            population[i+1]=child2;
        }
        
    }
}

/* Applies exchange neighbourhood for all of chromosomes in the population */
void GA::mutation(vector<vector<int> >& population){
    for(int i=0;i<population.size();++i){
        population[i]=exchange_neigborhood(population[i]);
    }
}

/* finds best solution in the population */
vector<int> GA::find_best_solution(vector <vector<int> > population,int& result_feasible_limit,int& result_min_dif){
    int min_dif=MAX_INT;
    int difference,feasible_limit,bests_feasible_limit,bests_index;
    for(int i=0;i<population.size();++i){
        feasible_limit=find_feasible_limit(population[i],difference);  
        if(difference<min_dif){
            min_dif=difference;
            bests_feasible_limit=feasible_limit;
            bests_index=i;
        }
    }

    result_feasible_limit=bests_feasible_limit;
    result_min_dif=min_dif;

    return population[bests_index];
}

/* Random exchange for mutation */
vector <int> GA::exchange_neigborhood(vector<int> permutation){
    /* Select randoms */
    int rand1=rand()%permutation.size(),rand2;
    do{
        rand2=rand()%permutation.size();
    }while(rand1==rand2);

    /* Exchange */
    int temp=permutation[rand1];
    permutation[rand1]=permutation[rand2];
    permutation[rand2]=temp;

    return permutation;
}

/* Genetic Algorithm Implementation */
void GA::GA_algorithm(){
    int termination_criteria=100;
    int population_size=20;
    vector<vector<int> > population=random_population_generate(population_size,case_set_list[test_index].get_vector().size());
    int best_feasible_limit,best_min_dif=MAX_INT;
    vector<int> solution;
    for(int i=0;i<termination_criteria;++i){
        vector<vector<int> > mating_pool=create_mating_pool(population);
        O1_crossover(mating_pool);
        mutation(mating_pool);
        int local_best_feasible_limit,local_best_min_dif;
        vector<int> local_best=find_best_solution(mating_pool,local_best_feasible_limit,local_best_min_dif);
        
        if(local_best_min_dif<best_min_dif){
            best_min_dif=local_best_min_dif;
            best_feasible_limit=local_best_feasible_limit;
            solution=local_best;
        }
        population=mating_pool;
    }
    
    /* prints the solution that found */
    cout<<"(Test "<<test_index<<") The solution is:";
    print_solution(solution,best_feasible_limit);
    
}

ACO::ACO(){ 
    alpha=1;
    beta=1;
    t_max=10;
}

ACO::ACO(int test_index,int alpha,int beta,int t_max){
    this->test_index=test_index;
    this->alpha=alpha;
    this->beta=beta;
    this->t_max=t_max;
}

float ACO::calculateNij(int case_num1,int case_num2,bool& is_lower){
    int difference;
    vector<int> indexes;
    indexes.push_back(case_num1);
    indexes.push_back(case_num2);

    is_lower=order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference);
    //cout<<" "<<case_num1<<" "<<case_num2<<" "<<difference<<endl;
    
    return 1.0/fabs(difference);

}

void ACO::initializepheromones(float initial_value,vector<int> initial_solution){
    for(int i=0;i<case_set_list[test_index].get_vector().size();++i){
        vector<float> temp_vector;
        for(int j=0;j<case_set_list[test_index].get_vector().size();++j){
            temp_vector.push_back(0.005);
        }
        pheromone_matrix.push_back(temp_vector);
    }
    for(int i=0;i<initial_solution.size()-1;++i){
        pheromone_matrix[initial_solution[i]][initial_solution[i+1]]=0.005+initial_value;
    }
    /*for(int i=0;i<case_set_list[test_index].get_vector().size();++i){
        for(int j=0;j<case_set_list[test_index].get_vector().size();++j){
            cout<<pheromone_matrix[i][j]<<" ";
        }
        cout<<endl;
    }*/
}


/* Performs the roulette wheel selection by looking the objective fuction */
int ACO::roulette_selection(vector<float> fitness_array){
    float upper_bound=0,lower_bound=0,random=rng_zero_between_one(),total_fitness_value=0; 
    int i;
    for(i=0;i<fitness_array.size();++i){
        total_fitness_value+=fitness_array[i];
    }
    random*=total_fitness_value;

    for(i=0;i<fitness_array.size();++i){
        if(i==0){
            upper_bound=fitness_array[0];
            lower_bound=0;
        }
        else{
            lower_bound+=fitness_array[i-1];
            upper_bound+=fitness_array[i];
        }

        if(random>=lower_bound && random<=upper_bound){
            return i;
        }
        
    }
    return i;
}

int ACO::find_feasible_limit(vector<int> solution,int& difference){
    vector<int> indexes;
    int feasible_limit=0;
    for(int i=0;i<solution.size();++i){
        indexes.push_back(solution[i]);
        ++feasible_limit;
        if(order_set_list[test_index].is_lower(case_set_list[test_index].return_sum_value(indexes),difference)){
            break;
        }
    }
    return feasible_limit;
}

vector<float> ACO::remaining_city_probs(int choosen_city,vector<int>remaining_cities){
    float denominator,nominator;
    bool temp_bool,is_lower;
    vector<float> probs;
    for(int l=0;l<remaining_cities.size();++l){
        denominator=0;
        nominator=pow(pheromone_matrix[choosen_city][remaining_cities[l]],this->alpha)*pow(calculateNij(choosen_city,remaining_cities[l],temp_bool),this->beta);
        //cout<<nominator<<"nom"<<endl;
        for(int j=0;j<remaining_cities.size();++j){
            denominator+=pow(pheromone_matrix[choosen_city][remaining_cities[j]],this->alpha)*pow(calculateNij(choosen_city,remaining_cities[l],is_lower),this->beta);
        }
        //cout<<denominator<<"denom"<<endl;
        //cout<<(10000*nominator)/(10000*denominator)<<"res"<<endl;
        float result=(10000.0*nominator)/(10000.0*denominator);
        probs.push_back(result);
    }
    return probs;
}

void ACO::ACO_algorithm(){
    int case_size=case_set_list[test_index].get_vector().size();
    int ant_size=case_size;

    greedies_and_bb algorithm2;
    algorithm2.read_and_setup("CSE624TESTSET.txt");
    vector<int> initial_sol=algorithm2.greedy_algorithm(test_index,false);
    int difference;
    find_feasible_limit(initial_sol,difference);
    initializepheromones(1.0/(float)difference,initial_sol);

    int best_sol=MAX_INT;
    int best_feasible_limit=0;
    vector<int> best_sol_vec;

    vector<vector<float> > pheromone_matrix_local;
    /* initialize the local pheromone matrix */
    for(int i=0;i<case_size;++i){
        vector<float> temp_vector;
        for(int j=0;j<case_size;++j){
            temp_vector.push_back(0.);
        }
        pheromone_matrix_local.push_back(temp_vector);
    }

    /* Main loop */
    for(int ct=0;ct<t_max;++ct){
        for(int j=0;j<case_size;++j){
            for(int k=0;k<case_size;++k){
                pheromone_matrix_local[j][k]=0.;
            }
        }
        /* ant loop */
        for(int ant=0;ant<ant_size;++ant){
            /* City vector initialize */
            vector<int>cities;
            for(int i=0;i<case_size;++i){
                cities.push_back(i);
            }
            /* path creation loop */
            vector<int> ant_path;
            /* Choose a random city for beginning */
            int index=rand()%cities.size();
            int city=cities[index];
            while(1){
                /* Each loop choose a new city by looking pheromones and distance */
                ant_path.push_back(city);
                cities.erase(cities.begin()+index);
                if(cities.size()==0){
                    break;
                }
                /* Externs remaining cities probabilities */
                vector<float> probs=remaining_city_probs(city,cities);
                /* Choose a new city looking probs with roulette selection */
                int new_selected_index=roulette_selection(probs);
                index=new_selected_index;
                city=cities[new_selected_index];
            }
            /* Updates the best solution */
            int dif;
            int feasible_limit=find_feasible_limit(ant_path,dif);
            if(dif<best_sol){
                best_sol=dif;
                best_sol_vec=ant_path;
                best_feasible_limit=feasible_limit;
            }
            //cout<<best_sol<<","<<dif<<endl;
            /* Deposit a trail */
            for(int i=0;i<feasible_limit-1;++i){
                pheromone_matrix_local[ant_path[i]][ant_path[i+1]]+=1.0/(float)dif;
            }
        }
        /* Evaporate trails */
        for(int i=0;i<case_size;++i){
            for(int j=0;j<case_size;++j){
                pheromone_matrix[i][j]=0.7*pheromone_matrix[i][j]+pheromone_matrix_local[i][j];
            }
        }
    }

    cout<<"(Test "<<test_index<<") The solution is:";
    for(int i=0;i<best_feasible_limit;++i){
        cout<<best_sol_vec[i]+1<<" ";
    }
    cout<<endl;
    
}

/* Main function. It runs all of algorithms between test 0-5 */
int main(){
    srand(time(NULL));

    cout<<"**** Brute Force Algorithm (HW1) ****"<<endl;

    brute_force algorithm;
    algorithm.read_and_setup("CSE624TESTSET.txt");
   
    for(int i=0;i<5;++i){
        brute_force algorithm_temp=algorithm;
        cout<<"(Test "<<i<<")";
        algorithm_temp.brute_force_algorithm(i);
    }

    cout<<endl<<"**** Greedy and Branch and Bound (HW2) ****"<<endl;

    greedies_and_bb algorithm2;
    algorithm2.read_and_setup("CSE624TESTSET.txt");
   
    for(int i=0;i<5;++i){
        greedies_and_bb algorithm_temp=algorithm2;
        cout<<"(Test "<<i<<")";
        algorithm_temp.greedy_algorithm(i,true);
    }
    cout<<endl;

    for(int i=0;i<5;++i){
        greedies_and_bb algorithm_temp=algorithm2;
        cout<<"(Test "<<i<<")";
        algorithm_temp.greedy_algorithm2(i);
    }
    cout<<endl;

    for(int i=0;i<5;++i){
        greedies_and_bb algorithm_temp=algorithm2;
        cout<<"(Test "<<i<<")";
        algorithm_temp.branch_and_bound(i);
    }
    cout<<endl;

    cout<<endl<<"**** Variable Neighbourhood Search (HW3) ****"<<endl;
    VNS algorithm3(0);
    algorithm3.read_and_setup("CSE624TESTSET.txt");

    for(int i=0;i<5;++i){
        VNS algorithm_temp;
        algorithm_temp=algorithm3;
        algorithm_temp.set_test_index(i);
        algorithm_temp.VNS_algorithm();
    }

    cout<<endl<<"**** Simulated Annealing (HW4) ****"<<endl;
    SA algorithm4(0);
    algorithm4.read_and_setup("CSE624TESTSET.txt");

    for(int i=0;i<5;++i){
        if(i!=1){
            SA temp;
            temp=algorithm4;
            temp.set_test_index(i);
            temp.SA_algorithm();
        }
        else{
            cout<<endl;
        }
        
    }

    cout<<endl<<"**** Tabu Search (HW5) ****"<<endl;
    TS algorithm5(0);
    algorithm5.read_and_setup("CSE624TESTSET.txt");

    for(int i=0;i<5;++i){
        TS temp;
        temp=algorithm5;
        temp.set_test_index(i);
        temp.TS_algorithm();
    }

    cout<<endl<<"**** Genetic Algorithm (HW6) ****"<<endl;
    GA algorithm6(0);
    algorithm6.read_and_setup("CSE624TESTSET.txt");

    for(int i=0;i<5;++i){
        GA temp;
        temp=algorithm6;
        temp.set_test_index(i);
        temp.GA_algorithm();
    }

     cout<<endl<<"**** Ant Colony Algorithm (HW7) ****"<<endl;
    ACO algorithm7(0,2,1,10);
    algorithm7.read_and_setup("CSE624TESTSET.txt");
    /*algorithm.set_test_index(1);
    algorithm.ACO_algorithm();*/
    for(int i=0;i<5;++i){
        ACO algorithm_temp=algorithm7;
        algorithm_temp.set_test_index(i);
        algorithm_temp.ACO_algorithm();
    }
}