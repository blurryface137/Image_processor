#define BOOST_TEST_MODULE FiltersTests
#include <boost/test/unit_test.hpp>

#include "Bitmap.h"
#include "Filter.h"

BOOST_AUTO_TEST_SUITE(FiltersTests)

BOOST_AUTO_TEST_CASE( CropFilterTest )
{
	Bitmap bmp;
	bmp.read("/home/shogun/test.bmp");

	CropFilter f(50,50);
	f.apply(&bmp);

    BOOST_REQUIRE( bmp.info.biWidth == 50 && bmp.info.biHeight == 50 );
}

BOOST_AUTO_TEST_CASE (GrayScaleFilterTest){
	Bitmap bmp;
	bmp.read("/home/shogun/test.bmp");

	RGB* pixel = bmp.data;
	BYTE expected = 0.299 * pixel->R + 0.587 * pixel->G + 0.114 * pixel->B;

	GrayScaleFilter f;
	f.apply(&bmp);

	BOOST_REQUIRE( bmp.data->R == expected && bmp.data->G == expected && bmp.data->B == expected );
}

BOOST_AUTO_TEST_SUITE_END()
