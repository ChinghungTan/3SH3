#ifndef LRU_H
#define LRU_H

class LRU
{
public:
    void init();

    void reset(int cur);

    void timerefresh();

    bool search(int pageId);

    void replace(int pageId);

    void display();

    void running();

private:
    int PRO_MEMORY;
    int count;
    int lackTime;
    int length;
};

#endif // LRU_H
