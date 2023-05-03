// Braedon Behnke
// Akiel Aries
//


// check schedule algo, 

// if FCFS
    // select first/next available process
    
// if SRTF
    // create large number for default for shortest runtime encountered

    // while process is available && process is shorter than the current selection

    // at end of while loop select process with shortest runtime

// if RR
    // set static variable for the working pointer

    // if wkgPTR == NULL
        // wkgPTR = headPTR
        
        // while state is not READY && wkgPTR != NULL
            // advance to next PCB

// at the very end of func, return PCB that was selected


// execute CPU
    // checking scheduler algo

    // while check for interrupts, cycles done, and quantum time
        // if interrupt
            // resolve interrupt
        // quantum time
            // select new process


