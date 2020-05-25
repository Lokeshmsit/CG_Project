#ifndef SKYDOME_H
#define SKYDOME_H

#include <Model.h>

class SkyDome : public Model {
public:
  SkyDome();

  void load(const std::string &modelPath);
  void Render(Context &ctx);
};

#endif // SKYDOME_H
