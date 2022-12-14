#ifndef TREENODE_H
#define TREENODE_H


#include <string>

using namespace std ; 

class TreeNode{
  
    private:
        TreeNode* Parent ; 
        TreeNode* Lnode ;   // the right side of this node in the graph
        TreeNode* Rnode ;   // the top side of this node in the graph (having the same X coordinate)
        
        string block_name ; 
        int block_x  ;   // block_x 
        int block_y  ;   // block_y 
        int block_w  ; 
        int block_h  ;

    public :  
        
        TreeNode(string Name , int x , int y , int w , int h ) : Lnode(0) , Rnode(0) , block_name(Name) , block_x(x) , block_y (y) , block_w (w) , block_h(h) {} ; 
        
        string get_Name() {return block_name ; } 
        int get_x() {return block_x ; }
        int get_y() {return block_y ; }
        int get_w() {return block_w ; }
        int get_h() {return block_h ; }
        TreeNode* get_Lnode() {return Lnode ;}
        TreeNode* get_Rnode() {return Rnode ;} 
        TreeNode* get_Parent() {return Parent ;} 
        
        void set_x(int x ) { block_x = x ; }
        void set_y(int y ) { block_y = y ; }
        void set_w(int w ) { block_w = w ; }
        void set_h(int h ) { block_h = h ; }
        
        void set_Lnode(TreeNode* node) { Lnode = node ;  }
        void set_Rnode(TreeNode* node) { Rnode = node ;  }
        void set_Name(string Name ) { block_name = Name; } 
        void set_Parent(TreeNode* node) { Parent = node ;  }
        
};





























#endif
