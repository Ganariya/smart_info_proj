//
//  ChaosSpell.hpp
//  empty
//
//  Created by ganariya on 2020/06/11.
//

#ifndef ChaosSpell_hpp
#define ChaosSpell_hpp

#include <Siv3D.hpp>
#include "MagicSpell.hpp"

class ChaosSpell: public MagicSpell{
    
private:
    
    int W;
    int H;
    int count;
    
    int make_line_num = 0;
    
    double per_width;
    
    double init_r;
    int per_draw_line = 5;
    int num_of_lines = 30;
    
    Vec2 pos;
    Array<Line> lines;
    const Audio audio;
    
public:
    
    ChaosSpell(): MagicSpell(), W(Window::ClientWidth()), H(Window::ClientHeight()), audio(Audio(Resource(U"sphe.mp3"))){
        per_width = W / (double)num_of_lines;
        count = 0;
        init_r = Random();
        pos = Vec2(0, init_r);
    }
    
    void update(Player &player){
        count++;
        
        if(MouseL.pressed()){
            if(lines.size() and count % per_draw_line == 0){
                lines.pop_back();
            }
        }
        else if(count % per_draw_line == 0){
            if(count % (per_draw_line * 2) == 0)audio.playOneShot();
            double nr = mei_next(pos.y);
            double ny = H * nr;
            double nx = pos.x + per_width;
            lines << Line(pos.x, pos.y * H, nx, ny);
            pos = Vec2(nx, nr);
           
        }
        if(make_line_num > num_of_lines){
            is_finish = true;
        }
        if(count % per_draw_line == 0) make_line_num++;
        
        collision(player);
    }
    
    void collision(Player  &player){
        auto player_areas = player.player_body_area();
        for(auto x: player_areas){
            for(auto &line : lines){
                if(line.intersects(x)){
                    player.is_attacked = true;
                }
            }
        }
    }
    
    void draw() const{
        for(const auto &line: lines){
            line.draw(5, Palette::White);
        }
    }
    
    double mei_next(double x){
        return 4 * x * (1-x);
    }
    
    
};

#endif /* ChaosSpell_hpp */
