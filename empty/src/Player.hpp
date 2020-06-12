//
//  Player.hpp
//  empty
//
//  Created by ganariya on 2020/06/08.
//

#ifndef Player_hpp
#define Player_hpp

#include <Siv3D.hpp>

class Player{
    
public:
    
    const Audio attacked_audio;
    
    Vec2 pos;
    Vec2 vec;
    
    int speed;
    int hp;
    int length;
    
    bool is_attacked;
    
    Color color;
    
public:
    
    Player(): attacked_audio(Resource(U"damage.mp3")){
        pos = Vec2(50, 50);
        hp = 30;
        speed = 10;
        length = 10;
        color = Palette::Red;
        is_attacked = false;
    }
    
    void draw() const {
        RectF(pos + Vec2(-(length/ 2) + 1, 0), length* 2, length).rotated(45_deg).draw(Palette::Red);
        RectF(pos + Vec2(length/2-1 , 0), length * 2, length).rotated(135_deg).draw(Palette::Red);
    }
    
    void update(){
        move();
        clamp();
        attacked();
    }
    
    void attacked(){
        if(is_attacked){
            is_attacked = false;
            attacked_audio.playOneShot();
            hp--;
        }
    }
    
    void clamp(){
        if(pos.x < 0) pos.x = 0;
        if(pos.x > Window::ClientWidth()) pos.x = Window::ClientWidth();
        if(pos.y< 0) pos.y = 0;
        if(pos.y >Window::ClientHeight()) pos.y = Window::ClientHeight();
    }
    
    Array<Quad> player_body_area(){
        Array<Quad> rects;
        rects <<  RectF(pos + Vec2(-(length/ 2) + 1, 0), length* 2, length).rotated(45_deg);
        rects <<  RectF(pos + Vec2(length/2-1 , 0), length * 2, length).rotated(135_deg);
        return rects;
    }
    
    void move(){
        vec = Vec2(0, 0);
        if(KeyW.pressed()){
            vec += Vec2(0, -speed);
        }
        if(KeyA.pressed()){
            vec += Vec2(-speed, 0);
        }
        if(KeyS.pressed()){
            vec += Vec2(0, speed);
        }
        if(KeyD.pressed()){
            vec += Vec2(speed, 0);
        }
        if(MouseR.pressed()){
            vec /= 2;
        }
        pos += vec;
    }
    
};

#endif /* Player_hpp */
