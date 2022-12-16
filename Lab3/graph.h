
#ifndef GRAPH_H
#define GRAPH_H

using namespace std ; 
#include <vector>
#include "block.h"
#include "terminal.h"
#include <fstream>

    class ROW{
       private :
         int Left_bottom_x  ; 
         int Right_bottom_x ;
       public  : 
         ROW( int x1 , int x2 ) : Left_bottom_x(x1) , Right_bottom_x(x2) {} ; 
         
         int get_x1() { return Left_bottom_x ;  } 
         int get_x2() { return Right_bottom_x ;  }
    
    };
    
    class OVERLAP {
      private :
         BLOCK* Overlap_cell_1 ; 
         BLOCK* Overlap_cell_2 ; 
         int    Overlap_area ; 
         bool   Overlap_flag ; 
      public  :
         OVERLAP(BLOCK* cell_1 , BLOCK* cell_2 , int area) : Overlap_cell_1(cell_1) , Overlap_cell_2(cell_2) , Overlap_area(area) , Overlap_flag(false) {} ; 
      
         int    get_area     () { return Overlap_area  ; }
         bool   get_overlap  () { return Overlap_flag  ; }
         BLOCK* get_cell_1   () { return Overlap_cell_1; }
         BLOCK* get_cell_2   () { return Overlap_cell_2; }
         
         void set_area     (int  area) { Overlap_area   = area  ; } 
         void set_overlap  (bool flag) { Overlap_flag   = flag  ; } 
         void set_cell_1(BLOCK* b) { Overlap_cell_1 = b  ; } 
         void set_cell_2(BLOCK* b) { Overlap_cell_2 = b  ; } 
         
    }; 
    
    
    class GRAPH{
        private :
            vector<BLOCK* > All_block ; 
            vector<BLOCK* > block_chip_1 ; 
            vector<BLOCK* > block_chip_2 ; 
            
            vector<TERMINAL* > All_terminal ; 
            vector<vector<BLOCK* > > block_of_row ; 
            vector<vector<ROW* > > row_of_row ;
            
            vector<vector<OVERLAP* > > Overlap_graph ;
            //int Overlap_area_vec[250000] ;  
            //int Actually_overlap[250000] ; 
            
            vector<int > row_value ; 
            
            //CLUSTER* root ; 
            
            int die_x ;
            int die_y ; 
            int row_height ;
            int row_num ;  
            int cell_num ; 
            int original_overlap ; 
            int final_overlap    ; 
            int terminal_overlap_num ; 
            double overlap_remaining_percent ; 
            bool flag_exceed_row ; 
            
        public : 
            GRAPH(int x , int y , int height , int num) : die_x(x) , die_y(y) , row_height(height) , row_num (num) , cell_num(0) ,  original_overlap (0) ,final_overlap(0) , overlap_remaining_percent(0.0) {   block_of_row.reserve(num) ; 
                                    row_of_row.reserve(num) ; 
                                    row_value.reserve(num) ;  
  } 
        
            void set_all_block(ifstream& block_file)    ; 
            void set_all_terminal(ifstream& terminal_file) ; 
            
            
            void partition () ; 
            void partition_2 () ;
            int  check_overlap(int one_x , int one_w  , int one_y  , int one_h   , int two_x , int two_w , int two_y , int two_h    ) ;
             
            void placement () ; 
            
            void split_row () ;
            int  place_row (BLOCK* new_b , int now_row , bool is_trial) ; 
            void Collapse( CLUSTER* c , int cluster_index , vector<CLUSTER* >& row_cluster , int split_index , int now_row );
            //bool check_terminal_overlap(int c_x , int c_w , int now_row ) ; 
            
            void compute_init_overlap_area() ; 
            void compute_chip1_overlap_area() ; 
            void compute_chip2_overlap_area() ; 
            void write_output_file (ofstream& output_file) ; 
    };    




#endif
