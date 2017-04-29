#pragma once

class TableCell {
public:
	static TableCell ErrorCell() noexcept;

	TableCell() noexcept;
	TableCell(const long long value) noexcept;
	TableCell(const double value) noexcept;

	bool isEmpty() const noexcept;
	bool isInteger() const noexcept;
	bool isDouble() const noexcept;
	bool isString() const noexcept;
	bool isError() const noexcept;

	long long toInteger() const noexcept;

protected:
	enum TableCellType {
		Empty,
		Integer,
		Double,
		Error
	};

	union TableCellValue {
		void* noValue;
		long long integerValue;
		double doubleValue;
	};

	TableCellType cellType;
	TableCellValue cellValue;
};
