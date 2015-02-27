/*****************************************************************************
 Program file name: QueueManipulator			  OS: Windows 				Assignment: 6
 Programmer: Matthew Fennell and Ethan Beaver (Pair programmed with Dr. Klein's permission)
 Ryan Rabello (MiniMenu function recycled)
 Class: CPTR 142	        Date: 2/12/15
 Compiler:

 Assistance/references: Lecture 14, 15
 Description: A menu based application that does various queue related tasks.
 Inputs:
 Outputs:

 Special Comments:
    The queue is reset at the beginning of each function call to prevent errors.
~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~

 Assignment Requirements: ___/3.0

 Code Format/Cosmetics: ___/3.0

 Header & Code Comments: ___/2.0

 Output Format/Cosmetics: ___/2.0
 ***Does Not Compile***: ___ (-10.0)
 ***Late Work Deduction***: ___ (-0.5/day)
 Total Grade: ___/10.0

*****************************************************************************/
#include <iostream>
#include <cstdlib>

using namespace std;

/////////////////////////////
//Class Declaration Section//
/////////////////////////////

template <class T>

class Queue
{
private:
    T *Q;
    int size;
    int front, rear;
public:
    Queue();
    Queue(int);
    bool emptyQ();
    bool fullQ();
    void addQ(T);
    T delQ();
    int lengthQ();
    void writeQ();
    void clearQ();
    void growShrinkQ();
    void wrapQ();
    void growTilOverflowQ();
    void shrinkTilUnderflowQ();
    void output1Q();
    void output5Q();
    void outputFullQ();
    void outputClearedQ();

};

////////////////////////////////
//Class Implementation Section//
////////////////////////////////


//Constructor Function:
//Defines the Queue object, which is an array of default size 15, with the front and rear pointers set to position 0
template <class T>
Queue <T>::Queue()
{
    size=15;
    Q = new T[size];
    front=rear=0;
}

//Overloaded Constructor Function:
//Allows an object of type Queue to be defined with a specific array size, read in as the setSize
template <class T>
Queue <T>::Queue(int setSize)
{
    size=setSize;
    Q = new T[size];
    front=rear=0;
}

//Empty Check Function:
//Checks to see if a queue is empty, a case where the front and rear pointers would be equal
template <class T>
bool Queue<T>::emptyQ()
{
    if(front==rear)
        return true;
    else
        return false;
}

//Full Check Function:
//Checks to see if the queue is full, by checking the positions of the front and rear pointer.
//If the rear pointer is one position behind the front, the queue is full.
//Wraparound is handled by making the addition operation modular.
template <class T>
bool Queue<T>::fullQ()
{
    if(front==(rear+1)%size)
        return true;
    else
        return false;
}

//Add Queue Function:
//First, checks for a full queue. If there is room in the queue, the rear position is moved to the next available spot.
//The element is added, and a message is displayed.
template <class T>
void Queue<T>::addQ(T data)
{
    if(fullQ())
    {
        cout << "\nQueue Overflow\n\n";
        exit;
    }
    else
    {
        rear = (rear+1)%size;
        Q[rear] = data;
        //cout << "Element Added\n";
    }
}

//Delete Queue Function:
//First, checks for an empty queue. If there are indeed elements in the queue, the front pointed element is returned,
//and the front pointer is moved one spot forward. This effectively removes the element, as it is overwritten when the rear loops back around to it.
template <class T>
T Queue<T>::delQ()
{
    if(emptyQ())
    {
        cout << "\nQueue Underflow\n\n";
        return Q[front];
    }
    else
    {
        front = (front +1)%size;
        //cout << "Element Deleted\n";
        return Q[front];
    }
}

//Length Queue Function:
//Checks for the number of active elements in the queue, by measuring the distance between the front and the rear.
//If the rear has a greater value than the front, a simple rear-front operation is performed, and the difference is output as the length.
//If the front has a greater value than the rear, rear - front is performed, but the size of the queue is added to give an accurate, positive valued length.
template <class T>
int Queue<T>::lengthQ()
{
    if (emptyQ())
    {
        return 0;
    }
    else if(front<rear)
    {
        return rear-front;
    }
    else
    {
        return rear-front+size;
    }
}

//Write Queue Function
//This function outputs the elements in the queue, along with null characters for empty elements, in their corresponding positions.
//If the queue is not empty, the process begins. If the rear pointer is greater than the front pointer, a third pointer works from
//the 0th element of the array to the final element. Each element is checked. If it falls inside the front <-> rear range, the value of the array is returned.
//Otherwise, a null character is printed.
//If the front pointer is greater than the rear pointer, the same 0 to final loop is run, but here, elements that are either less than the rear,
//or greater than the front are returned. Else, the null character is returned.

template <class T>
void Queue<T>::writeQ()
{
    char nullchar = 237;
    if(emptyQ())
    {
        cout << "\nQueue Empty\n";
    }
    else if(rear>front)
    {
        for(int i=0; i<size;i++)
        {
            if((i<=rear)&&(i>front))
                cout << Q[i%size] << "  ";
            else
                cout << nullchar << "  ";
        }
    }
    else if(rear<front)
    {
        for(int i=0; i<size;i++)
        {
            if((i<=rear)||(i>front))
                cout << Q[i%size] << "  ";
            else
                cout << nullchar << "  ";
        }
    }
}


//Clear Queue Function:
//A simple clearing function. The front is set to be equal to the rear, so all the values will be overwritten as new elements are added.
template <class T>
void Queue <T>::clearQ()
{
    front=rear=0;
}

//Grow Shrink Queue Function:
//A function for testing growing and shrinking of the queue.
//This menu based function allows you to add elements, delete elements, and print the length until you wish to quit.
//The function is just a simple while loop, fetching input, and running the add and del functions.
template <class T>
void Queue<T>::growShrinkQ()
{
    int option;
    cout << "This is a function to grow and shrink the queue.\n";
    cout << endl << "What would you like to do?" << endl;
    cout << endl;
    cout << "\t1) Grow your Queue." << endl;
    cout << "\t2) Shrink your Queue." << endl;
    cout << "\t3) Output Queue length." << endl;
    cout << endl;
    cout << "\t0) Quit" << endl;
    cout << "Enter your choice: ";
    cin >> option;
    while(option!=0)
    {
        switch(option)
        {
            case 1:
                addQ('A');
                break;
            case 2:
                delQ();
                break;
            case 3:
                cout << lengthQ() << endl; break;
            default:
                cerr << "Please enter a valid choice." << endl; cout << endl << "What would you like to do?" << endl;
                cout << "\t1) Grow your Queue." << endl;
                cout << "\t2) Shrink your Queue." << endl;
                cout << "\t3) Output Queue length." << endl;
                cout << endl;
                cout << "\t0) Quit" << endl; break;
        }
        cout << "Enter your choice: ";
        cin >> option;
    }
}

//Wrap Queue Function:
//A simple function that is used to test to make sure wraparound error is handled correctly.
//The queue is filled almost to the brim, emptied, and then filled a bit more, causing wraparound.
//The front and rear pointers are then displayed to show that wraparound has indeed occurred and has been handled without error.
template <class T>
void Queue<T>::wrapQ()
{
    for(int i=1;i<=8;i++)
    addQ('A');
    for(int i=1;i<=3;i++)
    delQ();
    for(int i=1;i<=3;i++)
    addQ('A');
    cout << "The front pointer is " << front << endl;
    cout << "The rear pointer is " << rear << endl;
}

//Grow Until Overflow Function:
//This function checks for a full queue, clears it if it is so, and then adds elements until an overflow message is generated.
template <class T>
void Queue <T>::growTilOverflowQ()
{
    if(fullQ())
    {
        while(!emptyQ())
        {
            delQ();
        }
    }
cout << "Queue length is " << lengthQ() << " . Adding until overflow" << endl;
while(!fullQ())
    addQ('A');
addQ('A');
}

//Shrink Until Underflow Function:
//This function checks for a empty queue, fills it if it is so, and then deletes elements until an underflow message is generated.
template <class T>
void Queue <T>::shrinkTilUnderflowQ()
{
    if(emptyQ())
    {
        while(!fullQ())
        {
            addQ('A');
        }
    }
cout << "Queue length is " << lengthQ() << " . Deleting until underflow" << endl;
while(!emptyQ())
    delQ();
delQ();
}

//Output Queue Length 1 Function:
//Shows that a queue of length one is handled correctly by creating one, and displaying a message verifying the length.
template <class T>
void Queue <T>::output1Q()
{
    addQ('A');

    if(lengthQ()==1)
    {
        cout << "\nThere is " << lengthQ() << " element in the queue. Congratulations." << endl;
    }
    else
    {
        cout << "\nThere is NOT one element in the queue. Rather, there are " << lengthQ() << " elements." << endl;
    }
}

//Output Queue Length 5 Function:
//Shows that a queue of length five is handled correctly by creating one, and displaying a message verifying the length.
template <class T>
void Queue <T>::output5Q()
{
    for(int i=1; i<=5; i++)
    {
         addQ('A');
    }

    if(lengthQ()==5)
    {
        cout << "\nThere are " << lengthQ() << " elements in the queue. Congratulations." << endl;
    }
    else
    {
        cout << "\nThere are NOT five elements in the queue. Rather, there are " << lengthQ() << " elements." << endl;
    }
}

//Full Output Check:
//Shows that a full queue (size - 1) can be handled correctly by filling a queue, and then displaying a message.
template <class T>
void Queue <T>::outputFullQ()
{
    while(!fullQ())
    {
        addQ('A');
    }
    if(fullQ())
    {
        cout << "\nQueue is full with "<< lengthQ() << " elements." << endl;
    }
    else
    {
        cout << "\nQueue is NOT full with " << lengthQ() << " elements." << endl;
    }
}

//Output Cleared Check:
//Shows that clearing queues is handled correctly by showing the original length, clearing the queue, and then showing the new, cleared length.
template <class T>
void Queue <T>::outputClearedQ()
{

        cout << "\nQueue contains "<< lengthQ() << " elements. Clearing Queue." << endl;
        clearQ();
        cout << "\nQueue length is now: " << lengthQ() << ". That is all." << endl;


}

