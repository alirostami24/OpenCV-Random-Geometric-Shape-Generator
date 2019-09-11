#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

#include "ShapeCreator.h"

/*
* This file is the main source for using the CShapeCreator class in order to create color shapes.
* usage: the scenario is quite simple, just we should create an object of the CShapeCreator class and call
* the create_and_write_all_images function.
*/

int main()
{
	CSahpeCreator* m_ShapeCreator = new CSahpeCreator();

	// The path into which the created images should be placed
	std::string train_path = "Images/train/";
	std::string test_path = "Images/test/";

	std::cout << "\n";
	std::cout << "Creating and saving shape images and respective .csv files started...!\n\n";

	std::cout << "I will take a few minutes to accomplish, so be patient please. \n\n";

	std::cout << "This has two stages:\n\n 1) first train shapes are created \n 2) then, test shapes are created.\n\n";
	std::cout << "Please check the paths: <Images/train> and <Images/test> to see the result of shape creation procedure.\n\n";

	std::cout << "The corresponding .csv files will be created in the current folder\n";

	m_ShapeCreator->create_and_write_all_images_for_train(
		train_path,  // The specified path
		30000,  // the total number of images
		700,   // the width of the images
		700	   // the height of the images
		);

	std::cout << "Train dataset has been prepared!\n\n";

	m_ShapeCreator->create_and_write_all_images_for_test(
		test_path,  // The specified path
		2000,  // the total number of images
		900,   // the width of the images
		700	   // the height of the images
		);

	std::cout << "Test dataset has been prepared!\n";


	return 0;
}

