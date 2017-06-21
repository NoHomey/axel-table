#include "RootOfNegNumCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "../ErrorCell/ErrorCellSpec.mcrs"

SINGLETON_CELL_SPEC(RootOfNegNumCell, 13, "constantly returns 13 (length of \"#\\ROOT(-num)!\")")

ERROR_CELL_SPEC(RootOfNegNumCell)