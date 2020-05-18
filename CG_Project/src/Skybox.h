#ifndef SKYBOX_H
#define SKYBOX_H

struct Context;

class Skybox {
public:
  Skybox();
  void Render(Context &ctx);
};

#endif // SKYBOX_H
