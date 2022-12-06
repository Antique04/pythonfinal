<?xml version="1.0" encoding="utf-8" ?>
<DUMMY>
  <!-- toolbar item template -->
  <TEMPLATE id="TPL_TOOLBAR_ITEM" short_text="">
    <IMAGE_ACTION_BUTTON image="$image$"
                          opaque_mouse_mask="true"
                         cursor="system::hand" action="$action$" opacity="$opacity$" auto_focus="false"  ignore_mask_file="true" image_scaling=".5">
      <TOOLTIP text="$text$"/>
    </IMAGE_ACTION_BUTTON>
  </TEMPLATE>

  <!-- The actual horizontal toolbar template -->
  <TEMPLATE id="TPL_TOOLBAR" icon_opacity="100%" bar_opacity="100%" width="100%" font_size="10" font_name="Arial" preset_box_width="200"  show_bypass="true" show_settings="true" show_manual="true" show_logo="true" text="$PLUGIN_NAME$" text_string_id="" text_width="-1" 
            buttons_cell="CELL" buttons_per_row="6" empty_buttons_count="0" spacing="5" opacity_param_id="window.opacity" display_zoom="true"
            extra_menu_items="DUMMY">
    <DEFINE>
      <_LOCAL_BUTTONS_ITEMS_ base_type="$buttons_cell$"/>
      <_LOCAL_MENU_ITEMS_ base_type="$extra_menu_items$"/>
    </DEFINE>
    <!-- toolbar background -->
    <IMAGE_GROUP_BOX width="$width$" font_size="$font_size$" font_size_mode="character" height="55" h_margin="4" v_margin="2" 
                     image_top="$THEME_PATH$/toolbar/toolbar_bg.png" image_top_left="$THEME_PATH$/toolbar/toolbar_bg_left.png" image_top_right="$THEME_PATH$/toolbar/toolbar_bg_right.png" 
                     ignore_mask_files="true"
                     spacing="$spacing$" layout_type="row">
      <!-- MAIN BUTTONS area -->
      <!-- Bypass -->
      <REPEAT count="$show_bypass$!=0">
        <CELL width="10"/>
        <LAYER_STACK>
        <IMAGE_PARAM_BUTTON param_id="dsp.input0" reverse="true" cursor="system::hand"
                            image="$THEME_PATH$/toolbar/power_button.png" image_hover="$THEME_PATH$/toolbar/power_button_hi.png"  image_focus="$THEME_PATH$/toolbar/power_button_hi.png" image_scaling=".5"
                            ignore_mask_files="true" >
          <TOOLTIP text="Bypass"/>
        </IMAGE_PARAM_BUTTON>
          <THEME_DSP_PARAM_SMALL_ROUND_SETTINGS_BUTTON param_id="dsp.input0" v_align="bottom" v_offset="7" button_index="toolbar"/>
        </LAYER_STACK>
      </REPEAT>
      <!-- additional stuff-->
      <_LOCAL_BUTTONS_ITEMS_/>

      <!-- toolbar elements-->
      <LOCAL_VARIABLE id="toolbar_width" formula="round(round($PIXEL_SCALE_FACTOR$*24)*($buttons_per_row$-1)/$PIXEL_SCALE_FACTOR$)+round(round($PIXEL_SCALE_FACTOR$*25)/$PIXEL_SCALE_FACTOR$)"/>
      <LOCAL_VARIABLE id="toolbar_height" formula="round((round($PIXEL_SCALE_FACTOR$*16)+round($PIXEL_SCALE_FACTOR$*17))/$PIXEL_SCALE_FACTOR$)"/>
      <IMAGE_GROUP_BOX image="$THEME_PATH$/toolbar/toolbar_buttons.png" width="$toolbar_width$" height="$toolbar_height$" layout_type="row" margin="1" spacing_flex="1" reflow="true" internal_h_align="left" ignore_mask_files="true">
        <TPL_TOOLBAR_ITEM image="$THEME_PATH$/toolbar/menu.png" action="OpenMenu" text="Plug-in Menu" short_text="Menu"/>
        <REPEAT count="$show_settings$!=0">
          <PARAM id="theme.show_settings" type="boolean" default="0" persistent="true" locked="false"/>
          <ACTION id="theme.Toggle_show_settings" name="Show Control Settings" type="Script" requires="theme.show_settings" script="if(theme.show_settings==0) theme.show_settings=1; else theme.show_settings=0;"/>
          <ACTION id="theme.Toggle_SettingsLock" name="Lock Control Settings" type="Script" requires="dsp.controller.meta.locked" script="if(dsp.controller.meta.locked==0) dsp.controller.meta.locked=1; else dsp.controller.meta.locked=0;"/>
          <POPUP_MENU id="theme.control_settings_menu">
            <MENU_ITEM action_id="theme.Toggle_show_settings" checked_param_id="theme.show_settings" />
            <MENU_ITEM action_id="theme.Toggle_SettingsLock" checked_param_id="dsp.controller.meta.locked" />
            <MENU_ITEM action_id="ResetPresetMIDISettings" />
            <MENU_ITEM action_id="Show_AllControls_Setup" />
            <MENU_SEPARATOR/>
            <MENU_ITEM action_id="SavePresetMIDISettingsAsGlobal" />
            <_LOCAL_MENU_ITEMS_/>
          </POPUP_MENU>
          <IMAGE_ACTION_BUTTON action_id="theme.control_settings_menu.Popup" cursor="system::hand"
                              image="$THEME_PATH$/toolbar/settings.png" image_focus="$THEME_PATH$/toolbar/settings_hover.png"
                              opaque_mouse_mask="true"
                              ignore_mask_file="true" image_scaling=".5">
            <TOOLTIP text="Controls Settings"/>
          </IMAGE_ACTION_BUTTON>
        </REPEAT>
        <TPL_TOOLBAR_ITEM image="$THEME_PATH$/toolbar/undo.png" action="Undo" text="Undo" short_text="Undo"/>
        <TPL_TOOLBAR_ITEM image="$THEME_PATH$/toolbar/redo.png" action="Redo" text="Redo" short_text="Redo"/>
        <REPEAT count="$show_manual$!=0">
          <TPL_TOOLBAR_ITEM image="$THEME_PATH$/toolbar/help.png" action="OpenManual" text="Manual"/>
        </REPEAT>
        <TPL_TOOLBAR_ITEM image="$THEME_PATH$/toolbar/about.png" action="DisplayAbout" text="About"/>
        <IMAGE_PARAM_MENU_BUTTON image="$THEME_PATH$/toolbar/zoom.png" opaque_mouse_mask="true" cursor="system::hand" param_id="gui.zoom" positions_count="14" image_scaling=".5" display="$display_zoom$">
          <PARAM_TOOLTIP param_id="gui.zoom" content="Zoom: {text_value}{unit}"/>
        </IMAGE_PARAM_MENU_BUTTON>
        <!-- additional toolbar buttons -->
        <TEMPLATE_INNER_CONTENT/>
        <!-- empty TB buttons-->
        <REPEAT count="$empty_buttons_count$+($show_manual$==0)">
          <CELL width="23"/>
        </REPEAT>
      </IMAGE_GROUP_BOX>

      <!-- Presets area -->
      <IMAGE_GROUP_BOX image="$THEME_PATH$/toolbar/lcd.png" stretch="true" margin="3" font_size="12" font_face="Arial" layout_type="column" ignore_mask_files="true"
                       id="theme.toolbar.lcd" drop_target_ids="current_preset.absolute_path" drop_applicative_types="system::filepath">
        <ACTION_TRIGGER event_id="theme.toolbar.lcd.dropping.value_changed" condition_formula="(theme.toolbar.lcd.dropping==0)&amp;&amp;(theme.toolbar.lcd.drop_operation!=0)"
                       action_id="RevertCurrentPreset"/>
        <ROW spacing="1" h_margin="4">
          <LAYER_STACK>
            <CELL h_margin="1">
              <IMAGE image="$THEME_PATH$/toolbar/arrow_left.svg" ignore_mask_files="true" />
            </CELL>
            <INVISIBLE_ACTION_BUTTON action="PreviousPreset"  width="180%" height="180%" cursor="system::hand" h_align="right">
              <TOOLTIP text="Previous Preset"/>
            </INVISIBLE_ACTION_BUTTON>
			<CELL h_align="right" v_align="bottom" v_offset="7" h_offset="1">
				<THEME_DSP_PARAM_SMALL_ROUND_SETTINGS_BUTTON param_id="PreviousPreset" button_index="toolbar"/>
			</CELL>
          </LAYER_STACK>
          <TEXT string_id="theme.toolbar.preset_display_name" width="$preset_box_width$" text_color="#d3d3d3" font_weight="bold" text_h_align="center">
            <INVISIBLE_ACTION_BUTTON action="OpenPresetsMenu" width="100%" height="100%" cursor="system::hand" id="presets_button"  handled_keys="ArrowLeft;ArrowRight;ArrowDown;ArrowUp">
			  <ACTION_TRIGGER event_id="presets_button.key_pressed" condition_formula="presets_button.key_pressed.key!=0" script="
			  if(presets_button.key_pressed.key.text_value==&quot;ArrowLeft&quot; || presets_button.key_pressed.key.text_value==&quot;ArrowUp&quot;) PreviousPreset(); 
			  else if(presets_button.key_pressed.key.text_value==&quot;ArrowRight&quot; || presets_button.key_pressed.key.text_value==&quot;ArrowDown&quot;) NextPreset();" 
			  requires="presets_button.key_pressed.key.text_value;PreviousPreset;NextPreset"/>
              <TOOLTIP string_id="current_preset.path"/>
            </INVISIBLE_ACTION_BUTTON>
          </TEXT>
          <LAYER_STACK>
            <CELL h_margin="1">
              <IMAGE image="$THEME_PATH$/toolbar/arrow_right.svg" ignore_mask_files="true"/>
            </CELL>
            <INVISIBLE_ACTION_BUTTON action="NextPreset" width="180%" height="180%" cursor="system::hand"  h_align="left">
              <TOOLTIP text="Next Preset"/>
            </INVISIBLE_ACTION_BUTTON>
			<CELL h_align="left" v_align="bottom" v_offset="7" h_offset="-1">
			<THEME_DSP_PARAM_SMALL_ROUND_SETTINGS_BUTTON param_id="NextPreset" button_index="toolbar"/>
			</CELL>
          </LAYER_STACK>
        </ROW>
        <ROW width="100%">
        <REPEAT count="$PLUGIN_HAS_AUDIO_IO_CONFIG$!=0">
          <TEXT value="I/O" text_color="#44b5ff" font_size="11" font_weight="bold">
            <INVISIBLE_PARAM_MENU_BUTTON param_id="dsp.audio_io_configuration" width="100%" height="100%" cursor="system::hand" id="">
                <PARAM_TOOLTIP param_id="dsp.audio_io_configuration" to="toolbar.main_lcd_text" content="Audio I/O: {text_value}" enabled="false" id="toolbar.audio_io_text_display_link"/>
            </INVISIBLE_PARAM_MENU_BUTTON>
          </TEXT>
          </REPEAT>
          <TEXT flex="1" text_color="#585959" font_size="-1" string_id="toolbar.main_lcd_text" text_h_align="center" width="0">
            <INVISIBLE_PARAM_TOGGLE_SWITCH param_id="toolbar.empty_text_link.enabled" width="100%" height="100%"/>
          </TEXT>
          <STRING id="toolbar.main_lcd_text"/>
          <STRING id="toolbar.empty_text"/>
          <STRING_LINK from="toolbar.empty_text" to="toolbar.main_lcd_text" enabled="false" id="toolbar.empty_text_link"/>
          <!-- opacity -->
          <PARAM id="theme.opacity" min="0" max="100" default="100" unit="%" persistent="true" locked="false" name="Opacity" value_format=".0"/>
          <PARAM_LINK from="theme.opacity" to="$opacity_param_id$" normalized="true"/>
          <THEME_OPACITY_KNOB param_id="theme.opacity" positions_count="101" id="toolbar.opacity_knob"/>
          <PARAM_TO_STRING_LINK from="theme.opacity" to="toolbar.main_lcd_text" content="Window Opacity:{text_value}{unit}" enabled="false" id="toolbar.opacity_text_display_link"/>
          <PARAM_LINK from="toolbar.opacity_knob.focus" to="toolbar.opacity_text_display_link.enabled"/>
        </ROW>
      </IMAGE_GROUP_BOX>
      <ROW flex="10" spacing="2">
        <CELL flex="10" id="toolbar.title_image_container" width="0">
          <LAYER_STACK>
            <IMAGE image="$title_image$" opacity="100%" ignore_mask_files="true" id="toolbar.title_image"/>
            <IMAGE image="$title_image_small$" ignore_mask_files="true" id="toolbar.title_image_small"/>
          </LAYER_STACK>
          <FORMULA_PARAM id="toolbar.title_image_display" formula="toolbar.title_image_container.width&gt;=toolbar.title_image.width"/>
          <FORMULA_PARAM id="toolbar.title_image_small_display" formula="(toolbar.title_image_display==false)&amp;&amp;(toolbar.title_image_container.width&gt;=toolbar.title_image_small.width)"/>
          <PARAM_LINK from="toolbar.title_image_display" to="toolbar.title_image.visible"/>
          <PARAM_LINK from="toolbar.title_image_small_display" to="toolbar.title_image_small.visible"/>
        </CELL>
        <REPEAT count="$show_logo$!=0">
          <IMAGE image="$THEME_PATH$/toolbar/logo.svg" ignore_mask_files="true" id="toolbar.logo">
            <INVISIBLE_ACTION_BUTTON action_id="OpenBCAWebsite" cursor="system::hand" width="100%" height="100%"/>
            <ACTION id="OpenBCAWebsite" type="OpenUrl" url="http://www.bluecataudio.com"/>
          </IMAGE>
          </REPEAT>
        <CELL flex=".1"/>
      </ROW>
    </IMAGE_GROUP_BOX>
    <!-- Preset Name: build from the actual name and additional "*" if modified -->
    <STRING id="theme.toolbar.preset_display_name"/>
    <STRING id="theme.toolbar.preset_modified_string"/>
    <PARAM id="theme.toolbar.preset_status" type="enumeration" enum_values=";*"/>
    <PARAM_LINK from="current_preset.modified" to="theme.toolbar.preset_status"/>
    <PARAM_TO_STRING_LINK from="theme.toolbar.preset_status" to="theme.toolbar.preset_modified_string"/>
    <STRING_MULTI_LINK from="current_preset.name;theme.toolbar.preset_modified_string" to="theme.toolbar.preset_display_name" separator=" "/>

    <UNDEFINE>
      <_LOCAL_BUTTONS_ITEMS_/>
      <_LOCAL_MENU_ITEMS_/>
    </UNDEFINE>
  </TEMPLATE>
</DUMMY>