#include <iostream>
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"

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
    LRU *lru = new LRU();
    OPT *opt = new OPT();
    cin >> select;
    switch (select) {
        case 1:
            cout << "-----FIFO-----" << endl;

            fifo->init();
            fifo->running();
            break;

        case 2:
            cout << "-----LRU-----" << endl;

            lru->init();
            lru->running();
            break;

        case 3:
            cout << "-----OPT-----" << endl;

            opt->init();
            opt->running();
            break;

        default:
            cout <<"Error!" << endl;
            break;
    }

    return 0;
}

