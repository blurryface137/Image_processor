#include "Handler.h"

Handler* AbstractHandler::SetNext(Handler* h){
	next = h;
	return next;
}

void AbstractHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	if(next)
		next->Handle(bitmap, argc, argv);
}

void CropHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-crop") == 0){
			if (i + 2 >= argc){
				std::cout << "Сrop: Некорректное количество аргументов" << std::endl;
				return;
			}
			int w, h;
			w = atoi(argv[i + 1]);
			h = atoi(argv[i + 2]);
			if(w <= 0 || h <= 0) {
				std::cout << "Сrop: Некорректное значение аргументов" << std::endl;
				return;
			}
			CropFilter f(w, h);
			f.apply(bitmap);
			std::cout << "crop " << w << "x" << h << ": OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}

void GrayScaleHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-gs") == 0){
			GrayScaleFilter f;
			f.apply(bitmap);
			std::cout << "grayscale: OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}

void NegativeHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-neg") == 0){
			NegativeFilter f;
			f.apply(bitmap);
			std::cout << "negative: OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}

void PosterizeHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-poster") == 0){
			if (i + 1 >= argc){
				std::cout << "Posterize: Некорректное количество аргументов" << std::endl;
				return;
			}
			int val = atoi(argv[i + 1]);
			if(val <= 0) {
				std::cout << "Posterize: Некорректное значение аргументов" << std::endl;
				return;
			}

			PosterizeFilter f(val);
			f.apply(bitmap);
			std::cout << "posterize: OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}

void CrystalizeHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-crystal") == 0){
			if (i + 1 >= argc){
				std::cout << "Crystalize: Некорректное количество аргументов" << std::endl;
				return;
			}
			int val = atoi(argv[i + 1]);
			if(val <= 0) {
				std::cout << "Crystalize: Некорректное значение аргументов" << std::endl;
				return;
			}

			CrystalizeFilter f(val);
			f.apply(bitmap);
			std::cout << "crystalize: OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}

void SharpeningHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-sharp") == 0){
			SharpeningFilter f;
			f.apply(bitmap);
			std::cout << "sharpening: OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}

void EdgeDetectionHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-edge") == 0){
			if (i + 1 >= argc){
				std::cout << "EdgeDetection: Некорректное количество аргументов" << std::endl;
				return;
			}
			int threshold = atoi(argv[i + 1]);
			if(threshold <= 0 || threshold > 255) {
				std::cout << "EdgeDetection: Некорректное значение аргументов" << std::endl;
				return;
			}
			EdgeDetectionFilter f(threshold);
			f.apply(bitmap);
			std::cout << "edge detection: OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}

void GaussianBlurHandler::Handle(Bitmap* bitmap, int argc, char **argv){
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-blur") == 0){
			if (i + 1 >= argc){
				std::cout << "GaussianBlur: Некорректное количество аргументов" << std::endl;
				return;
			}
			double sigma = std::stod(argv[i + 1]);
			if(sigma <= 0) {
				std::cout << "GaussianBlur: Некорректное значение аргументов" << std::endl;
				return;
			}
			GaussianBlurFilter f(sigma);
			f.apply(bitmap);
			std::cout << "gaussian blur: OK" << std::endl;
			break;
		}
	}
	AbstractHandler::Handle(bitmap, argc, argv);
}
