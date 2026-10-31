#include <iostream>
#include "../../include/model/moves.h"

bool Move::operator==(const Move &second) {
    return (this->from == second.from) && (this->to == second.to);
}