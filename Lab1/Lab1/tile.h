#ifndef TILE_H
#define TILE_H

using namespace std ; 

class TILE{
    private :
        int axis_x ; 
        int axis_y ;
        int width ;
        int height ;
        int index ;   // 0 means spaced  tile
        int solid_tile = 0 ;  // compute the number of solid_tile next to the tile
        int space_tile = 0 ;  // compute the number of space_tile next to the tile 
        bool been_counted = false ; 
        
        TILE* rt ; 
        TILE* tr ;
        TILE* lb ;
        TILE* bl ; 
        
    public :
        TILE(int x, int y, int w, int h , int idx) : axis_x(x) , axis_y(y) , width (w) , height(h) , index(idx) , solid_tile(0) , space_tile(0) , been_counted(0) , rt(0) , tr(0) , lb(0) , bl(0) {} ;  
//TILE(int x, int y, int h, int w , int idx , TILE* R , TILE* T , TILE* L , TILE* B ) : axis_x(x) , axis_y(y) , height(h) , width (w) , index(idx) , rt(T) , tr(R) , lb(B) , bl(L) {} ;   
 
        void add_solid_tile (TILE* T) {T -> solid_tile = T -> solid_tile + 1   ; } 
        void add_space_tile (TILE* T) {T -> space_tile = T -> space_tile + 1  ; }       
        
        void set_x  (int x  ) { axis_x = x ; }
        void set_y  (int y  ) { axis_y = y ; }
        void set_height  (int h  ) { height = h ; }
        void set_width   (int w  ) { width  = w ; }
        void set_index   (int idx) { index  = idx;}
        
        void set_rt (TILE* T) { rt = T ; }
        void set_tr (TILE* T) { tr = T ; }
        void set_lb (TILE* T) { lb = T ; }
        void set_bl (TILE* T) { bl = T ; }  
        
        void set_counted() {been_counted = true ; } 
        bool get_counted() {return been_counted ; } 
        
        TILE* get_rt () { return rt ; }
        TILE* get_tr () { return tr ; }
        TILE* get_lb () { return lb ; }
        TILE* get_bl () { return bl ; }
        
        int get_space_tile() {return space_tile ;}
        int get_solid_tile() {return solid_tile ;} 
        int get_x() {return axis_x;}
        int get_y() {return axis_y;} 
        int get_width() {return width;}
        int get_height() {return height;}
        int get_index() {return index ;} 
        
};

#endif
