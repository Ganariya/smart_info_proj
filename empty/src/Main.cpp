
#include "Main.hpp"
#include "Player.hpp"
#include "MagicSpell.hpp"
#include "BoidsSpell.hpp"
#include "PercolationSpell.hpp"
#include "ChaosSpell.hpp"
#include "LifeGameSpell.hpp"
#include "TextSpell.hpp"

void setup(){
    Window::Resize(Size(1280, 720));
    Scene::SetBackground(Palette::Black);
}

void update_audio(const Audio &audio){
    if(MouseL.pressed()){
        audio.setSpeed(0.75);
    }else{
        audio.setSpeed(1);
    }
}

void change_spell(unique_ptr<MagicSpell> &spell, const Audio &notice){
    if(spell->is_finish){
        notice.setPosSec(0.6);
        notice.play();
        int x = Random<int>(1000000000) % 4;
        spell.reset();
        if(x == 0) spell = unique_ptr<MagicSpell>(new BoidsSpell());
        if(x == 1) spell = unique_ptr<MagicSpell>(new PercolationSpell());
        if(x == 2) spell = unique_ptr<MagicSpell>(new ChaosSpell());
        if(x == 3) spell = unique_ptr<MagicSpell>(new LifeGameSpell());
    }
}

void Main()
{
    
    const Audio audio(Resource(U"bgm.mp3"), Arg::loop=true);
    const Audio notice(Resource(U"notice.mp3"));
    
    audio.setVolume(0.3);
    audio.play();
    notice.setPosSec(0.7);
    
    setup();
    
//    unique_ptr<MagicSpell> spell(new LifeGameSpell());
    unique_ptr<MagicSpell> spell(new TextSpell());
    
    Player player;
    
    
    while(System::Update()){
        update_audio(audio);
        player.update();
        spell->update(player);
        spell->draw();
        player.draw();
        change_spell(spell, notice);
    }
}
