    void removeOdd(list<int>& li)
    {
        list<int>::iterator p = li.begin();
        while (p != li.end()) {
            if (*p % 2 == 1) {
                p = li.erase(p);
            }
            else {
                p++;
            }
        }
    }
