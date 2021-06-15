#pragma once


static constexpr unsigned int SECTION_SIZE = 16u;


class Section final {
private:
	char block[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE] = { 0 };

public:
	Section();

	~Section();
};