#include "graph.h"
#include "block.h"
#include "terminal.h"
#include <limits>

#include <iostream>
#include <algorithm>
using namespace std ;

bool sort_value( BLOCK* B1 , BLOCK* B2  ) {


    return (B1 -> get_x() < B2 -> get_x() ) ;

}
bool sort_value_T( TERMINAL* T1 , TERMINAL* T2  ) {


    return (T1 -> get_x() < T2 -> get_x() ) ;

}

int difference (int x1 , int x2  ){
  if (x1 > x2 ){
    return  (  x1 - x2) ;
  }

  return (x2 - x1 ) ;
}


void GRAPH::partition () {

  block_chip_1.reserve(All_block.size()) ;
  block_chip_2.reserve(All_block.size()) ;

  // for test
  // unsigned int half_num = All_block.size() ;

  for (unsigned int i=0 ; i < All_block.size() ; i++){
     if ( All_block[i] -> get_index() == 0 ){
         block_chip_1.push_back(All_block[i]) ;
     }else {
         block_chip_2.push_back(All_block[i]) ;
         //All_block[i] -> set_index(1) ;
     }
  }

}

 


void GRAPH::partition_2 () {

    OVERLAP* new_overlap ;
    int overlap_area ;
    
   //cout << "partition_2 " << endl ;
    //int upper_bound = row_height*20 ;
    unsigned int upper_bound_for_loop = All_block.size() ; 
    if (All_block.size() > 150000)
      upper_bound_for_loop = 150000 ;
     
    int Overlap_area_vec[200000] ;  
    int Actually_overlap[200000] ; 
    for (unsigned int i=0 ; i < upper_bound_for_loop - 1 ; i++ ){
      //Overlap_graph[i].reserve(All_block.size() - 1 ) ; 
      for (unsigned int j=i+1 ; j < upper_bound_for_loop ; j++ ){
         overlap_area = check_overlap(All_block[i] -> get_x() , All_block[i] -> get_w() , All_block[i] -> get_y() , All_block[i] -> get_h()    
                                    , All_block[j] -> get_x() , All_block[j] -> get_w() , All_block[j] -> get_y() , All_block[j] -> get_h() ) ;
         if (  overlap_area == 0 ){
           continue ; 
         }else {
  //         cout << "overlap with block : " << j << endl ;
           new_overlap = new OVERLAP( All_block[i] , All_block[j] , overlap_area) ;
           Overlap_graph[i].push_back(new_overlap) ;
           Overlap_area_vec[i] = Overlap_area_vec[i] + overlap_area ;
           
           if (All_block[i] -> get_index() == All_block[j] -> get_index() ){
             new_overlap -> set_overlap(true) ;
             Actually_overlap[i] = Actually_overlap[i] + overlap_area ; 
             Actually_overlap[j] = Actually_overlap[j] + overlap_area ;
           }

           Overlap_graph[j].push_back(new_overlap) ;
           Overlap_area_vec[j] = Overlap_area_vec[j] + overlap_area ;
           
         }
      }
    }

    /*
    cout << "Construct overlap " << endl ;
    cout << Overlap_graph.size() << endl ;
    for (unsigned int i=0 ; i < Overlap_graph.size() ; i++){
      for ( unsigned int j= 0 ; j < Overlap_graph[i].size() ; j++){
         cout << Overlap_graph[i][j] -> get_cell_1() -> get_name() << " , " << Overlap_graph[i][j] -> get_cell_2() -> get_name() << " : " << Overlap_graph[i][j] -> get_area() << endl   ;
      }
      cout << " Actually_overlap       : " << Actually_overlap[i] << endl ;
      cout << " total_overlap_row_area : " << Overlap_area_vec[i] << endl ;
      cout << " ----------- " << endl ;
    }*/

    //cout << "  ==========  FM partition =================  " << endl ;
    // method 1
    long best_cost = -1;
    int best_cell = 0;
    int the_other_overlap ;
    int differ_area ;
    int number = 0 ;
    int counter = 0 ;   
    while (true ) {
      best_cost = numeric_limits<int>::max() ;
      counter = 0 ;
      for (unsigned int i=0 ; i < upper_bound_for_loop; i++ ){
          if (All_block[i] -> get_fixed() ) {
      //       cout << All_block[i] -> get_name() << " fixed " << endl ;
             continue ;
          }
          
    
          
          
          the_other_overlap  = Overlap_area_vec[i] - Actually_overlap[i] ;
          differ_area = the_other_overlap - Actually_overlap[i] ;
          if (differ_area < best_cost){
             best_cost = differ_area ;
             best_cell = i ;
               counter ++ ; 
             
             
          }
          
          if (counter == 9)
            break ;
          
          //cout << " ----------- " << endl ;
          //cout << " differ cost : " << differ_area << endl ;
          //cout << " ----------- " << endl ;
      }

   //   cout << " best cost : " << best_cost << endl ;
  //    cout << " best cell : " << best_cell << endl ;
   //   cout << " ----------- " << endl ;

      if (best_cost >= 0 ){
         break ;
      }

      All_block[best_cell] -> set_fixed() ;

      if (  ( All_block[best_cell] -> get_index() ) == 0  )
          All_block[best_cell] -> set_index( 1 ) ;
      else
          All_block[best_cell] -> set_index( 0 ) ;

    //  Actually_overlap[best_cell] = Overlap_area_vec[best_cell] - Actually_overlap[best_cell] ;


      for (unsigned int i=0 ; i < Overlap_graph[best_cell].size() ; i++){
         new_overlap = Overlap_graph[best_cell][i] ;
         new_overlap -> set_overlap (  ! (new_overlap -> get_overlap() )  ) ;
         if (new_overlap -> get_cell_1() -> get_fixed() ){
            number = new_overlap -> get_cell_2() -> get_number() ;
            if (  new_overlap -> get_overlap() == false ){
                Actually_overlap[number] = Actually_overlap[number] - new_overlap -> get_area() ;
            }else {
                Actually_overlap[number] = Actually_overlap[number] + new_overlap -> get_area() ;
            }
         }else {
            number = new_overlap -> get_cell_1() -> get_number() ;
            if (  new_overlap -> get_overlap() == false ){
                Actually_overlap[number] = Actually_overlap[number] - new_overlap -> get_area() ;
            }else {
                Actually_overlap[number] = Actually_overlap[number] + new_overlap -> get_area() ;
            }
         }
      }
      
      
    }
  //  cout << " ============================== " << endl ;
 /*
    for (unsigned int i=0 ; i < Overlap_graph.size() ; i++){
      for ( unsigned int j= 0 ; j < Overlap_graph[i].size() ; j++){
         cout << Overlap_graph[i][j] -> get_cell_1() -> get_name() << " , " << Overlap_graph[i][j] -> get_cell_2() -> get_name() << " : " << Overlap_graph[i][j] -> get_area() << endl   ;
      }
      cout << " Actually_overlap       : " << Actually_overlap[i] << endl ;
      cout << " total_overlap_row_area : " << Overlap_area_vec[i] << endl ;
      cout << " ----------- " << endl ;
    }
 */


    /*
    unsigned int overlap_size ;

    for (unsigned int i=0 ; i < All_block.size() ; i++ ){
       overlap_size = Overlap_graph[i].size() ;
       for (unsigned int j=0 ; j < overlap_size ; j++ ){
          new_overlap = Overlap_graph[i].back() ;
          Overlap_graph[i].pop_back() ;
          delete new_overlap ;
          new_overlap = NULL ;
       }
    }
    */
    // cout << "  ==========  Finish partition =================  " << endl ;
}

void AddCluster (CLUSTER* predecessor , CLUSTER* now_C ) {

    predecessor -> set_last_cell( now_C -> get_last_cell() );
    predecessor -> set_e        ( now_C -> get_e() + predecessor -> get_e()     )  ;
    predecessor -> set_q        ( now_C -> get_q() + predecessor -> get_q() - (now_C -> get_e() * predecessor -> get_w() )   )  ;
    predecessor -> set_w        ( now_C -> get_w() + predecessor -> get_w()     ) ;


}

void Add_cell(CLUSTER* c , BLOCK* new_b){
  // cout << "====== add cell ===== " << endl ;
   c -> set_last_cell (new_b) ;
   c -> set_e ( c -> get_e() + new_b -> get_w() ) ;
   c -> set_q ( c -> get_q() + (new_b -> get_w() ) *(new_b -> get_x() - c -> get_w() ) ) ;
   c -> set_w ( c -> get_w() + (new_b -> get_w() ) ) ;
}

void GRAPH::Collapse( CLUSTER* c , int cluster_index , vector<CLUSTER* >& row_cluster , int split_index , int now_row) {

  //cout << " q : "  << c -> get_q() << " e : " << c -> get_e() << endl ;

  c -> set_x( c -> get_q() / c -> get_e()  ) ;

  if ( c -> get_x() <  row_of_row[now_row][split_index]  -> get_x1()  ){
      c -> set_x(  row_of_row[now_row][split_index] -> get_x1() ) ;

  }else if  ( c -> get_x() > (  row_of_row[now_row][split_index] -> get_x2()  - c -> get_w() ) ) {
      c -> set_x(  row_of_row[now_row][split_index] -> get_x2() - c -> get_w() ) ;
  }


  // overlap between c and c'  ?

  //cout << cluster_index << endl ;
  if (cluster_index != 0){
    CLUSTER* predecessor = row_cluster[cluster_index - 1];
    if ( predecessor!= NULL  && ( predecessor -> get_x() + predecessor-> get_w() )  >  c -> get_x()  ){
      // cout << " ----- Merge ---------  " << endl ;
       AddCluster ( predecessor , c ) ;
       row_cluster.pop_back() ;
       delete c ;
       c = NULL ;


 //      cout << " need to collapse " << endl ;
       Collapse (predecessor , cluster_index -1  , row_cluster , split_index , now_row  ) ;
    }
  }


}
/*
bool GRAPH::check_terminal_overlap(int c_x , int c_w , int now_row ){
  bool flag = false ;
  terminal_overlap_num = 0 ;
  int new_x = c_x ;
  int new_w = c_w ;
  bool while_flag = false ;
  while (!while_flag) {

    for (unsigned int i=terminal_overlap_num ; i < All_terminal.size() ; i++){
        if ( (new_x + new_w ) < All_terminal[i] -> get_x() ) {
           while_flag = true ;
           break ;
        }

        if ( (All_terminal[i] -> get_y() < ( (now_row+1) * row_height)) &&  ((All_terminal[i] -> get_y() + All_terminal[i] -> get_h() )  > ( (now_row) * row_height)))    { // y match
          if ( (new_x <  ( All_terminal[i] -> get_x() + All_terminal[i] -> get_w() ) )   && (  (new_x + new_w ) > All_terminal[i] -> get_x() ) ){
             terminal_overlap_num = i ;
             new_x = All_terminal[i] -> get_x() + All_terminal[i] -> get_w();
             flag = true ;
             break ;
          }
        }

        if ( i == All_terminal.size()-1 ){
           while_flag = true ;
        }

    }

  }

  return flag ;
}
*/

void GRAPH::split_row (){
 //   cout << " ----  split row ----- " << endl ;
    ROW* splited ;
    int initial_x = 0 ;
    int x_plus_w  = 0 ;
    int row_y = 0 ;
    vector<ROW*   > new_row_of_row   ;

  //  cout << row_num << endl ;
    for ( int i=0 ; i < row_num ; i++) {    // i means now row ;
      row_y     = (i+1) * row_height ;
      initial_x = 0 ;
      new_row_of_row.clear() ;
      for (unsigned int j=0 ; j < All_terminal.size() ; j++){
   //      cout << All_terminal[j] -> get_y() << " , " << All_terminal[j] -> get_y() + All_terminal[j] -> get_h()  << endl ;
         if ( (All_terminal[j] -> get_y()  < ( row_y  ) )&&  ((All_terminal[j] -> get_y() + All_terminal[j] -> get_h() )  > ( i * row_height )   ) )    { // y match
            x_plus_w = All_terminal[j] -> get_x() + All_terminal[j] -> get_w() ;
            if (initial_x >= All_terminal[j] -> get_x() ){
              if ( initial_x < x_plus_w)
                initial_x = x_plus_w;
              continue ;
            }else {
              splited = new ROW ( initial_x , All_terminal[j] -> get_x() ) ;
              initial_x = x_plus_w ;
              new_row_of_row.push_back(splited) ;
            }

         }
      }
      if (initial_x != die_x){
        splited = new ROW ( initial_x , die_x ) ;
        new_row_of_row.push_back(splited) ;
      }

      row_of_row.push_back(new_row_of_row) ;
    }

 //   cout << " row_split " << endl  ;
 /*
    for ( int i=0 ; i < row_num ; i++) {
      cout << i << " : " << endl  ;
      for (unsigned int j=0 ; j < row_of_row[i].size() ; j++){
        cout << row_of_row[i][j] -> get_x1() << " , " << row_of_row[i][j] -> get_x2() << endl ;
      }
    }
    cout << " row_split " << endl  ;
  */
}


int GRAPH::place_row (BLOCK* new_b , int now_row , bool is_trial) {
   // cout << " =========== place row ============== trial : " << is_trial << endl ;
    CLUSTER* c ;
    block_of_row[now_row].push_back(new_b) ;
 //   if (now_row == 49){
 //     cout << block_of_row[now_row].size() << endl ;
 //   }

    vector<CLUSTER* > Cluster_vec;
    BLOCK* now_block = NULL;
    int cluster_index = 0 ;
    int offset = 0 ;
    unsigned int split_index = 0 ;
    int split_row_width = 0 ;
    int total_width = 0 ;
    flag_exceed_row = false ;

 //   if (!is_trial)
 //     cout << " now_cell " <<  new_b -> get_name() << endl ;
//    cout << " initial (x,y) : " <<  new_b -> get_x() << " , " << new_b -> get_y() << endl ;

    for (unsigned int i=0 ; i < block_of_row[now_row].size() ; i++ ){
        if (i!=0){
           c = Cluster_vec.back() ;
           cluster_index = Cluster_vec.size() - 1 ;
          // cout << " cluster x : " <<  c -> get_x() << " cluster w : " <<  c -> get_w() << endl ;
       }
       now_block = block_of_row[now_row][i] ;
//       cout << " this row cell " <<  now_block -> get_name() << " " << i << endl ;
       split_row_width = row_of_row[now_row][split_index] -> get_x2() - row_of_row[now_row][split_index] -> get_x1() ;

        /* if (i!=0  &&  now_block->get_name() == "C2372"  && !is_trial){
           cout << "(c -> get_w() + now_block -> get_w() )  : " << (c -> get_w() ) << endl ;
           cout << "(c -> get_x() + c -> get_w() )  : " << (c -> get_x() + c -> get_w() ) << endl ;
           cout << "now_block -> get_x()   : " << now_block -> get_x() << endl ;
           cout << " split_row_width : " << split_row_width << endl ;
         }  */
        total_width = total_width + now_block -> get_w()  ;
       if ( i==0 || (  ( ( c -> get_x() + c -> get_w() )  <=  now_block -> get_x() ) ) ||  ( ( total_width )  >   split_row_width  )     ){
        while (true){
          // to compare width
         // cout << "this one" << endl ;
          if (    total_width   >   split_row_width       ){    // if width is not enough , go to next row of row
              split_index ++ ;
              total_width = now_block -> get_w() ;
              if (split_index ==  row_of_row[now_row].size()  ){
                 flag_exceed_row = true ;
                 split_index -- ;
                 break ;
              }
              split_row_width = row_of_row[now_row][split_index] -> get_x2() - row_of_row[now_row][split_index] -> get_x1() ;
             // check_second_times = true ;
              continue ;
          }


          // to compare (larger than row_x2 )

           if (i==0){
             break ;
           }else if  ( now_block -> get_x()  >=  row_of_row[now_row][split_index] -> get_x2() ){
             split_index ++ ;
              if (split_index ==  row_of_row[now_row].size()  ){
                 flag_exceed_row = true ;
                 split_index -- ;
                 break ;
              }
              if (  now_block -> get_x()  < row_of_row[now_row][split_index] -> get_x1()){
                 split_index -- ;
                 break ;
              }else{
                total_width = now_block -> get_w() ;
                split_row_width = row_of_row[now_row][split_index] -> get_x2() - row_of_row[now_row][split_index] -> get_x1() ;
              }
           }else {
             break ;
           }


       }

         if (flag_exceed_row){
            break ;
         }    else if (  i!=0  && (  (row_of_row[now_row][split_index] -> get_x2() - now_block -> get_w()   )  <  ( c -> get_x() + c -> get_w() )  )    ) {    // add to origin cluster
             //       cout << "  --- add to origin Cluster --- " << endl  ;
            Add_cell ( c , block_of_row[now_row][i] ) ;
            Collapse ( c , cluster_index ,  Cluster_vec , split_index , now_row ) ;
         }
         else {
      //      cout << "  --- construct new Cluster --- " << endl  ;
            c = new CLUSTER ;
            Cluster_vec.push_back(c) ;
            if (   now_block -> get_x()  < row_of_row[now_row][split_index] -> get_x1()  ){
                c -> set_x (  row_of_row[now_row][split_index] -> get_x1() ) ;
            }else if (  (now_block -> get_x() +  now_block -> get_w()) > ( row_of_row[now_row][split_index] -> get_x2()  )   ) {
                c -> set_x (  row_of_row[now_row][split_index] -> get_x2() - now_block -> get_w()  ) ;
            }else {
                c -> set_x (  now_block -> get_x()  ) ;
            }
            c -> set_first_cell ( now_block ) ;
            Add_cell ( c , block_of_row[now_row][i] ) ;
         }

       }else{
         Add_cell ( c , block_of_row[now_row][i] ) ;
         Collapse ( c , cluster_index ,  Cluster_vec , split_index , now_row ) ;
       }

    }

    int number      = Cluster_vec.size() ;
    int x_ordinate  = 0 ;
    int temp_number = 0 ;
    BLOCK* cell = NULL ;

    if (!flag_exceed_row){

        for (int i=0 ; i< number ; i++ ){
           x_ordinate = Cluster_vec[i] -> get_x() ;
       //    cout <<  " Cluster (x,y) :  " << x_ordinate << " , "<< now_row * row_height << endl ;
           cell = Cluster_vec[i] -> get_first_cell() ;
       //    cout << cell -> get_name() << endl ;
           while ( true) {
             cell -> set_final_x ( x_ordinate ) ;
             cell -> set_final_y ( now_row * row_height ) ;


       //     cout << " final_xy : " << cell -> get_final_x() << " , " << cell -> get_final_y() << endl ;
             offset = offset + difference(cell -> get_x() , cell -> get_final_x() ) ;

          //   cout << " offset_x : " <<  difference(cell -> get_x() , cell -> get_final_x() ) << endl ;
             offset = offset + difference(cell -> get_y() , now_row * row_height) ;
          //   cout << " offset_y : " << difference(cell -> get_y() , now_row * row_height) << endl ;


             x_ordinate = x_ordinate + cell -> get_w() ;

        //     cout << " cell : " << cell -> get_name() << " ==>  " << cell -> get_final_x() << "  , " <<  cell -> get_final_y() << endl ;

        //     if (!is_trial)
        //       cell_num = cell_num + 1 ;
             temp_number ++ ;
             if (cell == Cluster_vec[i] -> get_last_cell() )
                break ;

             cell = block_of_row[now_row][temp_number] ;
           }
        }

    }

    if (is_trial){
      block_of_row[now_row].pop_back() ;
    }

    for (int i=0 ; i< number ; i++ ){
       c = Cluster_vec.back() ;
       Cluster_vec.pop_back() ;

       delete c ;
       c = NULL ;
    }



    return offset ;

}

/*
int GRAPH::place_row (BLOCK* new_b , int now_row , bool is_trial) {
   cout << " =========== place row ============== trial : " << is_trial << endl ;
   CLUSTER* c ;

   block_of_row[now_row].push_back(new_b) ;
   //cout << 55 << endl ;
   vector<CLUSTER* > row_cluster;
   int cluster_index = 0 ;
   int offset = 0 ;

   for (int i=0 ; i < block_of_row[now_row].size() ; i++ ){

     if (i!=0){
       c = row_cluster.back() ;
       cluster_index = row_cluster.size() - 1 ;
   //    cout << " cluster x : " <<  c -> get_x() << " cluster w : " <<  c -> get_w() << endl ;
     }
     cout << " this row cell " << block_of_row[now_row][i] -> get_name() << " " << i << endl ;
     if ( i==0 || ( c -> get_x() + c -> get_w() )  <=  block_of_row[now_row][i] -> get_x()  ){
   //     cout << "  --- Construct new Cluster --- " << endl  ;
        c = new CLUSTER ;
        row_cluster.push_back(c)  ;
        if  (  check_terminal_overlap (  c -> get_x()  , block_of_row[now_row][i] -> get_w() , now_row )  )  {
          c -> set_x ( All_terminal[terminal_overlap_num] -> get_x() + All_terminal[terminal_overlap_num] -> get_w() ) ;
          cout << "  Construct overlap " << endl ;
    //      cout << " cluster x : " <<  c -> get_x() << " cluster w : " <<  c -> get_w() << endl ;
        }else
          c -> set_x ( block_of_row[now_row][i] -> get_x()) ;

        c -> set_first_cell ( block_of_row[now_row][i]) ;
        Add_cell ( c , block_of_row[now_row][i] ) ;

     }else if (  check_terminal_overlap (  c -> get_x()  , c -> get_w() + block_of_row[now_row][i] -> get_w() , now_row )  ) {
    //    cout << "  overlap terminal  -> construct new cluster "  ;
        c = new CLUSTER ;
        row_cluster.push_back(c)  ;
        c -> set_x (    All_terminal[terminal_overlap_num] -> get_x() + All_terminal[terminal_overlap_num] -> get_w()     ) ;
        c -> set_first_cell ( block_of_row[now_row][i]) ;
        Add_cell ( c , block_of_row[now_row][i] ) ;

     }else {
   //     cout << "  --- add to origin Cluster --- " << endl  ;
        Add_cell ( c , block_of_row[now_row][i] ) ;
        Collapse ( c , cluster_index ,  row_cluster , now_row ) ;
   //     cout << " after _ collapse " << endl ;
     }

   }


    int number = row_cluster.size() ;
  //  cout << " now_row :  " << now_row << endl ;
  //  cout << " row_size : " << number  << endl ;
    int x_ordinate = 0 ;
    int temp_number = 1 ;
    BLOCK* cell ;

   // cout << "cell_num : " << cell_num << endl ;
   // cout << "block_of_row size : " << block_of_row[now_row].size() << endl ;
    //int cell_num = 0 ;

    for (int i=0 ; i< number ; i++ ){
       x_ordinate = row_cluster[i] -> get_x() ;
       cout <<  x_ordinate << " , "<<now_row*row_height << endl ;
       cell = row_cluster[i] -> get_first_cell() ;

    //   cout << "first cell : " << cell -> get_name()  <<  endl ;
    //   cout << "last cell  : " << row_cluster[i] -> get_last_cell() -> get_name()  <<  endl ;
       while ( true) {
         cell -> set_final_x ( x_ordinate ) ;
         cell -> set_final_y ( now_row * row_height ) ;
         offset = offset + difference(cell -> get_x() , cell -> get_final_x() ) ;
         offset = offset + difference(cell -> get_y() , now_row * row_height) ;

         x_ordinate = x_ordinate + cell -> get_w() ;

    //     cout << " cell : " << cell -> get_name() << " ==>  " << cell -> get_final_x() << "  , " <<  cell -> get_final_y() << endl ;

         if (!is_trial)
           cell_num = cell_num + 1 ;

         if (cell == row_cluster[i] -> get_last_cell() )
            break ;

         //while (cell !=
         cell = block_of_row[now_row][temp_number] ;
         temp_number ++ ;
       }

    }

    if (is_trial)
      block_of_row[now_row].pop_back() ;

    for (int i=0 ; i< number ; i++ ){
       c = row_cluster.back() ;
       row_cluster.pop_back() ;

       delete c ;
       c = NULL ;
    }



    return offset ;
}

*/


void GRAPH::placement () {
  overlap_remaining_percent = double(final_overlap) / double(original_overlap) ;

//  cout << "initial    : " << original_overlap << endl ;
 // cout << "final      : " <<final_overlap    << endl ;
//  cout << "percentage : " <<overlap_remaining_percent << endl ;

  sort (block_chip_1.begin() , block_chip_1.end() , sort_value) ;
  sort (All_terminal.begin() , All_terminal.end() , sort_value_T) ;
  /*
  cout << " CHIP1 : " << endl ;
  for (unsigned int i=0 ; i < block_chip_1.size() ; i++ ){
     cout << block_chip_1[i] -> get_name() << " "  ;
  }
  cout << endl ;
  cout << " CHIP2 : " << endl ;
  for (unsigned int i=0 ; i < block_chip_2.size() ; i++ ){
     cout << block_chip_2[i] -> get_name() << " "  ;
  }
  cout << endl ;  */

  // total cost  :  Manhatttan distance



  int chip1_offset = 0 ;
  int chip2_offset = 0 ;

  int best_row  = 0 ;    // max row =  row_num ;
  double best_cost = 0 ;

  int after_place_value = 0 ;
  vector<BLOCK* > new_row  ;


  //int now_row = 0 ;
  //cost =  overlap_remaining_percent * total_offset ;

  // block 1  ;

  int counter = 0 ;
  vector<BLOCK* > redundant_vec_1 ;
  vector<BLOCK* > redundant_vec_2 ;

  split_row() ;
  int actual_row = 0 ;
  int tmp_row = 0 ; 
  int lower_bound_move_vertical = row_height/2 ;
  int placed_cell_offset   = 0 ;
  int needed_row_num = 0 ; 
  bool plus_flag = false ;
  bool lower_bound_flag = false ; 
  
  needed_row_num = row_num / 5 ; 
  if (needed_row_num <= 2)
    needed_row_num = row_num ; 
    
  for ( unsigned int i=0 ; i < block_chip_1.size() ; i++ ){
     best_cost = numeric_limits<double>::max() ;
     lower_bound_flag = false ; 
     plus_flag = false ;
     //cout << 33<< endl ;
     if (i==0){
       for (int j=0 ; j < row_num ; j++ ){
         row_value.push_back(0) ;
         block_of_row.push_back(new_row) ;
       }
     }

     counter = 0 ;
     tmp_row = ( block_chip_1[i] -> get_y() ) / row_height ;

     for (int j=0 ; j < needed_row_num ; j++ ){

         if (plus_flag == false){
            tmp_row = tmp_row - j ;
            plus_flag = true ; 
         }else{
            tmp_row = tmp_row + j ;
            plus_flag = false ; 
         }   
         
         if ( tmp_row < 0 )
            continue ; 
         else if (tmp_row >= row_num)
            continue ;  
         else
            actual_row = tmp_row ; 

         chip1_offset = chip1_offset - row_value[actual_row] ;

         after_place_value = place_row (block_chip_1[i] , actual_row , 1 ) ;
        // cout << 12345 << endl ;
        // cout << " row : " << j << " row_value : " << after_place_value << endl ;

         chip1_offset = chip1_offset +  after_place_value;

        // cout << " chip1_offset " << chip1_offset << endl ;
         if (!flag_exceed_row)
            counter ++ ;
         if (  (chip1_offset < best_cost) && !flag_exceed_row ){
            best_row  = actual_row ;
            best_cost = chip1_offset ;
            placed_cell_offset = difference (block_chip_1[i] -> get_y() , block_chip_1[i] -> get_final_y() ) + difference (block_chip_1[i] -> get_x() , block_chip_1[i] -> get_final_x() ) ;
            if ( placed_cell_offset < lower_bound_move_vertical  ){  // lower_bound
              lower_bound_flag = true ; 
            }
         }

         chip1_offset = chip1_offset - after_place_value ;
         chip1_offset = chip1_offset + row_value[actual_row] ;
        // cout << placed_cell_offset << endl ; 
         if ( lower_bound_flag ){  // lower_bound
              break ;
         }
         //row_value[j] = 0 ;
     }

     //if ( actual_row - best_row > 10   || best_row - actual_row > 10){
     //  cout << "YES" << endl ;
     //}

     if (counter == 0 ) {
       redundant_vec_1.push_back(block_chip_1[i]) ;
     }else {
       chip1_offset          = chip1_offset - row_value[best_row] ;
       row_value[best_row]   = place_row (block_chip_1[i] , best_row , 0 ) ;
       chip1_offset = chip1_offset + row_value[best_row] ;
     }


  }

  /*
   for (unsigned int i=0 ; i < block_of_row.size() ; i++){
   cout << " row : " << i << endl ;
   for (unsigned int j=0 ; j < block_of_row[i].size() ; j++){
     cout << block_of_row[i][j] -> get_name() << " " << block_of_row[i][j] -> get_final_x() << " , " << block_of_row[i][j] -> get_final_y() << endl ;
   }
   cout << endl ;
 }
 */
//  cout << " ------ finish block_1 ------ "<< endl ;
  //cout << redundant_vec_1.size() << endl ;
  //total_offset = total_offset + chip1_offset ;

  bool do_again = false ;
  BLOCK* redundant = NULL ;

  while (redundant_vec_1.size() != 0){
     redundant = redundant_vec_1.back() ;
     redundant -> set_index(1) ;
     block_chip_2.push_back(redundant) ;
     redundant_vec_1.pop_back() ;
  }

  sort (block_chip_2.begin() , block_chip_2.end() , sort_value) ;
  //cell_num = 0 ;
  for ( int i=0 ; i < row_num ; i++ ){
    row_value[i] = 0 ;
    block_of_row[i].clear() ;
  }
 // cout << row_num << endl ;
  for ( unsigned int i=0 ; i < block_chip_2.size() ; i++ ){
  //   cout << i << endl ;
     best_cost = numeric_limits<double>::max() ;
     lower_bound_flag = false ; 
     plus_flag = false ;
     counter = 0 ;
     tmp_row = ( block_chip_2[i] -> get_y() ) / row_height ;
     for (int j=0 ; j < needed_row_num ; j++ ){
         
         if (plus_flag == false){
            tmp_row = tmp_row - j ;
            plus_flag = true ; 
         }else{
            tmp_row = tmp_row + j ;
            plus_flag = false ; 
         }   
         
         if ( tmp_row < 0 )
            continue ; 
         else if (tmp_row >= row_num)
            continue ;  
         else
            actual_row = tmp_row ; 
     
         chip2_offset = chip2_offset - row_value[actual_row] ;
         after_place_value = place_row (block_chip_2[i] , actual_row , 1 ) ;

     //    cout << " row : " << j << " row_value : " << after_place_value << endl ;

         chip2_offset = chip2_offset +  after_place_value;

//         cout << " chip2_offset " << chip2_offset << endl ;

         if (!flag_exceed_row)
           counter++ ;

         if ( (chip2_offset < best_cost) &&  !flag_exceed_row ){
            best_row  = actual_row ;
            best_cost = chip2_offset ;

         placed_cell_offset = difference (block_chip_2[i] -> get_y() , block_chip_2[i] -> get_final_y() ) + difference (block_chip_2[i] -> get_x() , block_chip_2[i] -> get_final_x() ) ; 
            if ( placed_cell_offset < lower_bound_move_vertical  ){  // lower_bound
              lower_bound_flag = true ; 
            }
         }
         chip2_offset = chip2_offset - after_place_value ;
         chip2_offset = chip2_offset + row_value[actual_row] ;
         if (lower_bound_flag){  // lower_bound
              break ;
         }
         //row_value[j] = 0 ;
     }


     if (counter == 0){
       redundant_vec_2.push_back( block_chip_2[i] ) ;
     }else {
       chip2_offset          = chip2_offset - row_value[best_row] ;
       row_value[best_row]   = place_row (block_chip_2[i] , best_row , 0 ) ;
       chip2_offset = chip2_offset + row_value[best_row] ;
     }

  }
   /*
     for (int i=0 ; i < block_of_row.size() ; i++){
       cout << " row : " << i << " size : " <<  block_of_row[i].size()  <<  endl ;
       for (int j=0 ; j < block_of_row[i].size() ; j++){
         cout << block_of_row[i][j] -> get_name() << " " << block_of_row[i][j] -> get_final_x() << " , " << block_of_row[i][j] -> get_final_y() << endl ;
       }
       cout << endl ;
     }  */

  //cout << redundant_vec_2.size() << endl ;
  while (redundant_vec_2.size() != 0){
     redundant = redundant_vec_2.back() ;
     redundant -> set_index(0) ;
     block_chip_1.push_back(redundant) ;
     redundant_vec_2.pop_back() ;
     do_again = true ;
  }

  if (do_again){

     sort (block_chip_1.begin() , block_chip_1.end() , sort_value) ;
     for ( int i=0 ; i < row_num ; i++ ){
        row_value[i] = 0 ;
        block_of_row[i].clear() ;
      }
      chip1_offset = 0 ;
     for ( unsigned int i=0 ; i < block_chip_1.size() ; i++ ){
         best_cost = numeric_limits<double>::max() ;

         for (int j=0 ; j < row_num ; j++ ){
             chip1_offset = chip1_offset - row_value[j] ;

             after_place_value = place_row (block_chip_1[i] , j , 1 ) ;

             chip1_offset = chip1_offset +  after_place_value;

             if (  (chip1_offset < best_cost) && !flag_exceed_row ){
                best_row  = j ;
                best_cost = chip1_offset ;

                if (chip1_offset == 0 ){  // lower_bound
                  break ;
                }
             }

             chip1_offset = chip1_offset - after_place_value ;
             chip1_offset = chip1_offset + row_value[j] ;
         }
           chip1_offset          = chip1_offset - row_value[best_row] ;
           row_value[best_row]   = place_row (block_chip_1[i] , best_row , 0 ) ;
           chip1_offset = chip1_offset + row_value[best_row] ;



      }
  }

 // cout << " ------ finish block_2 ------ "<< endl ;
}
/*
void GRAPH::compute_chip2_overlap_area() {

   int area = 0 ;
  int A_x , A_xw , A_y , A_yh;
  int B_x , B_xw , B_y , B_yh;
  int overlap_x = 0 ;
  int overlap_y = 0 ;

  //cout << All_block.size() << endl;

  for (unsigned int i=0 ; i < block_chip_2.size()-1 ; i++){
    for (unsigned int j=i+1 ; j < block_chip_2.size() ; j++){
      //cout << i << " , " <<j<< endl ;
      //cout << " ============" << endl ;
      A_x  = block_chip_2[i] -> get_x() ;
      A_xw = block_chip_2[i] -> get_x() + block_chip_2[i] -> get_w() ;
      A_y  = block_chip_2[i] -> get_y() ;
      A_yh = block_chip_2[i] -> get_y() + block_chip_2[i] -> get_h() ;

      B_x  = block_chip_2[j] -> get_x() ;
      B_xw = block_chip_2[j] -> get_x() + block_chip_2[j] -> get_w() ;
      B_y  = block_chip_2[j] -> get_y() ;
      B_yh = block_chip_2[j] -> get_y() + block_chip_2[j] -> get_h() ;

      //cout << "A : " << A_x << " " << A_xw << " " << A_y << " " << A_yh << " "  << endl ;
      //cout << "B : " << B_x << " " << B_xw << " " << B_y << " " << B_yh << " "  << endl ;

      if (  B_x < A_xw && B_xw > A_x ){    // overlap_x
         if (B_x <= A_x){
             if (B_xw > A_xw)
               overlap_x = A_xw - A_x ;
             else
               overlap_x = B_xw - A_x ;
         }else {
             if (B_xw > A_xw)
               overlap_x = A_xw - B_x ;
             else
               overlap_x = B_xw - B_x ;
         }
      } else {
        overlap_x = 0 ;
      }

      if (  B_y < A_yh && B_yh > A_y ){    // overlap_x
         if (B_y <= A_y){
             if (B_yh > A_yh)
               overlap_y = A_yh - A_y ;
             else
               overlap_y = B_yh - A_y ;
         }else {
             if (B_yh > A_yh)
               overlap_y = A_yh - B_y ;
             else
               overlap_y = B_yh - B_y ;
         }
      } else {
        overlap_y = 0 ;
      }



       area = area + overlap_x * overlap_y ;
       //cout << area << endl ;
    }


  }

 // cout << "CHIP2 area : "<< area << endl ;
  //cout << "final_overlap area : "<< final_overlap << endl ;
  final_overlap = final_overlap + area ;


}*/
/*
void GRAPH::compute_chip1_overlap_area() {

  int area = 0 ;
  int A_x , A_xw , A_y , A_yh;
  int B_x , B_xw , B_y , B_yh;
  int overlap_x = 0 ;
  int overlap_y = 0 ;

  //cout << All_block.size() << endl;

  for (unsigned int i=0 ; i < block_chip_1.size()-1 ; i++){
    for (unsigned int j=i+1 ; j < block_chip_1.size() ; j++){
      //cout << i << " , " <<j<< endl ;
      //cout << " ============" << endl ;
      A_x  = block_chip_1[i] -> get_x() ;
      A_xw = block_chip_1[i] -> get_x() + block_chip_1[i] -> get_w() ;
      A_y  = block_chip_1[i] -> get_y() ;
      A_yh = block_chip_1[i] -> get_y() + block_chip_1[i] -> get_h() ;

      B_x  = block_chip_1[j] -> get_x() ;
      B_xw = block_chip_1[j] -> get_x() + block_chip_1[j] -> get_w() ;
      B_y  = block_chip_1[j] -> get_y() ;
      B_yh = block_chip_1[j] -> get_y() + block_chip_1[j] -> get_h() ;

      //cout << "A : " << A_x << " " << A_xw << " " << A_y << " " << A_yh << " "  << endl ;
      //cout << "B : " << B_x << " " << B_xw << " " << B_y << " " << B_yh << " "  << endl ;

      if (  B_x < A_xw && B_xw > A_x ){    // overlap_x
         if (B_x <= A_x){
             if (B_xw > A_xw)
               overlap_x = A_xw - A_x ;
             else
               overlap_x = B_xw - A_x ;
         }else {
             if (B_xw > A_xw)
               overlap_x = A_xw - B_x ;
             else
               overlap_x = B_xw - B_x ;
         }
      }else {
         overlap_x = 0 ;
      }

      if (  B_y < A_yh && B_yh > A_y ){    // overlap_x
         if (B_y <= A_y){
             if (B_yh > A_yh)
               overlap_y = A_yh - A_y ;
             else
               overlap_y = B_yh - A_y ;
         }else {
             if (B_yh > A_yh)
               overlap_y = A_yh - B_y ;
             else
               overlap_y = B_yh - B_y ;
         }
      } else {
         overlap_y = 0 ;
      }



       area = area + overlap_x * overlap_y ;
       //cout << area << endl ;
    }


  }

  //cout << "CHIP1 area : "<< area << endl;
  //cout << "final_overlap area : "<< final_overlap << endl;
  final_overlap = final_overlap + area ;

}
*/
//int GRAPH::check_overlap(BLOCK* b1 , BLOCK* b2 ) {
int GRAPH::check_overlap(int one_x , int one_w  , int one_y  , int one_h   , int two_x , int two_w , int two_y , int two_h    ) {
  int area = 0 ;
  int A_x , A_xw , A_y , A_yh;
  int B_x , B_xw , B_y , B_yh;
  int overlap_x = 0 ;
  int overlap_y = 0 ;

  A_x  = one_x ;
  A_xw = one_x + one_w ;
  A_y  = one_y ;
  A_yh = one_y + one_h ;

  B_x  = two_x ;
  B_xw = two_x + two_w ;
  B_y  = two_y ;
  B_yh = two_y + two_h ;

      if (  B_x < A_xw && B_xw > A_x ){    // overlap_x
         if (B_x <= A_x){
             if (B_xw > A_xw)
               overlap_x = A_xw - A_x ;
             else
               overlap_x = B_xw - A_x ;
         }else {
             if (B_xw > A_xw)
               overlap_x = A_xw - B_x ;
             else
               overlap_x = B_xw - B_x ;
         }
      }else{
        overlap_x = 0 ;
        return 0 ; 
      }

      if (  B_y < A_yh && B_yh > A_y ){    // overlap_y
         if (B_y <= A_y){
             if (B_yh > A_yh)
               overlap_y = A_yh - A_y ; 
             else
               overlap_y = B_yh - A_y ;
         }else {
             if (B_yh > A_yh)
               overlap_y = A_yh - B_y ;
             else
               overlap_y = B_yh - B_y ;
         }
      } else  {
        overlap_y = 0 ;
        return 0 ; 
      }

  area = overlap_x * overlap_y ;



  return area ;
}

void GRAPH::compute_init_overlap_area() {

  int area = 0 ;
  int A_x , A_xw , A_y , A_yh;
  int B_x , B_xw , B_y , B_yh;
  int overlap_x = 0 ;
  int overlap_y = 0 ;
  final_overlap = 0 ;
  //cout << All_block.size() << endl;

  for (unsigned int i=0 ; i < All_block.size()-1 ; i++){
    for (unsigned int j=i+1 ; j < All_block.size() ; j++){
      //cout << i << " , " <<j<< endl ;
      //cout << " ============" << endl ;
      A_x  = All_block[i] -> get_x() ;
      A_xw = All_block[i] -> get_x() + All_block[i] -> get_w() ;
      A_y  = All_block[i] -> get_y() ;
      A_yh = All_block[i] -> get_y() + All_block[i] -> get_h() ;

      B_x  = All_block[j] -> get_x() ;
      B_xw = All_block[j] -> get_x() + All_block[j] -> get_w() ;
      B_y  = All_block[j] -> get_y() ;
      B_yh = All_block[j] -> get_y() + All_block[j] -> get_h() ;

      //cout << "A : " << A_x << " " << A_xw << " " << A_y << " " << A_yh << " "  << endl ;
      //cout << "B : " << B_x << " " << B_xw << " " << B_y << " " << B_yh << " "  << endl ;

      if (  B_x < A_xw && B_xw > A_x ){    // overlap_x
         if (B_x <= A_x){
             if (B_xw > A_xw)
               overlap_x = A_xw - A_x ;
             else
               overlap_x = B_xw - A_x ;
         }else {
             if (B_xw > A_xw)
               overlap_x = A_xw - B_x ;
             else
               overlap_x = B_xw - B_x ;
         }
      }else{
        overlap_x = 0 ;
      }

      if (  B_y < A_yh && B_yh > A_y ){    // overlap_y
         if (B_y <= A_y){
             if (B_yh > A_yh)
               overlap_y = A_yh - A_y ;
             else
               overlap_y = B_yh - A_y ;
         }else {
             if (B_yh > A_yh)
               overlap_y = A_yh - B_y ;
             else
               overlap_y = B_yh - B_y ;
         }
      } else  {
        overlap_y = 0 ;
      }

       area = area + overlap_x * overlap_y ;
       //cout << "area      : " << area << endl ;
       //cout << "overlap_x : " << overlap_x << endl ;
       //cout << "overlap_y : " << overlap_y << endl ;
    }


  }
 /*
  for (unsigned int i=0 ; i< All_block.size() ; i++){
    cout << All_block[i] -> get_name() << " " << All_block[i] -> get_x() << " " << All_block[i] -> get_y() << " " << All_block[i] -> get_w() << " " << All_block[i] -> get_h() << " " << All_block[i] -> get_index() << " " << endl ;

  }
  */
  original_overlap = area ;

}






void GRAPH::set_all_block(ifstream& block_file)  {

  string Title ;
  int block_num ;
  block_file >> Title ;
  block_file >> block_num ;

  string name ;
  int x , y, w , h ;
  BLOCK* block ;

  Overlap_graph.reserve(block_num) ;

  vector<OVERLAP* > overlap_vec ;
  //overlap_vec.reserve(block_num) ; 

  //int half_num = block_num / 2;
  bool one_flag = false ; 
  for (int i=0 ; i < block_num ; i++ ) {
     block_file >> name ;
     block_file >> x ;
     block_file >> y ;
     block_file >> w ;
     block_file >> h ;

     Overlap_graph.push_back(overlap_vec) ;
     //Overlap_graph[i].reserve(block_num) ; 
    // Overlap_area_vec.push_back(0) ;
    // Actually_overlap.push_back(0) ;
     block = new BLOCK(name ,i, x, y, w, h) ;
     if (i > 150000 ){
        if (one_flag){
          block -> set_index(1) ;
          one_flag = false ; 
        } else {
          one_flag = true ;
        }
     }
     All_block.push_back (block) ;
  }

  //for (unsigned int i=0 ; i< All_block.size() ; i++){
  //  cout << All_block[i] -> get_name() << " " << All_block[i] -> get_x() << " " << All_block[i] -> get_y() << " " << endl ;
  //}

}




void GRAPH::set_all_terminal(ifstream& terminal_file) {


  string Title ;
  int terminal_num ;
  terminal_file >> Title ;
  terminal_file >> terminal_num ;

  string name ;
  int x , y, w , h ;

  for (int i=0 ; i < terminal_num ; i++ ) {
     terminal_file >> name ;
     terminal_file >> x ;
     terminal_file >> y ;
     terminal_file >> w ;
     terminal_file >> h ;

     TERMINAL* Terminal = new TERMINAL(name , x, y, w, h) ;
     All_terminal.push_back (Terminal) ;
  }

  //for (unsigned int i=0 ; i< All_terminal.size() ; i++){
  //  cout << All_terminal[i] -> get_name() << " " << All_terminal[i] -> get_x() << " " << All_terminal[i] -> get_y() << " " << endl ;
  //}

}

void GRAPH::write_output_file (ofstream& output_file) {

   for (unsigned int i=0 ; i< All_block.size() ; i++){
    output_file << All_block[i] -> get_name() << " " << All_block[i] -> get_final_x() << " " << All_block[i] -> get_final_y() << " " << All_block[i] -> get_index() << endl ;
 //   cout << All_block[i] -> get_name() << endl ;
 //   cout << All_block[i] -> get_final_x() << " " << All_block[i] -> get_final_y() << " " << All_block[i] -> get_index() << " " << endl ;
 //   cout << All_block[i] -> get_x() << " " << All_block[i] -> get_y() << " " << All_block[i] -> get_index() << " " << endl ;
 //   cout << endl ;
  }

  /*
  for (int i=0 ; i< row_num; i++){
     cout << i << " row " << endl ;
      for (unsigned int j=0 ; j< row_of_row[i].size() ; j++){
        cout << row_of_row[i][j] -> get_x1() << " , " << row_of_row[i][j] -> get_x2() << endl ;
      }
  }
  */

}
