
#ifndef PINBALLGAME_LIGHTSHIELDOBJECT_HPP
#define PINBALLGAME_LIGHTSHIELDOBJECT_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>
#include <threepp/geometries/ShapeGeometry.hpp>

#include "utils.hpp"

class LightShieldObject{

public:
    void defineLightShieldDimensions(float width, float length) {

        points_.emplace_back(0,0);
        points_.emplace_back(0,length);
        points_.emplace_back(width*0.6,length);
        points_.emplace_back(width*0.6,length*0.7);
        points_.emplace_back(width*0.4, length*0.5);
        points_.emplace_back(width*0.6, length*0.3);
        points_.emplace_back(width*0.6,0);

    }

    void addToScene(threepp::Object3D &scene){

        auto shapeGeometry = ShapeGeometry::create(shape);
        shapeGeometry->center();

    }



private:
    threepp::Vector3 LightShieldPos_;

    std::vector<threepp::Vector2> points_;

    std::shared_ptr<threepp::Mesh> LightShieldSide1_;
    std::shared_ptr<threepp::Mesh> LightShieldSide2_;
    std::shared_ptr<threepp::Mesh> LightShieldSide3_;

    std::shared_ptr<threepp::Mesh>TopCorner_;
    threepp::Vector3 TopCornerPos_;
    std::shared_ptr<threepp::Mesh>BottomCorner_;
    threepp::Vector3 BottomCornerPos_;
    std::shared_ptr<threepp::Mesh>InsideCorner_;
    threepp::Vector3 InsideCornerPos_;

};

#endif //PINBALLGAME_LIGHTSHIELDOBJECT_HPP
