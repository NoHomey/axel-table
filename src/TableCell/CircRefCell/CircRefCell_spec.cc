#include "CircRefCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "../ErrorCell/ErrorCellSpec.mcrs"

SINGLETON_CELL_SPEC(CircRefCell, 9, "constantly returns 9 (length of \"#CircRef!\")")

ERROR_CELL_SPEC(CircRefCell)