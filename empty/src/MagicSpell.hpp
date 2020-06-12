//
//  MagicSpell.hpp
//  empty
//
//  Created by ganariya on 2020/06/08.
//

#ifndef MagicSpell_hpp
#define MagicSpell_hpp

#include <stdio.h>
#include <Siv3D.hpp>
#include "Player.hpp"

class MagicSpell{
    
public:
      bool is_finish;
    
protected:
    Stopwatch watch;
  
    
public:
    
    MagicSpell(){
        is_finish = false;
        watch.start();
    }
    
    void start(){
        watch.restart();
    }
    
    virtual ~MagicSpell(){
        
    }
    
    virtual void update(Player &player){
        
    }
    
    virtual void draw() const {
        
    }
    
};

#endif /* MagicSpell_hpp */
