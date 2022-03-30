#include "Page.h"
#include "LRU.h"
#include <iostream>
#include <vector>
#include<conio.h>


using namespace std;

typedef vector<Page> LISTPAGE_LRU;
typedef vector<int> USEPAGE_LRU;
LISTPAGE_LRU pages_LRU;
USEPAGE_LRU usePageNumList_LRU;

void LRU::init()
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
        usePageNumList_LRU.push_back(da);
        ofs_LRU << da << " ";
    }
    ofs_LRU << "\n页面置换过程如下：\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages_LRU.push_back(*p);
    }
}

void LRU::reSet(int cur)
{
    pages_LRU[cur].setCount(0);
}

void LRU::timeRefresh()
{
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        pages_LRU[i].inc();
    }
}

void LRU::display()
{
    cout << "Now Pages: ";
    for (int i = 0; i < pages_LRU.size(); i++)
    {
        cout << pages_LRU[i].getId() << " ";
        ofs_LRU << pages_LRU[i].getId() << " ";

    }
    ofs_LRU << "\n";
    cout << endl;
}

bool LRU::search(int pageId)
{
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        if (pages_LRU[i].getId() == pageId)
        {
            timeRefresh();
            reSet(i);
            return true;
        }
    }
    return false;
}

void LRU::replace(int pageId)
{
    int max = 0, perCount, outPageId = -1, cur = 0;
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        perCount = pages_LRU[i].getCount();
        if (max < perCount)
        {
            max = perCount;
            cur = i;
        }
    }
    outPageId = pages_LRU[cur].getId();
    timeRefresh();
    reSet(cur);
    pages_LRU[cur].setId(pageId);

    cout << "ID: " << id << "being put into memory, ID: " << outPageId << "is replaced" << endl;
}

void LRU::running()
{

    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_LRU[i];

        int key = getch();
        if(key==13)
        {

            if (search(pageId))
            {
                cout << "ID: " << inPageId << "cannot be replaced!" << endl;
            }
            else if (count < PRO_MEMORY)
            {
                pages_LRU[count].setId(pageId);
                cout << "ID: " << inPageId << "being put into memory" << endl;
                timeRefresh();
                reSet(count);
                count++;
            }
            else
            {
                replace(pageId);

                lackTime++;
            }
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
