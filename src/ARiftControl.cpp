#include "../include/IDSuEyeInputHandler.h"
#include "../include/ARiftControl.h"
#include "../include/GraphicsAPI.h"
#include "../include/Helpers.h"
#include "../include/OculusHMD.h"


#include <iostream>

#define GetCurrentDir _getcwd

using namespace cv;

ARiftControl::ARiftControl()
{
  // Write read in from file for this
  if (HMD_DISTORTION)
  {
    left_cam_params_.Nxc = -112.4f;
    left_cam_params_.Nyc = 67.2f;
    left_cam_params_.z = -177.0f;
  }
  else
  {
    left_cam_params_.Nxc = -39.0f;
    left_cam_params_.Nyc = 90.0f;
    left_cam_params_.z = -250.0f;
  }
  left_cam_params_.p6 = 0.0f;
  left_cam_params_.p5 = 16.264f;
  left_cam_params_.p4 = 109.7055f;
  left_cam_params_.p3 = 289.2309f;
  left_cam_params_.p2 = 372.8583f;
  left_cam_params_.p1 = 654.9667f;
  left_cam_params_.p0 = 717.4737f;
  left_cam_params_.c = 0.9999f;
  left_cam_params_.d = -0.00019449f;
  left_cam_params_.e = -0.00030843f;
  left_cam_params_.xc = 214.4453f;
  left_cam_params_.yc = 353.3091f;

  if (HMD_DISTORTION)
  {
    right_cam_params_.Nxc = 112.4f;
    right_cam_params_.Nyc = 67.2f;
    right_cam_params_.z = -177.0f;
  }
  else
  {
    right_cam_params_.Nxc = 79.0f;
    right_cam_params_.Nyc = 94.0f;
    right_cam_params_.z = -250.0f;
  }
  right_cam_params_.p6 = 50.2189f;
  right_cam_params_.p5 = 313.8636f;
  right_cam_params_.p4 = 759.1147f;
  right_cam_params_.p3 = 864.7065f;
  right_cam_params_.p2 = 420.4562f;
  right_cam_params_.p1 = 438.6404f;
  right_cam_params_.p0 = 628.5998f;
  right_cam_params_.c = 0.9993f;
  right_cam_params_.d =  0.000046388f;
  right_cam_params_.e = -0.000052631f;
  right_cam_params_.xc = 238.1835f;
  right_cam_params_.yc = 391.6032f;
}

ARiftControl::~ARiftControl()
{
  //dtor
  if(cam_input != NULL) delete cam_input;
}

void ARiftControl::init()
{
  char cCurrentPath[FILENAME_MAX];

  if (GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
  {
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    std::cout << "The current working directory is " <<  cCurrentPath << std::endl << std::endl;
  } else {
    std::cout << "Error retrieving working path." << std::endl << std::endl;
  }
  base_save_name = getTimeString();
  cam_input = new IDSuEyeInputHandler();
  cam_input->openCams(CAM1,CAM2);
  cam_input->retrieveFrame(CAM1);
  cam_input->retrieveFrame(CAM2);

}

void ARiftControl::getImages()
{
  cam_input->retrieveFrame(CAM1);
  cam_input->retrieveFrame(CAM2);

}

void ARiftControl::handleKey(char key)
{
  switch (key)
  {
    case 15: // carrige return
    {
      OculusHMD::instance()->Recenter();
      break;
    }
    case 'w':
    {
      left_cam_params_.Nyc += step;
      right_cam_params_.Nyc -= step;
      break;
    }
    case 'a':
    {
      left_cam_params_.Nxc -= step;
      right_cam_params_.Nxc += step;
      break;
    }
    case 's':
    {
      left_cam_params_.Nyc -= step;
      right_cam_params_.Nyc += step;
      break;
    }
    case 'd':
    {
      left_cam_params_.Nxc += step;
      right_cam_params_.Nxc -= step;
      break;
    }

    case 'W':
    {
      left_cam_params_.Nyc += step;
      right_cam_params_.Nyc += step;
      break;
    }
    case 'A':
    {
      left_cam_params_.Nxc -= step;
      right_cam_params_.Nxc -= step;
      break;
    }
    case 'S':
    {
      left_cam_params_.Nyc -= step;
      right_cam_params_.Nyc -= step;
      break;
    }
    case 'D':
    {
      left_cam_params_.Nxc += step;
      right_cam_params_.Nxc += step;
      break;
    }
		case 'Z':
		{
			left_cam_params_.z += step;
			right_cam_params_.z += step;
			break;
		}
		case 'z':
		{
			left_cam_params_.z -= step;
			right_cam_params_.z -= step;
			break;
		}
    case '1':
    {
      step = 0.1f;
      break;
    }
    case '2':
    {
      step = 0.2f;
      break;
    }
    case '3':
    {
      step = 0.5f;
      break;
    }
    case '4':
    {
      step = 1.0f;
      break;
    }
    case '5':
    {
      step = 5.0f;
      break;
    }
    case 'o':
    {
      std::cout << "(x, y, z) left:  (" << left_cam_params_.Nxc << ", " << left_cam_params_.Nyc << ", " << left_cam_params_.z << " ) ";
      std::cout << " right: (" << right_cam_params_.Nxc << ", " << right_cam_params_.Nyc << ", " << right_cam_params_.z << " ) " << std::endl;
      break;
    }
    case 'P':
    {
      cam_input->changeAutoSensorSpeeds(step);
      break;
    }
    case 'p':
    {
      cam_input->changeAutoSensorSpeeds(-step);
      break;
    }
    case 'f':
    {
      std::cout << " cam " << CAM1 << " has " << cam_input->getFrameRate(CAM1) << "frames / s  |";
      std::cout << " cam " << CAM2 << " has " << cam_input->getFrameRate(CAM2) << "frames / s" << std::endl;
      break;
    }
    default:
      break;
  }
}

void ARiftControl::hanldeFlip()
{
}

void ARiftControl::handleSave()
{
}

void ARiftControl::handleCameraAutoFeatures()
{
}
