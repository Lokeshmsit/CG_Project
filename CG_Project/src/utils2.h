#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/constants.hpp>
#include <glm/gtx/quaternion.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct MeshVAO;
// Struct for representing a virtual 3D trackball that can be used for
// object or camera rotation
struct Trackball {

  double radius;
  glm::vec2 center;
  bool tracking;
  glm::vec3 vStart;
  glm::quat qStart;
  glm::quat qCurrent;

  Trackball();
};

// Struct for Wavefront (OBJ) triangle meshes that are indexed and has
// per-vertex normals
struct OBJMesh {
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<std::uint32_t> indices;
};

// Struct for Wavefront (OBJ) triangle meshes that are indexed and has
// per-vertex normals and UV texture coordinates
struct OBJMeshUV {
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> texcoords;
  std::vector<std::uint32_t> indices;
};

// Helper functions
namespace {
glm::vec3 mapMousePointToUnitSphere(glm::vec2 point, double radius,
                                    glm::vec2 center);

void computeNormals(const std::vector<glm::vec3> &vertices,
                    const std::vector<std::uint32_t> &indices,
                    std::vector<glm::vec3> *normals);
} // namespace

// Start trackball tracking
void trackballStartTracking(Trackball &trackball, glm::vec2 point);

// Stop trackball tracking
void trackballStopTracking(Trackball &trackball);

// Rotate trackball from, e.g., mouse movement
void trackballMove(Trackball &trackball, glm::vec2 point);

// Get trackball orientation in matrix form
glm::mat4 trackballGetRotationMatrix(Trackball &trackball);

// Read an OBJMesh from an .obj file
bool objMeshLoad(OBJMesh &mesh, const std::string &filename);

struct uvec3Less;

// Read an OBJMeshUV from an .obj file. This function can read texture
// coordinates and/or normals, in addition to vertex positions.
bool objMeshUVLoad(OBJMeshUV &mesh, const std::string &filename);

void loadMesh(const std::string &filename, OBJMesh *mesh);

void loadUVMesh(const std::string &filename, OBJMeshUV *mesh);

void createMeshVAO(const OBJMeshUV &mesh, MeshVAO *meshVAO);
