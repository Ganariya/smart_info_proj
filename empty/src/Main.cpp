
#include "Main.hpp"
#include "Player.hpp"
#include "BoidsSpell.hpp"

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

void Main()
{
    
    const Audio audio(Resource(U"bgm.mp3"), Arg::loop=true);
    audio.setVolume(0.5);
    audio.play();
    
    setup();
    
    Player player;
    BoidsSpell boids_spell;
    
    while(System::Update()){
        update_audio(audio);
        player.update();
        boids_spell.update(player);
        player.draw();
        boids_spell.draw();
    }
}
