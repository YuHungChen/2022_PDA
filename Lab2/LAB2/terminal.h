
#ifndef TERMINAL_H
#define TERMINAL_H



#include<string>

class Terminal{

  private:
       string t_name ; 
       int t_x ; 
       int t_y ;
  public :
      Terminal( string name , int x , int y ) : t_name(name), t_x(x) , t_y(y)  {} ; 
      
      int get_x () {return t_x ; }
      int get_y () {return t_y ; }
      string get_Name () { return t_name ; }  


};








#endif