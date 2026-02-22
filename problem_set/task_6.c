#include <superkarel.h>

void turn_around();
void turn_right();



int main(){
    turn_on("task_6.kw");
    set_step_delay(100);
    while(front_is_clear()){
        step();
        if (beepers_present()){
            turn_left();
            pick_beeper();
            if(no_beepers_present()){
                if(facing_south()){
                    turn_around();
                }else if(facing_west()){
                    turn_right();
                }else if(facing_east()){
                    turn_left();
                }else{
                    continue;
            }
            }
        }
        if (beepers_present()){
            turn_left();
            pick_beeper();
            if(no_beepers_present()){
                if(facing_north()){
                    turn_left();
                }else if(facing_south()){
                    turn_right();
                }else if(facing_east()){
                    turn_around();
                }else{
                    continue;
            }
            }
            
        }
        if (beepers_present()){
            turn_left();
            pick_beeper();

            if(no_beepers_present()){
                if(facing_north()){
                    turn_around();
                }else if(facing_west()){
                    turn_left();
                }else if(facing_east()){
                    turn_right();
                }else{
                    continue;
            }
            }
        }
        if (beepers_present()){
            pick_beeper();
            if(no_beepers_present()){
                if(facing_north()){
                    turn_right();
                }else if(facing_south()){
                    turn_left();
                }else if(facing_west()){
                    turn_around();
                }else{
                    continue;
            }
            }
            
        }
        if(beepers_present()){
            pick_beeper();
            break;
        }

    }

    turn_off();
    return 0;
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


