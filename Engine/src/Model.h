#ifndef CG_TP_ENGINE_SRC_MODEL_H_
#define CG_TP_ENGINE_SRC_MODEL_H_

#include <string>
#include <vector>

#include <Common/vectors.h>

using namespace std;

class Model {
private:
    vector<vec3> vertices_ = vector<vec3>();

protected:
    void AddVertex(double x, double y, double z) {
        vertices_.push_back({x, y, z});
    }

public:
    explicit Model(const string& filename);

    void Render();
};

#endif //CG_TP_ENGINE_SRC_MODEL_H_
