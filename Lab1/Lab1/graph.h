
#ifndef GRAPH_H
#define GRAPH_H

#include "tile.h"
#include <vector>  
using namespace std ; 

class GRAPH{
    private : 
       int border_w ;
       int border_h ; 
       TILE* First_tile ; 
       vector<int> POINT_xy ; 
    public : 
        GRAPH(int w, int h) :  border_w (w) ,border_h(h)  {
          First_tile = new TILE(0,0,border_w,border_h,0) ; 
        } ;  
        
        void Point_Finding(int object_x, int object_y ) ; 
        void Insert_tile (int x, int y, int w, int h , int idx) ; 
        TILE* Get_First_Tile() {return First_tile ; } 
        
        void split_tile (TILE* Spaced_T, int diff_y, int new_y ) ; // for bottom and top 
        void split_tile_LR (TILE* Spaced_T , TILE* Insert_T ) ;  // for left and right
        void update_pointer(TILE* New_Tile) ;  
        void merge_top_bottom ( TILE* TOP , TILE* BOTTOM) ; 
        void merge_bottom_top ( TILE* TOP , TILE* BOTTOM) ; 
        void area_search (int border_x , int border_y , char* argv[] ) ; 
        
        void neighbor_finding(TILE* T) ;
        void compute_point_XY(TILE* T) ; 
};






#endif
