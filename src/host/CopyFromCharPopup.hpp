/*++
Copyright (c) Microsoft Corporation

Module Name:
- CopyFromCharPopup.hpp

Abstract:
- Popup used for use copying from char input
- contains code pulled from popup.cpp and cmdline.cpp

Author:
- Austin Diviness (AustDi) 18-Aug-2018
--*/

#pragma once

#include "popup.h"

class CopyFromCharPopup : public Popup
{
public:
    CopyFromCharPopup(SCREEN_INFORMATION& screenInfo);

    [[nodiscard]]
    NTSTATUS Process(COOKED_READ_DATA& cookedReadData) noexcept override;

protected:
    void _DrawContent() override;
};