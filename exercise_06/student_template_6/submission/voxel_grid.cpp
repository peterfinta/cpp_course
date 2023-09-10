#include "voxel_grid.h"

#include "transformations.h"
#include "operations.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>

VoxelGrid::VoxelGrid(const Shape& shape)
{
    //throw std::logic_error("task 6.4 b)");
    //(void) shape; // silence unused parameter warning
    AABB shapeBounds = shape.getBounds();
    bounds = shapeBounds;
    //if( !std::isfinite(shapeBounds.extents().x)
    // || !std::isfinite(shapeBounds.extents().y)
    // || !std::isfinite(shapeBounds.extents().z)) 
    //    throw std::logic_error(
    //        "Infinitly large bounding box can not be voxelized!");
    if(!std::isfinite(shapeBounds.extents().x))
      res_x = 1;
    else
      res_x = static_cast<unsigned>(shapeBounds.extents().x) * level_of_detail;

    if(!std::isfinite(shapeBounds.extents().y))
      res_y = 1;
    else
      res_y = static_cast<unsigned>(shapeBounds.extents().y) * level_of_detail;

    if(!std::isfinite(shapeBounds.extents().z))
      res_z = 1;
    else
      res_z = static_cast<unsigned>(shapeBounds.extents().z) * level_of_detail;

    if(res_x == 0) res_x = 1;
    if(res_y == 0) res_y = 1;
    if(res_z == 0) res_z = 1;
    unsigned sizeXYZ = res_x * res_y * res_z;
    unsigned sizeXY  = res_x * res_y;
    unsigned sizeX   = res_x;
    voxels.resize(sizeXYZ);
    for(unsigned i = 0; i < sizeXYZ; i++)
        voxels.at(i) = shape.isInside(voxelCenter((i % sizeXY) % sizeX,
                                                  (i % sizeXY) / sizeX,
                                                   i / sizeXY));
}

std::tuple<uint32_t, uint32_t, uint32_t> VoxelGrid::getResolution() const
{
    return {res_x, res_y, res_z};
}

VoxelSlice VoxelGrid::extractSlice(Axis axis, uint32_t slice) const
{
    //throw std::logic_error("task 6.4 d)");
    //(void) axis, (void) slice; // silence unused parameter warning
    unsigned sliceX, sliceY, sliceZ;
    switch(axis)
    {
        case Axis::X: sliceX = res_y, sliceY = res_z, sliceZ = res_x;
                      break;
        case Axis::Y: sliceX = res_z, sliceY = res_x, sliceZ = res_y;
                      break;
        case Axis::Z: sliceX = res_x, sliceY = res_y, sliceZ = res_z;
                      break;
    }
    VoxelSlice voxelSlice{sliceX, sliceY};
    for(unsigned y = 0; y < sliceY; y++)
      for(unsigned x = 0; x < sliceX; x++)
      {
        switch(axis)
        {
          case Axis::X: voxelSlice.data[y][x] = isSet(slice, x, y);
                        break;
          case Axis::Y: voxelSlice.data[y][x] = isSet(y, slice, x);
                        break;
          case Axis::Z: voxelSlice.data[y][x] = isSet(x, y, slice);
                        break;
        }
      }
    return voxelSlice;
}

Shape VoxelGrid::clone_impl() const
{
    return {std::make_shared<VoxelGrid>(*this)};
}

AABB VoxelGrid::getBounds_impl() const
{
    return bounds;
}

bool VoxelGrid::isInside_impl(const Point3D& p) const
{
    //throw std::logic_error("task 6.4 f)");
    //(void) p; // silence unused parameter warning
    Point3D resolution {float(res_x), float(res_y), float(res_z)};
    Point3D pOffseted = (p - bounds.min) * resolution / bounds.extents();
    if(!bounds.contains(p)) return false;
    return isSet(static_cast<size_t>(pOffseted.x),
                 static_cast<size_t>(pOffseted.y),
                 static_cast<size_t>(pOffseted.z));
}

bool VoxelGrid::isSet(uint32_t x, uint32_t y, uint32_t z) const
{
    // When running in debug mode, these will check whether the supplied indices are valid or "trap" to the debugger.
    // When no debugger is running, failing the assertion will terminate the program immediately.
    // When compiled in release mode, assert() does nothing.
    //assert(x < res_x);
    //assert(y < res_y);
    //assert(z < res_z);
    //throw std::logic_error("task 6.4 c)");
    unsigned sizeXY  = res_x * res_y;
    unsigned sizeX   = res_x;
    return(voxels.at(x + (sizeX * y) + (sizeXY * z)));
}

Point3D VoxelGrid::voxelCenter(uint32_t x, uint32_t y, uint32_t z) const
{
    //throw std::logic_error("task 6.4 a)");
    //(void) x, (void) y, (void) z; // silence unused parameter warning
    Point3D resolution {float(res_x), float(res_y), float(res_z)};
    Point3D stepSize = bounds.extents() / resolution;
    Point3D offset = bounds.min;
    return (Point3D{float(x) + 0.5f, float(y) + 0.5f, float(z) + 0.5f} 
             * stepSize) + offset;
}

std::ostream& operator<<(std::ostream& ostream, const VoxelSlice& slice)
{
    unsigned res_y = static_cast<unsigned>(slice.data.size());
    unsigned res_x = static_cast<unsigned>(slice.data.at(0).size());
    for(unsigned y = 0; y < res_y; y++)
    {
      for(unsigned x = 0; x < res_x; x++)
      {
        if(slice.data[y][x]) ostream << "X ";
        else ostream << ". ";
      }
      ostream << std::endl;
    }
    //throw std::logic_error("task 6.4 e)");
    //(void) slice; // silence unused parameter warning

    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const VoxelGrid& vg)
{
    uint32_t res_z;
    std::tie(std::ignore, std::ignore, res_z) = vg.getResolution();

    for (uint32_t z=0; z<res_z; ++z) {
        auto slice = vg.extractSlice(Axis::Z, z);
        ostream << slice << std::endl;
    }
    return ostream;
}
