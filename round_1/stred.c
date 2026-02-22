#include <superkarel.h>
void turn_right();
void turn_around();
void find_corner();
void find_center();


int main() {
    turn_on("stred.kw");
    set_step_delay(100);

    find_corner();
    find_center();
    find_center();
    turn_off();
    return 0;
}

void find_corner(){
    while(not_facing_west()){
        turn_left();
    }
    while(front_is_clear()){
        step();
    }
    turn_left();
    while(front_is_clear()){
        step();
    }
    turn_left();
}

void find_center(){
    put_beeper();
    while(front_is_clear()){
        step();
    }
    put_beeper();
    turn_around();
    step();
    while(front_is_clear()){
        if(beepers_present()){
            pick_beeper();
            turn_around();
            
            step();
            if(beepers_present()){
                while(not_facing_north()){
                    turn_left();
                }
                while(beepers_present()){
                    pick_beeper();
                }
                break;
            }
            put_beeper();
            step();
        }
        step();
        if(beepers_present()){
            pick_beeper();
            turn_around();
            step();
            put_beeper();
            step();
        }
    }



}


void turn_right() {
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(100);
}

void turn_around() {
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(100);
}

