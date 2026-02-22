#include <superkarel.h>

void turn_around();
void turn_right();
void go_to_corner();
void fill_the_walls();
void find_center();


// go_to_corner();
//     while(beepers_in_bag()){
//         if(front_is_clear()){
//             if(no_beepers_present()){
//                 put_beeper();
//                 step();
//             }else{
//                 step();
//                 break;
//             }
            
//         }
//         if(front_is_blocked()){
//             turn_left();
//         }
//     }
//     turn_left();
//     step();
//     while(beepers_in_bag()){
//         if(no_beepers_present()){
//             step();
//         }else{
//             turn_around();
//             step();
//             put_beeper();
//         }
//     }




int main(){       
    set_step_delay(100);                      //MAIN MAIN MAIN MAIN MAIN
    turn_on("task_5.kw");
    go_to_corner();
    put_beeper();
    step();
    fill_the_walls();
        turn_left();
        step();
        turn_left();
        step();

    find_center();
    find_center();
    while(not_facing_north()){
        turn_left();
    }
    

    turn_off();
    return 0;
}




void fill_the_walls(){
    while(beepers_in_bag()){
        if(front_is_clear()){
            if(beepers_present()){
                break;
            }
            put_beeper();
            step();
        }else if(right_is_blocked()){
            if(beepers_present()){
                break;
            }
            turn_left();
            put_beeper();
            step();
            continue;
        }
    }
}

void find_center(){

    
    while(beepers_in_bag()){
        if(beepers_present() && front_is_clear()){
            pick_beeper();
            if(beepers_present()){
                pick_beeper();
                if(facing_west()){
                    turn_right();
                    break;
                }else{
                    turn_left();
                    break;
                }
            }
            
            turn_around();
            
            step();
            if(beepers_present()){
                pick_beeper();
                if(facing_west()){
                    turn_right();
                    break;
                }else{
                    turn_left();
                    break;
                }
            }
            put_beeper();
            step();
            continue;
        }else if(beepers_present() && front_is_blocked()){
            pick_beeper();
            if(beepers_present()){
                if(facing_west()){
                    turn_right();
                    break;
                }else{
                    turn_left();
                    break;
                }
            }else{
                put_beeper();
            }
            
            turn_around();
            step();
            if(beepers_present()){
                pick_beeper();
                if(facing_west()){
                    turn_right();
                    break;
                }else{
                    turn_left();
                    break;
                }
            }
            put_beeper();
            step();
            continue;
        }
        step();
    }


}


void go_to_corner(){
    
        if(facing_north()){
            turn_around();
        }else if(facing_south()){
            turn_right();
            turn_left();
        }else if(facing_west()){
            turn_left();
        }else if(facing_east()){
            turn_right();
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


