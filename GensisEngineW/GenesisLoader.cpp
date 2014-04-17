#include "pch.h"
#include "GenesisLoader.h"
#include "BasicTimer.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace concurrency;

#define PARAM_STRING_UTF8_CMD "-utf8"

#define PARAM_STRING_HWND_CMD   "--hwnd"
#define PARAM_STRING_HWND_CONFIG L"hwnd"

#define PARAM_STRING_GAMEDIR_CMD   "--gamedir"
#define PARAM_STRING_GAMEDIR_CONFIG L"gamedir"

#define PARAM_STRING_SYSDIR_CMD   "--sysdir"
#define PARAM_STRING_SHDDIR_CMD   "--shddir"

#define PARAM_STRING_REMOTEPATH_CMD   "--remotepath"
#define PARAM_STRING_REMOTEPATH_CONFIG L"remotepath"

#define PARAM_STRING_SCENENAME_CMD   "--scenename"
#define PARAM_STRING_SCENENAME_CONFIG L"scenename"

#define PARAM_STRING_DEBUGSCRIPT_CMD   "--debugscript"
#define PARAM_STRING_DEBUGSCRIPT_CONFIG L"debugscript"

#define PARAM_STRING_NOGUI_CMD     "--nogui"
#define PARAM_STRING_GUI_CONFIG     L"gui"

#define PARAM_STRING_SCREENSIZE_CMD     "--screensize"
#define PARAM_STRING_SCREENWIDTH_CONFIG   L"screenwidth"
#define PARAM_STRING_SCREENHEIGHT_CONFIG  L"screenheight"

#define PARAM_STRING_FILESERVICEDIR_CMD    "--fspath"
#define PARAM_STRING_FILESERVICEDIR_CONFIG  L"fspath"

GensisApp::GensisApp() :
	m_windowClosed(false),
	m_windowVisible(true)
{
}

void GensisApp::Initialize(CoreApplicationView^ applicationView)
{
	applicationView->Activated +=
		ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &GensisApp::OnActivated);

	CoreApplication::Suspending +=
		ref new EventHandler<SuspendingEventArgs^>(this, &GensisApp::OnSuspending);

	CoreApplication::Resuming +=
		ref new EventHandler<Platform::Object^>(this, &GensisApp::OnResuming);

	m_renderer = ref new CubeRenderer();
}

void GensisApp::SetWindow(CoreWindow^ window)
{
	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &GensisApp::OnVisibilityChanged);

	window->Closed += 
		ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &GensisApp::OnWindowClosed);

	window->PointerPressed +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &GensisApp::OnPointerPressed);

	window->PointerMoved +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &GensisApp::OnPointerMoved);

	window->PointerReleased +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &GensisApp::OnPointerReleased);

	m_renderer->Initialize(CoreWindow::GetForCurrentThread());
}

void GensisApp::Load(Platform::String^ entryPoint)
{
}

void GensisApp::Run()
{
	BasicTimer^ timer = ref new BasicTimer();

	while (!m_windowClosed)
	{
		if (m_windowVisible)
		{
			timer->Update();
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
			m_renderer->Update(timer->Total, timer->Delta);
			m_renderer->Render();
			m_renderer->Present(); // This call is synchronized to the display frame rate.
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
		}
	}
}

void GensisApp::Uninitialize()
{
}

void GensisApp::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void GensisApp::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

void GensisApp::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
	// Insert your code here.
}

void GensisApp::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
	// Insert your code here.
}

void GensisApp::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
	// Insert your code here.
}

void GensisApp::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	CoreWindow::GetForCurrentThread()->Activate();
}

void GensisApp::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
	// Save app state asynchronously after requesting a deferral. Holding a deferral
	// indicates that the application is busy performing suspending operations. Be
	// aware that a deferral may not be held indefinitely. After about five seconds,
	// the app will be forced to exit.
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
	m_renderer->ReleaseResourcesForSuspending();

	create_task([this, deferral]()
	{
		// Insert your code here.

		deferral->Complete();
	});
}
 
void GensisApp::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// Restore any data or state that was unloaded on suspend. By default, data
	// and state are persisted when resuming from suspend. Note that this event
	// does not occur if the app was previously terminated.
	 m_renderer->CreateWindowSizeDependentResources();
}

IFrameworkView^ GenesisLoader::CreateView()
{
	return ref new GensisApp();
}


namespace Genesis
{

}

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^ argv)
{
	using namespace Genesis;

	auto genesisLoader = ref new GenesisLoader();
	CoreApplication::Run(genesisLoader);
	return 0;
}