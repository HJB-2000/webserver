#include "config.hpp"

/*
    *open_configfile
        * use state to determin :
            * is a richable valid file
            * is a regulare file
            * is a text based {ascii} file
    * open the file in the in mode in the fstream
        * check if the file is opened 
        * 
*/

inline bool isAsciiFile(const std::string& file_name)
{
    std::ifstream conf(file_name.c_str(), std::ios::binary);
    if (!conf.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        exit(1);
    }
    char c;
    while (conf.get(c)) {
        if (static_cast<unsigned char>(c) > 127) {
            return false;
        }
    }
    conf.close();
    return true;
}

void open_configfile(std::string file_name)
{
    struct stat buf;
    
    if (stat(file_name.c_str(), &buf) < 0 || access(file_name.c_str(), F_OK) < 0 || access(file_name.c_str(), R_OK) < 0)
    {
            std::cerr << "Config File Error: " << strerror(errno) << " (errno " << errno << ")" << std::endl;
            exit(errno);
    }
    if (S_ISREG(buf.st_mode) == 0 || !isAsciiFile(file_name))
    {
        std::cerr << file_name << " : is not a regulare file" << std::endl;
        exit(1);
    }
    std::fstream conf(file_name.c_str(), std::ios::in);
    if (!conf.is_open())
    {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        exit(1);
    }
// now i have the file checked and opened .
// this is design choice work from the heap to avoid the stack frames dependency
    // config *confobj = new config;
    /*====================end of the function open_configfile*============================*/
    // conf.close();
    /*this function should return to the main the core of the server
        the created instance of the config object that contain all the rules set to the server
        to run under it.
    */
    using namespace std;
    string line;
    for(int i = 0; i < 20; i++)
    {
        getline(conf, line);
        cout << line << endl;
    }

    return;
}



int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "usage: ./server {name}.conf" << std::endl;
        return 1;
    }
    std::string file_name = av[1];
    open_configfile(file_name);

    std::fstream fs;
    fs.open((const char *)av[1], std::fstream::in);

    if (fs.is_open())
        fs.close();
    return 0;
}