#include "ZeroRaisedOnZeroCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "../ErrorCell/ErrorCellSpec.mcrs"

SINGLETON_CELL_SPEC(ZeroRaisedOnZeroCell, 5, "constantly returns 5 (length of \"#0^0!\")")

ERROR_CELL_SPEC(ZeroRaisedOnZeroCell, "constantly returns \"#0^0!\"", "#0^0!", 5)