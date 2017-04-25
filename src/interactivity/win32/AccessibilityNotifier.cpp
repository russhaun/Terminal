/********************************************************
*                                                       *
*   Copyright (C) Microsoft. All rights reserved.       *
*                                                       *
********************************************************/

#include "precomp.h"

#include "AccessibilityNotifier.hpp"

#include "..\inc\ServiceLocator.hpp"
#include "ConsoleControl.hpp"

using namespace Microsoft::Console::Interactivity::Win32;

void AccessibilityNotifier::NotifyConsoleCaretEvent(_In_ RECT rectangle)
{
    CONSOLE_CARET_INFO caretInfo;
    caretInfo.hwnd = ServiceLocator::LocateConsoleWindow()->GetWindowHandle();
    caretInfo.rc = rectangle;

    ServiceLocator::LocateConsoleControl<ConsoleControl>()
        ->Control(ConsoleControl::ControlType::ConsoleSetCaretInfo,
                  &caretInfo,
                  sizeof(caretInfo));
}

void AccessibilityNotifier::NotifyConsoleCaretEvent(_In_ ConsoleCaretEventFlags flags, _In_ LONG position)
{
    DWORD dwFlags = 0;

    if (flags == ConsoleCaretEventFlags::CaretSelection)
    {
        dwFlags = CONSOLE_CARET_SELECTION;
    }
    else if (flags == ConsoleCaretEventFlags::CaretVisible)
    {
        dwFlags = CONSOLE_CARET_VISIBLE;
    }

    NotifyWinEvent(EVENT_CONSOLE_CARET,
                   ServiceLocator::LocateConsoleWindow()->GetWindowHandle(),
                   dwFlags,
                   position);
}

void AccessibilityNotifier::NotifyConsoleUpdateScrollEvent(_In_ LONG x, _In_ LONG y)
{
    IConsoleWindow *pWindow = ServiceLocator::LocateConsoleWindow();
    if (pWindow)
    {
        NotifyWinEvent(EVENT_CONSOLE_UPDATE_SCROLL,
                       ServiceLocator::LocateConsoleWindow()->GetWindowHandle(),
                       x,
                       y);
    }
}

void AccessibilityNotifier::NotifyConsoleUpdateSimpleEvent(_In_ LONG start, _In_ LONG charAndAttribute)
{
    IConsoleWindow *pWindow = ServiceLocator::LocateConsoleWindow();
    if (pWindow)
    {
        NotifyWinEvent(EVENT_CONSOLE_UPDATE_SIMPLE,
                       ServiceLocator::LocateConsoleWindow()->GetWindowHandle(),
                       start,
                       charAndAttribute);
    }
}

void AccessibilityNotifier::NotifyConsoleUpdateRegionEvent(_In_ LONG startXY, _In_ LONG endXY)
{
    IConsoleWindow *pWindow = ServiceLocator::LocateConsoleWindow();
    if (pWindow)
    {
        NotifyWinEvent(EVENT_CONSOLE_UPDATE_REGION,
                        ServiceLocator::LocateConsoleWindow()->GetWindowHandle(),
                        startXY,
                        endXY);
    }
}

void AccessibilityNotifier::NotifyConsoleLayoutEvent()
{
    IConsoleWindow *pWindow = ServiceLocator::LocateConsoleWindow();
    if (pWindow)
    {
        NotifyWinEvent(EVENT_CONSOLE_LAYOUT,
                       ServiceLocator::LocateConsoleWindow()->GetWindowHandle(),
                       0,
                       0);
    }
}

void AccessibilityNotifier::NotifyConsoleStartApplicationEvent(_In_ DWORD processId)
{
    IConsoleWindow *pWindow = ServiceLocator::LocateConsoleWindow();
    if (pWindow)
    {
        NotifyWinEvent(EVENT_CONSOLE_START_APPLICATION,
                        ServiceLocator::LocateConsoleWindow()->GetWindowHandle(),
                        processId,
                        0);
    }
}

void AccessibilityNotifier::NotifyConsoleEndApplicationEvent(_In_ DWORD processId)
{
    IConsoleWindow *pWindow = ServiceLocator::LocateConsoleWindow();
    if (pWindow)
    {
        NotifyWinEvent(EVENT_CONSOLE_END_APPLICATION,
                       ServiceLocator::LocateConsoleWindow()->GetWindowHandle(),
                       processId,
                       0);
    }
}