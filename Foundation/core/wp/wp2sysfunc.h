/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once
//------------------------------------------------------------------------------
/**
@class Win32::SysFunc

Provides Win32 specific helper functions.
*/

//#include "stdneb.h"
#include "core/types.h"
#include "core/exithandler.h"

namespace System
{
	class SystemInfo;
}

//------------------------------------------------------------------------------
namespace WP
{

	class SysFunc
	{
	public:
		/// setup lowlevel static objects (must be called before spawning any threads)
		static void Setup();
		/// exit process, and to proper cleanup, memleak reporting, etc...
		static void Exit(int exitCode);
		/// display an error message box
		static void Error(const char* error);
		/// display a message box which needs to be confirmed by the user
		static void MessageBox(const char* msg);
		/// print a message on the debug console
		static void DebugOut(const char* msg);
		/// sleep for a specified amount of seconds
		static void Sleep(double sec);

		/// get system info 
		static const System::SystemInfo* GetSystemInfo();

	private:
		friend class Core::ExitHandler;
		/// register an exit handler which will be called from within Exit()
		static const Core::ExitHandler* RegisterExitHandler(const Core::ExitHandler* exitHandler);

		static bool volatile SetupCalled;
		static const Core::ExitHandler* ExitHandlers;     // forward linked list of exit handlers
		static System::SystemInfo systemInfo;

	};

} // namespace WP
//------------------------------------------------------------------------------
