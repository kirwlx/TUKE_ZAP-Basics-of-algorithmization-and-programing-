#include <superkarel.h>
void turn_right();
void turn_around();
void divide();
void divide_even_beepers();

int main() {
    turn_on("divide.kw");
    
    step();
    divide_even_beepers();

    turn_off();
    return 0;
}

void divide_even_beepers(){
    divide();
    step();
    while(beepers_in_bag()){
        put_beeper();
    }
    turn_around();
    while(front_is_clear()){
        step();
    }
    turn_around();
}

void divide(){
    pick_beeper();
    pick_beeper();
    if(beepers_present()){
        divide();
    }
    put_beeper();
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

