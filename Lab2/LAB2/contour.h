#ifndef CONTOUR_H
#define CONTOUR_H

using namespace std ; 

class Contour{
   
   private :
     int x ; 
     int y ; 
     Contour* prev ; 
     Contour* next ;
      
   public : 
     Contour ( int c_x ,int c_y ) : x(c_x) , y(c_y) , prev(0) , next(0)  {} ;  
     
     Contour* get_prev() {return prev ; } 
     Contour* get_next() {return next ; }
     int get_x () {return x ; }
     int get_y () {return y ; }
     
     void set_x (int c_x ) { x = c_x ; }
     void set_y (int c_y ) { y = c_y ; }
     void set_prev (Contour* C ) { prev = C ; }
     void set_next (Contour* C ) { next = C ; }
     
};



#endif