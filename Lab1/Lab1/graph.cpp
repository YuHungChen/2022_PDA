#include <iostream>
#include "tile.h"
#include "graph.h"
#include <fstream>
#include <algorithm>
using namespace std ;

void GRAPH::Insert_tile(int x, int y, int w, int h , int idx){

    //cout << "===========Insert_tile==========" << endl ;
    TILE* Insert_T = new TILE (x , y, w ,h ,idx) ;
  //  cout << x << "," << y << " w : " <<  w  << " h : " << h  << " idx : " << idx <<endl;
    // FOR UPPER EDGE
    int Left_top_y = y + h ;
    int differ_y =  0  ;

    if(Left_top_y == border_h){
        differ_y =  0  ;
    }else{
        Point_Finding ( x, Left_top_y) ;
        differ_y = y + h - First_tile -> get_y() ;
    }

 //   cout << differ_y << endl  ;

    if (differ_y > 0  ){
        if(Left_top_y != border_h)
        split_tile( First_tile , differ_y , Left_top_y ) ;
    }
  //  cout << y << endl ;
    // FOR LOWER EDGE
    Point_Finding ( x, y) ;
    differ_y = y - First_tile -> get_y()  ;
  //  cout << differ_y << endl  ;

   // cout << First_tile -> get_x() << "," << First_tile -> get_y() << " w : " << First_tile -> get_width() << " h : " << First_tile -> get_height() <<endl;
  //  if(First_tile -> get_rt() != 0)
   //     cout << First_tile -> get_rt() -> get_x() << "," << First_tile -> get_rt() -> get_y() << " w : " << First_tile -> get_rt() -> get_width() << " h : " << First_tile -> get_rt() -> get_height() <<endl;
 //   cout << 777 << endl ;
   // if ( First_tile -> get_y() != y ){

    if (differ_y > 0  ){
        split_tile( First_tile , differ_y , y ) ;
    }


    // FOR LEFT and RIGHT side


   while(true){
      Point_Finding ( x, Left_top_y  ) ;
      if(Left_top_y != border_h)
        First_tile = First_tile -> get_lb() ;
    //  cout << "LR_TILE" << endl ;
    //  cout << First_tile -> get_x() << "," << First_tile -> get_y() << " w : " << First_tile -> get_width() << " h : " << First_tile -> get_height() <<endl;
      //  cout << First_tile -> get_x() << "," << First_tile -> get_y() << " w : " << First_tile -> get_width() << " h : " << First_tile -> get_height() <<endl;

      while (true){
        while ( !  ( First_tile -> get_x() + First_tile -> get_width() > Insert_T -> get_x() )  ){
            First_tile = First_tile -> get_tr() ;
        }
        if( First_tile -> get_y() >= Left_top_y){
            First_tile = First_tile -> get_lb() ;
        }else if (First_tile -> get_y() == Left_top_y){
            if(Left_top_y == 0 ){
                break ;
            }else{
                First_tile = First_tile -> get_lb() ;
            }
        }else
            break ;

      }

      if ( First_tile -> get_y() < y )
        break ;
      else if (First_tile -> get_y() == y ){
     //   cout << "====LR1====" << endl ;
        split_tile_LR(First_tile , Insert_T) ;
        break ;
      }
      else{
        Left_top_y = First_tile -> get_y() ;
    //    cout << "=====LR2====" << endl ;
        split_tile_LR(First_tile , Insert_T) ;

       }
   }

//Point_Finding( 0 , border_h) ;

delete Insert_T ;
Insert_T = NULL ;
   // cout << First_tile -> get_x() << "," << First_tile -> get_y() << " w : " << First_tile -> get_width() << " h : " << First_tile -> get_height() <<endl;
}


void GRAPH::merge_top_bottom( TILE* TOP , TILE* BOTTOM){
// delete top
    if ( ( TOP -> get_x() == BOTTOM -> get_x()) && TOP -> get_width() == BOTTOM -> get_width() && TOP -> get_index() == BOTTOM -> get_index() ) {
        BOTTOM -> set_rt (TOP -> get_rt() ) ;
        BOTTOM -> set_tr (TOP -> get_tr() ) ;
        BOTTOM -> set_height (TOP -> get_height() + BOTTOM -> get_height() ) ;

    //    cout << "YES" << endl ;

        update_pointer(BOTTOM) ;
        delete TOP ;
        TOP = 0 ;
    }


}

void GRAPH::merge_bottom_top( TILE* TOP , TILE* BOTTOM){
// delete bottom
    if ( ( TOP -> get_x() == BOTTOM -> get_x()) && TOP -> get_width() == BOTTOM -> get_width() && TOP -> get_index() == BOTTOM -> get_index() ) {

        TOP -> set_bl (BOTTOM -> get_bl() ) ;
        TOP -> set_lb (BOTTOM -> get_lb() ) ;
        TOP -> set_height (TOP -> get_height() + BOTTOM -> get_height() ) ;
        TOP -> set_y  (BOTTOM -> get_y () ) ;

      //  cout << "YES_2" << endl ;

        update_pointer(TOP) ;
   //     merge_success = true ;
        delete BOTTOM ;
        BOTTOM = 0 ;
    }


}


void GRAPH::split_tile_LR (TILE* Spaced_T , TILE* Insert_T ){
    // 4 situation
      TILE* Test_t ;
   //   if(Spaced_T != 0)
    //    cout << Spaced_T  -> get_x() << "," << Spaced_T  -> get_y() << " w : " << Spaced_T -> get_width() << " h : " << Spaced_T  -> get_height() <<endl;
    //  if(Insert_T != 0)
      //  cout << Insert_T  -> get_x() << "," << Insert_T  -> get_y() << " w : " << Insert_T -> get_width() << " h : " << Insert_T  -> get_height() <<endl;
    // 1.  only second  ( it means spaced_T = insert_T )
        if (Spaced_T -> get_x() == Insert_T -> get_x()  && Spaced_T -> get_width() == Insert_T -> get_width()){
           // cout << "===========1111111==========" << endl ;
                Spaced_T -> set_index(Insert_T -> get_index() ) ;
                update_pointer(Spaced_T) ;

                if(Spaced_T -> get_rt() != 0)
                    merge_top_bottom(Spaced_T -> get_rt() , Spaced_T) ;

        }

    // 2.  first and second
        else if (Spaced_T -> get_x() + Spaced_T -> get_width() == Insert_T -> get_x() + Insert_T -> get_width()){
               // cout << "===========22222==========" << endl ;
                TILE* Second_T = new TILE(Insert_T -> get_x() , Spaced_T -> get_y() , Insert_T -> get_width() , Spaced_T -> get_height() , Insert_T -> get_index() ) ;
                Second_T -> set_tr(Spaced_T -> get_tr() ) ;
                Second_T -> set_rt(Spaced_T -> get_rt() ) ;
                Second_T -> set_bl(Spaced_T) ;
                Test_t = Spaced_T -> get_lb() ;
                if (Test_t != 0 ){
                    while (Test_t -> get_x() + Test_t -> get_width()  <= Second_T -> get_x()  ){
                        Test_t = Test_t -> get_tr() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Second_T -> set_lb (Test_t) ;
                //==========================

                Spaced_T -> set_width(Insert_T -> get_x() - Spaced_T -> get_x()) ;
                Spaced_T -> set_tr   (Second_T) ;
                Test_t = Spaced_T -> get_rt() ;
                if(Test_t != 0){
                    while (Test_t -> get_x() >= Spaced_T -> get_x() + Spaced_T -> get_width() ){
                        Test_t = Test_t -> get_bl() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Spaced_T -> set_rt(Test_t) ;



                update_pointer(Spaced_T) ;
                update_pointer(Second_T) ;

                if(Second_T -> get_rt() != 0)
                    merge_top_bottom(Second_T  -> get_rt() , Second_T             ) ;

                if(Spaced_T -> get_rt() != 0)
                    merge_top_bottom(Spaced_T  -> get_rt() , Spaced_T             ) ;
                if(Spaced_T -> get_lb() != 0)
                merge_bottom_top(Spaced_T              , Spaced_T -> get_lb() ) ;

        }
    // 3. second and third
        else if (Insert_T -> get_x() == Spaced_T -> get_x() ){
               // cout << "===========333333==========" << endl ;
                TILE* Third_T  = new TILE(Insert_T -> get_x() + Insert_T -> get_width() , Spaced_T -> get_y() , Spaced_T -> get_x() + Spaced_T -> get_width() - Insert_T -> get_x() - Insert_T -> get_width() , Spaced_T -> get_height() , 0 )  ;
                Third_T -> set_rt(Spaced_T -> get_rt() ) ;
                Third_T -> set_tr(Spaced_T -> get_tr() ) ;
                Third_T -> set_bl(Spaced_T) ;
                Test_t = Spaced_T -> get_lb() ;
                if (Test_t != 0 ){
                    while (Test_t -> get_x() + Test_t -> get_width()  <= Third_T -> get_x()  ){
                        Test_t = Test_t -> get_tr() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Third_T -> set_lb (Test_t) ;
                //============================
                Spaced_T -> set_width(Insert_T -> get_width() ) ;
                Spaced_T -> set_index( Insert_T -> get_index() ) ;
                Spaced_T -> set_tr   (Third_T) ;
                Test_t = Spaced_T -> get_rt() ;
                if (Test_t != 0 ){
                    while (Test_t -> get_x()  >=  Spaced_T -> get_x() + Spaced_T -> get_width() ){
                        Test_t = Test_t -> get_bl() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Spaced_T -> set_rt (Test_t) ;

                update_pointer(Third_T) ;
                update_pointer(Spaced_T) ;

                if(Spaced_T -> get_rt() != 0)
                    merge_top_bottom(Spaced_T -> get_rt() , Spaced_T            ) ;

                if(Third_T -> get_rt() != 0)
                merge_top_bottom(Third_T  -> get_rt() , Third_T             ) ;

                if(Third_T -> get_lb() != 0)
                merge_bottom_top(Third_T              , Third_T -> get_lb() ) ;

        }



    // 4. first, second, third
        else {
               // cout << "===========44444==========" << endl ;
                TILE* Second_T = new TILE(Insert_T -> get_x() , Spaced_T -> get_y() , Insert_T -> get_width() , Spaced_T -> get_height() , Insert_T -> get_index() ) ;
                TILE* Third_T  = new TILE(Insert_T -> get_x() + Insert_T -> get_width() , Spaced_T -> get_y() , Spaced_T -> get_x() + Spaced_T -> get_width() - Insert_T -> get_x() - Insert_T -> get_width() , Spaced_T -> get_height() , 0 )  ;

                Third_T -> set_tr(Spaced_T -> get_tr() ) ;
                Third_T -> set_rt(Spaced_T -> get_rt() ) ;
                Third_T -> set_bl(Second_T) ;
                Test_t = Spaced_T -> get_lb() ;
                if (Test_t != 0 ){
                    while (Test_t -> get_x() + Test_t -> get_width()  <= Third_T -> get_x()  ){
                        Test_t = Test_t -> get_tr() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Third_T -> set_lb (Test_t) ;

                // ===========================================
                Second_T -> set_tr(Third_T) ;
                Second_T -> set_bl(Spaced_T) ;
                Test_t = Spaced_T -> get_rt() ;
                if (Test_t != 0 ){
                    while (Test_t -> get_x()  >=  Second_T -> get_x() + Second_T -> get_width() ){
                        Test_t = Test_t -> get_bl() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Second_T -> set_rt (Test_t) ;

                Test_t = Spaced_T -> get_lb() ;
                if (Test_t != 0 ){
                    while (Test_t -> get_x() + Test_t -> get_width()  <= Second_T -> get_x()  ){
                        Test_t = Test_t -> get_tr() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Second_T -> set_lb (Test_t) ;

                // =========================================
                Spaced_T -> set_width(Insert_T -> get_x() - Spaced_T -> get_x() ) ;
                Spaced_T -> set_tr(Second_T) ;
                Test_t = Spaced_T -> get_rt() ;
                if(Test_t != 0){
                    while (Test_t -> get_x() >= Spaced_T -> get_x() + Spaced_T -> get_width() ){
                        Test_t = Test_t -> get_bl() ;
                        if(Test_t == 0 )
                            break ;
                    }
                }
                Spaced_T -> set_rt(Test_t) ;

                update_pointer(Third_T) ;
                update_pointer(Second_T) ;
                update_pointer(Spaced_T) ;

                if(Third_T -> get_rt() != 0)
                merge_top_bottom(Third_T  -> get_rt() , Third_T             ) ;

                if(Third_T -> get_lb() != 0)
                merge_bottom_top(Third_T              , Third_T -> get_lb() ) ;

                if(Second_T -> get_rt() != 0)
                merge_top_bottom(Second_T -> get_rt() , Second_T            ) ;

                if(Spaced_T -> get_rt() != 0)
                merge_top_bottom(Spaced_T  -> get_rt() , Spaced_T             ) ;

                if(Spaced_T -> get_lb() != 0)
                merge_bottom_top(Spaced_T              , Spaced_T -> get_lb() ) ;

        }

}

/*
void GRAPH::split_tile_LR (TILE* Spaced_T , TILE* Insert_T ){   // spaced_T   = top_spaced_T
 // cout << "===========split_tile_LR==========" << endl ;
  // cout << Spaced_T -> get_x() << "," << Spaced_T -> get_y() << " w : " << Spaced_T -> get_width() << " h : " << Spaced_T -> get_height() <<endl;

    TILE* Test_t  = NULL   ;

    TILE* First_T  = new TILE(Spaced_T -> get_x() , Spaced_T -> get_y() , Insert_T -> get_x() - Spaced_T -> get_x() , Spaced_T -> get_height() , 0) ;

    TILE* Second_T = new TILE(Insert_T -> get_x() , Spaced_T -> get_y() , Insert_T -> get_width() , Spaced_T -> get_height() , Insert_T -> get_index() ) ;

    TILE* Third_T  = new TILE(Insert_T -> get_x() + Insert_T -> get_width() , Spaced_T -> get_y() , Spaced_T -> get_x() + Spaced_T -> get_width() - Insert_T -> get_x() - Insert_T -> get_width() , Spaced_T -> get_height() , 0 )  ;


    // set Third_T
        if (Third_T -> get_width() == 0){
             Second_T -> set_tr(Spaced_T -> get_tr()  ) ;
             delete Third_T ;
             Third_T = NULL ;
        }else {
            Third_T -> set_rt( Spaced_T -> get_rt() ) ;
            Third_T -> set_tr( Spaced_T -> get_tr() ) ;
            Third_T -> set_bl( Second_T ) ;

            Test_t = Spaced_T -> get_lb() ;
            if (Test_t != 0 ){
                while (Test_t -> get_x() + Test_t -> get_width()  <= Third_T -> get_x()  ){
                    Test_t = Test_t -> get_tr() ;
                    if(Test_t == 0 )
                        break ;
                }
            }
            Third_T -> set_lb (Test_t) ;
            update_pointer(Third_T) ;

            Second_T -> set_tr (Third_T) ;
        }

    // Second_T setting
        if (First_T -> get_width() != 0)
            Second_T -> set_bl (First_tile) ;

        Test_t = Spaced_T -> get_rt() ;
        if (Test_t != 0 ){
            while (Test_t -> get_x()  >=  Second_T -> get_x() + Second_T -> get_width() ){
                Test_t = Test_t -> get_bl() ;
                if(Test_t == 0 )
                    break ;
            }
        }
        Second_T -> set_rt (Test_t) ;

        Test_t = Spaced_T -> get_lb() ;
        if (Test_t != 0 ){
            while (Test_t -> get_x() + Test_t -> get_width()  <= Second_T -> get_x()  ){
                Test_t = Test_t -> get_tr() ;
                if(Test_t == 0 )
                    break ;
            }
        }
        Second_T -> set_lb (Test_t) ;

        update_pointer(Second_T) ;
    // First_T setting
        if(First_T -> get_width() == 0){
            Second_T -> set_bl(Spaced_T -> get_bl()) ;
            delete Spaced_T ;
            Spaced_T = 0 ;
            First_tile = Second_T ;
            delete First_T ;
            First_T = NULL ;
        }else{

            Spaced_T -> set_tr(Second_T) ;
            Spaced_T -> set_width (First_T -> get_width() ) ;
            Test_t = Spaced_T -> get_rt() ;
            if(Test_t != 0){
                while (Test_t -> get_x() >= Spaced_T -> get_x() + Spaced_T -> get_width() ){
                    Test_t = Test_t -> get_bl() ;
                    if(Test_t == 0 )
                        break ;
                }
            }
            Spaced_T -> set_rt(Test_t) ;

        }
// update First_T
    if (First_T != 0)
        update_pointer(Spaced_T) ;

// update Second_T
    update_pointer(Second_T) ;

// update Third_T
    if (Third_T != 0 ){
        update_pointer(Third_T) ;

        if( Third_T -> get_rt() != 0){
        merge_top_bottom(Third_T -> get_rt() , Third_T) ;
        }

        if( Third_T -> get_lb() != 0){
        merge_bottom_top(Third_T  ,Third_T -> get_lb() ) ;
        }

      //  cout << Third_T -> get_x() << "," << Third_T -> get_y() << " w : " << Third_T -> get_width() << " h : " << Third_T -> get_height() <<endl;
    }

    if(Second_T -> get_rt() != 0  ){
        merge_top_bottom(Second_T -> get_rt() , Second_T) ;
    }
        //cout << "SecondT" << endl ;
       // cout << Second_T -> get_x() << "," << Second_T -> get_y() << " w : " << Second_T -> get_width() << " h : " << Second_T -> get_height() <<endl;

    if (First_T != 0 ){

        if(Spaced_T -> get_rt() != 0){
            merge_top_bottom(Spaced_T -> get_rt() , Spaced_T) ;
        }

        if( Spaced_T -> get_lb() != 0){
            merge_bottom_top(Spaced_T  ,Spaced_T -> get_lb() ) ;
        }

 //       if (Spaced_T -> get_tr() != 0)
 //           cout << Spaced_T -> get_tr() ->  get_x() << "," << Spaced_T -> get_tr() -> get_y() << " w : " << Spaced_T -> get_tr() -> get_width() << " h : " << Spaced_T -> get_tr() -> get_height() <<endl;


        delete First_T ;
        First_T = NULL ;
    }

}
*/

// For bottom and top
void GRAPH::split_tile(TILE* Spaced_T, int diff_y , int new_y ){
   // cout << "===========split_tile==========" << endl ;
 //   cout << First_tile -> get_x() << "," << First_tile -> get_y() << " w : " << First_tile -> get_width() << " h : " << First_tile -> get_height() <<endl;
    //TILE* TEST = Spaced_T -> get_tr() ;
    //cout << TEST << endl ;

    TILE* New_T =  new TILE ( Spaced_T -> get_x() , Spaced_T -> get_y() , Spaced_T -> get_width(), diff_y  , 0 ) ;

    New_T -> set_rt (Spaced_T  ) ;
    New_T -> set_lb (Spaced_T -> get_lb() ) ;
    New_T -> set_bl (Spaced_T -> get_bl() ) ;


    TILE* Test_t = Spaced_T -> get_tr()  ;

    if ( Test_t != 0){
      while ( new_y <=  Test_t -> get_y()   ){
          Test_t = Test_t -> get_lb() ;
      }
    }
    New_T -> set_tr (Test_t) ;

    Spaced_T -> set_height ( Spaced_T -> get_height() - diff_y ) ;

    Spaced_T -> set_y (new_y) ;
    Spaced_T -> set_lb (New_T) ;

    Test_t = Spaced_T -> get_bl()  ;
    if (Test_t != 0){
      while (Spaced_T -> get_y() >=  Test_t -> get_y() + Test_t -> get_height() ) {
          Test_t = Test_t -> get_rt() ;
      }
    }
    Spaced_T -> set_bl(Test_t) ;


    update_pointer (New_T) ;
  //  if(Spaced_T -> get_lb() != 0)
   //     cout << Spaced_T -> get_lb() -> get_x() << "," << Spaced_T -> get_lb() -> get_y() << " w : " << Spaced_T -> get_lb() -> get_width() << " h : " << Spaced_T -> get_lb() -> get_height() <<endl;

    update_pointer (Spaced_T) ;
  //  if(Spaced_T -> get_lb() != 0)
 //       cout << Spaced_T -> get_lb() -> get_x() << "," << Spaced_T -> get_lb() -> get_y() << " w : " << Spaced_T -> get_lb() -> get_width() << " h : " << Spaced_T -> get_lb() -> get_height() <<endl;

}

void GRAPH::update_pointer(TILE* New_Tile){

    //cout << "===========update_pointer==========" << endl ;
    TILE* modified_tile = NULL ;

    //Left
    modified_tile = New_Tile -> get_bl() ;

    if ( modified_tile != 0) {
        while ( modified_tile -> get_y() + modified_tile -> get_height() <= New_Tile -> get_y() + New_Tile -> get_height() ){
            if( modified_tile -> get_y() + modified_tile -> get_height() > New_Tile -> get_y()){
                modified_tile -> set_tr(New_Tile) ;
            }
            if (modified_tile -> get_rt() == 0)
                break ;
/*
        cout << "THIRD_T" << endl ;
        cout << modified_tile -> get_x() << "," << modified_tile -> get_y() << " w : " << modified_tile -> get_width() << " h : " << modified_tile -> get_height() <<endl;
        cout << "\n    RT : " ;
        if (modified_tile -> get_rt()!=0)
            cout << modified_tile -> get_rt() -> get_x() << "," << modified_tile -> get_rt() -> get_y() << " w : " << modified_tile -> get_rt() -> get_width() << " h : " << modified_tile -> get_rt() -> get_height() ;
        cout << "\n    TR : " ;
        if (modified_tile -> get_tr()!=0)
            cout << modified_tile -> get_tr() -> get_x() << "," << modified_tile -> get_tr() -> get_y() << " w : " << modified_tile -> get_tr() -> get_width() << " h : " << modified_tile -> get_tr() -> get_height() ;
        cout << "\n    LB : " ;
        if (modified_tile -> get_lb()!=0)
            cout << modified_tile -> get_lb() -> get_x() << "," << modified_tile -> get_lb() -> get_y() << " w : " << modified_tile -> get_lb() -> get_width() << " h : " << modified_tile -> get_lb() -> get_height() ;
        cout << "\n    BL : " ;
        if (modified_tile -> get_bl()!=0)
            cout << modified_tile -> get_bl() -> get_x() << "," << modified_tile -> get_bl() -> get_y() << " w : " << modified_tile -> get_bl() -> get_width() << " h : " << modified_tile -> get_bl() -> get_height() ;
        cout <<endl ;
*/

            modified_tile = modified_tile -> get_rt() ;
        }

    }

    //   TOP

    modified_tile = New_Tile -> get_rt() ;
    if ( modified_tile !=0) {
     while(modified_tile -> get_x() >= New_Tile -> get_x() ){
            if (modified_tile -> get_x() < New_Tile -> get_x() + New_Tile -> get_width() ){
                modified_tile -> set_lb(New_Tile) ;
            }

            if (modified_tile -> get_bl() == 0)
                break ;
            modified_tile = modified_tile -> get_bl() ;
        }
    }

    //  Right

    modified_tile = New_Tile -> get_tr() ;
    if ( modified_tile !=0) {
        while(modified_tile -> get_y() >= New_Tile -> get_y() ){
            if(modified_tile -> get_y() < New_Tile -> get_y() + New_Tile -> get_height() ){
                modified_tile -> set_bl(New_Tile) ;
            }
            if (modified_tile -> get_lb() == 0   )
                break ;
            modified_tile = modified_tile -> get_lb() ;
        }
    }

    // Down
    modified_tile = New_Tile -> get_lb() ;
    if ( modified_tile !=0) {
        while(modified_tile -> get_x() + modified_tile -> get_width() <= New_Tile -> get_x() + New_Tile -> get_width() ){
            if ( modified_tile -> get_x() + modified_tile -> get_width() > New_Tile -> get_x() ){
                modified_tile -> set_rt(New_Tile);
            }
            if (modified_tile -> get_tr() == 0 )
                break ;
            modified_tile = modified_tile -> get_tr() ;
        }
    }

}

bool cmp( TILE* A , TILE* B ){
   return A -> get_index() < B -> get_index() ;
}

void GRAPH::area_search(int border_x , int border_y , char* argv[]){  // in this lab , search entire graph
   // cout << "===========area_search==========" << endl ;

    int total_tile = 0 ;

    ofstream out1 ;
    out1.open(argv[2]) ;

  //  cout << argv[2] << endl   ;
  //  cout << "right" ;

   // array<TILE*, 25001> Sorting_tile{} ;

   // Sorting_tile.at(5) = First_tile ;

    Point_Finding( 0 , border_y) ;

    vector<TILE* > My_T ;
    vector<TILE* > Sort_T ;
    Sort_T.reserve(25000) ;
    My_T.push_back(First_tile) ;

    TILE* Test_t ;

    while ( !My_T.empty()  ) {
        total_tile ++ ;

        Test_t = My_T.back() ;
        Test_t -> set_counted() ;
        My_T.pop_back() ;
/*
        cout << Test_t -> get_x() << "," << Test_t -> get_y() << " w : " << Test_t -> get_width() << " h : " << Test_t -> get_height() ;

        cout << "\n    RT : " ;
        if (Test_t -> get_rt()!=0)
            cout << Test_t -> get_rt() -> get_x() << "," << Test_t -> get_rt() -> get_y() << " w : " << Test_t -> get_rt() -> get_width() << " h : " << Test_t -> get_rt() -> get_height() << "  index :" <<Test_t -> get_rt() -> get_index() ;
        cout << "\n    TR : " ;
        if (Test_t -> get_tr()!=0)
            cout << Test_t -> get_tr() -> get_x() << "," << Test_t -> get_tr() -> get_y() << " w : " << Test_t -> get_tr() -> get_width() << " h : " << Test_t -> get_tr() -> get_height() << "  index : " <<Test_t -> get_tr() -> get_index() ;
        cout << "\n    LB : " ;
        if (Test_t -> get_lb()!=0)
            cout << Test_t -> get_lb() -> get_x() << "," << Test_t -> get_lb() -> get_y() << " w : " << Test_t -> get_lb() -> get_width() << " h : " << Test_t -> get_lb() -> get_height() << "  index : " <<Test_t -> get_lb() -> get_index() ;
        cout << "\n    BL : " ;
        if (Test_t -> get_bl()!=0)
            cout << Test_t -> get_bl() -> get_x() << "," << Test_t -> get_bl() -> get_y() << " w : " << Test_t -> get_bl() -> get_width() << " h : " << Test_t -> get_bl() -> get_height() << "  index : " <<Test_t -> get_bl() -> get_index() ;

     //   cout << endl ;

*/



        if (Test_t -> get_index() >= 1){
   //         cout << "  solid" ;
            neighbor_finding(Test_t) ;
            Sort_T.push_back(Test_t) ;
  //          cout << " Index : " << Test_t -> get_index() ;
 //           cout << "   solid_tile : " << Test_t -> get_solid_tile() <<  "   spaced_tile : " << Test_t -> get_space_tile()     ;
        }
     //   TILE* TTT ;
   //     TTT = Test_t -> get_bl() ;
   //     if (TTT!=0)
   //         cout << " xxxxxxxx " << TTT -> get_x() << "," << TTT -> get_y() << " w : " << TTT -> get_width() << " h : " << TTT -> get_height() ;

 //       cout <<endl ;



        if(Test_t -> get_lb() != 0  ){
            if(My_T.empty() )
                My_T.push_back(Test_t -> get_lb()) ;
            else if(Test_t -> get_lb() -> get_y() >=  My_T.back() -> get_y() + My_T.back() -> get_height() ){
                if (Test_t -> get_lb() -> get_bl() -> get_counted() == true)
                    My_T.push_back(Test_t -> get_lb()) ;
            }
        }

        if( Test_t -> get_tr() != 0  ){
              if(Test_t -> get_tr() -> get_y() >= Test_t -> get_y()  ){
                  My_T.push_back(Test_t -> get_tr()) ;
              }
        }


    }
    out1 << total_tile << endl ;
    sort(Sort_T.begin() , Sort_T.end() , cmp) ;
    for (auto itr = Sort_T.begin() ; itr < Sort_T.end() ; itr++){
        out1 << (*itr) -> get_index() << " " << (*itr) -> get_solid_tile() << " " << (*itr) -> get_space_tile()  << endl ;
    }
    int a = 0 ;
    for (auto itr = POINT_xy.begin() ; itr < POINT_xy.end() ; itr++ ){
        if(a==0){
            out1 << (*itr) << " " ;
            a++ ;
        }else {
            out1 << (*itr) << endl ;
            a = 0 ;
        }

    }

    out1.close() ;

    //return total_tile ;

}

void GRAPH::compute_point_XY(TILE* T ){
    POINT_xy.push_back(T->get_x()) ;
    POINT_xy.push_back(T->get_y()) ;
}


void GRAPH::Point_Finding(int object_x , int object_y) {
   // cout << "===========Point_Finding==========" << endl ;
 //   cout << First_tile -> get_x() << "," << First_tile -> get_y() << " w : " << First_tile -> get_width() << " h : " << First_tile -> get_height() <<endl;
 //   cout << object_x << " , " << object_y  << endl ;
    while (true) {
      while(true){
            if( object_y > First_tile -> get_y() + First_tile -> get_height() ){
                First_tile = First_tile -> get_rt() ;
            }else if (object_y == First_tile -> get_y() + First_tile -> get_height()){
                if(object_y == border_h)
                    break ;
                else
                    First_tile = First_tile -> get_rt() ;
            }else{  // less than
                if (object_y >= First_tile -> get_y() )
                    break ;
                else
                    First_tile = First_tile -> get_lb() ;
            }
        }

          if (object_x < First_tile -> get_x() ){
            First_tile = First_tile -> get_bl() ;
          }else if (object_x == First_tile -> get_x()){
            break ;
          }else {

            if (object_x < First_tile -> get_x() + First_tile -> get_width()){
                break ;
            }else if (object_x == First_tile -> get_x() + First_tile -> get_width()) {
                if (object_x == border_w){
                    break ;
                }else{
                    First_tile = First_tile -> get_tr() ;
                }
            }else {
                First_tile = First_tile -> get_tr() ;
            }
          }
    }
}


void GRAPH::neighbor_finding(TILE* T){

    TILE* modified_tile = NULL ;

    modified_tile = T -> get_bl() ;

    while(true){
       if(modified_tile == 0   )
            break ;

        if ( modified_tile -> get_y()  >= T -> get_y() + T -> get_height()  )
            break ;

       if (modified_tile -> get_index() == 0){
            T -> add_space_tile(T) ;
          //  cout << "L0" << endl ;
       }else {
            T -> add_solid_tile(T) ;
          //  cout << "L1" << endl ;
       }

       modified_tile = modified_tile -> get_rt() ;

    }

    //   TOP
    modified_tile = T -> get_rt() ;

    while(true){

       if(modified_tile == 0   )
            break ;

        if ( modified_tile -> get_x() + modified_tile -> get_width() <= T -> get_x()   )
            break ;

       if (modified_tile -> get_index() == 0){
            T -> add_space_tile(T) ;
           // cout << "T0" << endl ;
       }else {
            T -> add_solid_tile(T) ;
         //   cout << "T1" << endl ;
       }

       modified_tile = modified_tile -> get_bl() ;

    }

    //  Right
    modified_tile = T -> get_tr() ;

    while(true){

       if(modified_tile == 0   )
            break ;

        if ( modified_tile -> get_y() + modified_tile -> get_height() <= T -> get_y()   )
            break ;

       if (modified_tile -> get_index() == 0){
            T -> add_space_tile(T) ;
          //  cout << "R0" << endl ;
       }else {
            T -> add_solid_tile(T) ;
          //  cout << "R1" << endl ;
       }

       modified_tile = modified_tile -> get_lb() ;

    }

    // Down
    modified_tile = T -> get_lb() ;

    while(true){

       if(modified_tile == 0   )
            break ;

        if ( modified_tile -> get_x() >= T -> get_x()  + T -> get_width()   )
            break ;

       if (modified_tile -> get_index() == 0){
            T -> add_space_tile(T) ;
           // cout << "B0" << endl ;
       }else {
            T -> add_solid_tile(T) ;
           // cout << "B1" << endl ;
       }

       modified_tile = modified_tile -> get_tr() ;

    }

}


