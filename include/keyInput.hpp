
#ifndef PINBALLGAME_KEYINPUT_HPP
#define PINBALLGAME_KEYINPUT_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

struct keys {
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool space = false;
};

struct KeyInput: KeyListener {

    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == 87){
            keys_.w = true;}
        else if (evt.key == 83){
            keys_.s = true;}
        else if (evt.key == 68){
            keys_.d = true;}
        else if (evt.key == 65){
            keys_.a = true;}
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
        else if (evt.key == 32){
            keys_.space = false;}
    }
   /* void flipperLeft (btHingeConstraint& flipper) const
    {
        if (keys_.a){
            flipper.setMotorTargetVelocity(-1000000);
        }
        else{
            flipper.setMotorTargetVelocity(1000000);
        }
    }*/


private:
    keys keys_;
};

#endif //PINBALLGAME_KEYINPUT_HPP
