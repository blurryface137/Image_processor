#ifndef FILTER_H_
#define FILTER_H_

#include <stdlib.h>
#include <cstring>
#include <cmath>
#include "Bitmap.h"

typedef struct {
	int x, y;
} point2D;

class Filter {
public:
	virtual ~Filter(){}
	virtual void apply(Bitmap* bitmap) = 0;
};

class CropFilter : public Filter{
public:
	CropFilter(int width, int height);
	~CropFilter(){};
	void apply(Bitmap* bitmap) override;
private:
	int w, h;
};

class GrayScaleFilter : public Filter{
public:
	GrayScaleFilter(){};
	~GrayScaleFilter(){};
	void apply(Bitmap* bitmap) override;
};

class NegativeFilter : public Filter{
public:
	NegativeFilter(){};
	~NegativeFilter(){};
	void apply(Bitmap* bitmap) override;
};

class PosterizeFilter : public Filter{
public:
	PosterizeFilter(int value);
	~PosterizeFilter(){};
	void apply(Bitmap* bitmap) override;
private:
	int value;
};

class CrystalizeFilter : public Filter{
public:
	CrystalizeFilter(int count);
	~CrystalizeFilter(){};
	void apply(Bitmap* bitmap) override;
private:
	int count;
	point2D* get_nearest(point2D* seeds, int x, int y);
	double lenght(int x1, int y1, int x2, int y2);
};

class MatrixFilter : public Filter {
public:
	virtual ~MatrixFilter(){};
protected:
	double Matrix[3][3];
	void multiply(Bitmap* bitmap);
};

class SharpeningFilter : public MatrixFilter{
public:
	SharpeningFilter();
	void apply(Bitmap* bitmap) override;
};

class EdgeDetectionFilter : public MatrixFilter{
public:
	EdgeDetectionFilter(BYTE threshold);
	void apply(Bitmap* bitmap) override;
private:
	BYTE threshold;
};

class GaussianBlurFilter : public MatrixFilter{
public:
	GaussianBlurFilter(double sigma);
	~GaussianBlurFilter(){};
	void apply(Bitmap* bitmap) override;
private:
	double sigma;
};
#endif /* FILTER_H_ */
