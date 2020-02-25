#include <string>
#include <utility>

using namespace std;

class Model {
    private:
        string file_;

    public:
        explicit Model(string file) { file_ = std::move(file); }
        string GetFile() { return file_; }
};