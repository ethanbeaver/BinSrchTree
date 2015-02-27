#include <iostream>
#include "Queues.cpp"
#include "Stacks.cpp"

using namespace std;

class node
{
public:
    int data;
    node *lson, *rson;
};

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
    void preOrder(node*);
    void preOrder();
    void inOrder(node*);
    void inOrder();
    void postOrder(node*);
    void postOrder();
    void levelOrder(node*);
    void levelOrder();
    void clearTree(node*);
    void clearTree();
};

BinSrchTree::BinSrchTree()
{
    T = NULL;
}

void BinSrchTree::fillNode()
{
    int value;
    ptr = new node;
    cout << "Enter a value: ";
    cin >> value;
    ptr->data = value;
    ptr->lson = ptr->rson = NULL;
}

void BinSrchTree::fillNode(int data)
{
    int value;
    ptr = new node;
    ptr->data = data;
    ptr->lson = ptr->rson = NULL;
}

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
            if(p1->lson = p2)
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
                    p1->rson = p2->rson;
                }
                else
                {
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

void BinSrchTree::preOrder(node *p)
{
    if (p!=NULL)
    {
        cout << p->data << " " ;
        inOrder(p->lson);
        inOrder(p->rson);
    }
}

void BinSrchTree::preOrder()
{
    if (T==NULL)
    {
        cout << "Tree empty.\n";
    }
    else
    {
        preOrder(T);
    }
}

void BinSrchTree::inOrder(node *p)
{
    if (p!=NULL)
    {
        inOrder(p->lson);
        cout << p->data << " " ;
        inOrder(p->rson);
    }
}

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

void BinSrchTree::postOrder(node *p)
{
    int tagdata;
    Stack<node*> a;
    Stack<int> tag;
    a.push(p);
    tag.push(1);
    while(a.top!=NULL)
    {
        p = a.pop();
        tagdata = tag.pop();
        switch(tagdata)
        {
            case 1:
                a.push(p);
                tag.push(2);
                if(p->lson==NULL)
                a.push(p->lson);
                tag.push(1);
                break;
            case 2:
                a.push(p);
                tag.push(3);
                if(p->rson==NULL);
                a.push(p->rson);
                tag.push(1);
                break;
            case 3:
                cout << p->data;
                break;
            default:
            cerr << "There is a nasty error here\n";
            break;
        }
    }
}

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
        cout << a.delQ() << " ";
        cout << p->data << " ";
        if(p->lson!=NULL)
        {
            a.addQ(p->lson);
        }
        if(p->rson!=NULL)
        {
            a.addQ(p->rson);
        }
        break;
    }
}

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

int main()
{
    BinSrchTree a;
    a.inOrder();
    a.postOrder();
    int n;
    cout << "Enter how many integers you would like to enter into the tree: ";
    cin >> n;
    for(int i=1; i<=n; i++)
    {
        a.fillNode();
        a.insertNode();
    }
    a.inOrder();
    cout << endl;
    a.postOrder();
}
