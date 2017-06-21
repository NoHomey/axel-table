#include "DivByZeroCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"

SINGLETON_CELL_SPEC(DivByZeroCell, 7, "constantly returns 7 (length of \"#DIV/0!\")")