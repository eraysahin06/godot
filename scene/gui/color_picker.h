/*************************************************************************/
/*  color_picker.h                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "scene/gui/aspect_ratio_container.h"
#include "scene/gui/box_container.h"
#include "scene/gui/button.h"
#include "scene/gui/control.h"
#include "scene/gui/grid_container.h"
#include "scene/gui/label.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/option_button.h"
#include "scene/gui/popup.h"
#include "scene/gui/separator.h"
#include "scene/gui/slider.h"
#include "scene/gui/spin_box.h"
#include "scene/gui/texture_rect.h"

class ColorMode;
class ColorModeRGB;
class ColorModeHSV;
class ColorModeRAW;
class ColorModeOKHSL;

class ColorPresetButton : public BaseButton {
	GDCLASS(ColorPresetButton, BaseButton);

	Color preset_color;

protected:
	void _notification(int);

public:
	void set_preset_color(const Color &p_color);
	Color get_preset_color() const;

	ColorPresetButton(Color p_color, int p_size);
	~ColorPresetButton();
};

class ColorPicker : public BoxContainer {
	GDCLASS(ColorPicker, BoxContainer);

public:
	enum ColorModeType {
		MODE_RGB,
		MODE_HSV,
		MODE_RAW,
		MODE_OKHSL,

		MODE_MAX
	};

	enum PickerShapeType {
		SHAPE_HSV_RECTANGLE,
		SHAPE_HSV_WHEEL,
		SHAPE_VHS_CIRCLE,
		SHAPE_OKHSL_CIRCLE,

		SHAPE_MAX
	};

	static const int SLIDER_COUNT = 4;

private:
	static Ref<Shader> wheel_shader;
	static Ref<Shader> circle_shader;
	static Ref<Shader> circle_ok_color_shader;
	static List<Color> preset_cache;
	static List<Color> recent_preset_cache;

	int current_slider_count = SLIDER_COUNT;
	static const int MODE_BUTTON_COUNT = 3;

	bool slider_theme_modified = true;

	Vector<ColorMode *> modes;

	Control *screen = nullptr;
	Control *uv_edit = nullptr;
	Control *w_edit = nullptr;
	AspectRatioContainer *wheel_edit = nullptr;
	MarginContainer *wheel_margin = nullptr;
	Ref<ShaderMaterial> wheel_mat;
	Ref<ShaderMaterial> circle_mat;
	Control *wheel = nullptr;
	Control *wheel_uv = nullptr;
	TextureRect *sample = nullptr;
	GridContainer *preset_container = nullptr;
	HBoxContainer *recent_preset_hbc = nullptr;
	Button *btn_add_preset = nullptr;
	Button *btn_pick = nullptr;
	Button *btn_preset = nullptr;
	Button *btn_recent_preset = nullptr;
	PopupMenu *shape_popup = nullptr;
	PopupMenu *mode_popup = nullptr;
	MenuButton *btn_shape = nullptr;
	MenuButton *btn_mode = nullptr;
	Button *mode_btns[MODE_BUTTON_COUNT];
	Ref<ButtonGroup> mode_group = nullptr;
	ColorPresetButton *selected_recent_preset = nullptr;
	Ref<ButtonGroup> preset_group;
	Ref<ButtonGroup> recent_preset_group;

	OptionButton *mode_option_button = nullptr;

	HSlider *sliders[SLIDER_COUNT];
	SpinBox *values[SLIDER_COUNT];
	Label *labels[SLIDER_COUNT];
	Button *text_type = nullptr;
	LineEdit *c_text = nullptr;

	HSlider *alpha_slider = nullptr;
	SpinBox *alpha_value = nullptr;
	Label *alpha_label = nullptr;

	bool edit_alpha = true;
	Size2i ms;
	bool text_is_constructor = false;
	PickerShapeType current_shape = SHAPE_HSV_RECTANGLE;
	ColorModeType current_mode = MODE_RGB;
	bool colorize_sliders = true;

	const int PRESET_COLUMN_COUNT = 9;
	int prev_preset_size = 0;
	int prev_rencet_preset_size = 0;
	List<Color> presets;
	List<Color> recent_presets;

	Color color;
	Color old_color;

	bool display_old_color = false;
	bool deferred_mode_enabled = false;
	bool updating = true;
	bool changing_color = false;
	bool spinning = false;
	bool presets_enabled = true;
	bool presets_visible = true;
	bool line_edit_mouse_release = false;
	bool text_changed = false;

	float h = 0.0;
	float s = 0.0;
	float v = 0.0;
	Color last_color;

	void _copy_color_to_hsv();
	void _copy_hsv_to_color();

	PickerShapeType _get_actual_shape() const;
	void create_slider(GridContainer *gc, int idx);
	void _reset_theme();
	void _html_submitted(const String &p_html);
	void _value_changed(double);
	void _update_controls();
	void _update_color(bool p_update_sliders = true);
	void _update_text_value();
	void _text_type_toggled();
	void _sample_input(const Ref<InputEvent> &p_event);
	void _sample_draw();
	void _hsv_draw(int p_which, Control *c);
	void _slider_draw(int p_which);

	void _uv_input(const Ref<InputEvent> &p_event, Control *c);
	void _w_input(const Ref<InputEvent> &p_event);
	void _slider_or_spin_input(const Ref<InputEvent> &p_event);
	void _line_edit_input(const Ref<InputEvent> &p_event);
	void _preset_input(const Ref<InputEvent> &p_event, const Color &p_color);
	void _recent_preset_pressed(const bool pressed, ColorPresetButton *p_preset);
	void _screen_input(const Ref<InputEvent> &p_event);
	void _text_changed(const String &p_new_text);
	void _add_preset_pressed();
	void _screen_pick_pressed();
	void _html_focus_exit();

	inline int _get_preset_size();
	void _add_preset_button(int p_size, const Color &p_color);
	void _add_recent_preset_button(int p_size, const Color &p_color);

	void _show_hide_preset(const bool &p_is_btn_pressed, Button *p_btn_preset, Container *p_preset_container);
	void _update_drop_down_arrow(const bool &p_is_btn_pressed, Button *p_btn_preset);

	void _set_mode_popup_value(ColorModeType p_mode);

	Variant _get_drag_data_fw(const Point2 &p_point, Control *p_from_control);
	bool _can_drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from_control) const;
	void _drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from_control);

protected:
	void _notification(int);
	static void _bind_methods();

public:
	HSlider *get_slider(int idx);
	Vector<float> get_active_slider_values();

	static void init_shaders();
	static void finish_shaders();

	void add_mode(ColorMode *p_mode);

	void set_edit_alpha(bool p_show);
	bool is_editing_alpha() const;

	int get_preset_size();

	void _set_pick_color(const Color &p_color, bool p_update_sliders);
	void set_pick_color(const Color &p_color);
	Color get_pick_color() const;
	void set_old_color(const Color &p_color);

	void set_display_old_color(bool p_enabled);
	bool is_displaying_old_color() const;

	void set_picker_shape(PickerShapeType p_shape);
	PickerShapeType get_picker_shape() const;

	void add_preset(const Color &p_color);
	void add_recent_preset(const Color &p_color);
	void erase_preset(const Color &p_color);
	void erase_recent_preset(const Color &p_color);
	PackedColorArray get_presets() const;
	PackedColorArray get_recent_presets() const;
	void _update_presets();
	void _update_recent_presets();

	void _select_from_preset_container(const Color &p_color);
	bool _select_from_recent_preset_hbc(const Color &p_color);

	void set_color_mode(ColorModeType p_mode);
	ColorModeType get_color_mode() const;

	void set_colorize_sliders(bool p_colorize_sliders);
	bool is_colorizing_sliders() const;

	void set_deferred_mode(bool p_enabled);
	bool is_deferred_mode() const;

	void set_presets_enabled(bool p_enabled);
	bool are_presets_enabled() const;

	void set_presets_visible(bool p_visible);
	bool are_presets_visible() const;

	void set_focus_on_line_edit();

	ColorPicker();
	~ColorPicker();
};

class ColorPickerButton : public Button {
	GDCLASS(ColorPickerButton, Button);

	// Initialization is now done deferred,
	// this improves performance in the inspector as the color picker
	// can be expensive to initialize.

	PopupPanel *popup = nullptr;
	ColorPicker *picker = nullptr;
	Color color;
	bool edit_alpha = true;

	void _about_to_popup();
	void _color_changed(const Color &p_color);
	void _modal_closed();

	virtual void pressed() override;

	void _update_picker();

protected:
	void _notification(int);
	static void _bind_methods();

public:
	void set_pick_color(const Color &p_color);
	Color get_pick_color() const;

	void set_edit_alpha(bool p_show);
	bool is_editing_alpha() const;

	ColorPicker *get_picker();
	PopupPanel *get_popup();

	ColorPickerButton(const String &p_text = String());
};

VARIANT_ENUM_CAST(ColorPicker::PickerShapeType);
VARIANT_ENUM_CAST(ColorPicker::ColorModeType);

#endif // COLOR_PICKER_H
