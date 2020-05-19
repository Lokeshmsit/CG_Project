#include "SkyDome.h"
#include <utils.h>
#include <utils2.h>

SkyDome::SkyDome() {}

void SkyDome::load(const std::string &modelPath) {
  loadUVMesh(modelPath, getMesh());
  createUVMeshVAO(*getMesh(), getMeshVBO());
  getMeshVBO()->texture = load2DTexture(modelDir() + "Skydome3D/Skydome.png");
}
