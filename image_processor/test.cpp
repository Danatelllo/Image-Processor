#include <catch.hpp>
#include "Image.h"
#include "Write_and_Read.h"
TEST_CASE("ReadFile") {
    Image photo;
    bool catch_error = false;
    std::string test_bad_path = "Meow";
    try {
        ReadFile(test_bad_path);
    } catch (std::exception& e) {
        catch_error = true;
    }
    REQUIRE(catch_error == true);
}
