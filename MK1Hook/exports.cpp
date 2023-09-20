#include "exports.h"
#include "pch.h"
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>

static HMODULE hDLL = 0;

static FARPROC pDirectSoundCaptureCreate = 0;
static FARPROC pDirectSoundCaptureCreate8 = 0;
static FARPROC pDirectSoundCaptureEnumerateA = 0;
static FARPROC pDirectSoundCaptureEnumerateW = 0;
static FARPROC pDirectSoundCreate = 0;
static FARPROC pDirectSoundCreate8 = 0;
static FARPROC pDirectSoundEnumerateA = 0;
static FARPROC pDirectSoundEnumerateW = 0;
static FARPROC pDirectSoundFullDuplexCreate = 0;
static FARPROC pGetDeviceID = 0;
static FARPROC pDllCanUnloadNow = 0;
static FARPROC pDllGetClassObject = 0;


bool LoadOriginalDLL()
{
    if (hDLL)
        return true;
    hDLL = 0;

    wchar_t systemPath[MAX_PATH];
    ZeroMemory(systemPath, MAX_PATH);

    GetSystemDirectoryW(systemPath, MAX_PATH);

    wcscat(systemPath, L"\\dsound.dll");

    hDLL = LoadLibraryW(systemPath);

    if (!hDLL)
        return false;

    pDirectSoundCaptureCreate = GetProcAddress(hDLL, "DirectSoundCaptureCreate");
    pDirectSoundCaptureCreate8 = GetProcAddress(hDLL, "DirectSoundCaptureCreate8");
    pDirectSoundCaptureEnumerateA = GetProcAddress(hDLL, "DirectSoundCaptureEnumerateA");
    pDirectSoundCaptureEnumerateW = GetProcAddress(hDLL, "DirectSoundCaptureEnumerateW");
    pDirectSoundCreate = GetProcAddress(hDLL, "DirectSoundCreate");
    pDirectSoundCreate8 = GetProcAddress(hDLL, "DirectSoundCreate8");
    pDirectSoundEnumerateA = GetProcAddress(hDLL, "DirectSoundEnumerateA");
    pDirectSoundEnumerateW = GetProcAddress(hDLL, "DirectSoundEnumerateW");
    pDirectSoundFullDuplexCreate = GetProcAddress(hDLL, "DirectSoundFullDuplexCreate");
    pGetDeviceID = GetProcAddress(hDLL, "GetDeviceID");
    pDllCanUnloadNow = GetProcAddress(hDLL, "DllCanUnloadNow");
    pDllGetClassObject = GetProcAddress(hDLL, "DllGetClassObject");

    return true;
}


typedef HRESULT(*fn_DirectSoundCaptureCreate)(LPGUID lpGUID, LPDIRECTSOUNDCAPTURE* lplpDSC, LPUNKNOWN pUnkOuter);
void _DirectSoundCaptureCreate() { (fn_DirectSoundCaptureCreate)pDirectSoundCaptureCreate(); }

typedef HRESULT(*fn_DirectSoundCaptureCreate8)(LPCGUID lpcGUID, LPDIRECTSOUNDCAPTURE8* lplpDSC, LPUNKNOWN pUnkOuter);
void _DirectSoundCaptureCreate8() { (fn_DirectSoundCaptureCreate8)pDirectSoundCaptureCreate8(); }

typedef HRESULT(*fn_DirectSoundCaptureEnumerateA)(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext);
void _DirectSoundCaptureEnumerateA() { (fn_DirectSoundCaptureEnumerateA)pDirectSoundCaptureEnumerateA(); }

typedef HRESULT(*fn_DirectSoundCaptureEnumerateW)(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext);
void _DirectSoundCaptureEnumerateW() { (fn_DirectSoundCaptureEnumerateW)pDirectSoundCaptureEnumerateW(); }

typedef HRESULT(*fn_DirectSoundCreate)(LPCGUID lpcGUID, LPDIRECTSOUND* ppDS, IUnknown* pUnkOuter);
void _DirectSoundCreate() { (fn_DirectSoundCreate)pDirectSoundCreate(); }

typedef HRESULT(*fn_DirectSoundCreate8)(LPCGUID lpcGUID, LPDIRECTSOUND8* ppDS, IUnknown* pUnkOuter);
void _DirectSoundCreate8() { (fn_DirectSoundCreate8)pDirectSoundCreate8(); }

typedef HRESULT(*fn_DirectSoundEnumerateA)(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext);
void _DirectSoundEnumerateA() { (fn_DirectSoundEnumerateA)pDirectSoundEnumerateA(); }

typedef HRESULT(*fn_DirectSoundEnumerateW)(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext);
void _DirectSoundEnumerateW() { (fn_DirectSoundEnumerateW)pDirectSoundEnumerateW(); }

typedef HRESULT(*fn_DirectSoundFullDuplexCreate)(const GUID* capture_dev, const GUID* render_dev, const DSCBUFFERDESC* cbufdesc, const DSBUFFERDESC* bufdesc, HWND  hwnd, DWORD level, IDirectSoundFullDuplex** dsfd, IDirectSoundCaptureBuffer8** dscb8, IDirectSoundBuffer8** dsb8, IUnknown* outer_unk);
void _DirectSoundFullDuplexCreate() { (fn_DirectSoundFullDuplexCreate)pDirectSoundFullDuplexCreate(); }

typedef HRESULT(*fn_GetDeviceID)(LPCGUID pGuidSrc, LPGUID pGuidDest);
void _GetDeviceID() { (fn_GetDeviceID)pGetDeviceID(); }

void _DllCanUnloadNow() { pDllCanUnloadNow(); }
void _DllGetClassObject() { pDllGetClassObject(); }