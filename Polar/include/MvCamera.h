/************************************************************************/
/* ??C++??????????????¨²??????§Ø??¦Ç??????????????                */
/************************************************************************/

#ifndef _MV_CAMERA_H_
#define _MV_CAMERA_H_

#include "MvCameraControl.h"
#include <string.h>

#ifndef MV_NULL
#define MV_NULL    0
#endif

class CMvCamera
{
public:
    CMvCamera();
    ~CMvCamera();

    // ch:???SDK?·Ú?? | en:Get SDK Version
    static int GetSDKVersion();

    // ch:????õô | en:Enumerate Device
    static int EnumDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST* pstDevList);

    // ch:?§Ø??õô?????? | en:Is the device accessible
    static bool IsDeviceAccessible(MV_CC_DEVICE_INFO* pstDevInfo, unsigned int nAccessMode);

    // ch:?????õô | en:Open Device
    int Open(MV_CC_DEVICE_INFO* pstDeviceInfo);

    // ch:????õô | en:Close Device
    int Close();

    // ch:?§Ø?????????????????? | en:Is The Device Connected
    bool IsDeviceConnected();

    // ch:???????????? | en:Register Image Data CallBack
    int RegisterImageCallBack(void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), void* pUser);

    // ch:?????? | en:Start Grabbing
    int StartGrabbing();

    // ch:???? | en:Stop Grabbing
    int StopGrabbing();

    // ch:???????????????? | en:Get one frame initiatively
    int GetImageBuffer(MV_FRAME_OUT* pFrame, int nMsec);

    // ch:???????? | en:Free image buffer
    int FreeImageBuffer(MV_FRAME_OUT* pFrame);

    // ch:???????? | en:Display one frame image
    int DisplayOneFrame(MV_DISPLAY_FRAME_INFO* pDisplayInfo);

    // ch:????SDK??????????????? | en:Set the number of the internal image cache nodes in SDK
    int SetImageNodeNum(unsigned int nNum);

    // ch:????õô??? | en:Get device information
    int GetDeviceInfo(MV_CC_DEVICE_INFO* pstDevInfo);

    // ch:???GEV???????????? | en:Get detect info of GEV camera
    int GetGevAllMatchInfo(MV_MATCH_INFO_NET_DETECT* pMatchInfoNetDetect);

    // ch:???U3V???????????? | en:Get detect info of U3V camera
    int GetU3VAllMatchInfo(MV_MATCH_INFO_USB_DETECT* pMatchInfoUSBDetect);

    // ch:?????????Int????????? Width??Height?????????¦Ï?SDK???????? MvCameraNode.xlsx ???
    // en:Get Int type parameters, such as Width and Height, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetIntValue(IN const char* strKey, OUT MVCC_INTVALUE_EX *pIntValue);
    int SetIntValue(IN const char* strKey, IN int64_t nValue);

    // ch:?????????Enum????????? PixelFormat?????????¦Ï?SDK???????? MvCameraNode.xlsx ???
    // en:Get Enum type parameters, such as PixelFormat, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetEnumValue(IN const char* strKey, OUT MVCC_ENUMVALUE *pEnumValue);
    int SetEnumValue(IN const char* strKey, IN unsigned int nValue);
    int SetEnumValueByString(IN const char* strKey, IN const char* sValue);
    int GetEnumEntrySymbolic(IN const char* strKey, IN MVCC_ENUMENTRY* pstEnumEntry);

    // ch:?????????Float????????? ExposureTime??Gain?????????¦Ï?SDK???????? MvCameraNode.xlsx ???
    // en:Get Float type parameters, such as ExposureTime and Gain, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetFloatValue(IN const char* strKey, OUT MVCC_FLOATVALUE *pFloatValue);
    int SetFloatValue(IN const char* strKey, IN float fValue);

    // ch:?????????Bool????????? ReverseX?????????¦Ï?SDK???????? MvCameraNode.xlsx ???
    // en:Get Bool type parameters, such as ReverseX, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetBoolValue(IN const char* strKey, OUT bool *pbValue);
    int SetBoolValue(IN const char* strKey, IN bool bValue);

    // ch:?????????String????????? DeviceUserID?????????¦Ï?SDK???????? MvCameraNode.xlsx ???UserSetSave
    // en:Get String type parameters, such as DeviceUserID, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int GetStringValue(IN const char* strKey, MVCC_STRINGVALUE *pStringValue);
    int SetStringValue(IN const char* strKey, IN const char * strValue);

    // ch:??????Command???????? UserSetSave?????????¦Ï?SDK???????? MvCameraNode.xlsx ???
    // en:Execute Command once, such as UserSetSave, for details please refer to MvCameraNode.xlsx file under SDK installation directory
    int CommandExecute(IN const char* strKey);

    // ch:??????????????§³(???GigE??????§¹) | en:Detection network optimal package size(It only works for the GigE camera)
    int GetOptimalPacketSize(unsigned int* pOptimalPacketSize);

    // ch:??????????? | en:Register Message Exception CallBack
    int RegisterExceptionCallBack(void(__stdcall* cbException)(unsigned int nMsgType, void* pUser), void* pUser);

    // ch:??????????? | en:Register Event CallBack
    int RegisterEventCallBack(const char* pEventName, void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), void* pUser);

    // ch:???IP | en:Force IP
    int ForceIp(unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay);

    // ch:????IP??? | en:IP configuration method
    int SetIpConfig(unsigned int nType);

    // ch:???????×Ï???? | en:Set Net Transfer Mode
    int SetNetTransMode(unsigned int nType);

    // ch:????????? | en:Pixel format conversion
    int ConvertPixelType(MV_CC_PIXEL_CONVERT_PARAM* pstCvtParam);

    // ch:?????? | en:save image
    int SaveImage(MV_SAVE_IMAGE_PARAM_EX* pstParam);

    // ch:?????????? | en:Save the image as a file
    int SaveImageToFile(MV_SAVE_IMG_TO_FILE_PARAM* pstParam);

    // ch:??????¦È????? | en:Draw circle auxiliary line
    int DrawCircle(MVCC_CIRCLE_INFO* pCircleInfo);

    // ch:???????¦È????? | en:Draw lines auxiliary line
    int DrawLines(MVCC_LINES_INFO* pLinesInfo);

private:

    void*               m_hDevHandle;

};

#endif//_MV_CAMERA_H_
