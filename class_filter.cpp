#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>


using std::vector;
using namespace cv;

int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
const int MAX_NUM_OF_IMG = 1024;



class Generic_filter_engine
{
  private:
    std::vector<Mat> images;
    std::vector<Mat> processed_images;
    int size = 0;
  public:
    //Constructor
    Generic_filter_engine( std::vector<Mat> input_images)
    {
	std::cout <<"Generic_image_filter: Contructor is called" << std::endl;
 	size = input_images.size();
        if (size == 0)
        {
          std::cout << "No input images, exiting" << std::endl;
          exit (-1);
	}
	//should I check whether input_images.size() > MAX_NUM_OF_IMG ?

	for (vector<Mat>::iterator it = input_images.begin(); it != input_images.end(); it++)
        {
	  images.push_back(*it); 
        }
	std::cout <<"Generic_image_filter: End of constructor" << std::endl;
    }
    
    //Get method for unmodified imgaes of member variabe called images. 
    //The images of the class is copied to user supplied raw_images buffer
    int Get_raw_images(std::vector<Mat> & raw_images)
    {
	std::cout <<"Generic_image_filter: Get_raw_images called" << std::endl;
      	for (vector<Mat>::iterator itr = images.begin(); itr != images.end(); itr++)
        {
          raw_images.push_back(*itr);
        }
	std::cout <<"Generic_image_filter: End of Get_raw_images " << std::endl;
        return (size); //return size on success. Exceptions are not handled yet
    }

    //The method to process images of the class. I use Gaussian for demo.
    //Processed images are copied to user supplied out_buff
    //Also, the processed images are copied to the member variable called processed_images
    int process_image(std::vector<Mat> & out_buff)
    {
       int count = 0;
       Mat src;
       for (vector<Mat>::iterator itr = images.begin(); itr != images.end(); itr++)
       {
          src = (*itr).clone(); //wanted to make sure that images are unaffected as Gaussian blur API seems to be altering src too
          out_buff.push_back(src);
	  for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
          { 
             GaussianBlur( src, out_buff[count], Size( i, i ), 0, 0 );
          }
          processed_images.push_back(out_buff[count]);
          count++; 
       }
       return (size);
     }
    
     //Get method for modified imgaes of member variabe called processed_images. 
     //The images of the class is copied to user supplied out_images buffer
     int Get_processed_images(std::vector<Mat> & out_images)
     {
	std::cout <<"Generic_image_filter: Get_processed_images called" << std::endl;
      	for (vector<Mat>::iterator itr = processed_images.begin(); itr != processed_images.end(); itr++)
        {
          out_images.push_back(*itr);
        }
	std::cout <<"Generic_image_filter: End of Get_processed_images " << std::endl;
        return (size); //return size on success. Exceptions are not handled yet
     }
   
     //Get size of the image vector
     int Get_size()
     {
	return (size);
     }
};


 int main( int argc, char** argv )
 {
   int i; 
   vector<Mat> frameList; //used by the constructor
   vector<Mat> buff_for_raw_images_in_class;
   vector<Mat> buff_for_processed_images_in_class;
   vector<Mat> buff;
   if (argc > MAX_NUM_OF_IMG)
   {
     std::cout << "Limit exceeded for number of images" << std::endl;
     exit (-1);
   }

   /// Load the source images
  for(int i=1;i<argc;i++) 
  {
    Mat frame = imread(argv[i],0);  ///What is zero by the way
    frameList.push_back (frame);  
    imshow("input image",frame);
    waitKey(0);
  }
  
  Generic_filter_engine xx(frameList);
  xx.Get_raw_images(buff_for_raw_images_in_class);
  xx.process_image( buff_for_processed_images_in_class );
  for (vector<Mat>::iterator itr = buff_for_raw_images_in_class.begin(); itr != buff_for_raw_images_in_class.end(); itr++)
  {
    imshow("Raw image", (*itr)); 
    waitKey(0);
  }
  for (vector<Mat>::iterator itr = buff_for_processed_images_in_class.begin(); itr != buff_for_processed_images_in_class.end(); itr++)
  {
    imshow("Processed image", (*itr)); 
    waitKey(0);
  }
  xx.Get_processed_images(buff); 
  for (vector<Mat>::iterator itr = buff.begin(); itr != buff.end(); itr++)
  {
    imshow("New out image", (*itr)); 
    waitKey(0);
  }
  i = xx.Get_size();
  std::cout << "size of the image vector is " << i << std::endl;
  return 0;
}


