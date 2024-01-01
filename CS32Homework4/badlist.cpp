    void removeBad(list<Movie*>& li)
    { // maybe wrong should check
        for (list<Movie*>::iterator p = li.begin(); p != li.end(); p++) {
            if ((*p)->rating() < 50) {
                delete (*p);
                list<Movie*>::iterator q = li.erase(p);
                p = q;
            }
        }
    }
