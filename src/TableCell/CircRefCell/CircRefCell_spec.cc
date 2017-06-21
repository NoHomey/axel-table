#include "CircRefCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "../ErrorCell/ErrorCellSpec.mcrs"

SINGLETON_CELL_SPEC(CircRefCell, 9, "constantly returns 9 (length of \"#CIRCREF!\")")

ERROR_CELL_SPEC(CircRefCell, "constantly returns \"#CircRef!\"", "#CIRCREF!", 9)