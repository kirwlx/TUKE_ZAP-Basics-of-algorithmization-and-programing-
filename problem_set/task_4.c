#include <superkarel.h>

void turn_around();
void turn_right();
void set_the_line();
void check_the_lines();

int main(){
    turn_on("task_4.kw");
    set_step_delay(100);
        
    turn_left();
    
    check_the_lines();

    turn_off();
    return 0;
}

void check_the_lines(){

    while(front_is_clear()){
        if(beepers_present()){
            set_the_line();
            turn_left();
            if(front_is_clear()){
                step();
                turn_left();
            }else{
                turn_off();
            }
            
        }
        if (front_is_clear()){
            step();
        }
        
        if(front_is_blocked()){
            turn_around();
            while(front_is_clear()){
                step();
            }
            turn_left();
            if(front_is_clear()){
                step();
                turn_left();
            }else{
                turn_off();
            }
            
        }
    }
    

}

void set_the_line(){
        while(front_is_clear()){
            step();
        }
        turn_around();
        while(front_is_clear()){
            if(no_beepers_present()){
                put_beeper();
                step();
                
            }else{
                step();
            }
        }
        if(no_beepers_present()){
                put_beeper();
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