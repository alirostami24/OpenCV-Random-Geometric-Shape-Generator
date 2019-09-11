/* 
* This program creates synthetic images containing simple geometric shapes.
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

#include "ShapeCreator.h"


CSahpeCreator::CSahpeCreator()
{
	testCSVFile.open("test.csv");
	trainCSVFile.open("train.csv");
	trainCSVFile << "Filename" << ";" << "Roi.X1" << ";" << "Roi.Y1" << ";" << "Roi.X2" << ";" << "Roi.Y2" << ";" << "ClassId \n";
	testCSVFile << "Filename" << ";" << "Roi.X1" << ";" << "Roi.Y1" << ";" << "Roi.X2" << ";" << "Roi.Y2" << ";" << "ClassId \n";
}

CSahpeCreator::~CSahpeCreator()
{
	trainCSVFile.close();
	testCSVFile.close();
}

/*
* This function appends some '0' digits before the number of the current image in order to make sure
* that image files will be read in write order.
*/
std::string CSahpeCreator::format_account_number(int acct_no)
{
	std::ostringstream out;
	out << std::internal << std::setfill('0') << std::setw(8) << acct_no;
	return out.str();
}

/*
* This function creates a filled rectangle using cv::fillConvexPoly function,
* usage: include center point, size, and degrees of rotation for the intended rectangle
* this function returns a cv::Mat containing a ROI of the main image, in which the rectangle resides
*/
cv::Mat CSahpeCreator::drawRotatedRectangle(cv::Mat &image, cv::Point centerPoint, cv::Size rectangleSize, double rotationDegrees, std::string numName, bool isTrain)
{
	cv::Scalar color = cv::Scalar(255.0, 0.0, 0.0); // blue (rectangles should be in blue)

	// Make a clone of image to keep image variable safe
	cv::Mat cloneMat(image.rows, image.cols, image.type());
	cloneMat.setTo(100);

	// Create the rotated rectangle
	cv::RotatedRect rotatedRectangle(centerPoint, rectangleSize, rotationDegrees);

	// take the edges that OpenCV calculated
	cv::Point2f vertices2f[4];
	rotatedRectangle.points(vertices2f);

	// Convert the edges so that they can be used in a fillConvexPoly
	cv::Point vertices[4];
	std::vector<cv::Point> edgePoints;
	for (int i = 0; i < 4; ++i)
	{
		vertices[i] = vertices2f[i];
		edgePoints.push_back(vertices2f[i]);
	}

	// Now we can fill the rotated rectangle with our specified color
	cv::fillConvexPoly(cloneMat,
		vertices,
		4,
		color);

	// An OpenCV function for filling the created shapes
	cv::fillConvexPoly(image,
		vertices,
		4,
		color);

	cv::Rect r = cv::boundingRect(edgePoints);

	
	if (isTrain) // write xmin,ymin,xmax,ymax,class name into annotation.csv
		trainCSVFile << numName << ".png" << "," << (int)(.03 * r.width) << "," << (int)(.03 * r.height) << "," << (int)(.03 * r.width) + r.width
			<< "," << (int)(.03 * r.height) + r.height << "," << "rectangle" << " \n";
	else
	{// write xmin,ymin,xmax,ymax,class name into test.csv
		r.x = std::max(0, r.x);
		r.y = std::max(0, r.y);
		r.width = std::min(r.width, cloneMat.cols - r.x);
		r.height = std::min(r.height, cloneMat.rows - r.y);
		testCSVFile << numName << ".png" << "," << r.x << "," << r.y << "," << r.x + r.width << "," << r.y + r.height << "," << "rectangle" << " \n";
	}

	r.x -= (int)(.03 * r.width);
	r.y -= (int)(.03 * r.height);
	r.width += (int)(.06 * r.width);
	r.height += (int)(.06 * r.height);

	r.x = std::max(0, r.x);
	r.y = std::max(0, r.y);
	r.width = std::min(r.width, cloneMat.cols - r.x);
	r.height = std::min(r.height, cloneMat.rows - r.y);

	cv::Mat mat(cloneMat, r);

	return mat;
}

/*
* This function creates a filled rectangle using cv::circle function,
* usage: include center point and radius for the intended circle
* this function returns a cv::Mat containing a ROI of the main image, in which the circle resides
*/
cv::Mat CSahpeCreator::drawCirlce(cv::Mat &image, cv::Point centerPoint, int radius, std::string numName, bool isTrain)
{
	cv::Scalar color = cv::Scalar(0.0, 0.0, 255.0); // red (rectangles should be in red)

	// Make a clone of image to keep image variable safe
	cv::Mat cloneMat(image.rows, image.cols, image.type());
	cloneMat.setTo(100);

	cv::circle(cloneMat, centerPoint, radius, color, CV_FILLED, 8, 0);
	
	cv::circle(image, centerPoint, radius, color, CV_FILLED, 8, 0);

	cv::Rect r = cv::Rect(centerPoint.x - radius, centerPoint.y - radius, 2 * radius, 2 * radius);

	
	if (isTrain) // write xmin,ymin,xmax,ymax,class name into annotation.csv
		trainCSVFile << numName << ".png" << "," << (int)(.03 * r.width) << "," << (int)(.03 * r.height) << "," << (int)(.03 * r.width) + r.width
		<< "," << (int)(.03 * r.height) + r.height << "," << "circle" << " \n";
	else
	{	// write xmin,ymin,xmax,ymax,class name into test.csv
		r.x = std::max(0, r.x);
		r.y = std::max(0, r.y);
		r.width = std::min(r.width, cloneMat.cols - r.x);
		r.height = std::min(r.height, cloneMat.rows - r.y);
		testCSVFile << numName << ".png" << "," << r.x << "," << r.y << "," << r.x + r.width << "," << r.y + r.height << "," << "circle" << " \n";
	}

	r.x -= (int)(.03 * r.width);
	r.y -= (int)(.03 * r.height);
	r.width += (int)(.06 * r.width);
	r.height += (int)(.06 * r.height);

	r.x = std::max(0, r.x);
	r.y = std::max(0, r.y);
	r.width = std::min(r.width, cloneMat.cols - r.x);
	r.height = std::min(r.height, cloneMat.rows - r.y);

	cv::Mat mat(cloneMat, r);

	return mat;
}

/*
* This function creates a filled triangle using cv::line and cv::fillConvexPoly function,
* usage: include three vertices (tuples) of the triangle
* this function returns a cv::Mat containing a ROI of the main image, in which the triangle resides
* Note: here, for convenience, a triangle is supposed a half of a rectangle, size of which is determined by cv::Size
*/
cv::Mat CSahpeCreator::drawTriangle(cv::Mat &image, cv::Point point1, cv::Point point2, cv::Point point3, std::string numName, bool isTrain)
{
	cv::Scalar color = cv::Scalar(0.0, 255.0, 0.0); // green (rectangles should be in green)

	// Make a clone of image to keep image variable safe
	cv::Mat cloneMat(image.rows, image.cols, image.type());
	cloneMat.setTo(100);

	// Drawing the triangle with the help of cv::lines with given points
	// the centroid of the triangle can be calculated using the following formula:
	// (X, Y) = (x1 + x2 + x3//3, y1 + y2 + y3//3) 
	cv::line(cloneMat, point1, point2, color, 3);
	cv::line(cloneMat, point2, point3, color, 3);
	cv::line(cloneMat, point1, point3, color, 3);

	// Convert the edges so that they can be used in a fillConvexPoly
	cv::Point vertices[3];
	vertices[0] = point1;
	vertices[1] = point2;
	vertices[2] = point3;

	std::vector<cv::Point> edgePoints;
	edgePoints.push_back(point1);
	edgePoints.push_back(point2);
	edgePoints.push_back(point3);

	// Now we can fill the triangle with our specified color
	cv::fillConvexPoly(cloneMat,
		vertices,
		3,
		color);

	cv::fillConvexPoly(image,
		vertices,
		3,
		color);


	cv::Rect r = cv::boundingRect(edgePoints);
	
	
	if (isTrain) // write xmin,ymin,xmax,ymax,class name into annotation.csv
		trainCSVFile << numName << ".png" << "," << (int)(.03 * r.width) << "," << (int)(.03 * r.height) << "," << (int)(.03 * r.width) + r.width
		<< "," << (int)(.03 * r.height) + r.height << "," << "triangle" << " \n";
	else
	{	// write xmin,ymin,xmax,ymax,class name into test.csv
		r.x = std::max(0, r.x);
		r.y = std::max(0, r.y);
		r.width = std::min(r.width, cloneMat.cols - r.x);
		r.height = std::min(r.height, cloneMat.rows - r.y);
		testCSVFile << numName << ".png" << "," << r.x << "," << r.y << "," << r.x + r.width << "," << r.y + r.height << "," << "triangle" << " \n";
	}

	r.x -= (int)(.03 * r.width);
	r.y -= (int)(.03 * r.height);
	r.width += (int)(.06 * r.width);
	r.height += (int)(.06 * r.height);

	r.x = std::max(0, r.x);
	r.y = std::max(0, r.y);
	r.width = std::min(r.width, cloneMat.cols - r.x);
	r.height = std::min(r.height, cloneMat.rows - r.y);

	cv::Mat mat(cloneMat, r);

	return mat;

}

/*
* This function creates and writes images containing color shapes.
* Some required params for setting the attributes of the output image can be passed into this function
*/
void CSahpeCreator::create_and_write_all_images_for_train(std::string path, int numSamples, int w, int h)
{
	cv::Mat image(h, w, CV_8UC3);

	// Check for invalid (Null) image
	if (image.empty())
	{
		std::cout << "Could not create the image" << std::endl;
		return;
	}

	int itr = 0;

	while (itr < numSamples)
	{
		image.setTo(100);
		cv::Mat tmpMat;  // This Mat is used for writing every shape in a seperate file for training stage
		std::string str_name; //a string for keeping the name of the current .png file

		// ******<<< creating rectangle with randomly selected params >>>******
		image.setTo(100);  // in the training level for every shap the image is reset
		int min_width_rect = (int)(0.01 * w);		// the minimum value for the width of the rectangle
		int max_width_rect = (int)(0.7 * w);		// the maximum value for the width of the rectangle
		int min_height_rect = (int)(0.01 * h);		// the minimum value for the height of the rectangle
		int max_height_rect = (int)(0.7 * h);		// the maximum value for the height of the rectangle
		tmpMat = drawRotatedRectangle(image,
			cv::Point((int)w / 2.0, (int) h / 2.0),
			cv::Size(rand() % (max_width_rect - min_width_rect + 1) + min_width_rect,
			rand() % (max_height_rect - min_height_rect + 1) + min_height_rect),
			rand() % 360,
			format_account_number(itr), true);

		//str_name = path + format_account_number(itr) + ".ppm";
		//cv::imwrite(str_name, tmpMat);
		str_name = path + format_account_number(itr++) + ".png";
		cv::imwrite(str_name, tmpMat);

		// ******<<< creating circle with randomly selected params >>>******
		image.setTo(100);  // in the training level for every shap the image is reset
		int min_radius = (int)(0.005 * w);			// the minimum value for the radius of the circle 
		int max_radius = (int)(0.3 * w);			// the maximum value for the radius of the circle 
		tmpMat = drawCirlce(image,
			cv::Point((int)w / 2.0, (int)h / 2.0),
			rand() % (max_radius - min_radius + 1) + min_radius,
			format_account_number(itr), true);
		
		//str_name = path + format_account_number(itr) + ".ppm";
		//cv::imwrite(str_name, tmpMat);
		str_name = path + format_account_number(itr++) + ".png";
		cv::imwrite(str_name, tmpMat);


		// ******<<< creating triangle with randomly selected params >>>******
		image.setTo(100);  // in the training level for every shap the image is reset
		int min_loc_x = (int)(0.1 * w);		// the minimum value for the x of the center point 
		int max_loc_x = w - (int)(0.1 * w);	// the maximum value for the x of the center point
		int min_loc_y = (int)(0.1 * h);		// the minimum value for the y of the center point 
		int max_loc_y = h - (int)(0.1 * h);	// the maximum value for the y of the center point
		tmpMat = drawTriangle(image,
			cv::Point(rand() % (max_loc_x - min_loc_x + 1) + min_loc_x, rand() % (max_loc_y - min_loc_y + 1) + min_loc_y),
			cv::Point(rand() % (max_loc_x - min_loc_x + 1) + min_loc_x, rand() % (max_loc_y - min_loc_y + 1) + min_loc_y),
			cv::Point(rand() % (max_loc_x - min_loc_x + 1) + min_loc_x, rand() % (max_loc_y - min_loc_y + 1) + min_loc_y),
			format_account_number(itr), true);
		
		//str_name = path + format_account_number(itr) + ".ppm";
		//cv::imwrite(str_name, tmpMat);
		str_name = path + format_account_number(itr++) + ".png";
		cv::imwrite(str_name, tmpMat);

		//cv::imshow("test", image);
		//cv::waitKey();
		cv::waitKey(20);
	}
}

/*
* This function creates and writes images containing color shapes.
* Some required params for setting the attributes of the output image can be passed into this function
*/
void CSahpeCreator::create_and_write_all_images_for_test(std::string path, int numSamples, int w, int h)
{
	cv::Mat image(h, w, CV_8UC3);

	// Check for invalid (Null) image
	if (image.empty())
	{
		std::cout << "Could not create the image" << std::endl;
		return;
	}

	int itr = 0;
	std::string str_name; //a string for keeping the name of the current .png file
	
	while (itr < numSamples)
	{
		image.setTo(100);

		// ******<<< creating rectangle with randomly selected params >>>******
		int min_loc_x_rect = (int)(0.1 * w);		// the minimum value for the x of the center point 
		int max_loc_x_rect = w - (int)(0.1 * w);	// the maximum value for the x of the center point
		int min_loc_y_rect = (int)(0.1 * h);		// the minimum value for the y of the center point 
		int max_loc_y_rect = h - (int)(0.1 * h);	// the maximum value for the y of the center point
		int min_width_rect = (int)(0.01 * w);		// the minimum value for the width of the rectangle
		int max_width_rect = (int)(0.7 * w);		// the maximum value for the width of the rectangle
		int min_height_rect = (int)(0.01 * h);		// the minimum value for the height of the rectangle
		int max_height_rect = (int)(0.7 * h);		// the maximum value for the height of the rectangle
		drawRotatedRectangle(image,
			cv::Point(rand() % (max_loc_x_rect - min_loc_x_rect + 1) + min_loc_x_rect,
			rand() % (max_loc_y_rect - min_loc_y_rect + 1) + min_loc_y_rect),
			cv::Size(rand() % (max_width_rect - min_width_rect + 1) + min_width_rect,
			rand() % (max_height_rect - min_height_rect + 1) + min_height_rect),
			rand() % 360,
			format_account_number(itr), false);

		// ******<<< creating circle with randomly selected params >>>******
		int min_loc_x_cir = (int)(0.3 * w);		// the minimum value for the x of the center point 
		int max_loc_x_cir = w - (int)(0.3 * w);	// the maximum value for the x of the center point
		int min_loc_y_cir = (int)(0.2 * h);		// the minimum value for the y of the center point 
		int max_loc_y_cir = h - (int)(0.2 * h);	// the maximum value for the y of the center point
		int min_radius = (int)(0.005 * w);			// the minimum value for the radius of the circle 
		int max_radius = (int)(0.3 * w);			// the maximum value for the radius of the circle 
		drawCirlce(image,
			cv::Point(rand() % (max_loc_x_cir - min_loc_x_cir + 1) + min_loc_x_cir,
			rand() % (max_loc_y_cir - min_loc_y_cir + 1) + min_loc_y_cir),
			rand() % (max_radius - min_radius + 1) + min_radius,
			format_account_number(itr), false);

		// ******<<< creating triangle with randomly selected params >>>******
		int min_loc_x = (int)(0.1 * w);		// the minimum value for the x of the center point 
		int max_loc_x = w - (int)(0.1 * w);	// the maximum value for the x of the center point
		int min_loc_y = (int)(0.1 * h);		// the minimum value for the y of the center point 
		int max_loc_y = h - (int)(0.1 * h);	// the maximum value for the y of the center point
		drawTriangle(image,
			cv::Point(rand() % (max_loc_x - min_loc_x + 1) + min_loc_x, rand() % (max_loc_y - min_loc_y + 1) + min_loc_y),
			cv::Point(rand() % (max_loc_x - min_loc_x + 1) + min_loc_x, rand() % (max_loc_y - min_loc_y + 1) + min_loc_y),
			cv::Point(rand() % (max_loc_x - min_loc_x + 1) + min_loc_x, rand() % (max_loc_y - min_loc_y + 1) + min_loc_y),
			format_account_number(itr), false);

		str_name = path + format_account_number(itr++) + ".png";
		cv::imwrite(str_name, image);

		//cv::imshow("test", image);
		cv::waitKey(20);
	}
}