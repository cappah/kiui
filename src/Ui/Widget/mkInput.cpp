//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkInput.h>

#include <Object/mkObject.h>
#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Widget/mkTypeIn.h>

using namespace std::placeholders;

namespace mk
{
	InputRadio::InputRadio(const string& label, StringVector choices, std::function<void(const string&)> callback, bool reverse)
		: Band()
	{
		if(!reverse) this->makeappend<Label>(label);
		this->makeappend<RadioSwitch>([callback](Widget& widget) { if(callback) callback(widget.label()); }, 0, choices);
		if(reverse) this->makeappend<Label>(label);
	}

	InputDropdown::InputDropdown(const string& label, StringVector choices, std::function<void(const string&)> callback, bool textinput, bool reverse)
		: Band()
	{
		if(!reverse) this->makeappend<Label>(label);
		if(textinput)
			this->makeappend<Typedown>([callback](Widget& widget) { if(callback) callback(widget.label()); }, choices);
		else
			this->makeappend<Dropdown>([callback](Widget& widget) { if(callback) callback(widget.label()); }, choices);
		if(reverse) this->makeappend<Label>(label);
	}

	template <class T_Val, class T_Widget>
	unique_ptr<WValue> valueWidget(Lref& parent, Lref& lref, T_Val val) { UNUSED(parent); UNUSED(val); return make_unique<T_Widget>(lref); }

	template <class T_Val, class T_Widget>
	unique_ptr<WValue> statValueWidget(Lref& parent, Lref& valref, T_Val& val) { UNUSED(parent); UNUSED(valref); return make_unique<T_Widget>(AutoStat<T_Val>(val, StatDef<T_Val>())); }

	template class Dispatch<DispatchInput, bool&, valueWidget<bool&, Input<bool>>>;
	template class Dispatch<DispatchInput, unsigned int&, statValueWidget<unsigned int, Input<unsigned int>>>;
	template class Dispatch<DispatchInput, int&, statValueWidget<int, Input<int>>>;
	template class Dispatch<DispatchInput, float&, statValueWidget<float, Input<float>>>;
	template class Dispatch<DispatchInput, double&, statValueWidget<double, Input<double>>>;
	template class Dispatch<DispatchInput, string&, valueWidget<string&, Input<string>>>;

	template class Dispatch<DispatchInput, AutoStat<int>&, valueWidget<AutoStat<int>&, StatSlider<float>>>;
	template class Dispatch<DispatchInput, AutoStat<float>&, valueWidget<AutoStat<float>&, StatSlider<float>>>;
}
