#include "EmptyCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"

SINGLETON_CELL_SPEC(EmptyCell, 0, "constantly returns 0 (length of \"\")")