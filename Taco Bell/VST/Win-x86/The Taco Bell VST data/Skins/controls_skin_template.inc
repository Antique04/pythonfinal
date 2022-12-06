<?xml version="1.0" encoding="utf-8" ?>
<SKIN layout_type="column" text_color="#text_color#" font_size="#text_size#">
  <!-- prepro and definitions / size computation-->
  <DEFINE>
    <CUS_KNOB_CONTROL_WIDGET base_type="#knob_style#"/>
    <CUS_GROUPING_BOX_WIDGET base_type="#grouping_style#"/>
    <CUS_OUTPUT_METER_WIDGET base_type="#meter_style#"/>
    <CUS_SWITCH_CONTROL_WIDGET base_type="#switch_style#"/>
  </DEFINE>

  <!-- No Parameters box, if no script parameters available-->
  <FORMULA_PARAM id="no_controls_available" formula="($script_input_params_count$+$script_output_params_count$+$script_input_strings_count$)==0"/>
  <PARAM_LINK from="no_controls_available" to="no_controls_box.display"/>
  <CELL spacing="0" layout_type="column" id="no_controls_box" display="false" height="90">
    <TEXT value="This script has no controls."/>
  </CELL>

  <!-- Script Strings (Input Strings) -->
  <PARAM_LINK from="$script_input_strings_count$" to="in_strings_box.display" formula="x>0"/>
  <CELL layout_type="column" id="in_strings_box" display="false" spacing="$spacing$" width="100%" h_margin="10" min_width="$minimum_width$">
    <REPEAT count="$SCRIPT_STRINGS_COUNT$">
      <PARAM_LINK from="$script_input_strings_count$" to="in_string_cell$index$.display" formula="(x>$index$)"/>
      <ROW id="in_string_cell$index$" spacing="$spacing$" display="false" width="100%" fit_text="abbreviate">
        <TEXT string_id="$script_input_string$index$_name$" flex="1" height="100%" auto_size="false" text_h_align="left"/>
        <TEXT value=":" height="17"/>
        <TEXT_EDIT_BOX string_id="$script_input_string$index$$" background_color="#182f41" show_edges="false" flex="2" height="100%"/>
      </ROW>
    </REPEAT>
    <REPEAT count="$SCRIPT_STRINGS_COUNT$!=0">
      <CELL height="5"/>
    </REPEAT>
  </CELL>

  <!-- Layout type -->
  <VARIABLE id="layout_type_text" value="#layout_type_text#"/>
  <VARIABLE id="other_layout_type_text" value="#other_layout_type_text#"/>
  <VARIABLE id="layout_type_int" value="#layout_type_int#"/>

  <LAYER_STACK>
    <!-- Grouping -->
    <CELL width="100%" height="100%" spacing="4" margin="10" id="groups_cell" layout_type="$other_layout_type_text$">
      <REPEAT count="#y_groups_count#">
        <CELL flex="#y_group_size#" #x_length#="0" #y_length#="100%" spacing="4" layout_type="$layout_type_text$">
          <REPEAT count="#x_groups_count#" index_name="sub_index">
            <CUS_GROUPING_BOX_WIDGET flex="#x_group_size#" #y_length#="0" #x_length#="100%"/>
          </REPEAT>
          <!-- last x group -->
          <REPEAT count="#x_last_group_size#>0" index_name="sub_index">
            <CUS_GROUPING_BOX_WIDGET flex="#x_last_group_size#" #y_length#="0" #x_length#="100%"/>
          </REPEAT>
        </CELL>
      </REPEAT>
      <!-- last y group -->
      <REPEAT count="#y_last_group_size#>0">
        <CELL flex="#y_last_group_size#" #x_length#="0" #y_length#="100%"  spacing="4" layout_type="$layout_type_text$">
          <REPEAT count="#x_groups_count#" index_name="sub_index">
            <CUS_GROUPING_BOX_WIDGET flex="#x_group_size#" #y_length#="0" #x_length#="100%"/>
          </REPEAT>
          <!-- last x group -->
          <REPEAT count="#x_last_group_size#>0" index_name="sub_index">
            <CUS_GROUPING_BOX_WIDGET flex="#x_last_group_size#" #y_length#="0" #x_length#="100%"/>
          </REPEAT>
        </CELL>
      </REPEAT>
    </CELL>

    <!-- Script Controls (Input Parameters) -->
    <VARIABLE id="controls_spacing" value="15"/>
    <VARIABLE id="actual_static_in_params_count" formula="min(#in_params_count#,$SCRIPT_PARAMS_COUNT$)"/>
    <VARIABLE id="controls_width" formula="$controls_spacing$+$layout_type_int$*#x_controls_display_count#*(90+$controls_spacing$)+(1-$layout_type_int$)*#y_controls_display_count#*(90+$controls_spacing$)"/>
    <REPEAT count="$actual_static_in_params_count$>0">
      <FORMULA_PARAM id="controls_height" formula="$controls_spacing$+$layout_type_int$*#y_controls_display_count#*(input_col0.height+$controls_spacing$)+(1-$layout_type_int$)*#x_controls_display_count#*(input_col0.height+$controls_spacing$)"/>
      <PARAM_LINK from="controls_height" to="controls_cell.height"/>
    </REPEAT>
    <REPEAT count="($actual_static_in_params_count$==0)&amp;&amp;(#out_params_count#>0)">
      <FORMULA_PARAM id="controls_height" formula="$controls_spacing$+$layout_type_int$*#y_controls_display_count#*(output_col0.height+$controls_spacing$)+(1-$layout_type_int$)*#x_controls_display_count#*(output_col0.height+$controls_spacing$)"/>
      <PARAM_LINK from="controls_height" to="controls_cell.height"/>
    </REPEAT>
    
    <!-- using custom parameters info to configure our controls -->
    <REPEAT count="$actual_static_in_params_count$">
      <PARAM_LINK from="$script_input_param$index$_steps$" to="input_control$index$.positions_count"/>
      <PARAM_LINK from="$script_input_param$index$_steps$" to="input_control_menu$index$.positions_count"/>
      <PARAM_LINK from="$script_input_param$index$_steps$" to="input_control$index$.visible" formula="x!=2"/>
      <PARAM_LINK from="$script_input_param$index$_steps$" to="input_control_switch$index$.visible" formula="x==2"/>
      <PARAM_LINK from="$script_input_param$index$_steps$" to="input_control_menu$index$.visible" formula="(x>=2)and(x&lt;=50)"/>
    </REPEAT>
    <VARIABLE id="display_input_params" value="false"/>
    <REPEAT count="$actual_static_in_params_count$>0">
      <VARIABLE id="display_input_params" value="true" override="true"/>
    </REPEAT>
    <CELL reflow="true" spacing="$controls_spacing$" h_margin="$controls_spacing$" v_margin="$controls_spacing$" internal_v_align="top" internal_h_align="left" id="controls_cell" layout_type="$layout_type_text$" width="$controls_width$">
      <!-- Input Params -->
      <REPEAT count="$actual_static_in_params_count$" index_name="param_index">
        <COLUMN v_align="top" spacing="0" id="input_col$param_index$" display="$display_input_params$" width="90">
          <PARAM_TEXT param_id="custom_param$param_index$" content="{name}"  width="100%" cursor="system::hand" font_weight="bold" fit_text="abbreviate"/>
          <LAYER_STACK id="input_control$param_index$_cell">
            <CUS_SWITCH_CONTROL_WIDGET param_id="custom_param$param_index$" id="input_control_switch$param_index$" visible="false"/>
            <CUS_KNOB_CONTROL_WIDGET param_id="custom_param$param_index$" id="input_control$param_index$" positions_count="101"/>
            <PNS_DSP_PARAM_SETTINGS_BUTTON param_id="$script_input$param_index$$" v_align="bottom" v_offset="4"/>
          </LAYER_STACK>
          <PARAM_TEXT param_id="custom_param$param_index$" width="100%">
            <INVISIBLE_PARAM_MENU_BUTTON width="100%" height="100%"  param_id="custom_param$param_index$" visible="false" id="input_control_menu$param_index$" cursor="system::hand"/>
          </PARAM_TEXT>
        </COLUMN>
      </REPEAT>
      <!-- Output Params -->
      <REPEAT count="#out_params_count#" index_name="param_index">
        <COLUMN v_align="top" spacing="0" id="output_col$param_index$" width="90">
          <PARAM_TEXT param_id="custom_out_param$param_index$" content="{name}"  width="100%" cursor="system::hand" font_weight="bold" fit_text="abbreviate"/>
          <REPEAT count="$actual_static_in_params_count$>0">
            <PARAM_LINK from="input_control0_cell.height" to="output_control$param_index$_cell.height"/>
          </REPEAT>
          <LAYER_STACK id="output_control$param_index$_cell">
            <CUS_OUTPUT_METER_WIDGET param_id="custom_out_param$param_index$" id="out_control$param_index$"/>
            <PNS_DSP_PARAM_SETTINGS_BUTTON param_id="$script_output$param_index$$" v_align="bottom"/>
          </LAYER_STACK>
          <PARAM_TEXT param_id="custom_out_param$param_index$" width="100%"/>
        </COLUMN>
      </REPEAT>
    </CELL>
  </LAYER_STACK>
  <!-- Script Strings (Output Strings) -->
  <PARAM_LINK from="$script_output_strings_count$" to="out_strings_box.display" formula="x>0"/>
  <CELL layout_type="column" id="out_strings_box" display="false" spacing="$spacing$" width="100%" h_margin="10" min_width="$minimum_width$">
    <REPEAT count="$SCRIPT_OUT_STRINGS_COUNT$">
      <PARAM_LINK from="$script_output_strings_count$" to="out_string_cell$index$.display" formula="(x>$index$)"/>
      <ROW id="out_string_cell$index$" spacing="$spacing$" display="false" width="100%" fit_text="abbreviate">
        <TEXT string_id="$script_output_string$index$_name$" flex="1" height="100%" auto_size="false" text_h_align="left"/>
        <TEXT value=":" height="17"/>
        <TEXT string_id="$script_output_string$index$$" flex="3" height="100%" auto_size="false" text_h_align="left"/>
      </ROW>
    </REPEAT>
  </CELL>
</SKIN>