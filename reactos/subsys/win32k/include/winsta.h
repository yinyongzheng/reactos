#ifndef __WIN32K_WINSTA_H
#define __WIN32K_WINSTA_H

#include <windows.h>
#include <ddk/ntddk.h>
#include <internal/ex.h>
#include <internal/ps.h>
#include "msgqueue.h"

typedef enum _WINSTA_LOCK_TYPE
{
  None,
  Any,
  Exclusive
} WINSTA_LOCK_TYPE; 

#define ASSERT_WINSTA_LOCK(a) (ASSERT(W32kVerifyWinStaLock(a)))

#define PROCESS_WINDOW_STATION() \
  ((HWINSTA)(IoGetCurrentProcess()->Win32WindowStation))

#define SET_PROCESS_WINDOW_STATION(WinSta) \
  ((IoGetCurrentProcess()->Win32WindowStation) = (PVOID)(WinSta))


NTSTATUS FASTCALL
InitWindowStationImpl(VOID);

NTSTATUS FASTCALL
CleanupWindowStationImpl(VOID);

NTSTATUS STDCALL
ValidateWindowStationHandle(HWINSTA WindowStation,
			    KPROCESSOR_MODE AccessMode,
			    ACCESS_MASK DesiredAccess,
			    PWINSTATION_OBJECT *Object);

NTSTATUS STDCALL
ValidateDesktopHandle(HDESK Desktop,
		      KPROCESSOR_MODE AccessMode,
		      ACCESS_MASK DesiredAccess,
		      PDESKTOP_OBJECT *Object);
LRESULT CALLBACK
W32kDesktopWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
PDESKTOP_OBJECT FASTCALL
W32kGetActiveDesktop(VOID);
PDESKTOP_OBJECT FASTCALL
W32kGetDesktopObject ( HDESK hDesk );
PUSER_MESSAGE_QUEUE FASTCALL
W32kGetFocusMessageQueue(VOID);
VOID FASTCALL
W32kInitializeDesktopGraphics(VOID);
VOID FASTCALL
W32kEndDesktopGraphics(VOID);
HDC FASTCALL
W32kGetScreenDC(VOID);
VOID STDCALL
W32kSetFocusMessageQueue(PUSER_MESSAGE_QUEUE NewQueue);
struct _WINDOW_OBJECT* STDCALL
W32kGetCaptureWindow(VOID);
VOID STDCALL
W32kSetCaptureWindow(struct _WINDOW_OBJECT* Window);

inline VOID W32kAcquireWinStaLockShared();
inline VOID W32kAcquireWinStaLockExclusive();
inline VOID W32kReleaseWinStaLock();
BOOL FASTCALL W32kVerifyWinStaLock(WINSTA_LOCK_TYPE Type);

#endif /* __WIN32K_WINSTA_H */

/* EOF */
