//
//  TextSpell.hpp
//  empty
//
//  Created by ganariya on 2020/06/12.
//

#ifndef TextSpell_hpp
#define TextSpell_hpp

using namespace std;

#include "MagicSpell.hpp"
#include "Player.hpp"
#include <Siv3D.hpp>

class TextSpell : public MagicSpell{
    
    const Font font;
    Stopwatch text_watch;
    
    const Vec2 base;
    int previous;
    
    Array<Vec2> offsets;
    const Texture ganariya;
    const Audio sans;
    RectF rect;
    
    int text_id = 0;
    Array<String> texts;
    
    int fin = 0;
    
public:
    
    TextSpell(): MagicSpell(), font(30), offsets(100, Vec2(0, 0)), base(60, Window::ClientHeight()/2+10), ganariya(Resource(U"ganariya_2.png")), sans(Resource(U"sans.mp3")){
        texts = {
            U"こんにちは。gssanariya(岩崎)の発表だよ。\n普段は競技プログラミングとかをやっているよ。",
            U"上にいるキャラクターがganariyaだと思ってくれたまえよ。",
            U"そんなこんなで、スマートインフォメディアの最終課題の発表をするよ。\n",
            U"ganariyaのテーマは「これまでの総まとめをしたい」だよ。\nつまりごった煮をしてすべて復習したいわけだね。お得ぅ！\n",
            U"ただ、本当は。\nUndertaleっぽいゲームを作りたかっただけなんだけど。",
            U"立ち話もなんだから、まずは中身から見ていこうか？\n",
        };
        text_watch.start();
        rect = RectF(40, Window::ClientHeight() / 2 , Window::ClientWidth() - 80, 300);
        previous = 0;
        text_id = 0;

    }
    
    void update(Player &player) {
        if(text_watch.ms() - previous > 30){
            previous = text_watch.ms();
            for(auto &off: offsets) off = RandomVec2(4, 4);
        }
        
        if(text_id >= texts.size()) fin++;
        if(fin >= 30) is_finish = true;
        
        check_text_fin();
    }
    
    void check_text_fin(){
        const int index = text_watch.ms() / 80;
        
        if(text_id >= texts.size()) return;
        String text = texts[text_id];
        String s = text.substr(0, index);
        
        if(index >= text.size() + 14){
            text_id++;
            text_watch.restart();
            previous = 0;
        }
        
    }
    
    void draw() const {
        
        ganariya.scaled(0.4).drawAt(Scene::Center() + Vec2(0, -200));
        rect.drawFrame(5, 0);
        
        if(text_id >= texts.size()) return ;
        
        Vec2 pos = base;
        const int index = text_watch.ms() / 80;
        String text = texts[text_id];
        String s = text.substr(0, index);
        
        if(!sans.isPlaying()){
            sans.setPosSec(0.4);
            sans.play();
        }

        
        int id = 0;
        for(const auto &glyph: font(s)){
            
            id++;
            
            if(glyph.codePoint == U'\n'){
                pos.x = base.x;
                pos.y += font.height();
                continue;
            }
            glyph.texture.draw(pos + glyph.offset + offsets[id % offsets.size()], Palette::White);
            pos.x += glyph.xAdvance;
        }
    }
};

#endif /* TextSpell_hpp */
