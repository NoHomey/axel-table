#include "ErrorCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"

SINGLETON_CELL_SPEC(ErrorCell, 7, "constantly returns 7 (length of \"#ERROR!\")")