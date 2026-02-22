#include <superkarel.h>
void turn_right();
void turn_around();
void check_the_size();
void get_left();

int main(){
    turn_on("task_3.kw");
    set_step_delay(200);
    check_the_size();
    turn_around();
    while(front_is_clear()){
        step();
    }
    turn_left();
    while(front_is_clear()){
        step();
    }
    turn_left();

    get_left();


    turn_off();
    return 0;
}


void check_the_size(){
    while (front_is_clear()){
        step();
        if(beepers_present()){
            turn_right();
            while(beepers_present()){
                pick_beeper();
                step();
                if(no_beepers_present()){
                    turn_around();
                    step();
                    turn_around();
                }
            }          
        put_beeper();
        turn_around();
        while(front_is_clear()){
            step();
        }
        turn_right();
        }
       
    }

}


void get_left(){
    while(front_is_clear()){
        step();
        if(beepers_present()){
            pick_beeper();
            turn_around();
            while(front_is_clear()){
                step();
            }
                turn_around();
                
        }
    }  
        turn_around();
        while(front_is_clear()){
            step();
        }
            turn_right();
            step();
            turn_right();

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