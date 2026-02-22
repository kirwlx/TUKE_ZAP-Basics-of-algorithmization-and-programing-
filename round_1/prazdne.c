#include <superkarel.h>
void turn_right();
void turn_around();
bool no_beepers();

int main() {
    turn_on("prazdne.kw");

    no_beepers();

    turn_off();
    return 0;
}

bool no_beepers(){
    if(beepers_present() || beepers_in_bag()){
        return false;
    }else{
        return true;
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

