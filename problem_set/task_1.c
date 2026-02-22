#include <superkarel.h>

void turn_right();
void turn_around();
void over_stair_left();
void over_stair_right();
void go_left();


int main(){
    set_step_delay(200);

    turn_on("task_14.kw");

    go_left();


    while(no_beepers_in_bag()){
        over_stair_right();
    }

        turn_around();
    
    while(beepers_in_bag()){   
        over_stair_left();
        if (beepers_present()){
            pick_beeper();
            break;
        }
    }
    while (not_facing_west()){
        turn_left();
    }
    

    


    turn_off();

    return 0;
}


void turn_right()
{
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(200);
}

void turn_around(){
    turn_left();
    turn_left();
}


void go_left(){
    put_beeper();
    
            if(front_is_clear()){
                while(front_is_clear()){
                step();
                }
                if(beepers_present()){
            pick_beeper();
        }
            }
            
            
            turn_left();
            
            while(right_is_blocked()){
                step();
            }
            turn_right();
            do{
                step();
            }while(right_is_blocked());
                turn_right();
                while(front_is_clear()){
                    step();
                }
                turn_left();
}


void over_stair_right(){
        if(front_is_clear()){
            while(front_is_clear()){
                step();
            }
        }
        if(beepers_present()){
            pick_beeper();
        }
    while(no_beepers_in_bag()){
        turn_left();
    
    while(right_is_blocked()){
        step();
        if(beepers_present()){
            pick_beeper();
            }  
    }
    turn_right();
    do {
        if(beepers_present()){
            pick_beeper();
            }  
        step();
         
    } while(right_is_blocked());
    turn_right();
    step();
    while(front_is_clear()){
        if(beepers_present()){
            pick_beeper();
            }   
        step();
    }

    if(front_is_blocked()){
        if(beepers_present()){
            pick_beeper();
            }   
        turn_left();
    }
    if(front_is_clear()){
        while(front_is_clear()){
        if(beepers_present()){
            pick_beeper();
            break;
            } 
            step();
              
        }
    }
     
    if(beepers_present()){
        pick_beeper();
    }
    }
        
}


    


// void over_stair_right(){
//     if(front_is_clear()){
//         while(front_is_clear()){
//             step();
//             if(beepers_present()){
//                 pick_beeper();
//                 break;
//             }
//         }
//     }
//     if(beepers_present()){
//                 pick_beeper();
                
//             }
//     turn_left();
//     while(right_is_blocked()){
//         if(front_is_blocked() && right_is_blocked()){
//             break;
//         }
//         step();
//         if(beepers_present()){
//             pick_beeper();
//             }  
//     }
//     if(front_is_blocked()&&right_is_blocked()){
//         turn_around();
//         while(front_is_clear()){
//             step();
//         }
//         turn_right();
        
//     }else{
//         turn_right();
//     do {
//         if(beepers_present()){
//             pick_beeper();
//             }  
//         step();
         
//     } while(right_is_blocked());
//     turn_right();
//     step();
//     while(front_is_clear()){
//         if(beepers_present()){
//             pick_beeper();
//             }   
//         step();
//     }

//     if(front_is_blocked()){
//         if(beepers_present()){
//             pick_beeper();
//             }   
//         turn_left();
//     }
//      while(front_is_clear()){
//         if(beepers_present()){
//             pick_beeper();
//             break;
//             } 
//             step();
              
//         }

//     }
    
// }

void over_stair_left(){
    if(front_is_clear()){
        while(front_is_clear()){
            if(beepers_present()){
                return;
            }
            step();
        }
        
    }
    turn_right();
    while (left_is_blocked()){
        step();
    }
    turn_left();

    do{
        step();
    }while(left_is_blocked());
    turn_left();
    while(front_is_clear()){
        step();
    }
    if(beepers_present()){
        return;
    }
    turn_right();
    while(front_is_clear()){
        if(beepers_present()){
                return;
            }
        step();
    }
    
}



