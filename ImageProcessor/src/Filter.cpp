#include "Filter.h"

CropFilter::CropFilter(int width, int height)
	: w(width), h(height){
}

void CropFilter::apply(Bitmap* bitmap){
	w = w < bitmap->info.biWidth ? w : bitmap->info.biWidth;
	h = h < bitmap->info.biHeight ? h : bitmap->info.biHeight;

	if(w == bitmap->info.biWidth && h == bitmap->info.biHeight)
		return;

	RGB* data = (RGB*)malloc(sizeof(RGB) * w * h);
	RGB* src = bitmap->data + bitmap->info.biWidth * bitmap->info.biHeight - bitmap->info.biWidth;
	RGB* dst = data + w * h - w;

	for(int i = 0; i < h; i++){
		memcpy((char*)dst, (char*)src, sizeof(RGB) * w);
		src -= bitmap->info.biWidth;
		dst -= w;
	}

	free(bitmap->data);
	bitmap->data = data;
	bitmap->info.biWidth = w;
	bitmap->info.biHeight = h;
	bitmap->head.bfSize = sizeof(bitmap->head) + sizeof(bitmap->info) + sizeof(RGB) * w * h;
	bitmap->info.biSizeImage = sizeof(RGB) * w * h;
}

void GrayScaleFilter::apply(Bitmap* bitmap){
	for(RGB* ptr = bitmap->data; ptr < bitmap->data + bitmap->info.biWidth * bitmap->info.biHeight; ptr++){
		BYTE new_value = (BYTE)(0.299 * ptr->R + 0.587 * ptr->G + 0.114 * ptr->B);
		ptr->R = new_value;
		ptr->G = new_value;
		ptr->B = new_value;
	}
}

void NegativeFilter::apply(Bitmap* bitmap){
	for(RGB* ptr = bitmap->data; ptr < bitmap->data + bitmap->info.biWidth * bitmap->info.biHeight; ptr++){
		ptr->R = 255 - ptr->R;
		ptr->G = 255 - ptr->G;
		ptr->B = 255 - ptr->B;
	}
}

PosterizeFilter::PosterizeFilter(int value) :
	value(value) {
}

void PosterizeFilter::apply(Bitmap* bitmap){
	for(RGB* ptr = bitmap->data; ptr < bitmap->data + bitmap->info.biWidth * bitmap->info.biHeight; ptr++){
		RGB color = *ptr;
		color.R = (color.R - (color.R % value));
		color.G = (color.G - (color.G % value));
		color.B = (color.B - (color.B % value));

		ptr->R = color.R;
		ptr->G = color.G;
		ptr->B = color.B;
	}
}

CrystalizeFilter::CrystalizeFilter(int count) :
	count(count) {
}

void CrystalizeFilter::apply(Bitmap* bitmap){
	int w = bitmap->info.biWidth, h = bitmap->info.biHeight;

	point2D* seeds = (point2D*)malloc(sizeof(point2D) * count);
	for(int i = 0; i < count; i++){
		(seeds + i)->x = rand() % w;
		(seeds + i)->y = rand() % h;
	}

	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			RGB* pixel = bitmap->data + i * w + j;
			point2D* seed_coord = get_nearest(seeds, j, i);
			RGB* seed = bitmap->data + seed_coord->y * w + seed_coord->x;
			pixel->R = seed->R;
			pixel->G = seed->G;
			pixel->B = seed->B;
		}
	}

	free(seeds);
}

point2D* CrystalizeFilter::get_nearest(point2D* seeds, int x, int y){
	if(count < 2) return seeds;
	point2D* nearest = seeds;
	double min = lenght(nearest->x, nearest->y, x, y);
	for(point2D* ptr = seeds + 1; ptr < seeds + count; ptr++){
		double curr = lenght(ptr->x, ptr->y, x, y);
		if(curr < min){
			nearest = ptr;
			min = curr;
		}
	}
	return nearest;
}

double CrystalizeFilter::lenght(int x1, int y1, int x2, int y2){
	return std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void MatrixFilter::multiply(Bitmap* bitmap){
	RGB* data = (RGB*)malloc(sizeof(RGB) * bitmap->info.biHeight * bitmap->info.biWidth);
	LONG w = bitmap->info.biWidth;
	LONG h = bitmap->info.biHeight;
	for(int i = 0; i < bitmap->info.biHeight; i++){
		for(int j = 0; j < bitmap->info.biWidth; j++){
			RGB* center = bitmap->data + i * w + j;
			RGB* up_left = i < h - 1 && j > 0 ? center + w - 1 : center;
			RGB* up = i < h - 1 ? center + w : center;
			RGB* up_right = i < h - 1 && j < w - 1 ? center + w + 1 : center;
			RGB* right = j < w - 1 ? center + 1 : center;
			RGB* bottom_right = i > 0 && j < w - 1 ? center - w + 1 : center;
			RGB* bottom = i > 0 ? center - w : center;
			RGB* bottom_left = i > 0 && j > 0 ? center - w - 1 : center;
			RGB* left = j > 0 ? center - 1 : center;

			double R = Matrix[0][0] * up_left->R + 	 Matrix[0][1] * up->R + 	Matrix[0][2] * up_right->R +
					 Matrix[1][0] * left->R +   	 Matrix[1][1] * center->R + Matrix[1][2] * right->R +
					 Matrix[2][0] * bottom_left->R + Matrix[2][1] * bottom->R + Matrix[2][2] * bottom_right->R;

			double G = Matrix[0][0] * up_left->G + 	 Matrix[0][1] * up->G + 	Matrix[0][2] * up_right->G +
					 Matrix[1][0] * left->G +   	 Matrix[1][1] * center->G + Matrix[1][2] * right->G +
					 Matrix[2][0] * bottom_left->G + Matrix[2][1] * bottom->G + Matrix[2][2] * bottom_right->G;

			double B = Matrix[0][0] * up_left->B + 	 Matrix[0][1] * up->B + 	Matrix[0][2] * up_right->B +
					 Matrix[1][0] * left->B +   	 Matrix[1][1] * center->B + Matrix[1][2] * right->B +
					 Matrix[2][0] * bottom_left->B + Matrix[2][1] * bottom->B + Matrix[2][2] * bottom_right->B;

			RGB* new_pixel = data + i * w + j;
			new_pixel->R = R < 0 ? 0 : R > 255 ? 255 : R;
			new_pixel->G = G < 0 ? 0 : G > 255 ? 255 : G;
			new_pixel->B = B < 0 ? 0 : B > 255 ? 255 : B;
		}
	}
	free(bitmap->data);
	bitmap->data = data;
}

SharpeningFilter::SharpeningFilter(){
	Matrix[0][0] = 0.0; Matrix[0][1] = -1.0; Matrix[0][2] = 0.0;
	Matrix[1][0] =-1.0; Matrix[1][1] =  5.0; Matrix[1][2] =-1.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = -1.0; Matrix[2][2] = 0.0;
}

void SharpeningFilter::apply(Bitmap* bitmap){
	multiply(bitmap);
}

EdgeDetectionFilter::EdgeDetectionFilter(BYTE threshold){
	Matrix[0][0] = 0; Matrix[0][1] = -1; Matrix[0][2] = 0;
	Matrix[1][0] =-1; Matrix[1][1] =  4; Matrix[1][2] =-1;
	Matrix[2][0] = 0; Matrix[2][1] = -1; Matrix[2][2] = 0;
	this->threshold = threshold;
}

void EdgeDetectionFilter::apply(Bitmap* bitmap){
	for(RGB* ptr = bitmap->data; ptr < bitmap->data + bitmap->info.biWidth * bitmap->info.biHeight; ptr++){
		BYTE new_value = (BYTE)(0.299 * ptr->R + 0.587 * ptr->G + 0.114 * ptr->B);
		ptr->R = new_value;
		ptr->G = new_value;
		ptr->B = new_value;
	}
	multiply(bitmap);
	for(RGB* ptr = bitmap->data; ptr < bitmap->data + bitmap->info.biWidth * bitmap->info.biHeight; ptr++){
		ptr->R = ptr->R > threshold ? 255 : 0;
		ptr->G = ptr->G > threshold ? 255 : 0;
		ptr->B = ptr->B > threshold ? 255 : 0;
	}
}

GaussianBlurFilter::GaussianBlurFilter(double sigma) :
		sigma(sigma){
}

void GaussianBlurFilter::apply(Bitmap* bitmap){
	double sum = 0.0;
	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			Matrix[i + 1][j + 1] = 1/(2 * M_PI * sigma * sigma) *
					exp(-(i*i + j*j)/(2 * sigma * sigma));
			sum += Matrix[i + 1][j + 1];
		}
	}
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			Matrix[i][j] /= sum;
		}
	}
	multiply(bitmap);
}
