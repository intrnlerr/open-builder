#pragma once

#include "../types.h"
#include <string>

#include "world_constants.h"
#include <glad/glad.h>
#include <unordered_map>
#include <vector>

enum class VoxelMeshStyle : u8 {
    Block = 0,
    Cross = 1,
    None = 2,

    Error,
};

enum class VoxelType : u8 {
    Solid = 0,
    Fluid = 1,
    Flora = 2,
    Gas = 3,

    Error,
};

/**
 * @brief Very common voxel types
 * The purpose of this is to give quick access to common voxel from
 * client/server engine
 */
enum class CommonVoxel : block_t {
    Air = 0,
    Stone,
    Sand,
    Water,

    Count
};

struct VoxelData {
    block_t id = 0;
    std::string name;
    std::string topTexture;
    std::string sideTexture;
    std::string bottomTexture;

    // Client only
    GLuint topTextureId = 0;
    GLuint sideTextureId = 0;
    GLuint bottomTextureId = 0;

    VoxelMeshStyle meshStyle = VoxelMeshStyle::Block;
    VoxelType type = VoxelType::Solid;

    bool isCollidable = true;
};

class VoxelDataManager {
  public:
    VoxelDataManager();
    void initCommonVoxelTypes();

    block_t addVoxelData(const VoxelData& voxel);

    const VoxelData& getVoxelData(block_t id) const;
    const VoxelData& getVoxelData(const std::string& name) const;

    block_t getVoxelId(CommonVoxel commonVoxel) const;
    block_t getVoxelId(const std::string& name) const;

    const std::vector<VoxelData>& getVoxelData() const;

  private:
    std::vector<VoxelData> m_voxels;
    std::vector<block_t> m_commonVoxels;
    std::unordered_map<std::string, block_t> m_voxelMap;
};