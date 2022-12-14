#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include "B_tree.h"
#include "terminal.h"
#include <ctime>

using namespace std ;

int main( int argc , char* argv[] ) {
   
    //srand (time(NULL)) ; 
    
    clock_t time_init, time_end;
    time_init = clock();
    ifstream block_file ;
   // ifstream net_file   ;
    ofstream output_file ;

    
    
    string alpha  ;
    alpha = argv[1] ;

    block_file.open (argv[2]) ;
    const char* net_file_path = argv[3] ;  
    //net_file.open   (argv[3]) ;
    output_file.open(argv[4]) ;

    //cout << alpha << endl ;

    string Title ;
    int border_x ;
    int border_y ;
    int blocks_number ;
    int terminals_number ;
    block_file >> Title  ;
    block_file >> border_x ;
    block_file >> border_y ;
    block_file >> Title ;
    block_file >> blocks_number ;
    block_file >> Title ;
    block_file >> terminals_number ;


    string node_name ;
    int node_w ;
    int node_h ;
    block_file >> node_name ;
    block_file >> node_w ;
    block_file >> node_h ;

    TreeNode* root = new TreeNode(node_name , 0 , 0 , node_w , node_h) ;
    Contour* head = new Contour( 0 ,0) ;
    Contour* tail = new Contour( numeric_limits<int>:: max() , 0 ) ;
    head -> set_next(tail) ;
    tail -> set_prev(head) ;
    //cout << 11 << endl ;
    B_TREE B_graph = B_TREE (root , head , border_x , border_y , stod(alpha) ) ;

    //cout << B_graph -> get_border_x() << endl ;
    //cout << B_graph -> get_border_y() << endl ;

    //TreeNode* now_parent = root ;
    TreeNode* new_child ;
    // insert block
    //srand(time(0)) ;
    for (int i=0 ; i < blocks_number -1 ; i++){

        block_file >> node_name ;
        block_file >> node_w ;
        block_file >> node_h ;

        new_child = new TreeNode(node_name , 0 , 0 , node_w , node_h ) ; // x , y is default value
        B_graph.Random_construct_tree( new_child ) ;


        //now_parent = new_child ;

    }
    

    
    B_graph.save_terminals (terminals_number , block_file ) ; 
    B_graph.save_net_name (net_file_path ) ; 
  //  B_graph.construct_map () ;
    
    B_graph.Simulated_Annealing_2( ) ;


  
   // B_graph.compute_HPWL(My_terminal , net_file) ;
    //int maximum ;
   // maximum = B_graph.compute_y() ;
   // cout << stod(alpha) << endl ;
   
    time_end = clock();
    double total_time = double(time_end - time_init) / ( CLOCKS_PER_SEC)  ; 
    B_graph.write_output_file(output_file , total_time ) ; 

    block_file.close()  ;
    output_file.close() ;

    return 0 ;
}
