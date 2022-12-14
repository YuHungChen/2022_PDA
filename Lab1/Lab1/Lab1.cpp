#include <iostream>
#include <fstream>
#include <string>

#include "graph.h"
using namespace std ;

int main(int argc , char* argv[]){


    ifstream in1 ;

    in1.open(argv[1]) ;

    int border_x , border_y  ;

    in1 >> border_x  ;
    in1 >> border_y ;

   // cout << border_x << " " << border_y << endl ;

    string text ;

    GRAPH My_Graph = GRAPH(border_x , border_y);
    //TILE main_ = TILE(0,0,border_x, border_y,0) ;
    TILE* main_T = 0 ;
    int x=0,y=0,w=0,h=0 ;
    //int total_tile = 0 ;
    //int now_line = 1 ;
    int index ;

    while (in1 >> text)
    {
        in1 >> x ;
        in1 >> y ;
        if (text == "P"){
            //cout << int (text)  << endl ;

             My_Graph.Point_Finding( x , y)  ;
             main_T = My_Graph.Get_First_Tile() ;
             My_Graph.compute_point_XY(main_T) ;
            // cout << endl << "===================="  << endl ;
           //  cout << main_T -> get_x() << " " << main_T -> get_y() <<endl ;
            // cout << "===================="  << endl ;
        }else{
            index = stoi(text) ;

            in1 >> w ;
            in1 >> h ;
            //index = atoi(text) - 48 ;
            My_Graph.Insert_tile(x, y, w, h,  index) ;
        }

         //My_Graph.area_search(border_x , border_y,argv ) ;
    }
    My_Graph.area_search(border_x , border_y , argv ) ;

    in1.close() ;

    return 0 ;
}
