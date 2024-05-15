#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FileDatabase {
protected:
    string filename;
    string extension;
    int size;
    string creationDate;
    string attributes;

public:
    FileDatabase(string name, string ext, int sz, string date, string attrs)
        : filename(name), extension(ext), size(sz), creationDate(date), attributes(attrs) {}

    virtual ~FileDatabase() {}

    virtual void displayInfo() const {
        cout << "Filename: " << filename << endl;
        cout << "Extension: " << extension << endl;
        cout << "Size: " << size << " bytes" << endl;
        cout << "Creation Date: " << creationDate << endl;
        cout << "Attributes: " << attributes << endl;
    }
};

class SpecializedFileDatabase : public FileDatabase {
private:
    string fileType;

public:
    SpecializedFileDatabase(string name, string ext, int sz, string date, string attrs, string type)
        : FileDatabase(name, ext, sz, date, attrs), fileType(type) {}

    void displayInfo() const override {
        FileDatabase::displayInfo();
        cout << "File Type: " << fileType << endl;
    }
};

class DatabaseManager {
private:
    vector<FileDatabase*> database;

public:
    ~DatabaseManager() {
        for (auto& file : database) {
            delete file;
        }
    }

    void addFile(FileDatabase* file) {
        database.push_back(file);
    }

    void removeFile(int index) {
        if (index >= 0 && index < database.size()) {
            delete database[index];
            database.erase(database.begin() + index);
        }
    }

    void displayAll() const {
        for (const auto& file : database) {
            file->displayInfo();
            cout << "------------------------" << endl;
        }
    }
};

int main() {
    DatabaseManager manager;

    FileDatabase* file1 = new SpecializedFileDatabase("document", "docx", 1024, "2024-05-15", "read-only", "document");
    FileDatabase* file2 = new SpecializedFileDatabase("image", "jpg", 2048, "2024-05-16", "hidden", "image");

    manager.addFile(file1);
    manager.addFile(file2);

    manager.displayAll();

    manager.removeFile(0);

    manager.displayAll();

    return 0;
}
