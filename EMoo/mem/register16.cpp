#include "register16.h"

Register16::Register16() : data(0)
{
}

const bool FlagsRegister::PARITY_TABLE[256] = {
    false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true
};
