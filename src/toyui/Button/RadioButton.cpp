//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/RadioButton.h>

#include <toyui/Container/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

namespace toy
{
	RadioChoice::RadioChoice(Wedge& parent, const Callback& trigger)
		: WrapButton(parent, trigger, cls())
	{}

	RadioSwitch::RadioSwitch(Wedge& parent, const Callback& onSelected, size_t active, StringVector labels)
		: WrapControl(parent, cls())
		, m_onSelected(onSelected)
		, m_active(nullptr)
		, m_activeIndex(active)
	{
		for(string& label : labels)
			this->emplace<Label>(label);
	}

	RadioChoice& RadioSwitch::addChoice()
	{
		RadioChoice& choice = this->emplaceLocal<RadioChoice>(*this, [this](Widget& button) { this->activated(button.as<RadioChoice>()); });

		if(m_contents.size() - 1 == m_activeIndex)
		{
			m_active = &choice;
			m_active->enableState(ACTIVATED);
		}

		return choice;
	}

	void RadioSwitch::activated(RadioChoice& button)
	{
		if(m_active)
			m_active->disableState(ACTIVATED);
		m_active = &button;
		m_active->enableState(ACTIVATED);
		if(m_onSelected)
			m_onSelected(m_active->content());
	}
}
