#include "OPT.h"
#include "LRU.h"
#include "Page.h"
#include <iostream>
#include <vector>
#include<conio.h>

using namespace std;

typedef vector<Page> LISTPAGE_OPT;
typedef vector<int> USEPAGE_OPT;
LISTPAGE_OPT pages_OPT;
USEPAGE_OPT usePageNumList_OPT;


void LRU::init()
{
    count = 0;
    cout << "Please Enter the Page-frames N: ";
    cin >> PRO_MEMORY;

    cout << "Please Enter the Pages M: ";
    cin >> length;

    cout << ""Please Enter the List: ";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList_LRU.push_back(da);
    }

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages_OPT.push_back(*p);
    }
}

void OPT::display()
{
    cout << "Now Pages: ";
    for (int i = 0; i < pages_OPT.size(); i++)
    {
        cout << pages_OPT[i].getId() << " ";
    }
    cout << endl;
}

bool OPT::search(int id)
{
    for (int i = 0; i < PRO_MEMORY; ++i)
    {
        if (pages_OPT[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}

void OPT::replace(int pageId, int currentPoint)
{
    int max = 0, perCount, outPageId = -1, cur = 0;
    int search_count[PRO_MEMORY];

    for (int i = 0; i < PRO_MEMORY; i++)
    {
        for (int j = currentPoint + 1; j < length; j++)
        {
            if (pages_OPT[i].getId() == usePageNumList_OPT[j])
            {
                search_count[i] = j;
                break;
            }
        }
        if (search_count[i] == 0)
        {
            search_count[i] = length;
        }
    }

    for (int k = 0; k < PRO_MEMORY; ++k)
    {
        perCount = search_count[k];
        if (max < perCount)
        {
            max = perCount;
            cur = k;
        }
    }

    outPageId = pages_OPT[cur].getId();
    pages_OPT[cur].setId(pageId);

     cout << "ID: " << pageId << "being put into memory, ID: " << outPageId << "is replaced" << endl;
}

void OPT::running()
{
    int currentPoint = 0;
    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_OPT[i];

        int key = getch();
        if(key==13)
        {

            if (search(pageId))
            {
                cout << "ID: " << pageId << "cannot be replaced!" << endl;
            }
            else if (count < PRO_MEMORY)
            {
                pages_OPT[count].setId(pageId);
                cout << "ID: " << pageId << "being put into memory" << endl;
                count++;
            }
            else
            {
                replace(pageId, currentPoint);
                lackTime++;
            }
            currentPoint++;
            display();
        }
        else
        {
            i--;
            cout<<"Please use Enter !"<<endl;
        }
    }

    cout << "Page-faults: " << lackTime << endl;
}
