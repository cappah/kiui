//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Device/mkDevice.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkScrollbar.h>

#include <Ui/Controller/mkController.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Object/Iterable/mkReverse.h>

#include <assert.h>

#include <iostream>

namespace mk
{
	RootSheet::RootSheet(UiWindow& window, InkTarget& target, bool absolute)
		: Sheet(cls(), LAYER)
		, m_window(window)
		, m_target(target)
	{
		if(absolute)
		{
			m_frame = make_unique<Layer>(*this, 0, &m_window.inkWindow().screenTarget());
			m_frame->as<Layer>().bind();
			m_state = static_cast<WidgetState>(m_state ^ BOUND);
		}

		m_cursor = &this->makeappend<Cursor>(*this);
	}

	RootSheet::~RootSheet()
	{
		this->cleanup();
	}

	void RootSheet::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);

		m_cursor->nextFrame();
	}

	InputReceiver* RootSheet::dispatchEvent(InputEvent& inputEvent)
	{
		return InputFrame::dispatchEvent(inputEvent);
	}
}
