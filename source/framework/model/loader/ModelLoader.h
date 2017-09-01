//
// Created by cauchywei on 2017/8/20.
//

#ifndef SHIBA_MODELLOADER_H
#define SHIBA_MODELLOADER_H

#define TINYOBJLOADER_IMPLEMENTATION

#include "../../../thirdpart/tiny_obj_loader.h"
#include "../Model.h"
#include <fstream>
#include <iostream>
#include <memory>

namespace shiba {
    namespace framework {
        namespace model {

            void extractVertex2Vec3(size_t offset, Vector3 &vertex, int verIndex,
                                    std::vector<tinyobj::index_t> &meshIndices,
                                    std::vector<tinyobj::real_t> &vertices);

            Model *load(char *name, char *path) {
                tinyobj::attrib_t attrib;
                std::vector<tinyobj::shape_t> shapes;
                std::vector<tinyobj::material_t> materials;

                std::string err;
                bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
                if (!err.empty()) { // `err` may contain warning message.
                    std::cerr << err << std::endl;
                    return nullptr;
                }
                if (!ret) {
                    return nullptr;
                }


                Model *model = new Model(name);
                auto vertexCount = attrib.vertices.size() / 3;
                for (int i = 0; i < vertexCount; ++i) {
                    model->vertices.push_back({attrib.vertices[i * 3],
                                               attrib.vertices[i * 3 + 1],
                                               attrib.vertices[i * 3 + 2]});
                }
//                bool hasNormals = !attrib.normals.empty();
                for (size_t s = 0; s < shapes.size(); s++) {
                    // Loop over faces(polygon)
                    size_t index_offset = 0;
                    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                        int fv = shapes[s].mesh.num_face_vertices[f];

                        Vector3 normal(0, 0, 0);
                        Vector3 current, next;
                        std::vector<tinyobj::index_t> &meshIndices = shapes[s].mesh.indices;
                        std::vector<tinyobj::real_t> &vertices = attrib.vertices;
                        for (int verIndex = 0; verIndex < fv; ++verIndex) {
                            extractVertex2Vec3(index_offset, current, verIndex, meshIndices, vertices);

                            if (verIndex == fv - 1) {
                                extractVertex2Vec3(index_offset, next, 0, meshIndices, vertices);
                            } else {
                                extractVertex2Vec3(index_offset, next, verIndex + 1, meshIndices, vertices);
                            }

                            normal.x += current.y * next.y - current.z * current.z;
                            normal.y += current.z * next.z - current.x * current.x;
                            normal.z += current.x * next.x - current.y * current.y;
                        }
                        model->normals.push_back(normal);

                        // Loop over vertices in the face.
                        for (size_t v = 0; v < fv; v++) {
                            // access to vertex
                            tinyobj::index_t idx = meshIndices[index_offset + v];
                            tinyobj::real_t vx = vertices[3 * idx.vertex_index + 0];
                            tinyobj::real_t vy = vertices[3 * idx.vertex_index + 1];
                            tinyobj::real_t vz = vertices[3 * idx.vertex_index + 2];

                            tinyobj::real_t nx, ny, nz, tx, ty;

//                            tx = attrib.texcoords[2 * idx.texcoord_index + 0];
//                            ty = attrib.texcoords[2 * idx.texcoord_index + 1];

//                            model->vertices.push_back({vx, vy, vz});
                            model->textures.push_back({tx, ty, 0});
                            model->indices.push_back((uint32_t) idx.vertex_index);
                        }
                        index_offset += fv;

                        // per-face material
//                        shapes[s].mesh.material_ids[f];
                    }
                }

                return model;
            }

            void extractVertex2Vec3(size_t offset, Vector3 &vertex, int verIndex,
                                    std::vector<tinyobj::index_t> &meshIndices,
                                    std::vector<tinyobj::real_t> &vertices) {
                tinyobj::index_t idx = meshIndices[offset + verIndex];
                vertex.x = vertices[3 * idx.vertex_index + 0];
                vertex.y = vertices[3 * idx.vertex_index + 1];
                vertex.z = vertices[3 * idx.vertex_index + 2];
            }
        }
    }
}

#endif //SHIBA_MODELLOADER_H
