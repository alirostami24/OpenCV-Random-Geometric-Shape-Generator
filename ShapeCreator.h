
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
* The CSahpeCreator class creates synthetic images containing simple geometric shapes.
* These color shapes are filled with the following style:
*
* - Rectangles are filled with blue
* - Circles are filled with red
* - Triangles are filled with green
*
* Random integers are created and used for the size of the shapes. A random angle is also used to rotate the shapes.
*
* Note: All (three) shapes may not appear in every single image, for this purpose a flag is set randomly to decide
* on what shapes should exist in the image.
*/
class CSahpeCreator
{
public:

	CSahpeCreator();
	~CSahpeCreator();
	
	/*
	* This function creates and writes images containing color shapes for testing the RetinaNet model. 
	* This function writes every singe shape in a separate .jpg file.
	* Some required params for setting the attributes of the output image can be passed into this function
	*/
	void CSahpeCreator::create_and_write_all_images_for_train(std::string path, int numSamples = 10000, int w = 500, int h = 500);
	
	/*
	* This function creates and writes images containing color shapes. 
	* Some required params for setting the attributes of the output image can be passed into this function
	*/
	void CSahpeCreator::create_and_write_all_images_for_test(std::string path, int numSamples = 1000, int w = 500, int h = 500);
	
	/*
	* This function receives the required params for setting the attributes of the output image
	*/
	void setOutputImageParams(int number, int w, int h);

private:

	std::ofstream trainCSVFile;
	std::ofstream testCSVFile;


	/*
	* This function appends some '0' digits before the number of the current image in order to make sure
	* that image files will be read in write order.
	*/
	std::string format_account_number(int acct_no);

	/*
	* This function creates a filled rectangle using cv::fillConvexPoly function,
	* usage: include center point, size, and degrees of rotation for the intended rectangle
	*/
	cv::Mat drawRotatedRectangle(cv::Mat &image, cv::Point centerPoint, cv::Size rectangleSize, double rotationDegrees, std::string numName, bool isTrain);
	
	/*
	* This function creates a filled rectangle using cv::circle function,
	* usage: include center point and radius for the intended circle
	*/
	cv::Mat CSahpeCreator::drawCirlce(cv::Mat &image, cv::Point centerPoint, int radius, std::string numName, bool isTrain);

	/*
	* This function creates a filled triangle using cv::fillConvexPoly function,
	* usage: include center point, size, and degrees of rotation for the intended triangle
	*
	* Note: here, for convenience, a triangle is supposed a half of a rectangle, size of which is determined by cv::Size
	*/
	cv::Mat CSahpeCreator::drawTriangle(cv::Mat &image, cv::Point point1, cv::Point point2, cv::Point point3, std::string numName, bool isTrain);
};