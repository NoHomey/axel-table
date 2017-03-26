#ifndef TableCell_H
#define TableCell_H

class TableCell {
public:
	TableCell();
	TableCell(const int value);
	TableCell(const double value);

	bool isEmpty() const;
	bool isInteger() const;
	bool isDouble() const;
	bool isString() const;
	bool isError() const;

protected:
	enum TableCellType {
		Empty,
		Integer,
		Double
	};

	TableCellType cellType;
};

#endif
