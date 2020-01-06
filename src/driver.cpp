#include "driver.hpp"

#include "parser.hpp"

driver::driver() { }

int driver::parse(const std::string& f) {
    file_name = f;
    location.initialize(&file_name);

    scan_begin();

    yy::parser parse(*this);

    // int res = 
    parse();

    scan_end();

    // return res;
    return 0;
}