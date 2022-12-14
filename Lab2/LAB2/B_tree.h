#ifndef B_TREE_H
#define B_TREE_H


#include <iostream>
#include <fstream>
#include <string> 
#include <vector> 
#include <map>

#include "Treenode.h"
#include "contour.h"
#include "terminal.h"

using namespace std ; 

class B_TREE{
    private:
        TreeNode* root ; 
        Contour*  head ;
        int area ;  
        int HPWL ; 
        int cost ; 
        int height ; 
        int width ; 
        int Border_x ;
        int Border_y ; 
        double alpha ; 
        
        vector <TreeNode*> All_tree_node ; 
        vector <Terminal*> Terminal_vec  ;
        vector < vector<string> > all_net_name ; 
        map< string , TreeNode* > TreeNode_map ; 
        map< string , Terminal* > Terminal_map ; 
        
    public:
        B_TREE(TreeNode* node , Contour*  first,  int x ,int y , double a )  : root(node) , head(first) ,area(0), HPWL(0.0) , cost (0), height(0) , width(0) ,Border_x(x) , Border_y (y) , alpha(a)  {}; 
        //~B_TREE() ; 
        void Print_block() ;
        int get_border_x() {return Border_x ; }
        int get_border_y() {return Border_y ; }
        //int get_cost() {return one ; }  
        
        void Random_construct_tree(TreeNode* new_child) ;
        bool set_each_block_x() ;  
        bool compute_y ();
        void compute_HPWL() ; 
        void contour_set_head();
        void contour_setting_right( TreeNode* child , int &max_width , int &max_height ) ;
        void contour_setting_top( TreeNode* child) ;
        
        void switch_node ( TreeNode* one , TreeNode* two ) ; 
        void rotate_node ( TreeNode* one ) ; 
        void delete_node ( TreeNode* child ) ;
        void insert_node (TreeNode* Insert_point , TreeNode* child ) ;
        
        
        void Simulated_Annealing() ;
        void Simulated_Annealing_2 ( )  ;       
        void Restore( TreeNode* rotate_n , TreeNode* switch_n_1 , TreeNode* switch_n_2 , TreeNode* delete_n , TreeNode* delete_parent , bool delete_is_left  , bool child_is_left  ) ; 
        
        void construct_map(); 
          
        void save_terminals (int terminals_number , ifstream& block_file ) ; 
        void save_net_name  (const char* net_file_path ) ;
        void write_output_file (ofstream& out_file , double total_time) ; 
};











#endif
