<?xml version="1.0" encoding="utf-8" ?>
<TEMPLATE id="TPL_DSP_PARAM_SETTINGS_BUTTON" param_id="#UNDEFINED#" button_index="" image_name="arrow" h_offset="0" v_offset="0" h_align="center" v_align="center" image_scaling="1">
    <!-- Action button to change the control settings for a dsp parameter -->
    <!-- image name defines the name of the image in the settings_buttons folder -->
    <IMAGE_ACTION_BUTTON action_id="Show_$param_id$_ControlSetup" cursor="system::hand" 
                         image="$THEME_PATH$/settings_buttons/$image_name$.svg" image_hover="$THEME_PATH$/settings_buttons/$image_name$.svg" image_focus="$THEME_PATH$/settings_buttons/$image_name$.svg" image_pushed="$THEME_PATH$/settings_buttons/$image_name$.svg"
                         image_mouse_mask="" image_hover_mouse_mask="" image_focus_mouse_mask="" image_pushed_mouse_mask="" image_scaling="$image_scaling$"
                         id="$param_id$_settings_button$button_index$" h_align="$h_align$" v_align="$v_align$" h_offset="$h_offset$" v_offset="$v_offset$"  ignore_mask_file="true">
      <TEMPLATE_INNER_CONTENT/>
    </IMAGE_ACTION_BUTTON> 
    <PARAM_LINK from="theme.show_settings" to="$param_id$_settings_button$button_index$.visible"/>
</TEMPLATE>