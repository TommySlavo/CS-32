void listAll(string path, const File* f)  // two-parameter overload
{
    if (f->files() == nullptr) {
        cout << path + f->name() << endl;
        return;
    }

    else if (f->files() != nullptr) {
        cout << path + f->name() << "/" << endl;
        for (int i = 0; i < f->files()->size(); i++) {
            listAll(path + f->name() + "/", f->files()->at(i));
        }
    }
}
