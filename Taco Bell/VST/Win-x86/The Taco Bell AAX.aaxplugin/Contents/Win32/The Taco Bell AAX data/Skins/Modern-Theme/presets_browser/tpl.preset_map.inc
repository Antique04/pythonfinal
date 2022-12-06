<?xml version="1.0" encoding="utf-8" ?>
<DUMMY>
  <INCLUDE_ONCE file="$_DIR_$../../tpl.subpreset_selector.inc"/>
  
  <!-- Helper: template preset icon definition -->
  <TEMPLATE id="TPL_PRESET_MAP_ICON" icon="" icon_scaling=".3" index="0" x="0" y="0" identifier="" text="" text_v_align="center" text_v_offset="0" 
            text_h_align="center" text_h_offset="0" icon_margin="30" ignore_locked_params="false">
    <LAYER_STACK h_position="0" v_position="0" id="$identifier$.predefined_value">
      <REQUIRED_OBJECTS object_ids="$identifier$.predefined_value.width;$identifier$.predefined_value.height"/>
      <FORMULA_PARAM id="$identifier$.predefined_value.x" formula="$icon_margin$+($area$.width-2*$icon_margin$)*$x$-$identifier$.predefined_value.width*.5"/>
      <PARAM_LINK from="$identifier$.predefined_value.x" to="$identifier$.predefined_value.h_offset"/>
      <FORMULA_PARAM id="$identifier$.predefined_value.y" formula="$icon_margin$+($area$.height-2*$icon_margin$)*(1-$y$)-$identifier$.predefined_value.height*.5"/>
      <PARAM_LINK from="$identifier$.predefined_value.y" to="$identifier$.predefined_value.v_offset"/>
      <IMAGE_ACTION_BUTTON image="$icon$" action_id="$identifier$.Open" opaque_mouse_mask="true" image_focus="$icon$" image_hover="$icon$" image_pushed="$icon$" image_scaling="$icon_scaling$" ignore_mask_files="true" cursor="system::hand">
        <ACTION id="$identifier$.Open" type="Script" script="$dest_file_path_string$=$file_string_id$;$map_id$.x=100*$x$;$map_id$.y=100*$y$;$map_id$.closest_item=$index$;$dest_load_action$();" requires="$map_id$.closest_item;$dest_file_path_string$;$file_string_id$;$dest_load_action$"/>
      </IMAGE_ACTION_BUTTON>
      <CELL width="100%" height="100%">
        <TEXT string_id="$string_id$" v_align="$text_v_align$" v_offset="$text_v_offset$" h_align="$text_h_align$" h_offset="$text_h_offset$" opacity=".7" buffered="true"/>
      </CELL>
    </LAYER_STACK>
  </TEMPLATE>

  <!-- Template 2D Presets Map definition -->
  <ACTION id="TPL_PRESET_MAP_DoNothing" type="Script" script=""/>
  <TEMPLATE id="TPL_PRESET_MAP" param_ids="#UNDEFINED#" param_paths="#UNDEFINED#" root_path="#UNDEFINED#" 
            default_wild_card=""  map_type="" map_file_ext="map" map_folder="" persist_extra_data="false" extra_data_id="" icon_scaling="1" text_v_offset="14"
            pre_analysis_action_id="TPL_PRESET_MAP_DoNothing" item_added_action_id="TPL_PRESET_MAP_DoNothing" post_setparams_action_id="TPL_PRESET_MAP_DoNothing" 
            dest_file_path_string="#UNDEFINED#" dest_load_action="TPL_PRESET_MAP_DoNothing"
            graphics_dir="$_DIR_$"
            >
    
    <!-- ANALYSIS DATA MODEL -->
    <!-- Analyzer input data-->
    <COLLECTION id="$id$.input_files" persistent="true" persistence_context="-Preset">
      <STRING id="$item_id$.path" default="" persistent="true" persistence_context="-Preset"/>
    </COLLECTION>
    
    <!-- Analyzer Output data-->
    <PROPERTY id="$id$.data" persistent="true" persistence_context="-Preset" exposed="true"/>
    <PARAM id="$id$.accuracy" min="0" max="100" unit="%" default="0" persistent="true" persistence_context="-Preset" exposed="true"/>
    <STRING id="$id$.analyzer_current_file_path" exposed="true"/>
    <COLLECTION id="$id$.items" exposed="true" persistent="true" persistence_context="-Preset">
      <STRING id="$item_id$.name" default="No Name" exposed="true" persistent="true" persistence_context="-Preset"/>
      <PARAM id="$item_id$.x" min="0" max="1" persistent="true" persistence_context="-Preset" exposed="true"/>
      <PARAM id="$item_id$.y" min="0" max="1" persistent="true" persistence_context="-Preset" exposed="true"/>
    </COLLECTION>

    <!-- Analyzer Actions -->
    <ACTION id="$id$.analyze" type="PCAnalyze" param_ids="$param_ids$" param_paths="$param_paths$" property_id="$id$.data"
          io_files_collection_id="$id$.input_files"
    results_collection_id="$id$.items" root_path="$root_path$"
    accuracy_param_id="$id$.accuracy" current_file_path_string_id="$id$.analyzer_current_file_path" exposed="true"/>
    <ACTION_TRIGGER event_ids="$id$.analyzer_current_file_path.value_changed" condition_formula="$id$.analyze.running" action_id="$item_added_action_id$"/>
    <ACTION_TRIGGER event_id="$id$.analyze.running.value_changed" condition_formula="$id$.analyze.running" action_id="$pre_analysis_action_id$"/>

    <!-- Navigation params-->
    <PARAM id="$id$.x" min="0" max="100" unit="%" default="50" persistent="true" persistence_context="-Preset" exposed="true"/>
    <PARAM id="$id$.y" min="0" max="100" unit="%" default="50" persistent="true" persistence_context="-Preset" exposed="true"/>

    <!-- SYNTHESIS DATA MODEL -->
    <FORMULA_PARAM id="$id$.xy_user_capture" formula="$id$.x.capturing||$id$.y.capturing" type="boolean"/>
    
    <!-- Synthesis Output Data-->
    <PARAM id="$id$.closest_item" exposed="true" min="-1" max="99999999"/>

    <!-- Synthesis Actions -->
    <ACTION id="$id$.set_params" type="PCSynthesize" param_ids="$param_ids$" property_id="$id$.data"
            x_param_id="$id$.x" y_param_id="$id$.y" closest_item_param_id="$id$.closest_item" exposed="true" ignore_locked_params="$ignore_locked_params$"/>
    <ACTION_TRIGGER event_ids="$id$.x.value_changed;$id$.y.value_changed" condition_formula="$id$.xy_user_capture!=0" action_id="$id$.set_params"/>

    <ACTION id="$id$.locate_current" type="PCProject" param_ids="$param_ids$" property_id="$id$.data"  x_param_id="$id$.x" y_param_id="$id$.y"/>
    
    <!-- Post Synthesis action-->
    <ACTION_TRIGGER event_ids="$id$.xy_user_capture.value_changed"
                    condition_formula="$id$.xy_user_capture==0" action_id="$post_setparams_action_id$"/>

    <!-- OTHER -->
    <!-- Reset Action-->
    <ACTION id="$id$.reset" type="Script" script="$id$.input_files.count=0;$id$.analyze();$id$.map_preset.reset_name();" requires="$id$.input_files.count;$id$.analyze;$id$.map_preset.reset_name"/>
    
    <!-- persistent data -->
    <GROUP id="$id$.map_data"
           object_ids="$id$.input_files.count;$id$.input_files[*].path;$id$.accuracy;$id$.items.count;$id$.items[*].name;$id$.items[*].x;$id$.items[*].y"
           object_aliases="paths_count;path*;accuracy;items_count;name*;x*;y*"/>
    
    <REPEAT count="$persist_extra_data$==false">
      <GROUP id="$id$.persistent_data"
             object_ids="$id$.map_data;$id$.data"
             object_aliases="map_data;analysis_data"/>
    </REPEAT>
    <REPEAT count="$persist_extra_data$==true">
      <GROUP id="$id$.persistent_data"
          object_ids="$id$.map_data;$id$.data;$extra_data_id$"
          object_aliases="map_data;analysis_data;extra_data"/>
    </REPEAT>
    <!-- LAYOUT -->
    <WIDGET id="$id$" width="100%" height="100%" background_color="#252729" margin="10">
      <!-- Toolbar -->
      <TPL_SUBPRESET_SELECTOR id="$id$.map_preset" applicative_type="$map_type$Map" file_types="*.$map_file_ext$" 
                              user_path="$PLUGIN_USER_DOCUMENTS_PATH$/Settings/Maps/$map_folder$" 
      factory_path="$PLUGIN_DATA_PATH$/Resources/Settings/Maps/$map_folder$" object_id="$id$.persistent_data"
      save_context="" locked="never" default_preset_name="Custom Map"/>
      <WIDGET width="100%" background_color="#151619" layout_type="row" h_margin="2" v_margin="3">
        <ROW spacing="0" text_color="#44b5ff" h_align="left" >
          <ROW>
            <IMAGE_PARAM_BUTTON  image="$graphics_dir$/arrow_left.svg" opaque_mouse_mask="true" param_id="$id$.map_preset.selector.selected_file_index" reverse="true" cursor="system::hand" images_count="1"/>
            <IMAGE_ACTION_BUTTON action_id="$id$.map_preset.menu.Popup" image="$THEME_PATH$/toolbar/menu.png" image_scaling=".5" opaque_mouse_mask="true" cursor="system::hand">
              <TOOLTIP text="Manage maps"/>
            </IMAGE_ACTION_BUTTON>
          <IMAGE_PARAM_BUTTON  image="$graphics_dir$/arrow_right.svg" opaque_mouse_mask="true" param_id="$id$.map_preset.selector.selected_file_index" cursor="system::hand" images_count="1"/>
          </ROW>
          <CELL width="2"/>
          <IMAGE_ACTION_BUTTON action_id="$id$.analyze" image="$graphics_dir$/reload.png" image_scaling=".5" opaque_mouse_mask="true" cursor="system::hand">
            <TOOLTIP text="Reload Presets"/>
          </IMAGE_ACTION_BUTTON>
          <IMAGE_ACTION_BUTTON  image="$THEME_PATH$/toolbar_buttons/trash.png" opaque_mouse_mask="true" image_scaling=".5" action_id="$id$.reset" cursor="system::hand">
            <TOOLTIP text="Clear Map (Remove all items)"/>
          </IMAGE_ACTION_BUTTON>
          <IMAGE_ACTION_BUTTON action_id="$id$.Center" image="$graphics_dir$/target.png" image_scaling=".5" opaque_mouse_mask="true" cursor="system::hand">
              <TOOLTIP text="Center map on cursor"/>
              <ACTION id="$id$.Center" type="Script" script="$id$.offset.x=1-$id$.x/100.0;$id$.offset.y=1-$id$.y/100.0;" requires="$id$.offset.x;$id$.x;$id$.offset.y;$id$.y"/>
          </IMAGE_ACTION_BUTTON>
          <IMAGE_ACTION_BUTTON action_id="$id$.locate_current" image="$graphics_dir$/find_on_map.png" image_scaling=".5" opaque_mouse_mask="true" cursor="system::hand">
            <TOOLTIP text="Find closest location for current tone on map"/>
          </IMAGE_ACTION_BUTTON>
        </ROW>
        <CELL flex="1"/>
        <ROW spacing="5" text_color="#556064">
          <TEXT string_id="$id$.map_preset.selected_name"/>
          <TEXT value="/"/>
          <PARAM_TEXT param_id="$id$.items.count" content="{text_value} items in map"/>
          <PARAM_TEXT content="(accuracy: {value}{unit})" value_format=".0" param_id="$id$.accuracy"/>
        </ROW>
      </WIDGET>
      <!-- Map 2D Browser-->
      <WIDGET id="$id$.outer_area" width="100%" flex="1" layout_type="layer_stack">
        <PARAM id="$id$.zoom" default="1" min="1" max="8" persistent="true" name="Zoom" unit="x"/>
        <PARAM id="$id$.offset.x" default=".5" min="0" max="1" persistent="true"/>
        <PARAM id="$id$.offset.y" default=".5" min="0" max="1" persistent="true"/>

        <FORMULA_PARAM id="$id$.area_width_diff" formula="$id$.outer_area.width*($id$.zoom-1)"/>
        <FORMULA_PARAM id="$id$.area_height_diff" formula="$id$.outer_area.height*($id$.zoom-1)"/>

        <FORMULA_PARAM id="$id$.area_width" formula="$id$.zoom*$id$.outer_area.width"/>
        <FORMULA_PARAM id="$id$.area_height" formula="$id$.zoom*$id$.outer_area.height"/>
        <PARAM_LINK from="$id$.area_width" to="$id$.area.width"/>
        <PARAM_LINK from="$id$.area_height" to="$id$.area.height"/>
        <FORMULA_PARAM id="$id$.area_h_offset" formula="($id$.outer_area.width-$id$.area.width)*(1-$id$.offset.x)"/>
        <FORMULA_PARAM id="$id$.area_v_offset" formula="($id$.outer_area.height-$id$.area.height)*$id$.offset.y"/>
        <PARAM_LINK from="$id$.area_h_offset" to="$id$.area.h_offset"/>
        <PARAM_LINK from="$id$.area_v_offset" to="$id$.area.v_offset"/>

        <WIDGET id="$id$.area" layout_type="layer_stack" h_position="0" v_position="0">
          <XYZ_PARAM_SCRATCH_PAD x_param_id="$id$.offset.x" y_param_id="$id$.offset.y" z_param_id="$id$.zoom" z_positions_count="10" width="100%" height="100%" cursor="system::open_hand" id="$id$.pad" />
          <PARAM_LINK from="$id$.area_width_diff" to="$id$.pad.x_pixel_range" formula="x*$PIXEL_SCALE_FACTOR$"/>
          <PARAM_LINK from="$id$.area_height_diff" to="$id$.pad.y_pixel_range" formula="x*$PIXEL_SCALE_FACTOR$"/>
          <!-- map_data map / dynamically generated-->
          <WIDGET width="100%" height="100%" buffered="true" background_color="#17191c" layout_type="layer_stack">
            <svg width="100%" height="100%" buffered="true">
              <ellipse cx="50%" cy="50%" rx="65%" ry="65%" fill="#1b1c1e"/>
              <ellipse cx="50%" cy="50%" rx="58%" ry="58%" fill="#1e1f21"/>
              <ellipse cx="50%" cy="50%" rx="50%" ry="50%" fill="#212224"/>
              <ellipse cx="50%" cy="50%" rx="42%" ry="42%" fill="#232527"/>
              <ellipse cx="50%" cy="50%" rx="34%" ry="34%" fill="#252729"/>
              <ellipse cx="50%" cy="50%" rx="26%" ry="26%" fill="#28292c"/>
              <ellipse cx="50%" cy="50%" rx="18%" ry="18%" fill="#2b2c2f"/>
              <ellipse cx="50%" cy="50%" rx="10%" ry="10%" fill="#2e2f32"/>
              <ellipse cx="50%" cy="50%" rx="3%" ry="3%" fill="#26282b"/>
              
            </svg>
            <FOREACH id="$id$.predefined_items" collection_id="$id$.items;$id$.input_files">
              <TPL_PRESET_MAP_ICON icon="$icon$" icon_scaling="$icon_scaling$" area="$id$.area" identifier="$item_id$" index="$item_index$" 
                                   string_id="$$id$.items_item_id$.name" x="$$id$.items_item_id$.x" y="$$id$.items_item_id$.y" 
                                   dest_file_path_string="$dest_file_path_string$" dest_load_action="$dest_load_action$" file_string_id="$$id$.input_files_item_id$.path"
                                   text_v_align="bottom" text_v_offset="$text_v_offset$"
                                   map_id="$id$"/>
            </FOREACH>
          </WIDGET>

          <!-- Joystick for selection-->
          <XYZ_IMAGE_PARAM_JOYSTICK width="100%" height="100%" margin="30" x_param_id="$id$.x" y_param_id="$id$.y" z_param_id="$id$.zoom" z_positions_count="10" 
                                    thumb_image="$graphics_dir$/cursor.svg" image_scaling=".5" cursor="system::size" opaque_mouse_mask="true"/>
        </WIDGET>
      </WIDGET>
    </WIDGET>
  </TEMPLATE>
</DUMMY>