
#ifndef BLOCK_H
#define BLOCK_H


#include<vector>
#include<string>

class BLOCK{

  private:
       string b_name ; 
       int number ; 
       int b_x ; 
       int b_y ;
       int b_w ; 
       int b_h ; 
       int chip_index ; 
       int final_x ; 
       int final_y ; 
       bool fixed  ; 
  public :
      BLOCK( string name , int num , int x , int y , int w , int h ) : b_name(name), number(num) , b_x(x) , b_y(y) , b_w(w) , b_h (h) , chip_index(0) , final_x(0) , final_y(0) , fixed(0) {} ; 
      
      int get_x () {return b_x ; }
      int get_y () {return b_y ; }
      int get_w () {return b_w ; }
      int get_h () {return b_h ; }
      int get_final_x () {return final_x ; }
      int get_final_y () {return final_y ; }
      int get_index()    {return chip_index ; }
      int get_number()    {return number ; }
      string get_name () {return b_name ; }  
      bool get_fixed  () {return fixed  ; }
      
      void set_x ( int x ) { b_x = x; }
      void set_y ( int y ) { b_y = y ; }
      void set_w ( int w ) { b_w = w ; }
      void set_h ( int h ) { b_h = h ; }
      void set_final_x ( int x ) { final_x = x; }
      void set_final_y ( int y ) { final_y = y ; }
      void set_index ( int index ) { chip_index = index ; }
      void set_fixed() { fixed = true ; }


};

class CLUSTER{
  private :
     //vector<BLOCK* > Cluster_vec ;
     //CLUSTER* pred     ; 
     BLOCK* last_cell  ;
     BLOCK* first_cell ;  
     int Cluster_w ; 
     int Cluster_x ; 
     int Cluster_e ; 
     int Cluster_q ; 
  public  :
     CLUSTER() : Cluster_w(0 ) , Cluster_x(0 ) , Cluster_e(0) , Cluster_q(0)  {} ; 
     
     int get_w() {  return Cluster_w  ; }
     int get_x() {  return Cluster_x  ; }
     int get_e() {  return Cluster_e  ; }
     int get_q() {  return Cluster_q  ; }
     BLOCK* get_last_cell () {  return last_cell  ; }
     BLOCK* get_first_cell() {  return first_cell  ; }
     
     
     void set_w ( int w ) { Cluster_w = w; }
     void set_x ( int x ) { Cluster_x = x ; }
     void set_e ( int e ) { Cluster_e = e ; }
     void set_q ( int q ) { Cluster_q = q ; }
     void set_last_cell  ( BLOCK* cell ) { last_cell  = cell ; }
     void set_first_cell ( BLOCK* cell ) { first_cell = cell ; }
     //void set_predecessor ( CLUSTER* cluster ) { pred = cluster ; }
    // int get_size() {  return Cluster_vec.size() ; }
    // BLOCK* get_vector(int i )  {return Cluster_vec[i] ; } 


};






#endif