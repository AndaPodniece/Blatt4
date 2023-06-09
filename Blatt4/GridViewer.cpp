#include "GridViewer.h"
#include <stdexcept>

using namespace std;

GridViewer::GridViewer(string titleP, int size, int cellSizeP) : cellSize(cellSizeP), gridSize(size / cellSizeP), ViewPortGL(titleP, size, size)
{
	if (floor(log2(size)) != ceil(log2(size)) || size < 4 || size> 1024)
	{
		throw logic_error("size has to be power of 2 and between 4 to 1034");
	}
	if (floor(log2(cellSizeP)) != ceil(log2(cellSizeP)) || cellSizeP < 4 || cellSizeP > 1024 || cellSizeP > size)
	{
		throw logic_error("cellSizeP has to be power of 2  and between 4 to 1024 and lower then size");
	}

	content = new unsigned int[gridSize * gridSize];
	memset(content, 0, gridSize * gridSize * sizeof(unsigned int));
}

GridViewer::~GridViewer()
{
	delete[]content;
}

Color GridViewer::colorFor(unsigned int value) {
	return Color((value & 0xFF000000) >> 24, (value & 0xFF0000) >> 16, (value & 0xFF00) >> 8);
}

void GridViewer::prepareCell(int x, int y) {
	Color color = colorFor(content[x + y * gridSize]);
	prepareBlock(x * cellSize - 1, y * cellSize, cellSize + 1, cellSize + 1, color.getRed(), color.getGreen(), color.getBlue());
}

void GridViewer::prepareCellBorder(int x, int y) {
	Color color = colorFor(content[x + y * gridSize]);
	int amount = 80;
	int offset = static_cast<float>(cellSize * 0.1f);

	color.lighten(amount);
	prepareBlock(x * cellSize - 1 + offset, y * cellSize, offset + 1, cellSize - 2 * offset + 1, color.getRed(), color.getGreen(), color.getBlue());
	prepareBlock(x * cellSize - 1 + offset, y * cellSize + cellSize - offset, cellSize - 2 * offset + 1, offset + 1, color.getRed(), color.getGreen(), color.getBlue());
	color.darken(amount);
	prepareBlock(x * cellSize - 1, y * cellSize + cellSize - offset, offset + 1, offset + 1, color.getRed(), color.getGreen(), color.getBlue());

}

unsigned int GridViewer::getCell(int x, int y) {
	if (x< 0 || x>gridSize || y < 0 || y > gridSize)
	{
		throw std::logic_error("position out of range");
	}
	return content[x + y * gridSize + x];
}


void GridViewer::setCell(int x, int y, unsigned int value)
{
	if (x< 0 || x>gridSize || y < 0 || y > gridSize)
		throw std::logic_error("position out of range");
	content[y * gridSize + x] = value;
}

void GridViewer::draw() {
	int count = 0;
	static const int maxPreparedTriangles = getMaxNumberOfPreparedTriangles();
	static const int maxPreparedLines = getMaxNumberOfPreparedLines();
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			prepareCell(x, y);
			prepareCellBorder(x, y);
			count++;
			if (maxPreparedTriangles - 1 <= count*2 || maxPreparedLines - 3 <= count * 4) {
				sendTriangles();
				sendLines();
				sendPixels();
				count = 0;
			}
		}
	}
	if (count > 0) {
		sendTriangles();
		sendLines();
		sendPixels();
	}
}

int GridViewer::getGridSize() {
	return gridSize;
}
