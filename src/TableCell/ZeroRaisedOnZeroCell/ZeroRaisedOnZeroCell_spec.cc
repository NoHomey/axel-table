#include "ZeroRaisedOnZeroCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"

SINGLETON_CELL_SPEC(ZeroRaisedOnZero, 5, "constantly returns 5 (length of \"#0^0!\")")