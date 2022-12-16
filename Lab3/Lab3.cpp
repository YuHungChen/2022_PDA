#include<iostream>
#include<fstream>
#include<string>
#include<limits>

#include <ctime>
#include "graph.h" 

using namespace std ;

int main( int argc , char* argv[] ) {
   
    //srand (time(NULL)) ; 
     
    //clock_t time_init, time_end;
    //time_init = clock();
    ifstream block_file ;
    ofstream output_file ;
      
   // cout << argv[1] << endl ; 
    block_file.open(argv[1]) ; 
    output_file.open(argv[2]) ;   
    
    string Title ;
    int die_x ;
    int die_y ; 
    int row_height ;
    int row_num ;  
    
    block_file >> Title ;
    block_file >> die_x ; 
    block_file >> die_y ;   
    block_file >> Title ;
    block_file >> row_height ; 
    block_file >> row_num ;    
    
    //cout << 1 << endl ; 
    //cout << row_num << endl ;
    GRAPH Graph(die_x , die_y , row_height , row_num ) ;
    //cout << 1 << endl ;  
    
    Graph.set_all_terminal(block_file) ;
    Graph.set_all_block(block_file) ; 
    //Graph.compute_init_overlap_area() ;
    
    Graph.partition_2() ; 
    Graph.partition() ; 
    
    //Graph.compute_chip1_overlap_area() ;
   // Graph.compute_chip2_overlap_area() ;
    Graph.placement() ; 
    //cout << " after placement " << endl ; 
    Graph.write_output_file(output_file) ;
    
    block_file.close() ; 
    output_file.close() ; 

    return 0 ;
}
