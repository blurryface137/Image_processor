#include "Bitmap.h"

Bitmap::Bitmap() :
	data(nullptr) {
}

Bitmap::~Bitmap() {
	if(data != nullptr)
		free(data);
}


int Bitmap::read(const char *file_name){
	std::ifstream file(file_name, std::ios_base::binary);
	if(!file){
		std::cout << "File open error!" << std::endl;
		return 0;
	}

	file.read((char*)&head, sizeof(head));
	file.read((char*)&info, sizeof(info));

	if(head.bfType != 0x4D42) {
		std::cout << "Error! Unrecognized file format!" << std::endl;
		return 0;
	}

	if(info.biBitCount != 24) {
		std::cout << "Error! Incompatible count of bits per pixel!" << std::endl;
		return 0;
	}

	data = (RGB*)malloc(sizeof(RGB) * info.biWidth * info.biHeight);

	file.seekg(head.bfOffBits, file.beg);
	file.read((char*)data, sizeof(RGB) * info.biWidth * info.biHeight);

	file.close();
	return 1;
}

int Bitmap::write(const char *file_name){
	std::ofstream file(file_name, std::ios_base::binary);
	if(!file){
		std::cout << "File open error!" << std::endl;
		return 0;
	}

	file.write((char*)&head, sizeof(head));
	file.write((char*)&info, sizeof(info));
	file.write((char*)data, sizeof(RGB) * info.biWidth * info.biHeight);

	file.close();
	return 1;
}
