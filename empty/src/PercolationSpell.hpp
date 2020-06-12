//
//  PercolationSpell.hpp
//  empty
//
//  Created by ganariya on 2020/06/11.
//

#ifndef PercolationSpell_hpp
#define PercolationSpell_hpp

#include "MagicSpell.hpp"
#include "Player.hpp"
#include <Siv3D.hpp>



class PercolationSpell: public MagicSpell{
    
private:
    
    const int per_block = 40;
    const int W;
    const int H;
    
    int w_cnt;
    int h_cnt;
    
    int times = 4;
    int draw_cnt = 0;
    int draw_per = 20;
    int spread_base = 40;
    int wait_before_spread = 30;
    
    bool ignitioned = false;
    bool firing = false;
    
    double tree_percent;
    double spread_percent;
    
    Array<Array<RectF>> blocks;
    
    // [0] nothing
    // [1] tree
    // [2] fire
    Array<Array<int>> burns;
    
    const Audio audio;
    
    
public:
    
    PercolationSpell(): MagicSpell(), W(Window::ClientWidth()), H(Window::ClientHeight()), audio(Audio(Resource(U"sphe.mp3"))){
        tree_percent = 0.55;
        spread_percent = 0.7;
        w_cnt = W / per_block;
        h_cnt = H / per_block;
        
        setup();
    }
    
    void setup(){
        draw_cnt = 0;
        ignitioned = false;
        firing = false;
        wait_before_spread = 30;
        blocks = Array<Array<RectF>>(h_cnt);
        burns = Array<Array<int>>(h_cnt, Array<int>(w_cnt, 0));
        for(int i = 0;i<h_cnt;i++){
            for(int j = 0;j<w_cnt;j++){
                blocks[i] << RectF(j * per_block, i * per_block, per_block, per_block);
                if(Random() < tree_percent){
                    burns[i][j] = 1;
                }
            }
        }
        times--;
        audio.play();
        if(times <= 0){
            is_finish = true;
        }
    }
    
    void update(Player &player) {
        draw_cnt += draw_per;
        if(draw_cnt >= w_cnt * h_cnt + 30) ignitioned = true;
        
        if(firing and draw_cnt % spread_base == 0 and wait_before_spread <= 0)fire();
        if(ignitioned and !firing) ignition();
        if(firing) wait_before_spread--;
        
        collision(player);
    }
    
    void collision(Player &player){
        auto player_areas = player.player_body_area();
        for(auto x: player_areas){
            for(int i = 0;i<h_cnt;i++){
                for(int j = 0;j<w_cnt;j++){
                    if(burns[i][j] == 2){
                        if(blocks[i][j].intersects(x)){
                            player.is_attacked = true;
                        }
                    }
                }
            }
        }
    }
    
    void fire(){
        int dy[] = {0, 1, 0, -1};
        int dx[] = {1, 0, -1, 0};
        
        auto next_burns = burns;

        int update = 0;
        for(int i = 0;i<h_cnt;i++){
            for(int j = 0;j<w_cnt;j++){
                if(burns[i][j] == 2){
                    for(int k = 0;k<4;k++){
                        int to_y = (i + dy[k] + h_cnt) % h_cnt;
                        int to_x = (j + dx[k] + w_cnt) % w_cnt;
                        if(burns[to_y][to_x] == 1){
                            next_burns[to_y][to_x] = 2;
                            update = 1;
                        }
                    }
                }
            }
        }
        
        burns = next_burns;
        if(!update) setup();
    }
    
    void ignition(){
        firing = true;
        
        double fire_percent = 0.01;
        
        for(int i = 0;i<h_cnt;i++){
            for(int j = 0;j<w_cnt;j++){
                if(burns[i][j] == 1 and Random() < fire_percent){
                    burns[i][j] = 2;
                }
            }
        }
        
    }
    
    void draw() const {
        int d_cnt = 0;
        for(int i = 0;i<h_cnt;i++){
            for(int j = 0;j<w_cnt;j++){
                d_cnt++;
                if(burns[i][j] == 1 and d_cnt < draw_cnt){
                    blocks[i][j].draw(ColorF(Palette::White, 1));
                }
                if(burns[i][j] == 2 and d_cnt < draw_cnt){
                    blocks[i][j].draw(ColorF(Palette::Red, 1));
                }
            }
        }
    }
    
};

#endif /* PercolationSpell_hpp */
