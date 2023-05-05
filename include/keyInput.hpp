
#ifndef PINBALLGAME_KEYINPUT_HPP
#define PINBALLGAME_KEYINPUT_HPP

#include <threepp/input/KeyListener.hpp>
#include "GameObjects.hpp"
#include <iostream>

struct Keys {
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool r = false;
    bool space = false;
};

struct KeyInput : public threepp::KeyListener {
public:
    void onKeyPressed(threepp::KeyEvent evt) override {
        if (evt.key == 87) {
            keys_.w = true;
        } else if (evt.key == 83) {
            keys_.s = true;
        } else if (evt.key == 68) {
            keys_.d = true;
        } else if (evt.key == 65) {
            keys_.a = true;
        } else if (evt.key == 82) {
            keys_.r = true;
        } else if (evt.key == 32) {
            keys_.space = true;
        } else if (evt.mods == 1){
            std::cout<<"Shift"<<std::endl;
        }
    }

    void onKeyReleased(threepp::KeyEvent evt) override {
        if (evt.key == 87) {
            keys_.w = false;
        } else if (evt.key == 83) {
            keys_.s = false;
        } else if (evt.key == 68) {
            keys_.d = false;
        } else if (evt.key == 65) {
            keys_.a = false;
        } else if (evt.key == 82) {
            keys_.r = false;
        } else if (evt.key == 32) {
            keys_.space = false;
        }
    }

    void flippers(FlipperObject &Right, FlipperObject &Left) const {
        if (keys_.d) {
            Right.activateFlipper();
        } else {
            Right.deactivateFlipper();
        }
        if (keys_.a) {
            Left.activateFlipper();
        } else {
            Left.deactivateFlipper();
        }
    }

    void plunger(PlungerObject &Plunger) {
        if (keys_.s && lowLim_ < 80) {
            lowLim_ += 0.5;
        }
        if (keys_.w && lowLim_ > 0) {
            lowLim_ -= 0.5;
        }

        Plunger.PlungerSetLowLim(lowLim_);

        if (keys_.space) {
            Plunger.releasePlunger();
            lowLim_ = 0;
        } else {
            Plunger.resetPlunger(lowLim_);
        }
    }

    void reset(std::shared_ptr<threepp::Mesh> pinBall, threepp::BulletPhysics &bullet) {
        if (keys_.r) {
            bullet.setMeshPosition(*pinBall, {30, 13.5, 0});
        }
    }

private:
    Keys keys_;
    float lowLim_ = 0;
};

#endif //PINBALLGAME_KEYINPUT_HPP
