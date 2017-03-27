#ifndef TableCell_H
#define TableCell_H

class TableCell {
public:
	static TableCell ErrorCell() noexcept;

	TableCell() noexcept;
	TableCell(const int value) noexcept;
	TableCell(const double value) noexcept;

	bool isEmpty() const noexcept;
	bool isInteger() const noexcept;
	bool isDouble() const noexcept;
	bool isString() const noexcept;
	bool isError() const noexcept;

	int toInteger() const noexcept;

protected:
	enum TableCellType {
		Empty,
		Integer,
		Double,
		Error
	};

	union TableCellValue {
		void* noValue;
		int integerValue;
		double doubleValue;
	};

	TableCellType cellType;
	TableCellValue cellValue;
};

#endif
