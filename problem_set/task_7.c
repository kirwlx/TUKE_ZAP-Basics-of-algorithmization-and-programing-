#include <superkarel.h>

void turn_right();
void turn_around();
void check_the_place();
void go_back();

int main(){
    turn_on("task_77.kw");
    set_step_delay(100);



    while(front_is_clear()){        //THE BEEPERS ON THE BOTTOM
        put_beeper();
        if(front_is_clear()){
            step();
        }
    }
    put_beeper();
    turn_around();
    while(front_is_clear()){
        step();
    }
    turn_around();                //END OF THE BOTTOM BEEPS

    while(front_is_clear()){
        if(left_is_clear()){
            
            check_the_place();
            
                step();
    }else{
        step();
    }
    }
    
    turn_around();
    while(front_is_clear()){
        if(beepers_present()){
            pick_beeper();
            step();
        }
    }
    if(beepers_present()){
            pick_beeper();
        }
    turn_around();
    while(front_is_clear()){
            if(beepers_present()){
            pick_beeper();
        }
            step();
    }
    if(beepers_present()){
            pick_beeper();
        }
    

    





    turn_off();
    return 0;
}   

void check_the_place(){
    turn_left();
    step();
    if(beepers_present()){
        turn_around();
        step();
        turn_left();
        return;
    }else{
        put_beeper();
    }
    if(right_is_clear()){
        turn_right();
        step();
    }
    if(front_is_blocked()){
        pick_beeper();
        turn_around();
        step();
        turn_left();
        return;
    }

    while(right_is_blocked()){
        if(front_is_blocked()&&left_is_clear()){
            turn_left();
        }else if(front_is_blocked()&&right_is_clear()){
            turn_right();
        }else if (right_is_blocked() && left_is_blocked() && front_is_blocked()){
            turn_around();
        }
        step();
        if(beepers_present() && right_is_blocked() && left_is_blocked()){
            pick_beeper();
            step();
            turn_left();
            return;
        }else if(beepers_present() && right_is_clear() && left_is_clear() && front_is_blocked()){
            turn_around();
            step();
            put_beeper();
            go_back();
            return;
        }else if(beepers_present() && left_is_blocked() && right_is_clear()){
            turn_around();
            step();
            put_beeper();
            go_back();
            return;
        }
        if(right_is_clear()){
            
            turn_right();
            step();
            if(right_is_clear()){
                turn_right();
                step();
                if(beepers_present()){
                    pick_beeper();
                    step();
                    turn_left();
                    return;
                }
            }
        }else if (right_is_blocked() && left_is_blocked() && front_is_blocked()){
            turn_around();
        }else if(front_is_blocked()&&left_is_clear()){
            turn_left();
           
        }
        
        
    }
    
}

void go_back(){
    if(front_is_blocked()&&left_is_clear()){
            turn_left();
        }else if(front_is_blocked()&&right_is_clear()){
            turn_right();
        }
    step();
    if(left_is_clear()){
            
            turn_left();
            step();
            if(left_is_clear()){
                turn_left();
                step();
            }
        }
    while(left_is_blocked()){
        if (right_is_blocked() && left_is_blocked() && front_is_blocked()){
            turn_around();
        }
        if(front_is_blocked()&&left_is_clear()){
            turn_left();
        }else if(front_is_blocked()&&right_is_clear()){
            turn_right();
        }else if (right_is_blocked() && left_is_blocked() && front_is_blocked()){
            turn_around();
        }
        step();
        
        if((beepers_present() && right_is_clear() && left_is_clear())||(beepers_present() && right_is_blocked() && left_is_clear())){
            turn_left();
            return;
        }
        if(left_is_clear()){
            
            turn_left();
            step();
            if(left_is_clear()){
                turn_left();
                step();
            }
        }else if (right_is_blocked() && left_is_blocked() && front_is_blocked()){
            turn_around();
        }else if(front_is_blocked()&&right_is_clear()){
            turn_right();
           
        }else if(left_is_blocked() && front_is_blocked() && right_is_clear() && beepers_present()){
            pick_beeper();
        }
        
        
        
        
    }

}


void turn_right(){
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(100);
}

void turn_around(){
    turn_right();
    turn_right();
}