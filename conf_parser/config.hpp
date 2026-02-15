#pragma onece
#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>



class config
{
    private:
        /*
            * this should contain all the setings that are going to be set by the config file
            * in the disgne i am thinking in maybe all create lot of object conatin diffrent data state 
            *   that are going to be inhireted by this class so i need to make sure that design patter be flixible
            *   that we can integrite any discovered state
        */
    public:
        config();
        config(const config& obj);
        /*
            * i dont thin i am gonna need to provid an assignemnt operator
                but in all cases i'll provide i way to refuse it
        */

    ~config();
};

// this is the master function
    config configfile_parser();

#endif