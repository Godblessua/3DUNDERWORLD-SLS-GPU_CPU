/* 
 * A point cloud class
 */
#pragma once
#include <core/Log.hpp>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>

namespace SLS
{

//! A point cloud class
void exportPointCloud2OBJ(std::string fileName, const std::vector<float> &pointCloud);
void exportPointCloud2PLY(std::string fileName, const std::vector<float> &pointCloud);
class PointCloud
{
private:
    //! Point cloud buffer, stores point cloud in (X,Y,Z,R,G,B) 
    std::vector<float> buffer_;
    const size_t FLOATS_PER_POINT = 6;
public:
    PointCloud() {}
    PointCloud(size_t numPoints)
    {
        buffer_.resize(numPoints * FLOATS_PER_POINT);
    }
    //! Get reference of buffer
    std::vector<float>& getBuffer()
    {
        return buffer_;
    }
    //! Get number of points
    size_t numPoints() const
    {
        return buffer_.size() / 6;
    }

    void pushPoint(const glm::vec3& pos, const glm::vec3& rgb)
    {
        buffer_.push_back(pos.x);
        buffer_.push_back(pos.y);
        buffer_.push_back(pos.z);
        buffer_.push_back(rgb.x);
        buffer_.push_back(rgb.y);
        buffer_.push_back(rgb.z);
    }

    /*! Export point cloud to file
     * \param fileName output file
     * \param type Export type, only supports ["ply", "obj"] for now
     */
    void exportPointCloud(std::string fileName, std::string type)
    {
        std::unordered_map<std::string, std::function<void(std::string, const std::vector<float>&)>> dispatcher;
        dispatcher["ply"] = exportPointCloud2PLY;
        dispatcher["obj"] = exportPointCloud2OBJ;

        dispatcher[type](fileName, buffer_);
    }

};
} // namespace SLS
