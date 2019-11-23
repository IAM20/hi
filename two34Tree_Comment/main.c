#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 234 Tree node Structure */
typedef struct _node
{
    int key[3]; // max 3 key
    struct _node *link1, *link2, *link3, *link4, *p; // max 4 external node, parent node
    int node; // number of keys
    int index, p_index; // parent's index
} node;

/*Tree Structure*/
typedef struct _234t
{
    node *root; // Tree's Root node.
    int number; // the number of elements.
} _234t;

/* Initialize Tree Function */
_234t*init_234t(void)
{
    _234t*tree = (_234t*)malloc(sizeof(_234t)); // Dynamic Allocation for new Tree memory
    tree->root = (node*)malloc(sizeof(_234t));  // Dynamic Allocation for new Tree's Root memory
    tree->number = 0;
    
    return tree;
}

/* Initialize Tree node Function */
node*init_234node(void)
{
    node*t = (node*)malloc(sizeof(node));
    t->key[0] = 0;  // node's value. node can have max 3 values.
    t->key[1] = 0;
    t->key[2] = 0;
    t->link1 = NULL; // node's child node. because this tree is 234tree, node can have max 4 link.
    t->link2 = NULL;
    t->link3 = NULL;
    t->link4 = NULL;
    t->p = NULL;     // parent node
    t->index = 0;    // when we do Search and Insetion opertaion with certain values,
                     // This index indicates where this value is supposed to be in one node.
                     // index value can have 0 to 2 (becasue 234node can have max Three value)
    
    t->node = 0;     // node value means how many values this node have. this value can have 0 to 3
    t->p_index = 0;  // when the node have parent, this p_index value means which link does this node came from.
    return t;
}

_234t* propagation(node*ptr, int*array) // 새로 만든다.
{
   if(ptr == NULL)
       printf("ERROR");
    
    _234t*new_Tree = init_234t();
    new_Tree->root->link1 = init_234node();
    new_Tree->root->link2 = init_234node();
    
    if(ptr->p->p == NULL)
    {
        new_Tree->root->key[0] = ptr->p->key[2];
        new_Tree->root->node = 1;
        
        new_Tree->root->link1->key[0] = ptr->p->key[0];
        new_Tree->root->link1->key[1] = ptr->p->key[1];
        new_Tree->root->link2->key[0] = array[2];
        new_Tree->root->link1->node = 2;
        new_Tree->root->link2->node = 1;
        
        if(ptr->p_index == 4)
        {
            new_Tree->root->link1->link1 = ptr->p->link1;
            new_Tree->root->link1->link2 = ptr->p->link2;
            new_Tree->root->link1->link3 = ptr->p->link3;
            
            new_Tree->root->link2->link1 = init_234node();
            new_Tree->root->link2->link1->key[0] = array[0];
            new_Tree->root->link2->link1->key[1] = array[1];
            new_Tree->root->link2->link1->node = 2;
            
            new_Tree->root->link2->link2 = init_234node();
            new_Tree->root->link2->link2->key[0] = array[3];
            new_Tree->root->link2->link2->node = 1;
        }
        
    }
    
    return new_Tree;
}


/* split_234t Function
 
 when split operation occurs, the number of values in one node is 'Four'.
 So before call this function, let's say there is temporary array[4].
 put sorted node's 4 values in array[4], and we put this array into split Function.
 So we can easily access node's 4 values, and put this values to newly made node's child node.
 
 */
void split_234t(node*ptr, int*array)
{
    if(ptr->p == NULL) // split at root node
   {
       ptr->link1 = init_234node(); // split operation makes two new node.so we allocate two node struct memory.
       ptr->link2 = init_234node();
       
       ptr->link1->p = ptr->link2->p = ptr; // Store parent ptr address at Child's parent node.
       
       ptr->key[0] = array[2]; //3rd elements go to the Parent node.(Rule)
       
       ptr->link1->key[0] = array[0]; // store key[0], key[1] values at link1 node.
       ptr->link1->key[1] = array[1];
       ptr->link2->key[0] = array[3]; // store key[2] values at link2 node.
       
       ptr->link1->node = 2; // as we put 2 values on link1, link1->node is 2.
       ptr->link2->node = 1; // as we put 1 values on link2, link2->node is 1.
       ptr->node = 1;
   }
    
   else // split at child node.
   {
       if(ptr->p_index == 1) // this means ptr is parent's first link.
                             //this condition means when split operation occurs at parent's firts link node.
       {
           if(ptr->p->node == 1) // ptr's parent has 1 value.
           {
               /*
               when ptr's parent has 1 value, it has 2 child node.(2node)
               so when split occurs, parent's link2 which aleady exist has to move to link3.
                */
               ptr->p->link3 = init_234node(); // newly make link3 node.
               ptr->p->link3->key[0] = ptr->p->link2->key[0]; // parent's link2 move to link3.
               ptr->p->link3->node = 1;
               ptr->p->key[ptr->p_index-1] = array[2]; // 3rd element go to parent node.
               ptr->p->link1->key[0] = array[0];
               ptr->p->link1->key[1] = array[1]; // store array[0], array[1] values at link1 node.
               ptr->p->link2->key[0] = array[3]; // store array[2] value at link2 node.
               ptr->p->link1->node = 2; ptr->p->link2->node = 1; // as we put 2 values on link1 and put 1 value on link2.
               ptr->p->node++; // as we put additional 1 value on parent node.
               
               ptr->link3->p = ptr;  // we fill link3's parent node.
           }
           
           else if(ptr->p->node ==2) // ptr's parent has 2 values
           {
               ptr->p->link4 = init_234node(); // newly make link4 node.
               ptr->p->link4->key[0] = ptr->p->link3->key[0]; // this time, ptr's parent has 2 value. which means there is link2, 3 aleady.
               ptr->p->link3->key[0] = ptr->p->link2->key[0]; // so we move ptr's each link2,3 which aleady exist to link3,4 to make space.
               ptr->p->link4->node = 1;
               ptr->p->key[2] = ptr->p->key[1];
               ptr->p->key[1] = ptr->p->key[0];
               ptr->p->key[ptr->p_index-1] = array[2];
               ptr->p->link1->key[0] = array[0];
               ptr->p->link1->key[1] = array[1];
               ptr->p->link2->key[0] = array[3];
               ptr->p->link1->node = 2; ptr->p->link2->node = 1;
               ptr->p->node++;
               
               ptr->p->link4->p = ptr;
           }
           
       }
       else if(ptr->p_index == 2) //this condition means when split operation occurs at parent's second link node.
       {
           
           if(ptr->p->node == 1)
           {
               ptr->p->link3 = init_234node(); // newly make link3 node.
               ptr->p->key[ptr->p_index-1] = array[2]; // this time, split occurs at link2, we don't need to move aleady exist link.
               ptr->p->link2->key[0] = array[0];
               ptr->p->link2->key[1] = array[1];
               ptr->p->link3->key[0] = array[3];
               ptr->p->link2->node = 2; ptr->p->link3->node = 1;
               ptr->p->node++;
               
               ptr->p->link3->p = ptr;
           }
           
           else if(ptr->p->node ==2)
           {
               ptr->p->link4 = init_234node(); // newly make link4 node.
               ptr->p->link4->key[0] = ptr->p->link3->key[0]; // this time ptr's parent has 2 values, which means there is link2,3 aleady.
               ptr->p->link3->key[0] = ptr->p->link2->key[0]; // so we move link2,3 to link 3,4
               ptr->p->link4->node = 1;
               ptr->p->key[2] = ptr->p->key[1];
               ptr->p->key[ptr->p_index-1] = array[2];
               ptr->p->link2->key[0] = array[0];
               ptr->p->link2->key[1] = array[1];
               ptr->p->link3->key[0] = array[3];
               ptr->p->link2->node = 2; ptr->p->link3->node = 1;
               ptr->p->node++;
               
               ptr->p->link4->p = ptr;
           }
       }
       else if(ptr->p_index == 3) //this condition means when split operation occurs at parent's third link node.
       {
          if(ptr->p->node == 1)
           {
               ptr->p->link4 = init_234node(); // newly make link3 node.
               ptr->p->key[1] = array[2];      // ptr's parent have 1 value. when array[2] go to parent node. we can just add this value at key[1].
               ptr->p->link3->key[0] = array[0];
               ptr->p->link3->key[1] = array[1];
               ptr->p->link4->key[0] = array[3];
               ptr->p->link3->node = 2; ptr->p->link4->node = 1;
               ptr->p->node++;
               
               ptr->p->link4->p = ptr;
           }
           
           else if(ptr->p->node ==2)
           {
               ptr->p->link4 = init_234node(); // newly make link4 node.
               /* this time, split occurs at link3, so we don't need to move aleady exist node.*/
               ptr->p->link4->node = 1;
               ptr->p->key[ptr->p_index-1] = array[2];
               ptr->p->link3->key[0] = array[0];
               ptr->p->link3->key[1] = array[1];
               ptr->p->link4->key[0] = array[3];
               ptr->p->link3->node = 2; ptr->p->link4->node = 1;
               ptr->p->node++;
               
               ptr->p->link4->p = ptr;
           }
       }
       
        else if(ptr->p_index == 4)
        {
           ptr->p = propagation(ptr, array)->root;
        }
       /*=========================================================================================*/
   }
}


    
    
    
    

/*
 this function is same as searchTree function. except that there is no printf operation.
 */
node*npSearchTree(node*ptr, int key)
{
    if(ptr->node == 0)
        return ptr;
         
     else if(ptr->node == 1){
        
         if(ptr->link1 == NULL )
         {
             if(ptr->key[0] == key)
                 return ptr;
             else
             {
                 if(ptr->key[0] > key)
                 {ptr->index = 0; return ptr;}
                 else if(ptr->key[0] < key)
                 {ptr->index = 1; return ptr;}
             }
             
         }
         else
         {
             if(ptr->key[0] == key)
                 return ptr;
             
             else if(ptr->key[0] > key)
             {ptr->link1->p = ptr; ptr->link1->p_index = 1;return npSearchTree(ptr->link1, key);}
             else
             {ptr->link2->p = ptr; ptr->link2->p_index = 2;return npSearchTree(ptr->link2, key);}
         }
     }
      
     else if(ptr->node == 2){
        if(ptr->link1 == NULL)
        {
            if(ptr->key[0] > key)
            {ptr->index = 0; return ptr;}
            
            else if(ptr->key[0] == key)
            return ptr;
            
            else if((ptr->key[0]) < key && (ptr->key[1] > key))
            {ptr->index = 1; return ptr;}
            
            else if(ptr->key[1] == key)
            return ptr;
            
            else
            {ptr->index = 2; return ptr;}
        }
         
        else
        {
         if(ptr->key[0] > key)
         {ptr->link1->p = ptr; ptr->link1->p_index = 1; return npSearchTree(ptr->link1, key);}
         
         else if(ptr->key[0] == key)
         return ptr;
         
         else if((ptr->key[0]) < key && (ptr->key[1] > key))
         {ptr->link2->p = ptr; ptr->link2->p_index = 2; return npSearchTree(ptr->link2, key);}
         
         else if(ptr->key[1] == key)
         return ptr;
         
         else
         {ptr->link3->p = ptr; ptr->link3->p_index = 3; return npSearchTree(ptr->link3, key);}
        }
     }
            
     else if(ptr->node == 3){
          
         if(ptr->link1 == NULL)
         {
             if(ptr->key[0] > key)
             {ptr->index = 0; return ptr;}
             
             else if(ptr->key[0] == key)
             return ptr;
             
             else if((ptr->key[0]) < key && (ptr->key[1] > key))
             {ptr->index = 1; return ptr;}
             
             else if(ptr->key[1] == key)
             return ptr;
             
             else if((ptr->key[1]) < key && (ptr->key[2] > key))
             {ptr->index = 2; return ptr;}
             
             else if(ptr->key[2] == key)
             return ptr;
             
             else
             {ptr->index = 3;  return ptr;}
         }
          
         else
         {
          if(ptr->key[0] > key)
          {ptr->link1->p = ptr; ptr->link1->p_index = 1; return npSearchTree(ptr->link1, key);}
          
          else if(ptr->key[0] == key)
          return ptr;
          
          else if((ptr->key[0]) < key && (ptr->key[1] > key))
          {ptr->link2->p = ptr; ptr->link2->p_index = 2; return npSearchTree(ptr->link2, key);}
          
          else if(ptr->key[1] == key)
          return ptr;
          
          else if((ptr->key[1]) < key && (ptr->key[2] > key))
          {ptr->link3->p = ptr; ptr->link3->p_index = 3; return npSearchTree(ptr->link3, key);}
             
          else if(ptr->key[2] == key)
          return ptr;
             
          else
          {ptr->link4->p = ptr; ptr->link4->p_index = 4; return npSearchTree(ptr->link4, key);}
         }
     }
     return ptr;
}
/*
 this searchTree Function serves two tasks.
 
 First, find the key we want in the Tree. and tell whether there is key or not.
 
 Second, when the function find the key we want, it returns key's node pointer.
 this pointer has index value. so we can access certain key using node and index value.
 even if the function couldn't find key, it returns the position where the key has to be in the node.
 this position is used in insertion Function.
 
 */
node*searchTree(node*ptr, int key)
{
    
    if(ptr->node == 0)
        {
         printf("no exist\n"); // print message when there is no key in the tree.
         return ptr;
        }
    
    else if(ptr->node == 1){
       
        if(ptr->link1 == NULL ) // TRUE : this node is at the lowest of tree. because this node's link1 points nothing.
        {
            if(ptr->key[0] == key)
            {printf("exist"); ptr->index = 0;return ptr;} // Found! print "exist" message.
            else
            {
                printf("no exist\n"); // when there isn't key in the tree.
                if(ptr->key[0] > key)
                {ptr->index = 0; return ptr;} // we put index value at ptr node and return.
                else if(ptr->key[0] < key)
                {ptr->index = 1; return ptr;}
            }
            // index : when we do insetion, index tells where to put inserted key.
        }
        else  // this node has childs.
        {
            if(ptr->key[0] == key)
            {printf("exist");return ptr;} // Found! print "exist" message.
            
            else if(ptr->key[0] > key)
            /*
                when this node has childs and there isn't key in this node, we have to move to node's links.
                so we use the recursive method. before call searchTree function, we put p_index value at link node.
                because when we use link node later, we want to know this link's exact position at the parent node.
                so when we go to ptr->link1, we put 1 value at ptr->link1->p_index.
            */
                
            {ptr->link1->p = ptr; ptr->link1->p_index = 1;return searchTree(ptr->link1, key);}
            else
            {ptr->link2->p = ptr; ptr->link2->p_index = 2;return searchTree(ptr->link2, key);}
        }
    }
     
    else if(ptr->node == 2){
       if(ptr->link1 == NULL)
       {
           if(ptr->key[0] > key)
           {ptr->index = 0; printf("no exist\n"); return ptr;}
           
           else if(ptr->key[0] == key)
           {printf("exist");ptr->index = 0;return ptr;}
           
           else if((ptr->key[0]) < key && (ptr->key[1] > key))
           {ptr->index = 1; printf("no exist\n"); return ptr;}
           
           else if(ptr->key[1] == key)
           {printf("exist");ptr->index =1;return ptr;}
           
           else
           {ptr->index = 2; printf("no exist\n"); return ptr;}
       }
        
       else // this node has childs
       {
        if(ptr->key[0] > key)
        {ptr->link1->p = ptr; ptr->link1->p_index = 1; return searchTree(ptr->link1, key);}
        
        else if(ptr->key[0] == key)
        {printf("exist");ptr->index = 0;return ptr;}
        
        else if((ptr->key[0]) < key && (ptr->key[1] > key))
        {ptr->link2->p = ptr; ptr->link2->p_index = 2; return searchTree(ptr->link2, key);}
        
        else if(ptr->key[1] == key)
        {printf("exist");ptr->index =1;return ptr;}
        
        else
        {ptr->link3->p = ptr; ptr->link3->p_index = 3; return searchTree(ptr->link3, key);}
       }
    }
           
    else if(ptr->node == 3){
         
        if(ptr->link1 == NULL)
        {
            if(ptr->key[0] > key)
            {ptr->index = 0; printf("no exist\n"); return ptr;}
            
            else if(ptr->key[0] == key)
            {printf("exist");ptr->index = 0;return ptr;}
            
            else if((ptr->key[0]) < key && (ptr->key[1] > key))
            {ptr->index = 1; printf("no exist\n"); return ptr;}
            
            else if(ptr->key[1] == key)
            {printf("exist");ptr->index = 1;return ptr;}
            
            else if((ptr->key[1]) < key && (ptr->key[2] > key))
            {ptr->index = 2; printf("no exist\n"); return ptr;}
            
            else if(ptr->key[2] == key)
            {printf("exist");ptr->index = 2;return ptr;}
            
            else
            {ptr->index = 3; printf("no exist\n"); return ptr;}
        }
         
        else // this node has child
        {
         if(ptr->key[0] > key)
         {ptr->link1->p = ptr; ptr->link1->p_index = 1; return searchTree(ptr->link1, key);}
         
         else if(ptr->key[0] == key)
         {printf("exist");ptr->index = 0;return ptr;}
         
         else if((ptr->key[0]) < key && (ptr->key[1] > key))
         {ptr->link2->p = ptr; ptr->link2->p_index = 2; return searchTree(ptr->link2, key);}
         
         else if(ptr->key[1] == key)
         {printf("exist");ptr->index = 1;return ptr;}
         
         else if((ptr->key[1]) < key && (ptr->key[2] > key))
         {ptr->link3->p = ptr; ptr->link3->p_index = 3; return searchTree(ptr->link3, key);}
            
         else if(ptr->key[2] == key)
         {printf("exist");ptr->index = 2;return ptr;}
            
         else
         {ptr->link4->p = ptr; ptr->link4->p_index = 4; return searchTree(ptr->link4, key);}
        }
    }
    return ptr;
}
/*
 insert_234t function uses npSearchTree(np means 'no printf') function.
 using npSearchTree function, we can access exact node where key has to be in the tree.
 so first we get key's exact node using npSearchTree function,
 and using node's index value, put key value at exact position in the node.
 */
void insert_234t(_234t*base,int key)
{
    node*p = npSearchTree(base->root, key); // first, we assign key'node to node*p.
    int temp[4]; // this temporary array is used when we do split operation.
    
    if(p == NULL)
        printf("Error"); // check p pointer has address.

    if(p->node == 0) // there is no value in the node.
    { p->key[0] = key; p->node++;}
    
    else if(p->node == 1)
    {
        if(p->index == 1) // there is 1 value in the node. so we use p's index variable and put key at right index.
        {p->key[p->index] = key; p->node++;}
        else
        {p->key[1] = p->key[0]; p->key[0] = key;p->node++;} // when key's index is same as aleady exist value's index, we have to move index firtst.
    }
    
    else if(p->node == 2)
    {
        if(p->index == 0)
        {p->key[2] = p->key[1]; p->key[1] = p->key[0]; p->key[0] = key;p->node++;}
        else if(p->index == 1)
        {p->key[2] = p->key[1]; p->key[1] = key;p->node++;}
        else if(p->index ==2)
        {p->key[2] = key;p->node++;}
    }
    else if(p->node ==3)
    {
        if(p->index == 0)
        {temp[0] = key; temp[1] = p->key[0]; temp[2] = p->key[1]; temp[3] = p->key[2];} // put values into temp array firtst,
        else if(p->index == 1)                                                              // Getting sorted,
        {temp[0] = p->key[0]; temp[1] = key; temp[2] = p->key[1]; temp[3] = p->key[2];} // Put them into Split Function!
        else if(p->index == 2)
        {temp[0] = p->key[0]; temp[1] = p->key[1]; temp[2] = key; temp[3] = p->key[2];}
        else
        {temp[0] = p->key[0]; temp[1] = p->key[1]; temp[2] = p->key[2]; temp[3] = key;} // [4,5,6,7]
            
        split_234t(p, temp);
        
    }
    base->number++;
}

void print_Tree(_234t*tree)
{
    int i;
    
        if(tree->root->link1 == NULL)
       {
           printf("(");
           for(i=0;i<tree->number;i++)
               printf("%3d",tree->root->key[i]);
           printf("  )");
           printf("\n");
       }
           
       else if(tree->root->link3 == NULL)
       {
           printf("(");
           for(i=0;i<tree->root->node;i++)
               printf("%3d",tree->root->key[i]);
           printf("  )");
           printf("\n");
           
           printf("(");
           for(i=0;i<tree->root->link1->node;i++)
               printf("%3d",tree->root->link1->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link2->node;i++)
               printf("%3d",tree->root->link2->key[i]);
           printf("  )");
           printf("\n");
           
       }
       else if(tree->root->link4 == NULL)
       {
           printf("(");
           for(i=0;i<tree->root->node;i++)
               printf("%3d",tree->root->key[i]);
           printf("  )");
           printf("\n");
           
           printf("(");
           for(i=0;i<tree->root->link1->node;i++)
               printf("%3d",tree->root->link1->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link2->node;i++)
               printf("%3d",tree->root->link2->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link3->node;i++)
               printf("%3d",tree->root->link3->key[i]);
           printf("  )");
           printf("\n");
       }
       else if(tree->number <= 12)
       {
           printf("(");
           for(i=0;i<tree->root->node;i++)
               printf("%3d",tree->root->key[i]);
           printf("  )");
           printf("\n");
           
           printf("(");
           for(i=0;i<tree->root->link1->node;i++)
               printf("%3d",tree->root->link1->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link2->node;i++)
               printf("%3d",tree->root->link2->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link3->node;i++)
               printf("%3d",tree->root->link3->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link4->node;i++)
               printf("%3d",tree->root->link4->key[i]);
           printf("  )");
           printf("\n");
       }
       
       else
       {
           printf("(");
           for(i=0;i<tree->root->node;i++)
               printf("%3d",tree->root->key[i]);
           printf("  )");
           printf("\n");
           
           printf("(");
           for(i=0;i<tree->root->link1->node;i++)
               printf("%3d",tree->root->link1->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link2->node;i++)
               printf("%3d",tree->root->link2->key[i]);
           printf("  )");
           printf("\n");
           
           printf("(");
           for(i=0;i<tree->root->link1->link1->node;i++)
               printf("%3d",tree->root->link1->link1->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link1->link2->node;i++)
               printf("%3d",tree->root->link1->link2->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link1->link3->node;i++)
               printf("%3d",tree->root->link1->link3->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link2->link1->node;i++)
               printf("%3d",tree->root->link2->link1->key[i]);
           printf("  ) (");
           for(i=0;i<tree->root->link2->link2->node;i++)
               printf("%3d",tree->root->link2->link2->key[i]);
           printf(" )");
           printf("\n");
        
    }
   
}

void deleteTree(_234t*tree,int key)
{
    node*p = npSearchTree(tree->root, key);
    
    if(p == NULL)
        printf("ERROR");
    
    if(p->node == 1)
    {
        /*Transfer*/
        
    }
    else if(p->node == 2)
    {
        if(p->key[0] == key)
        {
            p->key[0] = p->key[1];
            p->node--;
        }
        else
            p->node--;
    }
    
    else if(p->node == 3)
    {
        if(p->key[0] == key)
        {
            p->key[0] = p->key[1];
            p->key[1] = p->key[2];
            p->node--;
        }
        else if(p->key[1] == key)
        {
            p->key[1] = p->key[2];
            p->node--;
         }
        else
            p->node--;
    }
        
    if(p->link1 != NULL)
        free(p->link1);
    if(p->link2 != NULL)
        free(p->link2);
    if(p->link3 != NULL)
        free(p->link3);
    if(p->link4 != NULL)
        free(p->link4);
    
    tree->number--;
}

int main()
{
    int  choice, key;
    char mode;
    
    _234t*tree = init_234t();
    tree->root = init_234node();
    
    printf("==========================\n");
    printf("Mode 선택\n");
    printf("1. interactive mode\n");
    printf("2. batch mode\n");
    printf("==========================\n");
    printf("(1/2) ");
    scanf("%d",&choice);
    printf("\n");
    
    printf("**** interactive mode ****\n");
    printf("명령어를 입력하세요(i: insertion, d: deletion, s: searching\n");
    printf("종료하려면 해당 명령어 외 다른 키를 입력하세요.\n");
    
    while(1)
    {
        
        if( choice == 1)
        {
            
            scanf("%c",&mode);
            scanf("%d",&key);
          
            if( mode == 'i')
            {
                insert_234t(tree, key);
                print_Tree(tree);
            }
        
            else if( mode == 's')
            {
                searchTree(tree->root, key);
                printf("\n");
            }
            
            else if( mode == 'd')
            {
                deleteTree(tree, key);
                print_Tree(tree);
            }
        }
    }
}
/*
 
 -1120 0019
 
 parent node 가 가장 큰 문제이다.
 시작을 할 때 parent node 를 비우고 시작을 하는데 searching 과정에서 p가 추가가 되다 보니
 어쩔 수 없이 조건문에서 충돌이 일어나게 된다.
 구조를 다시 만들거나 조건을 바꿔야 할 것 같다.
 
 맨 처음 트리를 만드는 과정, 즉 층이 1층도 없는 과정이 가장 문제.
 
 -1120 2152
 
 split 1층 구조에서 완료
 propagation 및 display 해결해야 한다.

 -1121 0140
 
 propagation 일단 성공인데...
 display 를 함수로 만들어야할 것 같다.
 또한 propaagation이 된건지 엄밀히 확인.
*/




