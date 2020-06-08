//
//  BoidsSpell.hpp
//  empty
//
//  Created by ganariya on 2020/06/08.
//

#ifndef BoidsSpell_hpp
#define BoidsSpell_hpp

#include <stdio.h>
#include "MagicSpell.hpp"

using namespace std;

class BoidsSpell: MagicSpell{
    
    class Boid{
        
    private:
        Vec2 pos;
        Vec2 velocity;
        double can_see;
        const int BOID_SPEED = 10;
        
    public:
        
        Boid(){
            pos = RandomVec2(Window::ClientSize().x, Window::ClientSize().y);;
            velocity = RandomVec2(5, 5) - Vec2(2.5, 2.5);
            can_see = 98;
        }
        
        Boid(double x, double y){
            pos.x = x;
            pos.y = y;
        }
        
        Vec2 separation(const Array<Boid> &boids){
            Vec2 vec;
            for(const auto &boid : boids){
                if((pos - boid.pos).length() <= can_see){
                    Vec2 diff = pos - boid.pos;
                    if(diff == Vec2(0, 0)) continue;
                    vec += diff / diff.length();
                }
                
            }
            return vec / boids.size();
        }
        
        Vec2 alignment(const Array<Boid> &boids){
            Vec2 vec;
            for(const auto &boid: boids){
                if((pos - boid.pos).length() <= can_see){
                    vec += boid.velocity;
                }
            }
            vec /= boids.size();
            return vec - velocity;
        }
        
        Vec2 cohesion(const Array<Boid> &boids){
            Vec2 other;
            for(const auto &boid: boids){
                if((pos - boid.pos).length() <= can_see){
                    other += boid.pos - pos;
                }
            }
            other /= boids.size();
            return other;
        }
        
        Vec2 food_by_mouse(){
            if(MouseL.pressed()){
                auto mouse_pos = Cursor::PosF();
                auto diff = mouse_pos - pos;
                if(diff.length() > 0) diff /= diff.length();
                return diff;
            }
            return Vec2();
        }
        
        Vec2 trace_player(Player &player){
            Vec2 vec = player.pos - pos;
            return vec;
        }

        
        void update(Array<Boid> &boids, Player &player){
            auto sep = separation(boids);
            auto ali = alignment(boids);
            auto cohe = cohesion(boids);
            auto trace = trace_player(player);
            Vec2 ac =  0.89 * sep + 0.000240 * ali + cohe * 0.0100 + trace * 0.0001 + (RandomVec2(1, 1) - Vec2(0.5, 0.5)) * 0.1;
            velocity += BOID_SPEED * ac;
            pos += velocity;
            clamp();
            collision(player);
        }
        
        void collision(Player &player){
            auto player_areas = player.player_body_area();
            for(auto x: player_areas){
                if(RectF(Arg::center(pos), 10).rotated(45_deg).intersects(x)){
                    player.is_attacked = true;
                }
            }
        }
        
        void clamp(){
            if(pos.x < 0){
                long long x = (long long)(pos.x);
                x += 1000*Window::ClientWidth();
                x %= Window::ClientWidth();
                pos.x = x;
            }
            if(pos.x > Window::ClientSize().x){
                long long x = (long long)(pos.x);
                x += 1000*Window::ClientWidth();
                x %= Window::ClientWidth();
                pos.x = x;
            }
            if(pos.y < 0){
                long long y = (long long)(pos.y);
                y += 1000*Window::ClientHeight();
                y %= Window::ClientHeight();
                pos.y = y;
            }
            if(pos.y > Window::ClientSize().y){
                long long y = (long long)(pos.y);
                y += 1000*Window::ClientHeight();
                y %= Window::ClientHeight();
                pos.y = y;
            }
            if(velocity.length() >= BOID_SPEED){
                velocity = velocity.normalized() * BOID_SPEED;
            }
            if(MouseL.pressed()){
                velocity = velocity.normalized() * 2;
            }
        }
        
        void draw() const {
            RectF(Arg::center(pos), 10).rotated(45_deg).draw(Palette::White);
        }
        
    };
    
    
private:
    
    const int NUM_OF_BIRDS = 40;

    Array<Boid> boids;
    
public:
    
    BoidsSpell(): MagicSpell(){
        for(int i = 0;i<NUM_OF_BIRDS;i++){
            boids << Boid();
        }
    }
    
    void update(Player &player) {
        for(auto &boid: boids){
            boid.update(boids, player);
        }
    }
    
    void draw() const {
        for(auto &boid: boids){
            boid.draw();
        }
    }
    
};

#endif /* BoidsSpell_hpp */
