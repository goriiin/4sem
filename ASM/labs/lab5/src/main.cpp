#include <iostream>
#include <string>


void run(std::istream& in, std::ostream& out);

int main(){
   run(std::cin, std::cout);
}

extern "C"{
    const char* change_order(const char* input, size_t size, size_t num);
}

void run(std::istream& in, std::ostream& out){
    std::string input;
    std::cout << "Input str:\n";
    std::getline(std::cin, input);
    std::string run_opt;
    size_t n;

    std::cout << "enter run to run the program or something else to stop: ";
    std::cin >> run_opt;
    while (run_opt == "run"){
        std::cout << "enter num: ";
        std::cin >> n;

        change_order(input.c_str(), input.size(), n);

        std::cout << "enter run to run the program or something else to stop: ";
        std::cin >> run_opt;
    }
}