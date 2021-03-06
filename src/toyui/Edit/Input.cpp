//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/Input.h>

#include <toyobj/Object.h>
#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/StatString.h>

#include <toyui/Button/Dropdown.h>
#include <toyui/Button/Typedown.h>
#include <toyui/Button/RadioButton.h>
#include <toyui/Button/Image.h>

#include <toyui/Edit/TypeIn.h>

namespace toy
{
	InputRadio::InputRadio(Wedge& parent, const string& label, StringVector choices, std::function<void(const string&)> callback, bool reverse)
		: WrapControl(parent, cls())
		, m_label(*this, label)
		, m_input(*this, [callback](Widget& widget) { if(callback) callback(widget.label()); }, 0, choices)
	{
		if(reverse)
			this->swap(0, 1);
	}

	InputDropdown::InputDropdown(Wedge& parent, const string& label, StringVector choices, std::function<void(const string&)> callback, bool reverse)
		: WrapControl(parent, cls())
		, m_label(*this, label)
		, m_input(*this, [callback](Widget& widget) { if(callback) callback(widget.label()); }, choices)
	{
		if(reverse)
			this->swap(0, 1);
	}

	template <class T_Val, class T_Widget>
	unique_ptr<WValue> valueWidget(Lref& lref, T_Val& val, Lref& parent) { UNUSED(parent); UNUSED(val); return make_unique<T_Widget>(parent->as<Wedge>(), lref); }

	template <class T_Val, class T_Widget>
	unique_ptr<WValue> statValueWidget(Lref& lref, T_Val& val, Lref& parent) { UNUSED(parent); UNUSED(lref); return make_unique<T_Widget>(parent->as<Wedge>(), AutoStat<T_Val>(val, StatDef<T_Val>())); }
	
	class TOY_UI_EXPORT InputDispatch : public Global<InputDispatch>
	{
	public:
		InputDispatch()
		{
			DispatchInput::singleBranch<bool, valueWidget<bool, Input<bool>>>();
			DispatchInput::singleBranch<unsigned int, statValueWidget<unsigned int, Input<unsigned int>>>();
			DispatchInput::singleBranch<int, statValueWidget<int, Input<int>>>();
			DispatchInput::singleBranch<float, statValueWidget<float, Input<float>>>();
			DispatchInput::singleBranch<double, statValueWidget<double, Input<double>>>();
			DispatchInput::singleBranch<string, valueWidget<string, Input<string>>>();

			DispatchInput::singleBranch<AutoStat<int>, valueWidget<AutoStat<int>, StatSlider<float>>>();
			DispatchInput::singleBranch<AutoStat<float>, valueWidget<AutoStat<float>, StatSlider<float>>>();

			DispatchInput::singleBranch<Image256, valueWidget<Image256, Figure>>();
		}
	};
}
