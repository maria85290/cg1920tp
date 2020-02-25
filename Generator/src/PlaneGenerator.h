#ifndef CG_TP_PLANEGENERATOR_H
#define CG_TP_PLANEGENERATOR_H

#include <list>

#include <Common/vectors.h>
#include <string>
#include "AbstractGenerator.h"

class PlaneGenerator : public AbstractGenerator {
 private:
  int plane_ = 0;
  int width_ = 0;
  int height_ = 0;

  static const int kPlaneXY = 0;
  static const int kPlaneXZ = 1;
  static const int kPlaneYZ = 2;

 public:
  ~PlaneGenerator() override = default;

  bool ParseArguments(int argc, char *argv[]) override;

  void GenerateVertices() override;
};

#endif //CG_TP_PLANEGENERATOR_H
