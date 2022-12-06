<?xml version="1.0" encoding="utf-8" ?>
<DUMMY>
  <TEMPLATE id="TPL_PARAM_DROPDOWN" width="55" visible="true">
    <CUS_DROP_DOWN_GROUP layout_type="layer_stack" h_margin="3" visible="$visible$">
      <IMAGE image="$THEME_PATH$/buttons/dropdown_arrow.svg" h_align="right" v_offset="1" h_offset="2"/>
      <PARAM_TEXT width="$width$" param_id="$param_id$"/>
      <INVISIBLE_PARAM_MENU_BUTTON width="100%" height="100%" param_id="$param_id$" cursor="system::hand"/>
    </CUS_DROP_DOWN_GROUP>
  </TEMPLATE>
   <TEMPLATE id="TPL_ACTION_DROPDOWN" width="55" >
     <CUS_DROP_DOWN_GROUP layout_type="layer_stack" h_margin="3">
       <IMAGE image="$THEME_PATH$/buttons/dropdown_arrow.svg" h_align="right" v_offset="1" h_offset="2"/>
       <TEXT string_id="$action_id$.name" width="$width$"/>
       <INVISIBLE_ACTION_BUTTON width="100%" height="100%" action_id="$action_id$" cursor="system::hand"/>
     </CUS_DROP_DOWN_GROUP>
  </TEMPLATE>
  <DEFINE>
    <!-- standard icon buttons -->
    <CUS_ON_OFF_BUTTON base_type="IMAGE_PARAM_BUTTON" image="$THEME_PATH$/buttons/on_off_button.png" image_focus="$THEME_PATH$/buttons/on_off_button_hover.png" cursor="system::hand"/>
    <CUS_CHECK_BOX base_type="IMAGE_PARAM_BUTTON" image="$THEME_PATH$/buttons/check_box.svg" image_mouse_mask="" image_orientation="vertical" cursor="system::hand"/>
    
    <!-- Buttons that may be used to include text -->
    <CUS_DROP_DOWN_GROUP base_type="IMAGE_GROUP_BOX" image="$THEME_PATH$/buttons/drop_down_lcd.png" stretch="true" ignore_mask_files="true"/>
    <CUS_DROPDOWN_PARAM_BUTTON base_type="TPL_PARAM_DROPDOWN"/>
    <CUS_DROPDOWN_ACTION_BUTTON base_type="TPL_ACTION_DROPDOWN"/>
  </DEFINE>
</DUMMY>