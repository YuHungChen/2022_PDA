
#ifndef TERMINAL_H
#define TERMINAL_H



#include<string>

class TERMINAL{

  private:
       string t_name ; 
       int t_x ; 
       int t_y ;
       int t_w ; 
       int t_h ;
  public :
      TERMINAL( string name , int x , int y , int w , int h  ) : t_name(name), t_x(x) , t_y(y) , t_w (w) , t_h (h)  {} ; 
      
      int get_x () {return t_x ; }
      int get_y () {return t_y ; }
      int get_w () {return t_w ; }
      int get_h () {return t_h ; }
      string get_name () { return t_name ; }  


};








#endif