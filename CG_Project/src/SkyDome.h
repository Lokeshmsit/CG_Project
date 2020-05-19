#ifndef SKYDOME_H
#define SKYDOME_H

#include <Model.h>

class SkyDome : public Model {
public:
  SkyDome();

  void load(const std::string &modelPath);
};

#endif // SKYDOME_H
