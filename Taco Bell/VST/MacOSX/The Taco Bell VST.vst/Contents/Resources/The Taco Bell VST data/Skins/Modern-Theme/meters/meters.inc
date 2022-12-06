<?xml version="1.0" encoding="utf-8" ?>
<DEFINE>
  <!-- boxes for vu meters -->
  <CUS_METER_BOX base_type="IMAGE_GROUP_BOX" image="$_DIR_$/vu_bg.png" margin="4" spacing="1" ignore_mask_files="true"/>
  <CUS_METER_GREY_BOX base_type="IMAGE_GROUP_BOX" image="$_DIR_$/vu_grey_bg.png" margin="3" spacing="2" ignore_mask_files="true"/>

  <!-- Vertical meters -->
  <CUS_VMETER base_type="IMAGE_PARAM_LINEAR_METER" orientation="vertical" image="$_DIR_$/vmeter/vmeter.png" ignore_mask_files="true"/>
  <CUS_VMETER_SHORT base_type="IMAGE_PARAM_LINEAR_METER" orientation="vertical" image="$_DIR_$/vmeter/vmeter_short.png" ignore_mask_files="true"/>
  <CUS_VMETER_HOLD base_type="IMAGE_PARAM_LINEAR_METER" orientation="vertical" thumb_image="$_DIR_$/vmeter/hold_thumb.bmp" height="100%" ignore_mask_files="true"/>
  <CUS_VMETER_REVERSE base_type="IMAGE_PARAM_LINEAR_METER" orientation="vertical" image="$_DIR_$/vmeter/vmeter_mono_selected.png" image_selected="$_DIR_$/vmeter/vmeter_mono.png" ignore_mask_files="true"/>

  <!-- horizontal meters -->
  <CUS_HMETER_SHORT base_type="IMAGE_PARAM_LINEAR_METER" orientation="horizontal" image="$_DIR_$/hmeter/hmeter_short.png" ignore_mask_files="true"/>
  <CUS_HMETER_HOLD base_type="IMAGE_PARAM_LINEAR_METER" orientation="horizontal" thumb_image="$_DIR_$/hmeter/hhold_thumb.bmp" width="100%" ignore_mask_files="true"/>
</DEFINE>