
// INF4710 A2016 TP3 v1.4

#include "utils.hpp"

int main(int /*argc*/, char** /*argv*/) {
    try {
		cv::Mat histo1, histo2;
		int lastTransition = 0;

        cv::VideoCapture oCap("../data/TP3_video.avi");
        CV_Assert(oCap.isOpened());
		
		cv::Mat oImg;
		oCap >> oImg;

		// Get the first frame's histogram
		histo1 = tp3::histo(oImg, 256);

        for(int i=1; i<(int)oCap.get(cv::CAP_PROP_FRAME_COUNT); ++i) {
			oCap >> oImg;
            cv::imshow("oImg",oImg);
            cv::waitKey(1);
            // ... @@@@ TODO

			//Compteur pour s'assurer d'attendre un certain delais entre la detection de transition
			if (lastTransition == 0)
			{
				lastTransition--;
			}
				
			histo2 = tp3::histo(oImg, 256);

			// Treshold  pour la detection de transition && le delais de la derniere transition est passee
			if (tp3::euclid(histo1, histo2) > 0.5 && lastTransition == 0)
			{
				// Delais de 60 frames avant de pouvoir detecter une autre transition (utile dans le cas dun fading)
				lastTransition = 200;
				std::cout << "Transition detectee." << std::endl;
			}


			histo1 = histo2;
        }
    }
    catch(const cv::Exception& e) {
        std::cerr << "Caught cv::Exceptions: " << e.what() << std::endl;
    }
    catch(const std::runtime_error& e) {
        std::cerr << "Caught std::runtime_error: " << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Caught unhandled exception." << std::endl;
    }
    return 0;
}
