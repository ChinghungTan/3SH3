#include <iostream>
#include "LRU.h"
#include "OPT.h"
#include <string.h>

#include "Page.h"
#include "FIFO.h"
#include <vector>
#include <conio.h>



typedef vector<Page> LISTPAGE;
typedef vector<int> USEPAGE;
LISTPAGE pages;
USEPAGE usePageNumList;

void FIFO::init()
{
    count = 0;
    cout << "Please Enter the Page-frames N: ";
    cin >> PRO_MEMORY;

    cout << "Please Enter the Pages M: ";
    cin >> length;

    cout << "Please Enter the List: ";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList.push_back(da);
    }

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages.push_back(*p);
    }
}

void FIFO::display()
{

    cout << "Now Pages: ";
    for (int i = 0; i < pages.size(); i++)
    {
        cout << pages[i].getId() << " ";
    }
    cout << endl;
}

bool FIFO::search(int id)
{
    for (int i = 0; i < pages.size(); i++)
    {
        if (pages[i].getId() == id)
            return true;
    }
    return false;
}

void FIFO::replace(int id)
{
    int outPageId = -1;
    outPageId = pages[countOldPoint].getId();
    pages[countOldPoint].setId(id);

    cout << "ID: " << id << "being put into memory, ID: " << outPageId << "is replaced" << endl;
}

void FIFO::running()
{

    for (int i = 0; i < length; i++)
    {
        countOldPoint = countOldPoint % PRO_MEMORY;
        int inPageId = usePageNumList[i];
        int key = getch();
        if(key==13){

        if (search(inPageId))
        {
            cout << "ID: " << inPageId << "cannot be replaced!" << endl;
        }
        else if (count < PRO_MEMORY)
        {
            pages[count++].setId(inPageId);
            cout << "ID: " << inPageId << "being put into memory" << endl;
        }
        else
        {
            replace(inPageId);
            lackTime++;
            countOldPoint++;
        }
        display();
    }else{
        i--;
        cout<<"Please use Enter !"<<endl;
    }
    }
    cout << "Page-faults: " << lackTime << endl;
   
}

using namespace std;

int main() {

    int select;
    cout << "==============Page Replacement Algorithm==============" << endl;
    cout <<"    "<< "1--->FIFO" << "    ";
    cout <<"    "<< "2--->LRU" << "    ";
    cout <<"    "<< "3--->OPT" << "    ";
    cout<<endl;
    cout << "=============Please Select=============" << endl;

    FIFO *fifo = new FIFO();
    // LRU *lru = new LRU();
    // OPT *opt = new OPT();
    cin >> select;
    switch (select) {
        case 1:
            cout << "-----FIFO-----" << endl;

            fifo->init();
            fifo->running();
            break;

        case 2:
            cout << "-----LRU-----" << endl;

            // lru->init();
            // lru->running();
            break;

        case 3:
            cout << "-----OPT-----" << endl;

            // opt->init();
            // opt->running();
            break;

        default:
            cout <<"Error!" << endl;
            break;
    }

    return 0;
    
}

