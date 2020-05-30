#ifndef FAST_IMAGE_H_
#define FAST_IMAGE_H_
#include "common.h"
namespace FAST {
	class CFastImage {
	public: 
		CFastImage() {};
		~CFastImage() {};

		static void Mask2Index(const cv::Mat& _mask, int _pVec[], int& _nPixels) ; 
		static float FastSSD(cv::Mat _img1, cv::Mat _img2, const int _pVec[], int _nPixels);
		static float FastSSD(cv::Mat _img1, cv::Mat _img2, const int _pVec1[],  const int _pVec2[], int _nPixels);
		static float FastConvolution(cv::Mat _img1, cv::Mat _img2, const int _pVec[], int _nPixels);
		static float FastSSDCentral(cv::Mat _img1, cv::Mat _img2, cv::Mat _weight, float _norm, const int _pVec[], int _nPixel);
		static float FastSSD(cv::Mat _img, uchar _p[], const int _pVec[], int _nPixel); 
		static void FastErrorImage(cv::Mat _img1, cv::Mat _img2, cv::Mat& _out, const int _pVec[], int _nPixel); 
		static float FastConvolution(cv::Mat _img, const int _pVec[], int _nPixels);
		//static float FastConvolution(cv::Mat _img1, )
		static void NormalizePatch(cv::Mat& _img); 
		static void MagnifyPatch(cv::Mat& _img, int _factor); 
		static void ShowImages(vector<cv::Mat> _imgVec, string _name, 
			int _hGrid, int _wGrid, int _scale); 
		static void ThresholdZeroError(vector<float>& _errVec); 
		static void UpdateMask(cv::Size _imgSz, const int _pVec[], int _nPixel, 
			int _offset_x, int _offset_y, int _outPVec[], int& _outPixel); 
		static cv::Mat FastAddImages(const vector<cv::Mat>& _imgs); 
		static float FastSum(cv::Mat& _img, int _pVec[], int _n); 
	};
}
#endif //FAST_IMAGE_H_