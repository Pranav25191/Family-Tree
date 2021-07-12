/*Author: Balijapelly Pranav
  Roll No: 1903108
*/
#include<stdio.h>
class tnode{								// This is tree node
    int value,generation;                   // this integer is element of tree, generation is the generation of element
    class tnode *parent;                    // this is pointer to parent
    class LinkedList *child_list;           // this pointer to children list
    tnode(int q);                           
friend class LinkedList;
friend class Node;                  
friend class FamilyTree;
};
/*constructor of tree node. In this constructor all pointer made to point to NULL*/
tnode::tnode(int q){
    value=q;                         
    generation=0; 
    parent=NULL;
    child_list=NULL;
}
/*This is class of linked list node.*/
class Node{
    class tnode *ele;               //A pointer points to tree node.
    class Node *nxt;                //A pointer which points to next node.
friend class FamilyTree;
friend class LinkedList;
};
/*This is class of LinkedList.This class contains following functions.
1) addback 2)len 3)top 4)remove*/
class LinkedList{
public:
    class Node *head;
    class Node *tail;
    int length;
    LinkedList();//{head=NULL;tail=NULL;length=0;}
    void addback(class tnode *n);
    int len();
    class Node* top();
};
LinkedList::LinkedList(){
    head=NULL;
    tail=NULL;
    length=0;
}
/*Function Description: This function adds Node to the list at back of list.
  Input:  A class Node
  Output: NONE */
void LinkedList::addback(class tnode *n){
    if (tail==NULL)             //if the list is empty it creates a tail node.
    {                           //Then at initial stage head is tail. 
        tail = new Node;
        tail->ele=n;
        tail->nxt=NULL;
        head=tail;
        length++;               //For adding every single node lenght of list increments.
    }
    else
    {                            //If the list is not is not empty then now tail is created and adds in front of previous tail,  
        class Node *temp=tail;   
        tail = new Node;        //creating a new tail.
        tail->ele=n;            
        temp->nxt=tail;         //Pevious tail's next pointer should point to new tail. 
        tail->nxt=NULL;         //After tail is created its next pointer should points to NULL
        length++;               //For adding every single node lenght of list increments.
    }
}
/*Function Description: This function return the length of list.
  Input: NONE
  Output:length of list
*/
int LinkedList::len(){
    return length;
}
/*Function Description: This function returns head element of linkedlist
  Input: NONE
  Output: class Node*/
class Node* LinkedList::top(){
    return head;
}
//This is Familiy Tree class
class FamilyTree{
private:
    class tnode *root;
public:
    FamilyTree(int q);
    ~FamilyTree();
    class tnode* search(int x);
    class tnode* find(int x,class tnode *tr);
    class tnode* remove(class tnode *tr);
    void insertChild(int x,int y);
    int ischild(int x,int y);
    int isgrandparent(int x,int y);
    int isgrandchild(int x,int y);
    bool inchildlist(tnode* dummy,tnode* check);
    int isNephew(class tnode* temp,class tnode* temp_1);
    int isUncle(class tnode* temp,class tnode* temp_1);
    void print(int x,const char arr[],int i,int j);
    int isCousin(class tnode *temp,class tnode *temp_1 );
    void relationship(int x,int y);
};
/*FamilyTree constructor when the class variable is created this constructor is called and root node created with int value q.*/
FamilyTree::FamilyTree(int q){ 
    root = new tnode(q);
}
/*This is FamilyTree destructor. This function deletes every node in the tree.*/
FamilyTree::~FamilyTree(){
    remove(root);
}
/*Function Description:this function returns node which contains element x
  Input: integer
  Output: a tree node */
class tnode* FamilyTree::search(int x){
    return find(x,root);
}
/*Function Description: This function is recursive function.This functions will checks every element of tree node with with input integer
  Input: integer,root node of tree
  Output: returns tree node*/
class tnode* FamilyTree::find(int x,class tnode *tr){
    class tnode* found;
    if (tr->value==x)  return tr;                   //Base case. if it founds the node with given element it returns node                   
    if (tr->child_list==NULL) return NULL;              //Base case
    class Node *temp = tr->child_list->top();           //temp is assigned to head of linkedlist.
    for(int i=0;i<(tr->child_list->len());i++){
        found= find(x,temp->ele);               //recursive call.
        if(found!=NULL) return found;           //if node found and it is not NULL then the node is returned
        temp=temp->nxt;                         //this temp iterates through the children linkedlist.
    }
    return NULL;
}
/*Function Description: This function is recursive function. this function free up the space which dynamically allocated.
  Input: root node of tree.
  Outpuy:NULL
*/
class tnode* FamilyTree::remove(class tnode *tr){
    class tnode* found;
    if (tr->child_list==NULL) { delete tr; return NULL;}   //Base case. if the tree node has no childrens then that node's memory is freed.
    class Node *temp = tr->child_list->head;               //temp is assigned to head of linkedlist.
    while(temp!=NULL){
        found=remove(temp->ele);                   //recursive call
        temp=temp->nxt;                           //this temp iterates through the children linkedlist.
    }
    delete tr;                                  //after removing all children nodes of parent node then parent node's memory is freed
    return NULL;                                //after freeing up parent node memory it returns NULL
}
/*Function Description: This function adds a element to the tree
  Input:   integer
  Output: NONE*/
void FamilyTree::insertChild(int x,int y){
    class tnode* temp = search(x);                //For adding a child node to parent we have to find parent node.that is done here 
    if (temp==NULL) {                             //if parent is not found this if executed and returns from function
        printf("No parent found\n");              //because there is no parent to add child.
        return;
    } 
    tnode *node = new tnode(y);             //new child node is dynamically created
    node->parent=temp;                      //childs parent pointer is made point to parent node(which is returned from search function).
    node->generation=temp->generation+1;    //then childs genration is incremented
    if(temp->child_list==NULL)                          
        temp->child_list= new LinkedList();         //if parent chils list is empty then it is created.
    temp->child_list->addback(node);                //child node is added to the list
}
/*Function Description: This function checks relationship between x and y. If the relationship is child then it gets printed.
  Input:  integers.
  Output: integer.
*/
int FamilyTree::ischild(int x,int y){
    class tnode *temp =find(x,root);                  //temp is assigned to node with element x.
    if( temp==root) return 0;                         //if temp is root. since root cannot be child so it returns from function
    Node* temp_1=temp->parent->child_list->head;              //temp_1 is assigned head of children list of temp
    while(temp_1!=NULL){
        if (temp_1->ele->value==y){                       //if condition is met then relation get satisfied
            printf("%d and %d are siblings\n",x,y);   //relation ship is printed
            return 1;
        }
        temp_1=temp_1->nxt;
    }
    return 0;
}
/*Function Description:This function checks relationship between x and y. If the relationship is grandparent or parent then it gets printed.
  Input: integers
  Output: integer
*/
int FamilyTree::isgrandparent(int x,int y){
    class tnode* temp= find(y,root);            //temp is assigned to node with element y.
    int count=0;
    while(temp!=NULL){
        if (temp->value==x){                        //if this condition is stisfied
            print(count,"Parent",x,y);          //print function gets called
            return 1;
        }
        count++;
        temp=temp->parent;                     //temp will become its parent
    } 
    return 0;
}
/*Function Description: This function checks relationship between x and y. If the relationship is grandchild then it gets printed.
  Input: integers
  Output:integer
*/
int FamilyTree::isgrandchild(int x,int y){           
    class tnode* temp= find(x,root);                 //temp is assigned to node with element x.
    int count=0;                                        
    while(temp!=NULL){                                     
        if (temp->value==y){                                    
            print(count,"Child",x,y);               //print function is called to print relationship.
            return 1;
        }
        count++;
        temp=temp->parent;                          //temp will become its parent
    } 
    return 0;
}
/*Function Description:This function takes a tree node element and check that it is children list of other tree node.
  Input: 2 tree nodes
  Output: boolean value
*/
bool FamilyTree::inchildlist(tnode* dummy,tnode* check){
    if(dummy->parent==NULL) return false;            //if dummy is root then it returns from function.
    Node* temp= dummy->parent->child_list->head;        
    while(temp!=NULL){      
        if (temp->ele->value==check->value)                 //if this condition is satisfied it returns true  
            return true;
        temp=temp->nxt;
    }
    return false;
}
/*Function Description: This function checks relationship between x and y. If the relationship is nephew then it gets printed.
  Input: 2 class nodes
  Output:integer
*/
int FamilyTree::isNephew(class tnode* temp,class tnode* temp_1){
    class tnode *iter= temp;                        //iter is assigned to temp
    int count=1;
    while(iter->parent!=NULL){                              
        iter=iter->parent;                          //iter becomes its parent 
        if (inchildlist(temp_1,iter)==true) {       //if this condition is satisfied then the relation nephew 
            print(count,"Nephew/Niece",temp->value,temp_1->value);  //print function is called  
            return 1;
        }
        count++;
    }
    return count;
}
/*Function Description:This function checks relationship between x and y. If the relationship is uncle then it gets printed.
  Input: 2 class nodes
  Output:integer
*/
int FamilyTree::isUncle(class tnode* temp,class tnode* temp_1){
    class tnode *iter= temp_1;                      //iter is assigned to temp
    int count=1,k=0;
    while (iter->parent!=NULL)
    {
        iter=iter->parent;                              //iter becomes its parent 
        if (inchildlist(temp,iter)==true) {             //if this condition is satisfied then the relation uncle
            print(count,"Uncle/Aunt",temp->value,temp_1->value);   //print function is called  
            k=1;                                                            
            return 1;
        }
        count++;
    }
    return count;
}
/*Function Description: This Function prints the relation between given inputs to relationship function based on inputs given to this function
  Input:   3 integers and array
  Output:NONE
*/
void FamilyTree::print(int x,const char arr[],int i,int j){
    char plus[4][18]={"","Grand","Great Grand","Great Great Grand"}; 
    if (arr[0]=='C'|| arr[0]=='P'||arr[0]=='U'||arr[0]=='N'){
        if(x<5)
            printf("%d is %s %s of %d\n",i,plus[x-1],arr,j);
        else
            if(x==5)
                printf("%d is %drd %s %s of %d\n",i,x-2,plus[2],arr,j);
            else
                printf("%d is %dth %s %s of %d\n",i,x-2,plus[2],arr,j);
    }
}
/*Function Description: This function checks relationship between x and y. If the relationship is uncle then it gets printed.
  Input: 2 tree nodes
  Output: integer
*/
int FamilyTree::isCousin(class tnode *temp,class tnode *temp_1 ){
    tnode *iter= temp;                                  //iter is assigned to temp
    tnode *iter_1= temp_1;                              //iter_1 is assigned to temp_1
    char lls[4][3]={"st","nd","rd","th"};               //Initialising arrays
    char lln[4][7]={"once","twice","thrice","times"};   //intialising
    if(temp->generation<temp_1->generation){            
        int count=0,gen1,gen2;
        gen1=temp_1->generation;
        gen2=temp->generation;
        for(int i=0;i<gen1-gen2;i++){                   //here temp is updated to parent 
            temp_1=temp_1->parent;
        }
        while(temp!=temp_1){                    //This while loop runs till temp and temp_1 become equal
            temp=temp->parent;                  //temp is updated to its parent
            temp_1=temp_1->parent;              //temp_1 is updated to its parent
            count++;                            //count is incremented 
        }          
        if (temp==temp_1) 
        {	int k=count-1;
            if(k<3)
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[k-1],gen1-gen2,iter_1->value);
            else
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[3],gen1-gen2,iter_1->value); 
            return 1;
        }
    }
    else if(temp->generation>temp_1->generation){
        int count=0,gen1,gen2;
        gen2=temp_1->generation;
        gen1=temp->generation;
        for(int i=0;i<gen1-gen2;i++){
            temp=temp->parent;
        }
        while(temp!=temp_1){                           //This while loop runs till temp and temp_1 become equal
            temp=temp->parent;                         //temp is updated to its parent
            temp_1=temp_1->parent;                     //temp_1 is updated to its parent
            count++;                                    //count is incremented 
        }          
        if (temp==temp_1) 
        {	int k=count-1;
            if(k<3)
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[k-1],gen1-gen2,iter_1->value);
            else
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[3],gen1-gen2,iter_1->value);
            return 1;
        }
    }
    else {
        int count=0;
        int gen1=temp->generation;
        int gen2=temp_1->generation;
        int k=gen1-(gen1-gen2)-1;
        while(temp!=NULL){
            temp=temp->parent;
            temp_1=temp_1->parent;
            if(temp==temp_1) {printf("%d is %d%s cousin of %d\n",iter->value,count,lls[count-1],iter_1->value); return 1;}
            count++;
        }
    }
    return 0;
}
/*Function Description: This function calls every relation function inside it based on the conditions 
  Input:  2 integers
  Output: NONE
*/
void FamilyTree::relationship(int x,int y){
    tnode* temp= find(x,root);                 //search for node with element x
    tnode* temp_1= find(y,root);               //search for node with element y
    if( x==y ) {printf("Both are same menbers\n"); return;}
    if(temp==NULL || temp_1==NULL){
        printf("%d and %d are unrelated\n",x,y);  //if x or y are note in tree then this print statement printed
        return;                                     //returns from function
    }

    if (ischild(x,y)==1) return;
    if(temp->generation<=temp_1->generation){
            if(isgrandparent(x,y)==1) return;
            if(isUncle(temp,temp_1)==1 ) return;
            if(isCousin(temp,temp_1)==1) return;
    }
    else{
        if (isgrandchild(x,y)) return;
        if (isNephew(temp,temp_1)==1) return;
        if (isCousin(temp,temp_1)==1) return;
    }
}
int main(){
   class FamilyTree ft(30);
	ft.insertChild(30,20);
	ft.insertChild(20,15);
	ft.insertChild(15,3);
	ft.insertChild(15,16);
	ft.insertChild(16,17);
	ft.insertChild(17,18);
	ft.insertChild(3,8);
	ft.insertChild(8,10);
	ft.insertChild(3,4);
	ft.insertChild(3,11);
	ft.insertChild(3,12);
	ft.insertChild(4,5);
	ft.insertChild(4,6);
	ft.insertChild(6,7);
	ft.insertChild(10,13);
	ft.insertChild(4,100);
    ft.insertChild(100,101);
    ft.insertChild(101,102);
    ft.insertChild(102,103);
    ft.insertChild(103,104);
    ft.insertChild(104,105);
	ft.relationship(4,5);
	ft.relationship(10,7);
	ft.relationship(18,13);
	ft.relationship(4,6);
	ft.relationship(8,4);
	ft.relationship(8,17);
	ft.relationship(10,5);
	ft.relationship(16,10);
	ft.relationship(3,10);
	ft.relationship(3,13);
	ft.relationship(16,13);
	ft.relationship(15,13);
	ft.relationship(30,13);
	ft.relationship(40,13);
	ft.relationship(20,30);
	ft.relationship(5,4);
	ft.relationship(7,10);
	ft.relationship(13,18);
	ft.relationship(6,4);
	ft.relationship(4,8);
	ft.relationship(17,8);
	ft.relationship(5,10);
	ft.relationship(10,16);
	ft.relationship(10,3);
	ft.relationship(13,3);
	ft.relationship(13,16);
	ft.relationship(13,15);
	ft.relationship(13,30);
	ft.relationship(13,40);
	ft.relationship(30,20);
    ft.relationship(105,7);
    ft.relationship(105,5);
}