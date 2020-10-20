#include <iostream>
#include <getopt.h>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <set>

template <class Container>
void split2(const std::string& str, Container& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

struct globalArgs{
    std::string input_file = "input.txt";   /* -i --input   */
    std::string output_file = "output.txt"; /* -o --output  */
    bool flag = false;                      /* -f --flag*/
    int value;                              /* -v --value   */
    int* list;                              /* -l --list    */
    int list_size = 0;
} globalArgs;

static const struct option longOpts[] {
    {"help", no_argument, NULL, 'h'},
    {"input", optional_argument, NULL, 'i'},
    {"output", optional_argument, NULL, 'o'},
    {"value", required_argument, NULL, 'v'},
    {"list", required_argument, NULL, 'l'},
    {"flag", no_argument, NULL, 'f'},
    {NULL, no_argument, NULL, 0},
};

static const char *optString = "i::o::v:l:h?";

int* strToArray(std::string s, int& list_size){
    int size = std::count(s.begin(), s.end(), ',')+1;
    int arr[size]; 
    int index = 0;
    for (int i=0;i<s.size();i++){
        if (s[i] == ','){
            index++;
            continue;
        }
        arr[index] = (arr[index]*10)+s[i]-48;
    }
    list_size = size;
    int *p = arr;
    return p;
}

bool contains(std::set<char> flags, char s){
    return flags.find(s) != flags.end();
}

int main(int argc, char* argv[]){
    int option_index = -1;

    std::set<char> flags;
    char opt;
    while ((opt = getopt_long(argc, argv, optString, longOpts, &option_index))!=-1)
    {   
        switch (opt)
        {
        case 'h':
            if(!contains(flags, 'h')){
                flags.insert('h');
                std::cout << "Created by Smirnov Nazar\n"
                        << "-h    --help      help\n"
                        << "-i    --input     input_file\n"
                        << "-o    --output    output_file\n"
                        << "-v    --value     value\n"
                        << "-l    --list      list of args\n";
            }
            break;
        case 'i':
            if(!contains(flags, 'i')){
                flags.insert('i');
                std::cout << "Input";
                if (optarg != NULL){
                    globalArgs.input_file = optarg;
                    std::cout<< ":\t" << globalArgs.input_file;
                }
                std::cout<<std::endl;
            }
            break;
        case 'o':
            if(!contains(flags, 'o')){
                flags.insert('o');
                std::cout << "Output";
                if(optarg != NULL){
                    globalArgs.output_file = optarg;
                    std::cout << ":\t" << globalArgs.output_file;
                }
                std::cout<<std::endl;
            }
            break;
        case 'v':
            if(!contains(flags, 'v')){
                flags.insert('v');
                globalArgs.value = std::stoi(optarg);
                std::cout<< "Value:\t" << globalArgs.value << std::endl;
            }
            break;
        case 'l':
            if (!contains(flags, 'l')){
                flags.insert('l');
                globalArgs.list = strToArray(optarg, globalArgs.list_size);
                std::cout << "List:\t" << optarg << std::endl;
            }
            break;
        default:
            break;
        }    
    }
    
    return 0;
}