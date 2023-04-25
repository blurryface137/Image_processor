#ifndef HANDLER_H_
#define HANDLER_H_

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "Filter.h"

class Handler {
public:
	virtual ~Handler(){};
	virtual Handler* SetNext(Handler* h) = 0;
	virtual void Handle(Bitmap* bitmap, int argc, char **argv) = 0;
};

class AbstractHandler : public Handler{
private:
	Handler* next;
public:
	AbstractHandler() : next(nullptr){}
	virtual ~AbstractHandler(){};
	Handler* SetNext(Handler* h) override;
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class CropHandler : public AbstractHandler{
public:
	~CropHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class GrayScaleHandler : public AbstractHandler{
public:
	~GrayScaleHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class NegativeHandler : public AbstractHandler{
public:
	~NegativeHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class PosterizeHandler : public AbstractHandler{
public:
	~PosterizeHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class CrystalizeHandler : public AbstractHandler{
public:
	~CrystalizeHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class SharpeningHandler : public AbstractHandler{
public:
	~SharpeningHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class EdgeDetectionHandler : public AbstractHandler{
public:
	~EdgeDetectionHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};

class GaussianBlurHandler : public AbstractHandler{
public:
	~GaussianBlurHandler(){}
	void Handle(Bitmap* bitmap, int argc, char **argv) override;
};
#endif /* HANDLER_H_ */
