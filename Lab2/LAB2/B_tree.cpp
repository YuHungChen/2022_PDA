#include "B_tree.h"
#include "terminal.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <random>
using namespace std ;

// ======== public function ===========
//
//
//int a = 0 ;

void B_TREE::Random_construct_tree(TreeNode* new_child  ){    //

   // for (unsigned i=0 ; i<3 ; i++){
 //       cout << int (2.0*(rand() / (RAND_MAX +1.0)))   ;

  //  }
    //cout << endl ;

    TreeNode* Tptr = root  ;

    int random_num ;

    if (All_tree_node.empty() )
        All_tree_node.push_back(root) ;

    All_tree_node.push_back(new_child) ;

    while (true){
        random_num = int (2.0*(rand() / (RAND_MAX +1.0))) ;
        if (random_num == 0){
            if (Tptr -> get_Lnode() != NULL)
                Tptr = Tptr -> get_Lnode() ;
            else{
                Tptr -> set_Lnode(new_child) ;
                new_child -> set_Parent(Tptr) ;
                break ;
            }
        }else {
            if (Tptr -> get_Rnode() != NULL)
                Tptr = Tptr -> get_Rnode() ;
            else{
                Tptr -> set_Rnode(new_child) ;
                new_child -> set_Parent(Tptr) ;
                break ;
            }
        }

    }

}
/*
void B_TREE::Simulated_Annealing(){

    // if x axis exceed boundary


   int random_num , num_2  , num_2_2,  num_3 , num_4 ;
   //TreeNode* new_child    ;
   TreeNode* delete_child = NULL  ;
   TreeNode* rotate_n   = NULL;
   TreeNode* switch_n_1   = NULL;
   TreeNode* switch_n_2   = NULL;
   TreeNode* insert_n   = NULL;
   //TreeNode* temp = NULL ;
    bool flag = false  ;

    int a = 0 ;

    while (true){
       // flag = false ;
        // perturb until x of each block is legal ( < border_x )

        while ( true){

            delete_child = set_each_block_x() ;
            if ( delete_child == NULL ){
                break ;
            }else{
                while ( (delete_child -> get_Lnode() != NULL) && (delete_child -> get_Rnode() != NULL)  ){
                    delete_child = delete_child -> get_Lnode() ;
                }
            }

            random_num = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
             num_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
             num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
             while (num_2_2 == num_2)
                 num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;


             num_4 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
             while (All_tree_node[num_4] == delete_child  ) {
                    num_4 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
             }
            rotate_n = All_tree_node[random_num]  ;
            switch_n_1 = All_tree_node[num_2] ;
            switch_n_2 = All_tree_node[num_2_2]  ;
            insert_n     =  All_tree_node[num_4] ;


            rotate_node( rotate_n ) ;
            switch_node( switch_n_1  , switch_n_2 ) ;
            delete_node( delete_child  ) ;
            insert_node( insert_n , delete_child ) ;



               cout << "===============rotate_n  : ==========" << rotate_n -> get_Name() << endl ;
               cout << "===============switch_n1  : ==========" << switch_n_1 -> get_Name() <<endl ;
               cout << "===============switch_n2  : ==========" << switch_n_2 -> get_Name() <<endl ;
               cout << "===============delete_n  : ==========" << delete_child -> get_Name() <<endl ;
               cout << "===============insert_n  : ==========" << insert_n -> get_Name()  << endl ;


               for (unsigned int i =0 ; i< All_tree_node.size() ; i++){
                    cout << setw(10) << All_tree_node[i] -> get_Name() << " x : " << setw(5)  <<  All_tree_node[i] -> get_x()  << " y : " << setw(5)  <<  All_tree_node[i] -> get_y()  << " : " << setw(5)  <<  All_tree_node[i] -> get_w() << "," << setw(3) << All_tree_node[i] -> get_h() ;
                    if (All_tree_node[i] -> get_Lnode() != NULL)
                        cout  <<"   Left  : " << setw(10) <<  All_tree_node[i] -> get_Lnode() -> get_Name() ;
                    else {
                         cout <<"   Left  : " << setw(10) << "NULL"  ;
                    }
                    if (All_tree_node[i] -> get_Rnode() != NULL)
                        cout  << "    Right : " << setw(10) <<  All_tree_node[i] -> get_Rnode() -> get_Name() ;
                    else
                        cout  << "    Right : "<< setw(10) << "NULL"  ;

                    if (All_tree_node[i] -> get_Parent() != NULL)
                        cout  << "    Parent : " << setw(10) <<  All_tree_node[i] -> get_Parent() -> get_Name() ;
                    else
                        cout  << "    Parent : "<< setw(10) << "NULL"  ;

                    cout << endl ;
                }
               cout << "=================================" << endl ;
               cout << "=================================" << endl ;

        }
        //break ;

        // perturb until y  of each block is legal ( < border_x )


         random_num = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (num_2_2 == num_2)
             num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;

         num_3 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (    (All_tree_node[num_3] -> get_Lnode() != NULL  && All_tree_node[num_3] -> get_Rnode() != NULL  ) ||  All_tree_node[num_3] == root )
            num_3 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;

         num_4 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (num_4 == num_3     ) {
                num_4 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         }
            rotate_n = All_tree_node[random_num]  ;
            switch_n_1 = All_tree_node[num_2] ;
            switch_n_2 = All_tree_node[num_2_2]  ;
            delete_child =  All_tree_node[num_3] ;
            insert_n     =  All_tree_node[num_4] ;



        flag = compute_y() ;

        if ( flag ){
            rotate_node( rotate_n ) ;
            cout << 22<< endl ;
            switch_node( switch_n_1  , switch_n_2   ) ;
            cout << 22<< endl ;
            delete_node( delete_child  ) ;
            cout << 22<< endl ;
            insert_node( insert_n  , delete_child  ) ;
            cout << 22<< endl ;
            
            cout << "===============rotate_n  : ==========" << rotate_n -> get_Name() << endl ;
             cout << "===============switch_n1  : ==========" << switch_n_1 -> get_Name() <<endl ;
             cout << "===============switch_n2  : ==========" << switch_n_2 -> get_Name() <<endl ;
             cout << "===============delete_n  : ==========" << delete_child -> get_Name() <<endl ;
             cout << "===============insert_n  : ==========" << insert_n -> get_Name()  << endl ;
             cout << "==============after_YY===================" << endl ;
            for (unsigned int i =0 ; i< All_tree_node.size() ; i++){
                    cout << setw(10) << All_tree_node[i] -> get_Name() << " x : " << setw(5)  <<  All_tree_node[i] -> get_x()  << " y : " << setw(5)  <<  All_tree_node[i] -> get_y()  << " : " << setw(5)  <<  All_tree_node[i] -> get_w() << "," << setw(3) << All_tree_node[i] -> get_h() ;
                    if (All_tree_node[i] -> get_Lnode() != NULL)
                        cout  <<"   Left  : " << setw(10) <<  All_tree_node[i] -> get_Lnode() -> get_Name() ;
                    else {
                         cout <<"   Left  : " << setw(10) << "NULL"  ;
                    }
                    if (All_tree_node[i] -> get_Rnode() != NULL)
                        cout  << "    Right : " << setw(10) <<  All_tree_node[i] -> get_Rnode() -> get_Name() ;
                    else
                        cout  << "    Right : "<< setw(10) << "NULL"  ;

                    if (All_tree_node[i] -> get_Parent() != NULL)
                        cout  << "    Parent : " << setw(10) <<  All_tree_node[i] -> get_Parent() -> get_Name() ;
                    else
                        cout  << "    Parent : "<< setw(10) << "NULL"  ;

                    cout << endl ;
                }
               cout << "=================================" << endl ;
               cout << "=================================" << endl ;

            //All_tree_node[num_2_2]  = switch_n_1 ;
            //All_tree_node[num_2]    = switch_n_2 ;
        }else{

            break ;
        }




        a++ ;
        //cout << " times : " << a << endl ;
        if (a==100)
         break ;

    }

}*/


void B_TREE::Simulated_Annealing_2 ( )  {
    double T = 1000.0 ;
    double R = 0.9 ; 
    double choose_possibility = 0.0 ;
    bool delete_is_left ; 
    bool child_is_left ; 
    int new_cost_value = 0 ; 
    clock_t time_init, time_end;
    time_init = clock();
//    int old_area = 0 ;
  //  int old_HPWL = 0 ;
  //  int old_width = 0 ;
  //  int old_height = 0 ;
    
    int delta = 0 ;  
    int step = 4000 ; 
    //if(all_net_name.size() <10)
    //    step = 2000 ; 
  //  else if (all_net_name.size() <100)
  //      step = 750  ; 
        
    int num_1 , num_2  , num_2_2,  num_3 , num_4 ;
    int reject_number = 0 ; 
    bool exceed_x ;
    bool exceed_y ; 
    bool flag = false ; 
    
    TreeNode* delete_child  = NULL ;
    TreeNode* delete_parent = NULL ;
    TreeNode* rotate_n      = NULL ;
    TreeNode* switch_n_1    = NULL ;
    TreeNode* switch_n_2    = NULL ;
    TreeNode* insert_n      = NULL ;
 //   TreeNode* temp         = NULL ;
 
    // random value 
    std::random_device rd ;   // to get the random seed 
    std::mt19937 gen(rd()) ; 
    std::uniform_real_distribution <double> random_value(0.0,1.0) ; 
   
    exceed_x = set_each_block_x() ; 
    exceed_y = compute_y() ; 
    //compute_HPWL( ) ; 
    
    
    // first compact to the fixed floorplan
    //cost = 
    
    
    int exceed_distance = 0 ;
    if (exceed_x && exceed_y)
        exceed_distance = (  ( width - Border_x    ) * ( width - Border_x    ) +  (height - Border_y) * (height - Border_y) ) ;   
    else if (exceed_x)
        exceed_distance = (  ( width - Border_x    ) * ( width - Border_x    ) ) ; 
    else if (exceed_y)
        exceed_distance = (  ( height - Border_y   ) * (height - Border_y) ) ; 
    else 
        exceed_distance = 0 ;
    
    int new_exceed_distance = 0   ; 
    double total_time = 0 ; 
    
    while ( new_exceed_distance > -40 ){
        time_end = clock() ; 
        total_time = double(time_end - time_init) / ( CLOCKS_PER_SEC) ; 
        if (total_time > 150.0  &&  new_exceed_distance < 0 ){
          //cout << "exceed : " << total_time << endl ;
          break ; 
        } 
        
        for (int i=0 ; i< step ; i++) {
         num_1   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_2   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_3   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_4   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (num_2_2 == num_2)
             num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (    (All_tree_node[num_3] -> get_Lnode() != NULL  && All_tree_node[num_3] -> get_Rnode() != NULL  ) ||  All_tree_node[num_3] == root )
             num_3  = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (num_4 == num_3     ) {
                num_4 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         }
         rotate_n     =  All_tree_node[num_1  ] ;
         switch_n_1   =  All_tree_node[num_2  ] ;
         switch_n_2   =  All_tree_node[num_2_2] ;
         delete_child =  All_tree_node[num_3  ] ;
         delete_parent  = delete_child -> get_Parent() ; 
         delete_is_left =  (delete_parent -> get_Lnode() == delete_child) ; 
         child_is_left  =  (delete_child  -> get_Lnode() != NULL ) ;  
         insert_n       =  All_tree_node[num_4  ] ;
         
         rotate_node( rotate_n ) ;
         switch_node( switch_n_1  , switch_n_2   ) ;
         delete_node( delete_child  ) ;
         insert_node( insert_n  , delete_child  ) ;
         
         if (reject_number > 3000){
           reject_number = 0; 
           flag = true ; 
           continue ; 
         }
          
         exceed_x = set_each_block_x() ;
         exceed_y = compute_y() ; 
    
       
          if (exceed_x && exceed_y)
              new_exceed_distance = (  ( width - Border_x    ) * ( width - Border_x    ) +  (height - Border_y) * (height - Border_y) ) ;   
          else if (exceed_x)
              new_exceed_distance = (  ( width - Border_x    ) * ( width - Border_x    ) ) ; 
          else if (exceed_y)
              new_exceed_distance = (  ( height - Border_y   ) * (height - Border_y) ) ; 
          else {
              new_exceed_distance  = (  ( width - Border_x    ) +  (height - Border_y) ) ; 
              if (new_exceed_distance < -40 )
                 break  ; 
          }
          /*
          cout << "exceed_x" << exceed_x << endl ; 
          cout << "exceed_y" << exceed_y << endl ; 
          cout << "height" << height << endl ; 
          cout << "width" << width << endl ; 
          cout << "Border_x" << Border_x << endl ; 
          cout << "Border_y" << Border_y << endl ; 
*/              
          if (new_exceed_distance < exceed_distance){
             exceed_distance = new_exceed_distance ; 
             reject_number = 0 ;
          }else{
             delta = new_exceed_distance - exceed_distance ; 
             choose_possibility = exp( -delta / T ) ;  
          //   cout << "choose_possibility : " << choose_possibility << endl ;
            if (flag){
              exceed_distance = new_exceed_distance ;  
              flag = false ; 
            }else if ( random_value(gen) > choose_possibility ) {  // reject 
               Restore(  rotate_n , switch_n_1 ,  switch_n_2 ,  delete_child ,  delete_parent , delete_is_left , child_is_left) ; 
               reject_number ++ ; 
            }else{
              exceed_distance = new_exceed_distance ;  
              reject_number = 0 ;
            }
          }
       //   cout << " exceed_distance : " << exceed_distance << endl ; 
       //    cout << " new_exceed_distance : " << new_exceed_distance << endl ; 
       //   cout << "T : " << T << endl ;
        }
          T = T * R ; 
          
     //     cout << "T : " << T << endl ;
    }
         
    //cout << "T : " << T << endl ;
        
    // then find better performance
    exceed_x = set_each_block_x() ;
    exceed_y = compute_y() ; 
    construct_map() ; 
    compute_HPWL( ) ; 
    cost  =  int( alpha * area + (1.0 - alpha ) * HPWL ) ; 
    reject_number = 0 ;
    if ( total_time > 235.0)
        T = 0.1 ; 
    else  
        T = 1000 ; 
   // cout << "initial_cost   : " << cost     << endl ; 
   // cout << "initial_height : " << height     << endl ; 
   // cout << "initial_width  : " << width     << endl ; 
   // cout << "new_exceed_distance  : " << new_exceed_distance     << endl ; 
    //int initial_cost = cost ; 
   // int initial_height = height ; 
   // int initial_width = width ; 
    
    while ( T > 0.1){
      
      for (int i=0 ; i< step ; i++) {
         time_end = clock() ; 
         total_time = double(time_end - time_init) / ( CLOCKS_PER_SEC) ; 
         if (total_time > 240.0)
            break ; 
          // random number ; 
         num_1   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_2   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_3   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         num_4   = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (num_2_2 == num_2)
             num_2_2 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (    (All_tree_node[num_3] -> get_Lnode() != NULL  && All_tree_node[num_3] -> get_Rnode() != NULL  ) ||  All_tree_node[num_3] == root )
             num_3  = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         while (num_4 == num_3     ) {
                num_4 = int ( All_tree_node.size() *(rand() / (RAND_MAX +1.0))) ;
         }
         
         rotate_n     =  All_tree_node[num_1  ] ;
         switch_n_1   =  All_tree_node[num_2  ] ;
         switch_n_2   =  All_tree_node[num_2_2] ;
         delete_child =  All_tree_node[num_3  ] ;
         delete_parent  = delete_child -> get_Parent() ; 
         delete_is_left =  (delete_parent -> get_Lnode() == delete_child) ; 
         child_is_left  =  (delete_child  -> get_Lnode() != NULL ) ;  
         insert_n       =  All_tree_node[num_4  ] ;
         
         /*
               cout << "====================before=============" << endl ;
         for (unsigned int i =0 ; i< All_tree_node.size() ; i++){
                    cout << setw(10) << All_tree_node[i] -> get_Name() << " x : " << setw(5)  <<  All_tree_node[i] -> get_x()  << " y : " << setw(5)  <<  All_tree_node[i] -> get_y()  << " : " << setw(5)  <<  All_tree_node[i] -> get_w() << "," << setw(3) << All_tree_node[i] -> get_h() ;
                    if (All_tree_node[i] -> get_Lnode() != NULL)
                        cout  <<"   Left  : " << setw(10) <<  All_tree_node[i] -> get_Lnode() -> get_Name() ;
                    else {
                         cout <<"   Left  : " << setw(10) << "NULL"  ;
                    }
                    if (All_tree_node[i] -> get_Rnode() != NULL)
                        cout  << "    Right : " << setw(10) <<  All_tree_node[i] -> get_Rnode() -> get_Name() ;
                    else
                        cout  << "    Right : "<< setw(10) << "NULL"  ;

                    if (All_tree_node[i] -> get_Parent() != NULL)
                        cout  << "    Parent : " << setw(10) <<  All_tree_node[i] -> get_Parent() -> get_Name() ;
                    else
                        cout  << "    Parent : "<< setw(10) << "NULL"  ;

                    cout << endl ;
                }
               cout << "=================================" << endl ;
               */
         rotate_node( rotate_n ) ;
         switch_node( switch_n_1  , switch_n_2   ) ;
         delete_node( delete_child  ) ;
         insert_node( insert_n  , delete_child  ) ;
         /*
         cout << "===============rotate_n  : ==========" << rotate_n -> get_Name() << endl ;
             cout << "===============switch_n1  : ==========" << switch_n_1 -> get_Name() <<endl ;
             cout << "===============switch_n2  : ==========" << switch_n_2 -> get_Name() <<endl ;
             cout << "===============delete_n  : ==========" << delete_child -> get_Name() <<endl ;
             cout << "===============insert_n  : ==========" << insert_n -> get_Name()  << endl ;
               */
         exceed_x = set_each_block_x() ;
         exceed_y = compute_y() ; 
         construct_map() ; 
         compute_HPWL(  ) ; 
         new_exceed_distance  = (  ( width - Border_x    ) +  (height - Border_y) ) ; 

         new_cost_value =  int ( alpha * area + (1 - alpha ) * HPWL  )  ; 
        // cout << "1 - alpha " << (1 - alpha) << endl ;
       //  cout << "new_new : "<< new_cost_value << endl ; 
         if ( exceed_x || exceed_y){
               Restore(  rotate_n , switch_n_1 ,  switch_n_2 ,  delete_child ,  delete_parent , delete_is_left , child_is_left) ; 
               reject_number ++ ;
         }else if (new_cost_value < cost) {
            cost = new_cost_value ; 
            reject_number = 0 ; 
            T = 1000 ; 
         } else {
            delta = new_cost_value - cost ; 
            choose_possibility = exp( -delta / (T) )  ; 
           // cout << "choose_possibility : " << choose_possibility << endl ; 
            
            if ( (random_value(gen) > choose_possibility) || new_exceed_distance > -50 ) {  // reject 
            // restoration 
            reject_number ++ ; 
            Restore(  rotate_n , switch_n_1 ,  switch_n_2 ,  delete_child ,  delete_parent , delete_is_left , child_is_left) ; 

            }else{
            cost = new_cost_value ;  
            reject_number = 0 ;
            }
            //break ; 
         }
      
      }
      
       set_each_block_x() ;
       compute_y() ; 
       construct_map() ; 
       compute_HPWL(  ) ; 
       cost  =  int ( alpha * area + (1 - alpha ) * HPWL ) ; 
       /*
       cout << "====================finish=============" << endl ;
         for (unsigned int i =0 ; i< All_tree_node.size() ; i++){
                    cout << setw(10) << All_tree_node[i] -> get_Name() << " x : " << setw(5)  <<  All_tree_node[i] -> get_x()  << " y : " << setw(5)  <<  All_tree_node[i] -> get_y()  << " : " << setw(5)  <<  All_tree_node[i] -> get_w() << "," << setw(3) << All_tree_node[i] -> get_h() ;
                    if (All_tree_node[i] -> get_Lnode() != NULL)
                        cout  <<"   Left  : " << setw(10) <<  All_tree_node[i] -> get_Lnode() -> get_Name() ;
                    else {
                         cout <<"   Left  : " << setw(10) << "NULL"  ;
                    }
                    if (All_tree_node[i] -> get_Rnode() != NULL)
                        cout  << "    Right : " << setw(10) <<  All_tree_node[i] -> get_Rnode() -> get_Name() ;
                    else
                        cout  << "    Right : "<< setw(10) << "NULL"  ;

                    if (All_tree_node[i] -> get_Parent() != NULL)
                        cout  << "    Parent : " << setw(10) <<  All_tree_node[i] -> get_Parent() -> get_Name() ;
                    else
                        cout  << "    Parent : "<< setw(10) << "NULL"  ;

                    cout << endl ;
                }
               cout << "=================================" << endl ;
         */      
       //cout << "last_temp : " << T << endl ;  
       T = R * T ; 
      
     //  cout << "new_cost  : " << new_cost_value << endl ; 
     //  cout << "cost      : " << cost     << endl ; 
     //   if  ( (reject_number > 20000 )   ) 
     //     break ; 
       
    }
    
   // cout << "cost         : " << cost     << endl ; 
   //  cout << "now_temp  : " << T << endl ;
    // cout << "Reject number : " << reject_number << endl ;
   //  cout << "new_exceed_distance number : " << new_exceed_distance << endl ;
    /*
       cout << "height    : " << height << endl ;
       cout << "width     : " << width  << endl ;
       cout << "area      : " << area   << endl ;
       cout << "HPWL      : " << HPWL   << endl ;
       cout << "new_cost  : " << new_cost_value << endl ; 
       cout << "cost      : " << cost     << endl ; 
       cout << "initial_cost      : " << initial_cost     << endl ; 
       cout << "initial_height      : " << initial_height     << endl ; 
       cout << "initial_width      : " << initial_width     << endl ; 
       
      cout << "Reject number : " << reject_number << endl ;
      cout << "=================finish===============" << endl ;
      */
}

void B_TREE::Restore( TreeNode* rotate_n , TreeNode* switch_n_1 , TreeNode* switch_n_2 , TreeNode* delete_n , TreeNode* delete_parent , bool delete_is_left , bool child_is_left ){
    
    // from insert  
    TreeNode* Tptr  ; 
    Tptr = delete_n -> get_Parent() ; 
    if (Tptr -> get_Lnode() == delete_n){
        Tptr -> set_Lnode(delete_n -> get_Lnode() ) ; 
        if (delete_n -> get_Lnode() != NULL)
           delete_n -> get_Lnode() ->  set_Parent(Tptr) ; 
        
        delete_n -> set_Parent (NULL) ; 
        delete_n -> set_Lnode  (NULL) ;  
    }else{  // insert right
        Tptr -> set_Rnode(delete_n -> get_Rnode() ) ; 
        if (delete_n -> get_Rnode() != NULL)
           delete_n -> get_Rnode() -> set_Parent(Tptr) ; 
        
        delete_n -> set_Parent (NULL) ; 
        delete_n -> set_Rnode  (NULL) ;  
    }
 //   cout << "delete_n : " << delete_n -> get_Name() << endl ;
 //   cout << "delete_Parent  : " << delete_parent -> get_Name() << endl ;
 //   cout << "delete_is_left : " << delete_is_left  << endl ;
    // to delete node
    if (delete_is_left){
       Tptr = delete_parent -> get_Lnode() ; 
       if (Tptr != NULL)
         Tptr     -> set_Parent(delete_n) ; 
       
       if (child_is_left) 
          delete_n -> set_Lnode  (Tptr) ;
       else 
          delete_n -> set_Rnode  (Tptr) ;
          
       delete_n -> set_Parent (delete_parent) ; 
       
       delete_parent -> set_Lnode (delete_n) ; 
    }else {
       Tptr = delete_parent -> get_Rnode() ; 
       if (Tptr != NULL)
         Tptr     -> set_Parent(delete_n) ; 
       
       if (child_is_left) 
          delete_n -> set_Lnode  (Tptr) ;
       else 
          delete_n -> set_Rnode  (Tptr) ;
          
       delete_n -> set_Parent (delete_parent) ; 
       
       delete_parent -> set_Rnode (delete_n) ; 
    }
    
    // switch 
    switch_node( switch_n_1  , switch_n_2   ) ;
    
    // rotate 
    rotate_node( rotate_n ) ;
    
}



void B_TREE::insert_node (TreeNode* Insert_point , TreeNode* child ) {

    // The child will be constructed upon the Insert_point
    TreeNode* old_child ;

    int random_num = rand() % 2 ;
  //  cout << "RANDOM : " << random_num << endl ;
    //  set _child

    // if two nodes are both NULL . one NULL , zero NULL

    if ( !random_num ){  // insert to the left node
        old_child = Insert_point -> get_Lnode() ;

        Insert_point -> set_Lnode( child ) ;

        if (old_child != NULL){
            old_child -> set_Parent(child) ;
            child -> set_Lnode  (old_child) ;
        }
        child -> set_Parent (Insert_point) ;


    }else {
        old_child = Insert_point -> get_Rnode() ;

        Insert_point -> set_Rnode( child ) ;

        if (old_child != NULL){
            old_child -> set_Parent(child) ;
            child -> set_Rnode  (old_child) ;
        }

        child -> set_Parent (Insert_point) ;


    }



}

void B_TREE::delete_node ( TreeNode* child ) {
    // child's (# of child) should be zero

    TreeNode* parent = child -> get_Parent() ;

    if (child -> get_Lnode() == NULL && child -> get_Rnode() == NULL){

        if (parent -> get_Lnode() == child)
            parent -> set_Lnode(NULL) ;
        else
            parent -> set_Rnode(NULL) ;

        child -> set_Parent(NULL) ;

    }else if (child -> get_Lnode() == NULL){

        if (parent -> get_Lnode() == child)
            parent -> set_Lnode(child -> get_Rnode()) ;
        else
            parent -> set_Rnode(child -> get_Rnode()) ;

        child -> get_Rnode() -> set_Parent(parent) ;

        child -> set_Parent(NULL) ;
        child -> set_Rnode (NULL) ;


    }else {

        if (parent -> get_Lnode() == child)
            parent -> set_Lnode(child -> get_Lnode()) ;
        else
            parent -> set_Rnode(child -> get_Lnode()) ;

        child -> get_Lnode() -> set_Parent(parent) ;

        child -> set_Parent(NULL) ;
        child -> set_Lnode (NULL) ;

    }

}

void B_TREE::rotate_node ( TreeNode* one ){

    int temp ;
    temp = one -> get_w () ;
    one -> set_w (one -> get_h() ) ;
    one -> set_h (temp ) ;

}

void B_TREE::switch_node ( TreeNode* one , TreeNode* two ) {

   // TreeNode* node_parent ;
    string   name_two ;
    int      wh_two ;


    name_two = two -> get_Name() ;
    two -> set_Name (one -> get_Name() )  ;
    one -> set_Name (name_two) ;

    wh_two = two -> get_w() ;
    two -> set_w (one -> get_w() )  ;
    one -> set_w (wh_two) ;

    wh_two = two -> get_h() ;
    two -> set_h (one -> get_h() )  ;
    one -> set_h (wh_two) ;


}

bool B_TREE::compute_y(){

    bool exceed_y = false ;

    int a = 0 ;
    int b = 0 ;

    a = root -> get_w() ;
    b = root -> get_h() ;

    int* max_width  = &a ;
    int* max_height = &b ;

   // cout << " max_height : " << *max_height  << endl ;



    //int a =0 ; // debug
   // cout << "==============" << a << "=============" << endl ;
   // while (test != NULL){
  //      cout << test -> get_x () << "," << test -> get_y () << endl ;
  //      test = test -> get_next() ;
  //  }


    // delete contour first
  //  cout << "delete_start" << endl ;
    Contour* next_two ;
    Contour* delete_one ;
    Contour* delete_two ;
    Contour* delete_three ;



    next_two = head -> get_next() -> get_next() ;

    if (next_two != NULL){
   //  cout << " next_two : " <<  next_two -> get_x()    << " , " << next_two -> get_y() << endl ;
        next_two = next_two -> get_next() ;
    }
  //  cout << 11 << endl ;
  //  Contour* test = head ;
/*    while (test != NULL){
            cout << " Contour : " <<  test -> get_x()    << " , " << test -> get_y() << endl ;
            test = test -> get_next() ;
        }*/
    while (next_two != NULL ){
       // cout << " next_two : " <<  next_two -> get_x()    << " , " << next_two -> get_y() << endl ;

        delete_one = next_two -> get_prev() ;
        delete_two = next_two ;
        next_two = next_two -> get_next() ;

        delete_one -> get_prev() -> set_next(next_two) ;
        next_two -> set_prev (delete_one -> get_prev() ) ;
        next_two = next_two -> get_next() ;




    //    cout << " delete_one : " <<  delete_one -> get_x()    << " , " << delete_one -> get_y() << endl ;
    //    cout << " delete_two : " <<  delete_two -> get_x()    << " , " << delete_two -> get_y() << endl ;
        delete delete_one ;
       // delete_one = NULL ;
        delete delete_two ;
        //delete_two = NULL ;
    }

   // cout << 11 << endl ;

    next_two = head -> get_next() -> get_next() ;
    if (next_two != NULL) {
        delete_three = head -> get_next() ;
        head -> set_next(delete_three -> get_next() ) ;
        delete_three -> get_next() -> set_prev(head) ;
        delete delete_three ;
   // delete_one = NULL ;
    }
    
    //cout << " Contour : " <<  head -> get_x()    << " , " << head -> get_y() << endl ;
    //cout << " Contour : " <<  head -> get_next() -> get_x() << " , " << head -> get_next() -> get_y() << endl ;
    //cout <<  head -> get_next() -> get_next() << endl ;


    TreeNode* Tptr = root ;

    vector < TreeNode* > My_Q ;
    My_Q.clear() ;

    if (Tptr -> get_Rnode() != NULL){
            //cout << 11 << endl ;
            //cout << Tptr -> get_Rnode()  -> get_x () << "," << Tptr -> get_y () << endl ;
            My_Q.push_back(Tptr -> get_Rnode()) ;
        }

    if (root -> get_Lnode() != NULL){
        My_Q.push_back(root -> get_Lnode()) ;
    }

    contour_set_head() ;

    while (!My_Q.empty()){

        Tptr = My_Q.back() ;
      //  cout << Tptr -> get_x () << "," << Tptr -> get_y () << endl ;
       // cout << " max_height : " << *max_height  << endl ;
        contour_setting_right(Tptr , *max_width , *max_height) ;
       // cout << " max_height : " << *max_height  << endl ;
        //cout << "123456" << endl ;

        My_Q.pop_back() ;
        if (Tptr -> get_Rnode() != NULL){
            My_Q.push_back(Tptr -> get_Rnode()) ;
        }
        if (Tptr -> get_Lnode() != NULL){
            My_Q.push_back(Tptr -> get_Lnode()) ;
        }

        if (*max_height > Border_y){
            exceed_y = true ;
         //   cout << " max_height: " << *max_height << endl ;
            //break ;
        }
            // for debug ;

       // cout << "==============" << a << "=============" << endl ;
       // cout << "==============" << b << "=============" << endl ;
      //   cout << "out " << endl ;
       // while (test != NULL){
        //    cout << test -> get_x () << "," << test -> get_y () << endl ;
        //    test = test -> get_next() ;
       // }
    }
    width  = *max_width  ; 
    height = *max_height ; 
    area = (*max_width) * (*max_height) ; 


    //cout << "exceed_y : " << exceed_y << endl ;

    return exceed_y ;
}

void B_TREE::Print_block(){

    //TreeNode* Test;






  //  switch_node(All_tree_node[1], All_tree_node[5] ) ;


    // LEVEL_order

    vector <int>       order ;
    vector <TreeNode*> test ;

    test.push_back(root) ;
    order.push_back(0) ;

    TreeNode* one ;
    int  order_1 ;
    int Last_order = 0 ;
  //  cout << "=================================" << endl ;
  //  cout << "order : " << Last_order << endl ;
  //  cout << "=================================" << endl ;
    while(!test.empty()){

        one = test.front() ;
        test.erase(test.begin() ) ;
        order_1 = order.front() ;
        order.erase(order.begin()) ;

        if (one -> get_Lnode() != NULL){
            test.push_back(one -> get_Lnode()) ;
            order.push_back(order_1 + 1 ) ;
        }

        if (one -> get_Rnode() != NULL){
            test.push_back(one -> get_Rnode()) ;
            order.push_back(order_1 + 1 ) ;
        }

        if (Last_order != order_1) {
            Last_order = order_1 ;
          //  cout << "=================================" << endl ;
          //  cout << "order : " << Last_order << endl ;
           // cout << "=================================" << endl ;
        }

       // cout << one -> get_Name()  << " : " << one -> get_x()  << " , "<<one -> get_y() <<   endl ;

    }
    /*
    for (unsigned int i =1 ; i< All_tree_node.size() ; i++){
        cout << All_tree_node[i] -> get_Name()  << " : " << All_tree_node[i] -> get_x() -> <<   endl ;
        //cout << "Parent : " << All_tree_node[i] -> get_Parent() -> get_Name() << endl ;
    }*/

}

bool B_TREE::set_each_block_x(){

    TreeNode* Test;
    int new_x = 0 ;
    bool exceeded = false ;
   // All_tree_node.clear() ;
    vector < TreeNode* > My_Q ;

    My_Q.push_back(root) ;

    root -> set_x(0) ;
    int a = 0 ; 
    while (!My_Q.empty()){
        a ++ ; 
        //cout << 22<< endl ;
        Test = My_Q.back() ;
        My_Q.pop_back() ;

        new_x = Test -> get_x() + Test -> get_w () ;
       // cout << "Name : " << setw(10) << Test -> get_Name() << " new_x : " << new_x << endl ;
        //cout << Test-> get_Name() << " :  " << Test -> get_x() << endl ;
        if (new_x > Border_x){
            exceeded = true ;
            //break ;
           // cout << new_x << endl ;
        }

        if (Test -> get_Rnode() != NULL){
            Test -> get_Rnode() -> set_x ( Test -> get_x() ) ;
             My_Q.push_back(Test -> get_Rnode()) ;
        }

        if (Test -> get_Lnode() != NULL){
            Test -> get_Lnode() -> set_x ( new_x ) ;
             My_Q.push_back(Test -> get_Lnode()) ;
        }

  
    }
  //  cout << "Total X : " << a << endl ; 

   // Print_block() ;
    //cout << new_x << endl ;
/*
    for (unsigned int i =1 ; i< All_tree_node.size() ; i++){
        Test = All_tree_node[i] -> get_Parent() ;
        if (Test -> get_Lnode() == All_tree_node[i] ){  // right side of the block
            All_tree_node[i] -> set_x(Test -> get_x() + Test -> get_w () ) ;
        }else {     // upon the block
            All_tree_node[i] -> set_x(Test -> get_x() ) ;
        }
    }

    TreeNode* Leftmost = root ;
    while ( Leftmost -> get_Lnode() != NULL){
        Leftmost = Leftmost -> get_Lnode() ;
        cout << Leftmost -> get_Name() << " : " <<  Leftmost -> get_x()  << endl ;
    }
*/
 //   cout << "=====================" << endl ;
;

    return exceeded ;

}

void B_TREE::contour_set_head( ){

    // if left == 1   , the new block will at (parent_x + parent_w );
   // cout << root -> get_w() << " , " << root -> get_h() <<endl ;

    Contour* one   = new Contour ( 0  , root -> get_h()        )   ;  // top-right corner
    Contour* two   = new Contour ( root -> get_w()  , root -> get_h()  )   ;  // bottom-right corner
    Contour* three = new Contour ( root -> get_w()  , 0  )   ;  // bottom-right corner

    one   -> set_prev(head ) ;
    one   -> set_next(two )  ;
    two   -> set_prev(one)   ;
    two   -> set_next(three) ;
    three -> set_prev(two)   ;
    three -> set_next(head -> get_next() ) ;

    Contour* tail = head -> get_next() ;
    tail  -> set_prev(three) ;
    head  -> set_next(one)   ;


}

// remember to do level_order print   // for debug

void B_TREE::contour_setting_right( TreeNode* child , int &max_width , int &max_height){
    Contour* Cptr ;
    Cptr = head ;

    //cout << "now_child : " << child -> get_Name() <<endl ;
    while (Cptr -> get_x () < child -> get_x () ){
        Cptr = Cptr -> get_next() -> get_next() ;
    }

    if (Cptr -> get_x() != child -> get_x () ){  // add two new node
        Contour* new_node_1 = new Contour (child -> get_x() , Cptr -> get_y()     )   ;
        Contour* new_node_2 = new Contour (child -> get_x() , Cptr -> get_y()     )   ;

        new_node_1 -> set_next (new_node_2) ;
        new_node_1 -> set_prev (Cptr -> get_prev() ) ;

        new_node_2 -> set_prev (new_node_1) ;
        new_node_2 -> set_next (Cptr) ;

        Cptr = Cptr -> get_prev() ;
        Cptr -> get_next() -> set_prev(new_node_2 );
        Cptr -> set_next(new_node_1) ;
        Cptr = Cptr -> get_next() ;

    }
    //cout << "123456" << endl ;
    //cout << Cptr -> get_x () << "," << Cptr -> get_y () << endl ;

    Contour* Cptr2 = Cptr -> get_next() -> get_next()  ;
    int find_width = Cptr2 -> get_x() - Cptr -> get_x() ;

    Contour* delete_node_1 ;
    Contour* delete_node_2 ;
    int new_height = 0 ;
    new_height =  Cptr2 -> get_y() + child -> get_h() ;

    //cout << 11 << endl ;
    Contour* test ;
    test = head ;
    /*
    while (test != NULL){
        cout << " Contour : " <<  test -> get_x()    << " , " << test -> get_y() << endl ;
        test = test -> get_next() ;
    }*/

    while (find_width < child -> get_w() ){
        delete_node_1 = Cptr2 ;
        delete_node_2 = Cptr2 -> get_next() ;
     //   cout << " delete_node_1 : " <<  delete_node_1 -> get_x()    << " , " << delete_node_1 -> get_y() << endl ;
      //  cout << " delete_node_2 : " <<  delete_node_2 -> get_x()    << " , " << delete_node_2 -> get_y() << endl ;
      //  cout << " find_width : " <<  find_width  << endl ;
     //   cout << " child __w : " <<  child -> get_w()    << " , " << child -> get_w() << endl ;



        delete_node_1 -> get_prev() -> set_next( delete_node_2 -> get_next()  ) ;
        delete_node_2 -> get_next() -> set_prev( delete_node_1 -> get_prev()  ) ;


        Cptr2 = Cptr2 -> get_next() -> get_next() ;
        find_width = Cptr2 -> get_x() - Cptr -> get_x() ;

        if (new_height <  Cptr2 -> get_y() + child -> get_h() )
            new_height =  Cptr2 -> get_y() + child -> get_h() ;

        delete delete_node_1 ;
        delete_node_1 = NULL  ;
        delete delete_node_2 ;
        delete_node_2 = NULL  ;
        //Cptr2 = Cptr2 -> get_next() ;
        //find_width = Cptr2 -> get_x() - Cptr -> get_x() ;
    }


    if (new_height > max_height)
        max_height = new_height ;

    child -> set_y (new_height - child -> get_h() ) ;

    if (find_width == child -> get_w() ) {
        Cptr2 -> set_y (new_height) ;
    }else {
        Contour* one = new Contour (child -> get_x() + child -> get_w()  , new_height        )   ;  // top-right corner
        Contour* two = new Contour (child -> get_x() + child -> get_w()  , Cptr2 -> get_y()  )   ;  // bottom-right corner
        one -> set_prev(Cptr -> get_next() ) ;
        one -> set_next(two )  ;
        two -> set_prev(one)   ;
        two -> set_next(Cptr2) ;
        Cptr2 -> set_prev(two) ;
        Cptr  -> get_next() -> set_next(one) ;
    }

    if (child -> get_x() + child -> get_w() > max_width)
        max_width = child -> get_x() + child -> get_w() ;


     test = Cptr -> get_next() ;

    if (Cptr -> get_y () == new_height ){    // delete the next node   // and change the previous and next pointer
        Cptr -> get_prev() -> set_next(test -> get_next() ) ;
        test -> get_next() -> set_prev(Cptr -> get_prev() ) ;
        delete test ;
        test = NULL ;
        delete Cptr ;
        Cptr = NULL ;
    }else {  // height is not equal
        //Cptr -> get_prev() -> set_next(test -> get_next() ) ;
        //test -> set_next(one ) ;
        test -> set_y ( new_height ) ;
    }

  //  cout << 22 << endl ;
   // test = head ;
    //while (test != NULL){
    //    cout << " Contour : " <<  test -> get_x()    << " , " << test -> get_y() << endl ;
    //    test = test -> get_next() ;
    //}


}



/*
TreeNode* B_TREE::check_right( TreeNode* now_parent ) {

    TreeNode* right_block ;


    return right_block ;
}
*/

void B_TREE::save_terminals (int terminals_number , ifstream& block_file ) {

    Terminal* new_terminal ;
    Terminal_vec.reserve(terminals_number) ;
    
    string node_name , Title ; 
    int node_w ; 
    int node_h ; 
   // cout << 11<< endl ;
    for (int i=0 ; i < terminals_number ; i++){
        block_file >>  node_name ;
        block_file >>  Title ;
        block_file >> node_w ;
        block_file >> node_h ;

        new_terminal = new Terminal(node_name , node_w , node_h ) ;
        Terminal_vec.push_back(new_terminal) ;
    }
}

void B_TREE::construct_map(){
   TreeNode_map.clear() ; 
   for (unsigned int i=0 ; i < All_tree_node.size() ; i++ ){
       TreeNode_map.insert ( pair<string,TreeNode* > (All_tree_node[i] -> get_Name() , All_tree_node[i] ) ) ; 
   }
   
   Terminal_map.clear() ; 
   for (unsigned int i=0 ; i < Terminal_vec.size() ; i++ ){
       Terminal_map.insert ( pair<string,Terminal* > (Terminal_vec[i] -> get_Name() , Terminal_vec[i] ) ) ; 
   }

}

void B_TREE::compute_HPWL( ){


    string name  ;
    int each_HPWL = 0 ;
    int total_HPWL = 0 ;

    double First_x = 0 ;
    double First_y = 0 ;
    double tmp = 0 ;
    double Second_x = 0 ;
    double Second_y = 0 ;

    double Third_x = 0 ;
    double Third_y = 0 ;
    
    TreeNode* Tptr = NULL ; 
    Terminal* Ter_ptr = NULL ; 
    map< string , TreeNode* >::iterator it ; 
    
    //vector<TreeNode* > My_Q ;
    for (unsigned int i=0 ; i< all_net_name.size() ; i++ ){

         for (unsigned int k=0 ; k< all_net_name[i].size() ; k++ ) {

                name = all_net_name[i][k] ;
                it = TreeNode_map.find(name) ; 
                
                if ( it == TreeNode_map.end() ) { // terminal
                   Ter_ptr = Terminal_map[name] ; 
                    if (k==0 ){
                        First_x = Ter_ptr -> get_x()  ;
                        First_y = Ter_ptr -> get_y()  ;
                     } else if (k==1){
                        Second_x = Ter_ptr -> get_x()  ;
                        Second_y = Ter_ptr -> get_y()  ;

                        if (Second_x < First_x ) {
                          tmp      = Second_x ;
                          Second_x = First_x ;
                          First_x  = tmp ;
                        }

                        if (Second_y < First_y ) {
                          tmp      = Second_y ;
                          Second_y = First_y ;
                          First_y  = tmp ;
                        }

                     } else {
                        Third_x = Ter_ptr -> get_x()  ;
                        Third_y = Ter_ptr -> get_y()  ;

                        if (Third_x < First_x )
                            First_x = Third_x ;
                        else if (Third_x > Second_x)
                            Second_x = Third_x ;

                        if (Third_y < First_y )
                            First_y = Third_y ;
                        else if (Third_y > Second_y)
                            Second_y = Third_y ;


                     }  
                } else {  // block 
                   Tptr = it -> second ; 
                   //Tptr = TreeNode_map[name] ; 
                   if (k==0 ){
                        First_x = (Tptr -> get_x() + Tptr -> get_x() + Tptr -> get_w() ) / 2 ;
                        First_y = (Tptr -> get_y() + Tptr -> get_y() + Tptr -> get_h() ) / 2 ;
                     } else if (k==1){
                        Second_x = (Tptr -> get_x() + Tptr -> get_x() + Tptr -> get_w() ) / 2 ;
                        Second_y = (Tptr -> get_y() + Tptr -> get_y() + Tptr -> get_h() ) / 2 ;

                        if (Second_x < First_x ) {
                          tmp      = Second_x ;
                          Second_x = First_x ;
                          First_x  = tmp ;
                        }

                        if (Second_y < First_y ) {
                          tmp      = Second_y ;
                          Second_y = First_y ;
                          First_y  = tmp ;
                        }

                     } else {
                        Third_x = (Tptr -> get_x() + Tptr -> get_x() + Tptr -> get_w() ) / 2 ;
                        Third_y = (Tptr -> get_y() + Tptr -> get_y() + Tptr -> get_h() ) / 2 ;

                        if (Third_x < First_x )
                            First_x = Third_x ;
                        else if (Third_x > Second_x)
                            Second_x = Third_x ;

                        if (Third_y < First_y )
                            First_y = Third_y ;
                        else if (Third_y > Second_y)
                            Second_y = Third_y ;


                     }
                }
                
/*               if (name[0] == All_tree_node[0] -> get_Name()[0]){  // means block
                  for (unsigned int j=0 ; j< All_tree_node.size() ; j++){
                    if (name == All_tree_node[j] -> get_Name() ){
                         if (k==0 ){
                            First_x = (All_tree_node[j] -> get_x() + All_tree_node[j] -> get_x() + All_tree_node[j] -> get_w() ) / 2 ;
                            First_y = (All_tree_node[j] -> get_y() + All_tree_node[j] -> get_y() + All_tree_node[j] -> get_h() ) / 2 ;
                         } else if (k==1){
                            Second_x = (All_tree_node[j] -> get_x() + All_tree_node[j] -> get_x() + All_tree_node[j] -> get_w() ) / 2 ;
                            Second_y = (All_tree_node[j] -> get_y() + All_tree_node[j] -> get_y() + All_tree_node[j] -> get_h() ) / 2 ;

                            if (Second_x < First_x ) {
                              tmp      = Second_x ;
                              Second_x = First_x ;
                              First_x  = tmp ;
                            }

                            if (Second_y < First_y ) {
                              tmp      = Second_y ;
                              Second_y = First_y ;
                              First_y  = tmp ;
                            }

                         } else {
                            Third_x = (All_tree_node[j] -> get_x() + All_tree_node[j] -> get_x() + All_tree_node[j] -> get_w() ) / 2 ;
                            Third_y = (All_tree_node[j] -> get_y() + All_tree_node[j] -> get_y() + All_tree_node[j] -> get_h() ) / 2 ;

                            if (Third_x < First_x )
                                First_x = Third_x ;
                            else if (Third_x > Second_x)
                                Second_x = Third_x ;

                            if (Third_y < First_y )
                                First_y = Third_y ;
                            else if (Third_y > Second_y)
                                Second_y = Third_y ;


                         }
                      break ;
                    }

                  }

               } else {

                  for (unsigned int j=0 ; j< Terminal_vec.size() ; j++){
                    if (name == Terminal_vec[j] -> get_Name() ){
                         if (k==0 ){
                            First_x = Terminal_vec[j] -> get_x()  ;
                            First_y = Terminal_vec[j] -> get_y()  ;
                         } else if (k==1){
                            Second_x = Terminal_vec[j] -> get_x()  ;
                            Second_y = Terminal_vec[j] -> get_y()  ;

                            if (Second_x < First_x ) {
                              tmp      = Second_x ;
                              Second_x = First_x ;
                              First_x  = tmp ;
                            }

                            if (Second_y < First_y ) {
                              tmp      = Second_y ;
                              Second_y = First_y ;
                              First_y  = tmp ;
                            }

                         } else {
                            Third_x = Terminal_vec[j] -> get_x()  ;
                            Third_y = Terminal_vec[j] -> get_y()  ;

                            if (Third_x < First_x )
                                First_x = Third_x ;
                            else if (Third_x > Second_x)
                                Second_x = Third_x ;

                            if (Third_y < First_y )
                                First_y = Third_y ;
                            else if (Third_y > Second_y)
                                Second_y = Third_y ;


                         }
                      break ;
                    }

                  }

               }
          */
        }
        
     //   cout << " X - diff " << First_x << " , " << Second_x << endl ; 
        each_HPWL = int (Second_x) - int(First_x) ;
     //   cout << " Y - diff " << First_y << " , " << Second_y << endl ;
        each_HPWL = (each_HPWL) + ( int(Second_y) - int(First_y) ) ;
     //   cout << "Each HPWL " << each_HPWL << endl ;
        total_HPWL = total_HPWL + each_HPWL ;
    }  

  //  cout << "Title : " << Title << endl ;
  //  cout << "Degrees : " << degrees << endl ;
  //  cout << "name : " << name << endl ;
 // cout << "Total HPWL " << total_HPWL << endl ;
  HPWL = total_HPWL ;
  
 // net_file.close() ; 
  
  
 // return total_HPWL ; 
}
void B_TREE::save_net_name  (const char* net_file_path ) {
   ifstream net_file ; 
   net_file.open(net_file_path) ; 
   
   string Title ; 
   int degrees ; 
   int number_of_nets ; 
   string net_name ; 
   vector<string> My_str ; 
   
   net_file >> Title ;
   net_file >> number_of_nets ;
   
   for ( int i=0 ; i< number_of_nets ; i++) {
       net_file >> Title ;
       net_file >> degrees ;
       My_str.clear() ; 
       
       all_net_name.push_back(My_str) ; 
       for (int k=0 ; k< degrees ; k++ ) {
          net_file >> net_name ;
          all_net_name[i].push_back(net_name) ;       
       }
   }
   /*
   cout << "------start-----" << endl ; 
   for ( unsigned int i=0 ; i < all_net_name.size() ; i++){
   cout << "====new ==== " << endl ; 
     for (unsigned int j=0 ; j < all_net_name[i].size() ; j++) {
        cout << "name : "<< setw(5) << all_net_name[i][j] << endl ; 
     }
     cout << "====finish====" << endl ; 
   }
   */
   net_file.close() ; 
}

void B_TREE::write_output_file (ofstream& out_file , double total_time) {

    out_file << cost << endl ;
    out_file << HPWL << endl ;
    out_file << area << endl ;
    out_file << width << " " << height << endl ;
    out_file << total_time << endl  ;  // run time
    for (unsigned int i=0 ; i< All_tree_node.size() ; i++){
      out_file << All_tree_node[i] -> get_Name() << " " << All_tree_node[i] -> get_x() << " "  << All_tree_node[i] -> get_y() << " " << All_tree_node[i] -> get_x() + All_tree_node[i] -> get_w() << " " << All_tree_node[i] -> get_y() +  All_tree_node[i] -> get_h() << endl ;

    }
    
   // cout << "total time : " << total_time << "s" << endl ;


}



