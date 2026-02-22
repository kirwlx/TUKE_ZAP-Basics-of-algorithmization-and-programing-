#include <superkarel.h>

void turn_around();
void turn_right();

int main(){
    turn_on("task_2.kw");
    set_step_delay(100);

    while(no_beepers_present()){
        if(front_is_clear()){
            step();
        }else{
            turn_left();
            step();
        }

    }
    pick_beeper();
    turn_around();
    while(no_beepers_present()){
        while(front_is_clear()){
            step();
        }
        if (front_is_blocked()&& right_is_clear() && left_is_blocked()){
            turn_right();
            while(front_is_clear()){
                step();
            }
        }else if (front_is_blocked() && right_is_blocked() && left_is_blocked()){
            turn_right();
            break;
        }
        
    }

    turn_off();
    return 0;
}

void turn_around(){
    turn_left();
    turn_left();
}

void turn_right(){
    set_step_delay(10);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(100);
}