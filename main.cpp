#include <iostream>
#include "Queues.cpp"
#include "Stacks.cpp"

using namespace std;
//Initialize Node Structure
class node
{
public:
    int data;
    node *lson, *rson;
};
//Initialize Class uses node.
class BinSrchTree
{
private:
    node *T, *ptr, *p1, *p2;
public:
    BinSrchTree();
    void fillNode();
    void fillNode(int);
    bool search();
    bool search(int);
    void insertNode();
    void insertNode(int);
    void deleteNode(int);
    void inOrder(node*);
    void inOrder();
    void postOrder(node*);
    void postOrder();
    void levelOrder(node*);
    void levelOrder();
    void clearTree(node*);
    void clearTree();
    char miniMenu(bool);
    int menu();
};

//Constructor
BinSrchTree::BinSrchTree()
{
    T = NULL;
}

//Gives *ptr the data that it prompts for. 
void BinSrchTree::fillNode()
{
    int value;
    ptr = new node;
    cout << "Enter a value: ";
    cin >> value;
    ptr->data = value;
    ptr->lson = ptr->rson = NULL;
}

//Gives *ptr the data pasted to the function
void BinSrchTree::fillNode(int data)
{
    int value;
    ptr = new node;
    ptr->data = data;
    ptr->lson = ptr->rson = NULL;
}

//Searches the tree for data in ptr returns bool if (or not) found. This also aligns the p1 and p2 pointers. 
bool BinSrchTree::search()
{
    bool found = false;
    p1 = p2 = T;
    while((p2!=NULL)&&(!found))
    {
        if(ptr->data < p2->data)
        {
            p1 = p2;
            p2 = p2->lson;
        }
        else
        {
            if(ptr->data > p2->data)
            {
                p1 = p2;
                p2 = p2->rson;
            }
            else
            {
                found = true;
            }
        }
    }
    return found;
}

//Searches the tree for data pasted to it returns bool if (or not) found. This also aligns the p1 and p2 pointers. 
bool BinSrchTree::search(int data)
{
    bool found = false;
    p1 = p2 = T;
    while((p2!=NULL)&&(!found))
    {
        if(data < p2->data)
        {
            p1 = p2;
            p2 = p2->lson;
        }
        else
        {
            if(data > p2->data)
            {
                p1 = p2;
                p2 = p2->rson;
            }
            else
            {
                found = true;
            }
        }
    }
    return found;
}

//Inserts the node ptr with it's data into tree. 
void BinSrchTree::insertNode()
{
    if (search() == false)
    {
        if (T == NULL)
        {
         T = ptr;
        }
        else
        {
         if (ptr->data < p1->data)
         {
             p1->lson = ptr;
         }
         else if (ptr->data > p1->data)
         {
             p1->rson = ptr;
         }
         else
         {
             cout << ptr->data << " already in the tree\n";
         }
        }
    }
    else
        cout << ptr->data << " already in the tree\n";
}

//overload function inserts node with pasted data into tree. 
void BinSrchTree::insertNode(int data)
{
    fillNode(data);
    if (search(data) == false)
    {
        if (T == NULL)
        {
            T = ptr;
        }
        else
        {
         if (ptr->data < p1->data)
         {
             p1->lson = ptr;
         }
         else if (ptr->data > p1->data)
         {
             p1->rson = ptr;
         }
         else
         {
             cout << ptr->data << " already in the tree\n";
         }
        }
    }
    else
        cout << ptr->data << " already in the tree\n";
}

//uses search to find node. Then seperates out into three different cases and then about 4 more cases. 
//It eventualy deletes the node in a way that preserves the bianary treeness. 
void BinSrchTree::deleteNode(int data)
{
    if(!search(data))
        cout << "Data item to be deleted not found in tree" << endl;
    else
    {
        if((p2->lson==NULL)&&(p2->rson==NULL))
        {
            if(p1->lson == p2)
                p1->lson = NULL;
            else
                p1->rson = NULL;
            delete p2;
        }
        else if((p2->lson==NULL)||(p2->rson==NULL))
        {
            if(p1->lson==p2)
            {
                if(p2->lson==NULL)
                {
                    p1->lson = p2->rson;
                }
                else
                {
                    p1->lson = p2->lson;
                }
            }
            else
            {
                if(p2->lson==NULL)
                {
                    //We had to add this special condition for trees that had two nodes. 
                    if(p1==p2)
                    {
                        T = p2->rson;
                    }
                    else
                        p1->rson = p2->rson;
                }
                else
                {
                    //This is the above code's counterpart. 
                    if(p1==p2)
                    {
                        T = p2->lson;
                    }
                    else
                        p1->rson = p2->lson;
                }
            }
            delete p2;
        }
        else
        {
            node *r = p2->rson;
            node *q;
            if(r->lson==NULL)
            {
                p2->data = r->data;
                p2->rson = r->rson;
                delete r;
            }
            else
            {
                do
                {
                    q = r;
                    r = r->lson;
                }while(r->lson != NULL);
                p2->data = r->data;
                q->lson = r->rson;
                delete r;
            }
        }
    }
}

//Outputs the tree inOrder Uses cool recursivness. (acending order) Function Overloaded
void BinSrchTree::inOrder(node *p)
{
    if (p!=NULL)
    {
        inOrder(p->lson);
        cout << p->data << " " ;
        inOrder(p->rson);
    }
}

//Outputs the tree inOrder Uses cool recursivness. (acending order) Function Overloaded
void BinSrchTree::inOrder()
{
    if (T==NULL)
    {
        cout << "Tree empty.\n";
    }
    else
    {
        inOrder(T);
    }
}

//Outputs the tree in PostOrder. Function is overloaded. 
void BinSrchTree::postOrder(node *p)
{
    int tagdata;
    Stack<node*> a(30);
    Stack<int> tag(30);
    a.push(p);
    tag.push(1);
    while(!a.empty() && !tag.empty())
    {
        p = a.pop();
        tagdata = tag.pop();
        switch(tagdata)
        {
            case 1:
                a.push(p);
                tag.push(2);
                if(p->lson!=NULL)
                {
                    a.push(p->lson);
                    tag.push(1);
                }
                break;
            case 2:
                a.push(p);
                tag.push(3);
                if(p->rson!=NULL)
                {
                    a.push(p->rson);
                    tag.push(1);
                }
                break;
            case 3:
                cout << p->data << " ";
                break;
            default:
            cerr << "There is a nasty error here\n";
            break;
        }
    }
}

//Outputs the tree in PostOrder. Function is overloaded. 
void BinSrchTree::postOrder()
{
    if (T==NULL)
    {
        cout << "Tree empty.\n";
    }
    else
    {
        postOrder(T);
    }
}

////Outputs the tree in levelorder. Function is overloaded. 
void BinSrchTree::levelOrder(node *p)
{
    Queue<node*>a(256);
    if(p!=NULL)
    {
        a.clearQ();
        a.addQ(p);
    }
    while(!a.emptyQ())
    {
        p = a.delQ();
        cout << p->data << " ";

        if(p->lson!=NULL)
        {
            a.addQ(p->lson);
        }
        if(p->rson!=NULL)
        {
            a.addQ(p->rson);
        }
    }
}

//Outputs the tree in levelOrder. Function is overloaded. 
void BinSrchTree::levelOrder()
{
    if (T==NULL)
    {
        cout << "Tree empty.\n";
    }
    else
    {
        levelOrder(T);
    }
}

//This is a quick and dirty solution to clearing the tree. 
//by Clearing the two link feilds you render the rest of the tree blank. 
void BinSrchTree::clearTree(node *p)
{
    if(p!=NULL)
    {
    clearTree(p->lson);
    clearTree(p->rson);
    delete p;
    }
    p = NULL;
}

//Checks if the tree is empty then runs it's overloaded function.
void BinSrchTree::clearTree()
{
    if (T==NULL)
    {
        cout << "Tree empty.\n";
    }
    else
    {
        clearTree(T);
    }
    T = NULL;
}

//This function was created by Ryan Rabello for the Lists assignment. It was edited to include this assignment's functions.
char BinSrchTree::miniMenu(bool isMiniMenu)
//A menu that prints options, and takes the user's choice
{
    char choice;
    if (isMiniMenu){
    cout << endl << "What would you like to do?" << endl;
    cout << endl;
    cout << "\t1) Build a binary search tree." << endl;
    cout << "\t2) Traverse the tree using InOrder." << endl;
    cout << "\t3) Traverse the tree using LevelOrder." << endl;
    cout << "\t4) Traverse the tree using PostOrder." << endl;
    cout << "\t5) Delete a specific node." << endl;
    cout << "\t6) Clear the tree." << endl;
    cout << "\t7) Run the case specified in the homework." << endl;
    cout << endl << "\t0) Quit." << endl;
    }
    //if they have already seen the menu it prints the mini menue. As follows. 
    else
    {
        cout << "\n\n1)Build\t\t2)InOrder\t3)LevelOrder\t4)PostOrder\t5)Delete\t\t6)Clear\t\t7)HWCase\n";
    }
    cout << endl;
    cout << ">>>";
    //choice = getchar();
    cin >> choice;
    cout << endl;
    return choice;
}


//This function was created by Ryan Rabello for the Lists assignment. It was edited to include this assignment's functions.
//This is a nice welcome menu, along with the case statements for handling each of the potential menu choices
int BinSrchTree::menu()
{
    //initialize some menu options
    char option = NULL;
    bool printMenu = true;
    //A cool Splash screen
    cout <<"            ,@@@@@@@,\n"
    <<"    ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
    <<" ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
   <<",%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
   <<"%&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
   <<"%&&%/ %&%%&&@@\\ \V /@@' `88\\8 `/88'\n"
   <<"`&%\\ ` /%&'    |.|        \\ '|8'\n"
   <<"    |o|        | |         | |\n"
   <<"    |.|        | |         | |\n"
   <<" _\\/ ._\\/____ /__ \\_//__\\\\/___\\_//__/_*/ ____\n"
    <<"( \\/\\/ )( ___)(  )  / __)(  _  )(  \\/  )( ___)\n"
    <<" )    (  )__)  )(__( (__  )(_)(  )    (  )__) \n"
    <<"(__/\\__)(____)(____)\\___)(_____)(_/\\/\\_)(____)\n";
    //start the main menu loop breaks when option== 0;
    while(option!='0')
    {
        option = miniMenu(printMenu);
        switch(option)
        {
            case '0': cout << "  _____             ____\n"
                << " / ___/__  ___  ___/ / /  __ _____ \n"
                << "/ (_ / _ \\/ _ \\/ _  / _ \\/ // / -_)\n"
                << "\\___/\\___/\\___/\\_,_/_.__/\\_, /\\__/ \n"
                << "                        /___/      \n";
            break;
            case '1':
                int n;
                cout << "Enter how many integers you would like to enter into the tree: ";
                cin >> n;
                for(int i=1; i<=n; i++)
                    {
                        fillNode();
                        insertNode();
                    }
                printMenu = false;
                break;
            case '2': inOrder(); printMenu = false; break;
            case '3': levelOrder(); printMenu = false; break;
            case '4': postOrder(); printMenu = false; break;
            case '5':
                int del;
                cout << "Please enter the data value of the node you would like to delete: ";
                cin >> del;
                deleteNode(del);
                printMenu = false;
                break;
            case '6': clearTree(); printMenu = false; break;
            case '7':
                cout << "Clearing existing trees and executing the homework case." << endl;
                clearTree();
                int p;
                cout << "Enter how many integers you would like to enter into the tree: ";
                cin >> p;
                for(int i=1; i<=p; i++)
                    {
                        fillNode();
                        insertNode();
                    }
                inOrder();
                cout << endl;
                postOrder();
                cout << endl;
                levelOrder();
                cout << endl;
                int m;
                cout << "Enter how many integers you would like to enter into the subtree: ";
                cin >> m;
                if (m<p)
                {
                    Stack<int> mNodes(m);
                    for(int i=1; i<=m; i++)
                    {
                        fillNode();
                        mNodes.push(ptr->data);
                        insertNode();
                    }
                    cout << "Nodes inserted. Displaying inOrder." << endl;
                    inOrder();
                    cout << endl;
                    cout << "Deleting inserted nodes." << endl;
                    while(!mNodes.empty())
                    {
                        deleteNode(mNodes.pop());
                    }
                }
                else
                    {
                    cout << "The subbranch of the tree must be smaller than the original branch." << endl;
                    cout << "Skipping insertion and deletion." << endl;
                    }
                cout << "Displaying current tree." << endl;
                inOrder();
                cout << endl;
                postOrder();
                cout << endl;
                levelOrder();
                cout << endl;
                cout << "Clearing tree." << endl;
                clearTree();
                cout << "Displaying cleared tree." << endl;
                inOrder();
                cout << endl;
                postOrder();
                cout << endl;
                levelOrder();
                cout << endl;
                break;
            default : cerr << "\nERROR: '" << option << "' is not a valid menu option.\n\n"; printMenu = true; break;
        }
    }
    return(0);
}

int main()
{
    //Initialize tree.
    BinSrchTree a;
    //run menu loop
    a.menu();

}


