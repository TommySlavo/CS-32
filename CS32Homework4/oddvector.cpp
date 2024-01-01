    void removeOdd(vector<int>& v)
    {
        vector<int>::iterator p = v.begin();
        while (p != v.end()) {
            if (*p % 2 == 1) {
                vector<int>::iterator q = v.erase(p);
                p = q;
            }
            else {
                p++;
            }
        }
    }
