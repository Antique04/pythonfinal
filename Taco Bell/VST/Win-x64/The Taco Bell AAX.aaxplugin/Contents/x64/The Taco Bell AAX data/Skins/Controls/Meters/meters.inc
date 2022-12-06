<?xml version="1.0" encoding="utf-8" ?>
<DUMMY>
  <LOCAL_VARIABLE id="CURRENT_DIR" value="$_DIR_$"/>
  <TEMPLATE id="TPL_PNS_ANALOG_VU" reverse="false" needle_v_offset="-6">
    <LAYER_STACK>
      <IMAGE image="$image$" id="vu60" ignore_mask_files="true" />
      <IMAGE_PARAM_METER image="$needle_image$" param_id="$param_id$" images_count="$images_count$" v_offset="$needle_v_offset$" offset="1" ignore_mask_files="true" reverse="$reverse$"/>
    </LAYER_STACK>
  </TEMPLATE>
  <DEFINE>
    <PNS_SMALL_RED_LED base_type="IMAGE_PARAM_METER" image="$CURRENT_DIR$/small_red_led.png" images_count="21" positions_count="21" image_orientation="vertical" ignore_mask_files="true" image_scaling=".6"/>
    <PNS_RED_LED base_type="IMAGE_PARAM_METER" image="$CURRENT_DIR$/red_led.png" images_count="21" positions_count="21" image_orientation="vertical" ignore_mask_files="true"/>
    <PNS_BLUE_LED base_type="IMAGE_PARAM_METER" image="$CURRENT_DIR$/blue_led.png" images_count="21" positions_count="21" image_orientation="vertical" ignore_mask_files="true"/>
    <PNS_GREEN_LED base_type="IMAGE_PARAM_METER" image="$CURRENT_DIR$/green_led.png" images_count="21" positions_count="21" image_orientation="vertical" ignore_mask_files="true"/>
    <PNS_ORANGE_LED base_type="IMAGE_PARAM_METER" image="$CURRENT_DIR$/orange_led.png" images_count="21" positions_count="21" image_orientation="vertical" ignore_mask_files="true"/>
    <PNS_ANALOG_VU base_type="TPL_PNS_ANALOG_VU" image="$CURRENT_DIR$/analog_vu.png" needle_image="$CURRENT_DIR$/analog_vu_needle.png" images_count="151" needle_v_offset="-3"/>
    <PNS_ANALOG_VU_SQUARE base_type="TPL_PNS_ANALOG_VU" image="$CURRENT_DIR$/analog_vu_square.png" needle_image="$CURRENT_DIR$/analog_vu_needle.png" images_count="151" needle_v_offset="-3"/>
    <PNS_ANALOG_VU_30 base_type="TPL_PNS_ANALOG_VU" image="$CURRENT_DIR$/analogvu30.png" needle_image="$CURRENT_DIR$/analogvu_needle_large.png" images_count="151"/>
    <PNS_ANALOG_VU_60 base_type="TPL_PNS_ANALOG_VU" image="$CURRENT_DIR$/analogvu60.png" needle_image="$CURRENT_DIR$/analogvu_needle_large.png" images_count="151"/>
  </DEFINE>
</DUMMY>