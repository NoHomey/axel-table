#ifndef TableCell_H
#define TableCell_H

class TableCell {
public:
	TableCell();
	TableCell(int value);

	bool isEmpty() const;
	bool isInteger() const;
	bool isDouble() const;
	bool isString() const;
	bool isError() const;

protected:
	enum TableCellType {
		Empty,
		Integer
	};

	TableCellType cellType;
};

#endif
