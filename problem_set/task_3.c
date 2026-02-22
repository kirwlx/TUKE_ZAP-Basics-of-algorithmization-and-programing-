#include <superkarel.h>
void turn_right();
void turn_around();
void check_the_size();
void find_shoulders();
void put_left();
void set_closet();
void detected();
void check_the_line();
void final_fill();


int main(){                  //MAIN MAIN MAIN MAIN
    
    turn_on("task_3.kw");
    set_step_delay(100);
    check_the_size();

    


    find_shoulders();

    turn_left();
    while(front_is_clear()){
        step();
    }
    turn_left();

    while(left_is_clear()){
        put_left();
    }
                turn_around();
                step();
                turn_around();
     while(front_is_clear()){           //FOR THE 1 size
            step();
            if(beepers_present()){
                pick_beeper();
                turn_around();
                while(front_is_clear()){
                    step();
                }
                put_beeper();
                turn_around();
                continue;
            }
        }
        turn_around();
        while(front_is_clear()){
            step();
        }
        turn_left();
        while(front_is_clear()){
            step();
        }
        turn_left();
        
        
        
    while(left_is_clear()){
        set_closet();
        if(front_is_blocked() && facing_east()){
            break;
        }
    }
    turn_around();
    while(front_is_clear()){
        step();
    }
    turn_around();
    




    // turn_around();
    // find_final();
    

    turn_off();
    return 0;
}

void final_fill(){
    while(front_is_clear()){
        step();
        if(beepers_present()){
            turn_right();
            while(front_is_clear()){
                step();
                if(beepers_present()){
                    turn_around();
                    while(front_is_clear()){
                        step();
                        if(no_beepers_present()){
                            put_beeper();
                        }
                    }
                    turn_right();
                    return;
                }
            }
            if(front_is_blocked()){
                turn_around();
                while(front_is_clear()){
                    step();
                }
                turn_right();
            }
        }
    }
}



void find_final(){
    while(beepers_in_bag()){
        if(front_is_clear()){
            step();
            turn_left();
        }else{
            return;
        }
        
        while(front_is_clear()){
            if(no_beepers_present()){
            step();
            }else{
                turn_around();
                while(front_is_clear()){
                    step();
                }
                turn_around();
                return;
            }
        }
        turn_around();
        while(front_is_clear()){
            step();
        }
        turn_left();
        
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

void check_the_size(){
    while (front_is_clear()){
        step();
        if(beepers_present()){
            turn_right();
            while(beepers_present()){
                pick_beeper();
                
                if(front_is_clear()){
                    step();
                    if(no_beepers_present()){
                    turn_around();
                    step();
                    turn_around();
                }
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



void find_shoulders(){
    turn_around();
    while(front_is_clear()){
        if(right_is_blocked()){
            step();
        }else{ 
            turn_right();
            step();
            put_beeper();
            turn_around();
            step();
            turn_right();
            if(front_is_clear()){
                step();
            }
        }
    }
    if(right_is_blocked()){
            step();
        }else{ 
            turn_right();
            step();
            put_beeper();
            turn_around();
            step();
            turn_right();
            if(front_is_clear()){
                step();
            }
        }
}


void put_left(){
        while(front_is_clear()){
            step();
            if(left_is_blocked()){
                
                return;
            }
            if(beepers_present()){
                pick_beeper();
                turn_around();
                while(front_is_clear()){
                    step();
                }
                put_beeper();
                turn_around();
                continue;
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




void set_closet(){
    set_step_delay(100);

    if(beepers_present()){
        pick_beeper();
        step();
        if(left_is_blocked()){
            while(front_is_clear()){
                step();
            }
            turn_around();
            while(front_is_clear()){
                if(beepers_present()){
                    step();
                }else{
                    turn_right();
                    if(front_is_clear()){
                        step();
                    }
                    if(beepers_present()){
                        turn_around();
                        step();
                        turn_right();
                        step();
                    }else{
                        put_beeper();
                        turn_left();
                        while (front_is_clear()){
                            step();
                        }
                        if(beepers_present()){
                            turn_around();
                            set_closet();
                        }else{
                            turn_right();
                            while(front_is_clear()){
                                step();
                            }
                            turn_right();
                            while(front_is_clear()){
                                step();
                            }
                            if(right_is_clear()){
                                turn_right();
                                step();
                                turn_right();
                                if(beepers_present()){
                                    pick_beeper();
                                }
                                while(front_is_clear()){
                                    
                                    step();
                                    if(beepers_present()){
                                        pick_beeper();
                                    }
                                }

                            }else{
                                turn_around();
                                while(front_is_clear()){
                                    
                                    step();
                                    if(beepers_present()){
                                        pick_beeper();
                                    }
                                }
                            }
                            turn_left();
                            step();
                            turn_left();

                            while(beepers_in_bag()){
                                final_fill();
                            }
                        
                            return;
                        }
                        

                    }
                }
            }
            
        }else{
            while(front_is_clear()){
                // if(right_is_blocked()){
                //     return;
                // }
                step();
            }
            put_beeper();
            turn_left();
            
            while(front_is_clear()){
                step();   
                detected();   
            }
            put_beeper();
            turn_around();
            while(front_is_clear()){
                step();
                if(beepers_present()){
                    turn_right();
                    while(front_is_clear()){
                        step();
                    }
                    turn_around();
                    set_closet();
                }
            }
        }
    }else{
        step();
        if((left_is_blocked()&&facing_east()) || (right_is_blocked()&&facing_west())){

            //THE HELL STARTED

              turn_around();
    while(front_is_clear()){
        step();
    }
    turn_right();
    while(front_is_clear()){
        step();
    }
    
    turn_right();
    while(front_is_clear()){
        step();
    }
    if(right_is_clear()){
        turn_right();
        step();
        turn_right();
        while(front_is_clear()){
            if(beepers_present()){
                pick_beeper();
            }
            step();
        }
    }else{
        turn_around();
        while(front_is_clear()){
            if(beepers_present()){
                pick_beeper();
            }
            step();
        }
    }
    if(beepers_present()){
        pick_beeper();
    }
    turn_left();
    step();
    turn_left();
    while(beepers_in_bag()){
        final_fill();
    }
    
    return;





    // turn_around();
    // find_final();
                       //IF NO 1
            return;
        }else{
            turn_around();
            if(front_is_clear()){
                while(front_is_clear()){
                    step();
                }
            }
            if(front_is_clear()){
                step();
            }
            
            turn_around();
            turn_left();
            step();
            turn_right();
            set_closet();
        }
        
    }
}





void detected(){
     if(beepers_present()){
                turn_around();
                while(front_is_clear()){
                    step();
                    if(beepers_present()){
                        pick_beeper();
                        turn_right();
                        step();
                        turn_right();
                        put_beeper();
                        while(front_is_clear()){
                            step();
                            if(beepers_present()){
                                detected();
                            }
                        }
                    }
                    
                }
                
    }
}


void check_the_line(){
    while(front_is_clear()){
        step();
        if(left_is_blocked()){
            set_closet();
            return;
        }
    }
    turn_around();
    while(front_is_clear()){
        step();
    }
    turn_around();
}

