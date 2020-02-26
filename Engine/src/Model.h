#ifndef CG_TP_ENGINE_SRC_MODEL_H_
#define CG_TP_ENGINE_SRC_MODEL_H_

#include <string>

using namespace std;

class Model {
private:
    const string& file_;

public:
    explicit Model(const string& file) : file_(file) {}

    const string& GetFile() {
        return file_;
    }
};

#endif //CG_TP_ENGINE_SRC_MODEL_H_
