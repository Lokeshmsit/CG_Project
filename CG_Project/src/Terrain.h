#pragma once

#include <Model.h>

class Terrain : public Model {

public:
  Terrain();

  void load(const std::string &modelPath) override;
  void Render(Context &ctx);
};
