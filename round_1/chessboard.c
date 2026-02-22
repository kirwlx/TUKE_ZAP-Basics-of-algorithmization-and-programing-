#include <superkarel.h>
void turn_right();
void turn_around();
void chessboard();

int main() {
    turn_on("chessboard.kw");
    set_step_delay(100);
    chessboard();
    turn_off();
    return 0;
}


void chessboard() {
    put_beeper();
    while (facing_east() || facing_west()) {


        if (front_is_clear()) {

            step();
            if (front_is_clear()) {
                step();
                put_beeper();
            }else if (facing_east()){
                turn_left();
                step();
                turn_left();
            }else if (facing_west()) {
                turn_right();
                step();
                turn_right();
            }
        }else if (facing_east() && no_beepers_present()) {
            turn_left();
            if (front_is_blocked()) {
                turn_right();
                return;
            }
            step();
            turn_left();
        }else if (facing_west() && no_beepers_present()) {
            turn_right();
            if (front_is_blocked()) {
                turn_left();
                return;
            }
            step();
            turn_right();
        }else if (facing_east() && beepers_present()) {
            turn_left();
            if (front_is_blocked()) {
                turn_right();
                return;
            }
            step();
            turn_left();
            step();
        }else if (facing_west() && beepers_present()) {
            turn_right();
            if (front_is_blocked()) {
                turn_left();
                return;
            }
            step();
            turn_right();
            step();
        }
        if (no_beepers_present()) {
            put_beeper();
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