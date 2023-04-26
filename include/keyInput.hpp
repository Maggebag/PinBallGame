
#ifndef PINBALLGAME_KEYINPUT_HPP
#define PINBALLGAME_KEYINPUT_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

struct Keys {
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool r = false;
    bool space = false;
};

class KeyInput: public KeyListener {
public:
    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == 87){
            keys_.w = true;}
        else if (evt.key == 83){
            keys_.s = true;}
        else if (evt.key == 68){
            keys_.d = true;}
        else if (evt.key == 65){
            keys_.a = true;}
        else if (evt.key == 82){
            keys_.r = true;}
        else if (evt.key == 32){
            keys_.space = true;}
    }
    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == 87){
            keys_.w = false;}
        else if (evt.key == 83){
            keys_.s = false;}
        else if (evt.key == 68){
            keys_.d = false;}
        else if (evt.key == 65){
            keys_.a = false;}
        else if (evt.key == 82){
            keys_.r = false;}
        else if (evt.key == 32){
            keys_.space = false;}
    }

    void flippers (btHingeConstraint& flipperRight, btHingeConstraint& flipperLeft) const
    {
        if (keys_.d){
            flipperRight.setMotorTargetVelocity(-100000000);
        }
        else{
            flipperRight.setMotorTargetVelocity(100000000);
        }
        if (keys_.a){
            flipperLeft.setMotorTargetVelocity(100000000);
        }
        else{
            flipperLeft.setMotorTargetVelocity(-100000000);
        }
    }
    void launcher(btSliderConstraint& slider)
    {
        if(keys_.s && lowLim_ < 80){
           lowLim_+= 0.5;
        }
        if(keys_.w && lowLim_ > 0) {
        lowLim_-= 0.5;
        }

        slider.setUpperLinLimit(lowLim_);

        if(keys_.space){
            slider.setTargetLinMotorVelocity(-10000);
            lowLim_ = 0;
        }
        else{
            slider.setTargetLinMotorVelocity(10000);
        }
    }
    void reset(std::shared_ptr<Mesh> pinBall,BulletPhysics& bullet)
    {
        if(keys_.r){
        bullet.setMeshPosition(*pinBall,{30,13.5,0});
        }
    }

private:
    Keys keys_;
    float lowLim_ = 0;
};

#endif //PINBALLGAME_KEYINPUT_HPP
