//
//  LifeGameSpell.hpp
//  empty
//
//  Created by ganariya on 2020/06/11.
//

#ifndef LifeGameSpell_hpp
#define LifeGameSpell_hpp

#include "MagicSpell.hpp"
#include "Player.hpp"
#include <Siv3D.hpp>


class LifeGameSpell: public MagicSpell{
    
private:
    
    const int per_block = 40;
    const int W;
    const int H;
    
    int count = 0;
    int per_update = 5;
    
    int w_cnt;
    int h_cnt;
    
    double init_r = 0.15;
    
    Array<Array<RectF>> blocks;
    
    // death 0
    // live 1
    Array<Array<int>> states;
    
public:
    
    LifeGameSpell(): MagicSpell(), W(Window::ClientWidth()), H(Window::ClientHeight()){
        
        w_cnt = W / per_block;
        h_cnt = H / per_block;
        
        setup();
    }
    
    void setup(){
        blocks = Array<Array<RectF>>(h_cnt);
        states = Array<Array<int>>(h_cnt, Array<int>(w_cnt, 0));
        
        for(int i = 0;i<h_cnt;i++){
            for(int j = 0;j<w_cnt;j++){
                blocks[i] << RectF(j * per_block, i * per_block, per_block, per_block);
                if(Random() < init_r){
                    states[i][j] = 1;
                }
            }
        }
        
    }
    
    void update(Player &player){
        count++;
        
        if(MouseL.pressed()){
            per_update = 10;
        }else{
            per_update = 5;
        }
        
        if(count % per_update == 0){
            cell_update();
        }
        
        if(watch.sF() >= 3){
            is_finish = true;
        }
        
        collision(player);
    }
    
    void collision(Player &player){
        auto player_areas = player.player_body_area();
        for(auto x: player_areas){
            for(int i = 0;i<h_cnt;i++){
                for(int j = 0;j<w_cnt;j++){
                    if(states[i][j] ==1){
                        if(blocks[i][j].intersects(x)){
                            player.is_attacked = true;
                        }
                    }
                }
            }
        }
    }
    
    void cell_update(){
        
        Array<Array<int>> next(h_cnt, Array<int>(w_cnt, 0));
        
        int dy[] = {0, 1, 0, -1};
        int dx[] = {1, 0, -1, 0};
        
        for(int i = 0;i<h_cnt;i++){
            for(int j = 0;j<w_cnt;j++){
                int cnt = 0;
                
                for(int k = -1;k<=1;k++){
                    for(int l = -1;l<=1;l++){
                        if(k == 0 and l == 0) continue;
                        int to_y = (i + k + h_cnt) % h_cnt;
                        int to_x = (j + l + w_cnt) % w_cnt;
                        cnt += states[to_y][to_x];
                    }
                }
                
                // death
                if(states[i][j] == 0){
                    if(cnt == 3){
                        next[i][j] = 1;
                    }
                }
                
                if(states[i][j] == 1){
                    if(cnt == 2 or cnt == 3){
                        next[i][j] = 1;
                    }
                }
                
            }
        }
        
        swap(states, next);
    }
    
    void draw() const {
        for(int i = 0;i<h_cnt;i++){
            for(int j = 0;j<w_cnt;j++){
                int s = states[i][j];
                blocks[i][j].draw(ColorF(255 * s, 255 * s, 255 * s, 1));
            }
        }
    }
    
};

#endif /* LifeGameSpell_hpp */
