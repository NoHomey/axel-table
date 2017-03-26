#ifndef TableCell_H
#define TableCell_H

class TableCell {
public:
	TableCell();
	bool isEmpty() const;
	bool isInteger() const;
	bool isDouble() const;
	bool isString() const;
	bool isError() const;
};

#endif
