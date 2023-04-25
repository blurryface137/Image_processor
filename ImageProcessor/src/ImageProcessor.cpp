#include <iostream>
#include <iomanip>
#include <cstring>
#include "Handler.h"

void help();

int main(int argc, char **argv) {
	if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0)){
		help();
		return 0;
	}
	if(argc < 4){
		std::cout << "Отсутствуют обязательные параметры" <<std::endl;
		std::cout << "По команде «image_processor -help» или «image_processor -h» можно получить дополнительную информацию" <<std::endl;
		return 0;
	}

	CropHandler crop;
	GaussianBlurHandler gauss;
	GrayScaleHandler gray;
	NegativeHandler negative;
	PosterizeHandler poster;
	SharpeningHandler sharp;
	EdgeDetectionHandler edge;
	CrystalizeHandler crystal;

	crop.SetNext(&gauss)->
			SetNext(&gray)->
			SetNext(&negative)->
			SetNext(&sharp)->
			SetNext(&edge)->
			SetNext(&poster)->
			SetNext(&crystal);

	Bitmap bmp;

	if(!bmp.read(argv[1])){
		return 0;
	}

	crop.Handle(&bmp, argc, argv);

	if(!bmp.write(argv[2])){
		return 0;
	}

	std::cout << "Работа успешно завершена!" << std::endl;
	return 0;
}

void help(){
	std::cout << "Использование: image_processor ИСТОЧНИК НАЗНАЧЕНИЕ ПАРАМЕТРЫ" << std::endl;
	std::cout << "Считывает изображение в формате BMP из ИСТОЧНИК, применяет фильтры, "
			"указанные в ПАРАМЕТРЫ и сохраняет результат в НАЗНАЧЕНИЕ." << std::endl;
	std::cout << "Фильтры:" << std::endl;
	std::cout << std::left << std::setw(25) << "-crop width height" <<
			"Обрезает изображение до размеров width (int), height (int)" << std::endl;
	std::cout << std::left << std::setw(25) << "-gs" <<
			"Преобразует изображение в оттенки серого" << std::endl;
	std::cout << std::left << std::setw(25) << "-neg" <<
			"Преобразует изображение в негатив" << std::endl;
	std::cout << std::left << std::setw(25) << "-sharp" <<
			"Повышение резкости" << std::endl;
	std::cout << std::left << std::setw(25) << "-edge threshold" <<
			"Выделение границ. Пиксели, превысившие значение threshold (byte) "
			"окрашиваются в белый. Остальные в черный." << std::endl;
	std::cout << std::left << std::setw(25) << "-blur sigma" <<
			"Гауссово размытие с параметром sigma (double)" << std::endl;
	std::cout << std::left << std::setw(25) << "-poster value" <<
			"Постеризация изображения с параметром value (int)" << std::endl;
	std::cout << std::left << std::setw(25) << "-crystal count" <<
			"Кристаллизация изображения с параметром count (int). "
			"Count - количество кристаллов" << std::endl;
}
